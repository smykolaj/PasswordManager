//
// Created by Микола Суконнік on 22.05.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDLIBRARY_H
#define PASSWORDMANAGER_PASSWORDLIBRARY_H
#include <vector>
#include <filesystem>
#include "PasswordRecord.h"
#include <set>

namespace fs = std::filesystem;

class PasswordLibrary {
private:
    //file
    fs::path workingFileName;
    std::string filePassword;
public:
    void setFilePassword(const string &filePassword);

private:
    //time
    std::time_t lastReadTime;
    //all passwords
    std::vector< PasswordRecord > records;
    //all categories
    std::set <std::string> categories;

public:
    //File
    void setWorkingFileName(const fs::path& fileName);

    // Records
    void addRecord(const PasswordRecord& rec );
    void deleteRecord(const PasswordRecord& rec);
    void deleteRecordByCategory(const std::string& categ);

    void write() const;
    void writeLastReadTime() const;
    bool read();

    void printRecord(PasswordRecord rec) const;
    void printAllRecords() const;
    std::vector<PasswordRecord*> searchRecordBy(const std::string& attribute)const ;

    // Categories
    void addCategory(const std::string& category);
    void deleteCategory(const std::string& category);
    std::set <std::string> getCategories();

    // Last read time
    void setLastReadTimeToNow();
    std::time_t getLastReadTime() const;
//    static bool save( file_name, const PasswordLibrary& library );
};

extern PasswordLibrary lib;

#endif //PASSWORDMANAGER_PASSWORDLIBRARY_H
