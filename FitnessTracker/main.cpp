#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <stdexcept>

using namespace std;

class DatabaseManger
{
private:
    
public:
    DatabaseManger();
    ~DatabaseManger();
};

DatabaseManger::DatabaseManger(/* args */)
{
}

DatabaseManger::~DatabaseManger()
{
}


enum class Gender {
    male,
    female,
    nonbinary
};

class User
{
private:
    int UserID, age;
    float height, weight;
    string username, password;
    Gender gender;
public:
    User(int const UserID, int age, float height, float weight, string username, string password, Gender gender): UserID(UserID), 
    age(age), height(height), username(move(username)), password(move(password)), gender(gender){}
    ~User() = default;
    int getUserID()const{return UserID;}
    int getAge()const{return age;}
    float getHeight()const{return height;}
    float getWeight()const{return weight;}
    string getUserName()const{return username;}
    string getPassword()const{return password;}
    void setHeight();
    void setWeight();

};

class UserManager
{
public:
    UserManager() = default;
    ~UserManager() = default;
    static User logIn(string username, string password){

    }
    static User registerUser(string username, string password){

    }
};



int main(){

    return 0;
}
