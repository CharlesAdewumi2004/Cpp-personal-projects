#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <stdexcept>
#include <memory>
#include <filesystem>

using namespace std;
const string insertSQL = "INSERT INTO users (username, password, age, height, weight, gender) VALUES (?, ?, ?, ?, ?, ?)";

class FitnessProgress
{
private:
    int userID, progressTrackerID;

public:
    FitnessProgress(int userID, int progressTrackerID) : userID(userID), progressTrackerID(progressTrackerID) {}
    ~FitnessProgress() = default;
};

#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <exception>

using namespace std;

class DatabaseManager
{
private:
    std::unique_ptr<SQLite::Database> db;

    void createTable()
    {
        try
        {
            db->exec(R"(
                    CREATE TABLE IF NOT EXISTS users (
                        userid INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT NOT NULL UNIQUE,
                        password TEXT NOT NULL,
                        age INTEGER,
                        height REAL,
                        weight REAL,
                        gender INTEGER
                    );
                )");
            db->exec(R"(
                    CREATE TABLE IF NOT EXISTS progresstracker (
                        progresstrackerid INTEGER PRIMARY KEY AUTOINCREMENT,
                        user_id INTEGER,
                        FOREIGN KEY(user_id) REFERENCES users(userid)
                    );
                )");
        }
        catch (const std::exception &e)
        {
            cerr << "Failed to create table:\t" << e.what() << endl;
            throw;
        }
    }

public:
    DatabaseManager(const string &databasePath) : db(new SQLite::Database(databasePath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE))
    {
        createTable();
    }

    SQLite::Database &getDB() { return *db; }
};

enum class Gender
{
    male = 0,
    female = 1,
    other = 2
};

class User
{
private:
    int const UserID;
    int age;
    float height, weight;
    std::string username, password;
    Gender gender;
    std::unique_ptr<FitnessProgress> pCurrentFitnessTracker = nullptr;

public:
    User(SQLite::Database &db, int UserID, int age, float height, float weight, std::string username, std::string password, Gender gender)
        : UserID(UserID), age(age), height(height), weight(weight), username(std::move(username)), password(std::move(password)), gender(gender)
    {
        try
        {
            SQLite::Statement query(db, "SELECT user_id, progresstrackerid FROM users WHERE username = ? AND password = ?");
            query.bind(1, this->username);
            query.bind(2, this->password);
            if (query.executeStep() && query.getColumn(0).getInt() == getUserID())
            {
                pCurrentFitnessTracker = std::make_unique<FitnessProgress>(query.getColumn(0).getInt(), query.getColumn(1).getInt());
            }
            else
            {
                SQLite::Statement insert(db, insertSQL);
                insert.bind(1, getUserID());
                insert.exec();
                pCurrentFitnessTracker = std::make_unique<FitnessProgress>(getUserID(), query.getColumn(1).getInt());
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Failed to open database: \t" << e.what() << std::endl;
            throw; 
        }
    }
    ~User() = default;
    int getUserID() const { return UserID; }
    int getAge() const { return age; }
    float getHeight() const { return height; }
    float getWeight() const { return weight; }
    string getUserName() const { return username; }
    string getPassword() const { return password; }
    bool setHeight(float inputHeight);
    bool setWeight(float inputWeight);
};

bool User::setHeight(float inputHeight)
{
    try
    {
        if (height <= 0)
        {
            cout << "Invalid input" << endl;
            return false;
        }
        else
        {
            height = inputHeight;
            return true;
        }
    }
    catch (const exception &e)
    {
        cerr << "Failed to change height" << e.what() << endl;
        return false;
    }
}

bool User::setWeight(float inputWeight)
{
    try
    {
        if (inputWeight <= 0)
        {
            cout << "Invalid input" << endl;
            return false;
        }
        else
        {
            weight = inputWeight;
            return true;
        }
    }
    catch (const exception &e)
    {
        cerr << "Failed to change weight" << e.what() << endl;
        return false;
    }
}

class UserManager
{
public:
    UserManager() = default;
    ~UserManager() = default;
    static unique_ptr<User> logIn(SQLite::Database &db, string const &username, string const &password)
    {
        try
        {
            SQLite::Statement query(db, "SELECT userid, age, height, weight, gender FROM users WHERE username = ? AND password = ?");
            query.bind(1, username);
            query.bind(2, password);
            if (query.executeStep())
            {
                int userid = query.getColumn(0).getInt();
                int age = query.getColumn(1).getInt(); // Assuming these are available
                float height = query.getColumn(2).getDouble();
                float weight = query.getColumn(3).getDouble();
                Gender gender = static_cast<Gender>(query.getColumn(4).getInt()); // Convert to Gender enum
                cout << "Log in successfull" << endl;
                return make_unique<User>(db, userid, age, height, weight, username, password, gender);
            }
            else
            {
                cout << "Login failed" << endl;
                return nullptr;
            }
        }
        catch (const exception &e)
        {
            cerr << "User login failed: " << e.what() << endl;
            return nullptr;
        }
    }
    static unique_ptr<User> registerUser(SQLite::Database &db, string const &username, string const &password, float weight, float height, int age, Gender gender)
    {
        try
        {
            SQLite::Statement insert(db, insertSQL);
            insert.bind(1, username);
            insert.bind(2, password); // Consider hashing this password
            insert.bind(3, age);
            insert.bind(4, height);
            insert.bind(5, weight);
            insert.bind(6, static_cast<int>(gender));
            insert.exec();

            // Get the ID of the newly inserted user
            long long userid = db.getLastInsertRowid();
            return make_unique<User>(db, static_cast<int>(userid), age, height, weight, username, password, gender);
        }
        catch (const exception &e)
        {
            cerr << "Register user failed: " << e.what() << endl;
            return nullptr;
        }
    }
};

int main()
{
    DatabaseManager dbManager("/home/charlie/Cpp-personal-projects/FitnessTracker/forsen.db3");
    // Use dbManager.getDB() to get the reference of the SQLite::Database object]
    cout << "Database path: " << filesystem::absolute("forsen.db3") << endl;
    auto user = UserManager::registerUser(dbManager.getDB(), "charlie", "kappa", 165.5, 195.3, 19, Gender::male);

    return 0;
}
