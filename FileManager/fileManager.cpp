#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

class FileManager
{
private:
    string currentDirPath = fs::current_path().string(),currentFilePath = fs::current_path().string();
    int fileSize{};
public:
    FileManager() = default;
    ~FileManager() = default;
    string getDirName(){return currentDirPath;}
    string getFileName(){return currentFilePath;}
    int getFileSize(){return fileSize;}
    void moveToParentDir();
    void setDirPath(string inputDir);
    void setFilePath(string inputFile);
    void setFileSize();
    void viewContentsOfDir();

    void createDir();
    void createFile();
    void copyFile();
    void renameFiles();
    void moveFiles();
    void removeFile();
    void removeDir();
    void lookInDir();
};

void FileManager::viewContentsOfDir(){
    for(const auto file : fs::recursive_directory_iterator(getDirName())){
        cout << file.path() << endl;
    }
}

void FileManager::setFileSize(){
    fileSize = fs::file_size(getFileName());
}

void FileManager::moveToParentDir(){
    if(fs::exists(fs::current_path().parent_path())){
        setDirPath(fs::current_path().parent_path().string());
    }
    else{
        cout << "you have reach the home derectory" << endl;
    }
}

void FileManager::setFilePath(string inputFile){
    if (fs::exists(inputFile))
    {
        cout << "successfully changed file" << endl;
        currentFilePath = inputFile;
    }
    else{
        cout << "The file you want to access has not been found" << endl;
    }
    
}

void FileManager::setDirPath(string inputDir){
    if (fs::exists(inputDir))
    {
        cout << "successfully changed directory" << endl;
        currentDirPath = inputDir;
    }
    else{
        cout << "the directory you want to access has not been found" << endl;
    }
}


int main(){
    FileManager fileManager;
    cout << fileManager.getFileName() << endl;
    cout << fileManager.getDirName() << endl;
    fileManager.moveToParentDir();
    cout << fileManager.getFileName() << endl;
    cout << fileManager.getDirName() << endl;
    fileManager.moveToParentDir();
    cout << fileManager.getFileName() << endl;
    cout << fileManager.getDirName() << endl;
    return 0;
}
