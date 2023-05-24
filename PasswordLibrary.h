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

public:
    std::vector< PasswordRecord > records;
    std::set <std::string> categories;

    void add_record( const PasswordRecord& rec );
    void write( const fs::path& file);
    bool read(const fs::path& file);
    void printAllRecords();
//    static bool save( file_name, const PasswordLibrary& library );
};

extern PasswordLibrary lib;

#endif //PASSWORDMANAGER_PASSWORDLIBRARY_H
