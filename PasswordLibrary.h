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
    void write() const;
    bool read();
    void printAllRecords() const;

    // Categories
    void addCategory(const std::string& category);
    void deleteCategory(const std::string& category);

    // Last read time
    void setLastReadTimeToNow();
    std::time_t getLastReadTime() const;
//    static bool save( file_name, const PasswordLibrary& library );
};

extern PasswordLibrary lib;

#endif //PASSWORDMANAGER_PASSWORDLIBRARY_H
