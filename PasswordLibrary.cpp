//
// Created by Микола Суконнік on 22.05.2023.
//

#include <fstream>
#include "PasswordLibrary.h"
#include <fmt/ranges.h>
#include "Crypting.h"


PasswordLibrary lib;
const std::string CATEGORY_DELIMETER = "@@@categ_end!!!";


void PasswordLibrary::addRecord(const PasswordRecord &rec) {
records.push_back(rec);
}



void PasswordLibrary::write() const {

    std::stringstream memoryStream;


    // categories
    std::string cat;

    for(std::string a : categories){
        memoryStream << a << "\n";
    }
    memoryStream << CATEGORY_DELIMETER << "\n";

    // passwords
    for(auto i : records ) {
        memoryStream << i.getName() << "\n";
        memoryStream << i.getPass()<< "\n";
        memoryStream << i.getCategory()<< "\n";
        memoryStream << i.getWebsite()<< "\n";
        memoryStream << i.getLogin()<< "\n";
    }

    std::ofstream outFile(workingFileName);
    Crypting::process(&memoryStream, &outFile);
    outFile.close();
}

bool PasswordLibrary::read() {
    std::ifstream inFile(workingFileName);
    std::stringstream memoryStream;
    if(!Crypting::process(&inFile, &memoryStream)){
        return false;
    }

    inFile.close();

    // categories
    std::string cat;
    while (! memoryStream.eof()){
        std::getline(memoryStream, cat);
        if(cat == CATEGORY_DELIMETER)
            break;
        addCategory(cat);
    }

    for(std::string a : categories)
        std::cout << a << "\n";

    // passwords
    while (! memoryStream.eof()){
        PasswordRecord rec;

        std::string s;

        std::getline(memoryStream, s);
        rec.setName( s );

        if(memoryStream.eof())
            break;

        std::getline(memoryStream, s);
        rec.setPass( s );

        std::getline(memoryStream, s);
        rec.setCategory( s );
        addCategory(s);

        std::getline(memoryStream, s);
        rec.setWebsite( s );

        std::getline(memoryStream, s);
        rec.setLogin( s );


        addRecord(rec);
    }

    setLastReadTimeToNow();
}

void PasswordLibrary::printAllRecords() const{
    for(auto i : records ) {
        std::cout << i.getName() << "\n";
        std::cout << i.getPass()<< "\n";
        std::cout << i.getCategory()<< "\n";
        std::cout << i.getWebsite()<< "\n";
        std::cout << i.getLogin()<< "\n";
    }
};

void PasswordLibrary::addCategory(const std::string &category) {
    categories.insert(category);
}

void PasswordLibrary::deleteCategory(const std::string &category) {
    categories.erase(category);
}

void PasswordLibrary::setLastReadTimeToNow() {
    lastReadTime = std::time(nullptr);
}

std::time_t PasswordLibrary::getLastReadTime() const {
    return lastReadTime;
}

void PasswordLibrary::setWorkingFileName(const fs::path &fileName) {
    workingFileName = fileName;
}

