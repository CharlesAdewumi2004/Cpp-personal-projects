#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

class FileManager
{
private:
    string currentDirPath = fs::current_path().string(), currentFilePath = "";
    int fileSize{};

public:
    FileManager() = default;
    ~FileManager() = default;
    string getDirName() { return currentDirPath; }
    string getFileName() { return currentFilePath; }
    int getFileSize() { return fileSize; }
    void moveToParentDir();
    void setDirPath(string inputDir);
    void setFilePath(string inputFile);
    void setDirPath();
    void setFilePath();
    void setFileSize();
    void viewContentsOfDir();
    void createDir();
    void createFile();
    void removeFile();
    void removeDir();
    void copyFile();

};

void FileManager::copyFile(){
    fs::copy(currentFilePath, currentDirPath);
}


void FileManager::removeDir(){
    fs::remove_all(currentDirPath);
}

void FileManager::removeFile(){
    fs::remove(currentFilePath);
}

void FileManager::createFile(){
    ofstream file(currentFilePath);
    file.close();
}

void FileManager::createDir()
{
    string inputNewDirName;
    cout << "Enter the name of your new directory" << endl;
    cin >> inputNewDirName;

    if (fs::create_directories(inputNewDirName) == true)
    {
        cout << "new directory created successfully" << endl;
    }
    else
    {
        cout << "failed to create new directory" << endl;
    }
}

void FileManager::viewContentsOfDir()
{
    cout << "\n File:" << endl;
    for (const auto file : fs::recursive_directory_iterator(getDirName()))
    {
        cout << file.path() << endl;
    }
}

void FileManager::setFileSize()
{
    fileSize = fs::file_size(getFileName());
}

void FileManager::moveToParentDir()
{
    if (fs::exists(fs::current_path().parent_path()))
    {
        setDirPath(fs::current_path().parent_path().string());
    }
    else
    {
        cout << "you have reached the home derectory" << endl;
    }
}

void FileManager::setDirPath(){
    string inputDirName;
    cout << "enter directory name" << endl;
    cin >> inputDirName;

    if (fs::exists(inputDirName))
    {
        cout << "successfully changed directory" << endl;
        currentDirPath = inputDirName;
        fs::current_path(inputDirName);
    }
    else
    {
        cout << "the directory you want to access has not been found" << endl;
    }
}

void FileManager::setFilePath(){
    string inputfiLeName;
    cout << "enter file name" << endl;
    cin >> inputfiLeName;

    if (fs::exists(inputfiLeName))
    {
        cout << "successfully changed file" << endl;
        currentFilePath = inputfiLeName;
        fs::current_path(inputfiLeName);
    }
    else
    {
        cout << "The file you want to access has not been found" << endl;
    }
}

void FileManager::setFilePath(string inputFile)
{
    if (fs::exists(inputFile))
    {
        cout << "successfully changed file" << endl;
        currentFilePath = inputFile;
        fs::current_path(inputFile);
    }
    else
    {
        cout << "The file you want to access has not been found" << endl;
    }
}

void FileManager::setDirPath(string inputDir)
{
    if (fs::exists(inputDir))
    {
        cout << "successfully changed directory" << endl;
        currentDirPath = inputDir;
        fs::current_path(inputDir);
    }
    else
    {
        cout << "the directory you want to access has not been found" << endl;
    }
}

int main()
{
    FileManager fileManger;
    fileManger.setDirPath("/home/charlie/forsen]");
    cout << fileManger.getDirName() << endl;
    fileManger.setDirPath();
    fileManger.viewContentsOfDir();
    fileManger.setFilePath();
    fileManger.removeFile();
    fileManger.viewContentsOfDir();
    return 0;
}
