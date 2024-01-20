#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

class Post
{
private:
    string user, title, text;
    int like;

public:
    Post(string inputTitle, string inputText, string inputUser);
    ~Post() = default;
    string getUser() const { return user; }
    string getText() const {return text; }
    int getLikes() const { return like; }
    void setLikes();
    string getTitle() const { return title; }

    friend ostream &operator<<(ostream &os, const Post &post);
    friend istream &operator>>(istream &is, Post &post);
};

void Post::setLikes()
{
    like++;
}

Post::Post(string inputTitle, string inputText, string inputUser) : title(move(inputTitle)), text(move(inputText)), user(move(inputUser)), like(0) {}

ostream &operator<<(ostream &os, const Post &post)
{
    os << post.user << "\n"
       << post.title << "\n"
       << post.text << "\n"
       << post.like << "\n";
    return os;
}

istream &operator>>(istream &is, Post &post) {
    getline(is, post.user);
    getline(is, post.title);
    getline(is, post.text);
    is >> post.like;
    is.ignore();
    return is;
}


class User
{
private:
    string username;
    string password;
    bool isLoggedin;

public:
    User(string inputUsername, string inputPassword);
    ~User() = default;

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    void setisLoggedIn();
    bool getIsloggedIn();

    friend ostream &operator<<(ostream &os, const User &user);
    friend istream &operator>>(istream &is, User &user);
};

void User::setisLoggedIn()
{
    isLoggedin = !isLoggedin;
}

bool User::getIsloggedIn()
{
    return isLoggedin;
}

ostream &operator<<(ostream &os, const User &user)
{
    os << user.username << " " << user.password << "\n";
    return os;
}

istream &operator>>(istream &is, User &user)
{
    is >> user.username >> user.password;
    return is;
}

User::User(string inputUsername, string inputPassword) : username(move(inputUsername)), password((move(inputPassword)))
{
    isLoggedin = false;
}

// Prototype functions
User logIn();
void createAccount();
void createPost(User currentUser);
void displayUserPostHistory(User currentUser);
void displayGlobalPostHistory();
void likePost();


int main() {
    label:
    User currentUser("", "");
    bool userloggedin = false;
    while (!userloggedin) {
        int operation;
        cout << "(1) Login\n(2) Create account\n(3) Exit\n";
        if (!(cin >> operation)) {
            cin.clear();  // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the rest of the line
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        cin.ignore();  // Clear the newline character after reading an integer

        switch (operation) {
        case 1:
            currentUser = logIn();
            if (!currentUser.getIsloggedIn()) {
                cout << "Failed to login" << endl;
            } else {
                cout << "Successful login" << endl;
                userloggedin = true;
            }
            break;
        case 2:
            createAccount();
            break;
        case 3:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }

    // Loop for post-login actions
    bool running = true;
    while (running) {
        int operation;
        cout << "(1) Create post\n(2) Display personal post history\n(3) Display global post history\n(4) Like post\n(5) Exit\n" << endl;
        cin >> operation;
        cin.ignore();
        switch (operation) {
        case 1:
            createPost(currentUser);
            break;
        case 2: 
            displayUserPostHistory(currentUser);
            break;
        case 5:
            cout << "Logged out" << endl;
            goto label;
            break;
        case 3:
            displayGlobalPostHistory();
            break;
        case 4:
            likePost();
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }

    return 0;
}

void likePost(){
    string titleOfPost;
    ifstream rfile("post.bin");
    Post p("","","");
    vector<Post> vectorOfPosts;
    
    if (!rfile.is_open())
    {
        cerr << "error when opening file" << endl;
        exit(1);
    }

    cout << "enter the title of the post you want to like" << endl;
    getline(cin, titleOfPost);

    while (rfile >> p)
    {
        vectorOfPosts.push_back(p);
    }
    rfile.close();
    ofstream wfile("post.bin");
    for(auto& ps : vectorOfPosts){
        if (ps.getTitle().compare(titleOfPost) == 0)
        {
            ps.setLikes();
            break;
        }
    }
    for(const auto& post : vectorOfPosts){
        wfile << post;
    }
    wfile.close();  
}

void displayGlobalPostHistory(){
    ifstream rfile("post.bin");
    Post p("","","");
    if (!rfile.is_open())
    {
        cerr << "error when opeining file" << endl;
        exit(1);
    }
    while (rfile >> p)
    {
        cout << "\n" << endl; 
        cout << "User:\t" << p.getUser() << endl;
        cout << "Title:\t" << p.getTitle() << endl;
        cout << "Text:\t" << p.getText() << endl;
        cout << "likes:\t" << p.getLikes() << endl;
        cout << "\n" << endl;
    }
    rfile.close();
}

void createPost(User currentUser) {
    string title, text;
    ifstream rfile("post.bin");
    Post p("", "", "");

    if (!rfile.is_open()) {
        cerr << "error when opening file" << endl;
        exit(1);
    }

    cout << "enter the title of your post" << endl;
    getline(cin, title);
    cout << "enter the text for your post" << endl;
    getline(cin, text);

    while (rfile >> p)
    {
        if (title.compare(p.getTitle()) == 0)
        {
            cout << "This title has already been taken try another one" << endl;
            return;
        }
    }
    rfile.close();

    ofstream wfile("post.bin", ios::app);
    if (!wfile.is_open())
    {
        cerr << "error when opeing file" << endl;
    }

    Post newUser(title, text, currentUser.getUsername());
    wfile << newUser;
    wfile.close();
}

void displayUserPostHistory(User currentUser){
    ifstream rfile("post.bin");
    Post p("","","");
    if (!rfile.is_open())
    {
        cerr << "error when opeining file" << endl;
        exit(1);
    }
    while (rfile >> p)
    {
        if(p.getUser().compare(currentUser.getUsername()) == 0){
            cout << "\n" << endl; 
            cout << "User:\t" << p.getUser() << endl;
            cout << "Title:\t" << p.getTitle() << endl;
            cout << "Text:\t" << p.getText() << endl;
            cout << "likes:\t" << p.getLikes() << endl;
            cout << "\n" << endl;
        }
        }
    rfile.close();
}

void createAccount()
{
    string inputUsername, inputPasword;
    User p("", "");

    cout << "enter your username" << endl;
    cin >> inputUsername;
    cout << "enter your password" << endl;
    cin >> inputPasword;

    ifstream rfile("user.bin");
    if (!rfile.is_open())
    {
        cerr << "error when opening file" << endl;
        exit(1);
    }

    while (rfile >> p)
    {
        if (inputUsername.compare(p.getUsername()) == 0)
        {
            cout << "The username you entered is already in use try another" << endl;
            return;
        }
    }
    rfile.close();

    ofstream wfile("user.bin", ios::app);
    User newUser(inputUsername, inputPasword);

    if (!wfile.is_open())
    {
        cerr << "error when opening file" << endl;
        exit(1);
    }

    wfile << newUser;
    wfile.close();
}

User logIn()
{
    string inputUsername, inputPasword;
    ifstream file("user.bin");
    User p("", "");

    if (!file.is_open())
    {
        cerr << "error when opening file" << endl;
        exit(1);
    }

    cout << "enter your username" << endl;
    cin >> inputUsername;
    cout << "enter your password" << endl;
    cin >> inputPasword;

    while (file >> p)
    {
        if (inputUsername.compare(p.getUsername()) == 0 && inputPasword.compare(p.getPassword()) == 0)
        {
            p.setisLoggedIn();
            file.close();
            return p;
        }
    }
    file.close();
    return User("", "");
}
