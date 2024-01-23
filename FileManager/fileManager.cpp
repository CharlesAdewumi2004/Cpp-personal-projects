#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class FileManager
{
private:
    string dirName,fileName,fileSize;
public:
    FileManager() = default;
    ~FileManager() = default;
    string getDirName(){return dirName;}
    string getFileName(){return fileName;}
    string getFileSize(){return fileSize;}
    string getcurrentDirPath();
    string getcurrentfilePath();
    void setDirName();
    void setFileName();
    void setFileSize();
    void createDir();
    void createFile();
    void copyFile();
    void renameFiles();
    void moveFiles();
    void removeFile();
    void removeDir();
    void lookInDir();
};
void FileManager::createFile(){
    
}

string FileManager::getcurrentDirPath(){
    return fs::path(getDirName()).string();
}

string FileManager::getcurrentfilePath(){
    return fs::path(getFileName()).string();
}

void FileManager::setDirName(){
    cout << "input directory name" << endl;
    cin >> dirName;
    if(fs::exists(dirName)){
        cout << "A new directory has been selected" << endl;
    }
    else{
        cout << "Couldn't find directory" << endl;
        dirName = "";
    }
}

void FileManager::setFileName(){
    cout << "input file name" << endl;
    cin >> fileName;
    if(fs::exists(fileName)){
        cout << "A new file has been selected" << endl;
    }
    else{
        cout << "Couldn't find file" << endl;
        fileName = "";
    }
}

void FileManager::setFileSize(){
    if(fileName != ""){
        auto fileSize = fs::file_size(fileName);
        cout << "File size:\t"<< getFileSize() << endl;
    } 
    else{
        cout << "A file has not been selected\nSelect one" << endl;
        setFileName();
    }
}




int main(){
    return 0;
}
