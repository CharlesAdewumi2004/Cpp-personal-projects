#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <stdexcept>
#include <memory>
#include <filesystem>
#include <vector>

using namespace std;
const string insertSQL = "INSERT INTO users (username, password, age, height, weight, gender) VALUES (?, ?, ?, ?, ?, ?)";

class Workout
{
private:
    string workoutName;
    int sets, reps;

public:
    Workout() = default;
    ~Workout() = default;
};

class WorkoutSession
{
private:
    vector<unique_ptr<Workout>> vectortOfWorkouts;
    int workoutSessionid, progresstrackerid;

public:
    WorkoutSession(int workoutSessionid, int progresstrackerid) : workoutSessionid(workoutSessionid), progresstrackerid(progresstrackerid){}
    ~WorkoutSession() = default;
};

class FitnessProgress
{
private:
    int const userID, progressTrackerID;
    vector<unique_ptr<WorkoutSession>> vectorOfWorkoutSessions;

public:
    FitnessProgress(SQLite::Database &db, int userID, int progressTrackerID) : userID(userID), progressTrackerID(progressTrackerID) {}
    ~FitnessProgress() = default;
    int getUserID() const { return userID; }
    int getProgressTrackerID() const { return progressTrackerID; }
    void createWorkoutSession(SQLite::Database &db);
    const vector<unique_ptr<WorkoutSession>>& viewWorkoutSessions() const{return vectorOfWorkoutSessions;}
};

void FitnessProgress::createWorkoutSession(SQLite::Database &db)
{
    try
    {
        SQLite::Statement insert(db, "INSERT INTO workoutsession (progress_tracker_id) VALUES (?)");
        insert.bind(1, progressTrackerID);
        insert.exec();
        vectorOfWorkoutSessions.push_back(make_unique<WorkoutSession>(db.getLastInsertRowid(), progressTrackerID));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating workout seesion" << e.what() << endl;
    }
}

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
            db->exec(R"(
                    CREATE TABLE IF NOT EXISTS workoutsession (
                        workoutsessionid INTEGER PRIMARY KEY AUTOINCREMENT,
                        progress_tracker_id INTEGER,
                        FOREIGN KEY(progress_tracker_id) REFERENCES progresstracker(progresstrackerid)
                    );
                )");
            db->exec(R"(
        `           CREATE TABLE IF NOT EXISTS workout (
                        workoutid INTEGER PRIMARY KEY AUTOINCREMENT,
                        reps INTEGER,
                        sets INTEGER,
                        workout_session_id INTEGER,
                        FOREIGN KEY(workout_session_id) REFERENCES workoutsession(workoutsessionid)
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
        ensureFitnessProgress(db);
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
    void ensureFitnessProgress(SQLite::Database &db);
};

void User::ensureFitnessProgress(SQLite::Database &db)
{
    int progressTrackerID = -1;
    SQLite::Statement query(db, "SELECT progresstrackerid FROM progresstracker WHERE user_id = ?");
    query.bind(1, UserID);
    if (query.executeStep())
    {
        progressTrackerID = query.getColumn(0).getInt();
    }
    else
    {
        SQLite::Statement insert(db, "INSERT INTO progresstracker (user_id) VALUES (?)");
        insert.bind(1, UserID);
        insert.exec();
        progressTrackerID = static_cast<int>(db.getLastInsertRowid());
    }
    pCurrentFitnessTracker = std::make_unique<FitnessProgress>(db, UserID, progressTrackerID);
}

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
    try
    {
        DatabaseManager dbManager("/home/charlie/Cpp-personal-projects/FitnessTracker/forsen.db3");
        auto user = UserManager::registerUser(dbManager.getDB(), "charlie", "kappa123", 165.5, 195.3, 19, Gender::male);
        if (user)
        {
            cout << "Registration successful" << endl;
        }
        else
        {
            cout << "Registration failed" << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}
