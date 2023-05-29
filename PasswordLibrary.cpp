//
// Created by Микола Суконнік on 22.05.2023.
//

#include <fstream>
#include "PasswordLibrary.h"
#include <fmt/ranges.h>
#include "Crypting.h"
#include <algorithm>


PasswordLibrary lib;
const std::string CATEGORY_DELIMETER = "@@@categ_end!!!";
const std::string CRYPTING_IDENTIFIER = "@@@decryption!!!";


void PasswordLibrary::addRecord(const PasswordRecord &rec) {
records.push_back(rec);
}



void PasswordLibrary::write() const {

    std::stringstream memoryStream;

    //Line for checking the right password
    memoryStream << CRYPTING_IDENTIFIER << "\n";

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

    //Line for checking the right password
    std::string identifier;
    std::getline(memoryStream, identifier);
   // std::cout << identifier;
    if(identifier != CRYPTING_IDENTIFIER) {
        std::cout << "The password you entered is wrong, try again!";
        return false;
    }

    // categories
    std::string cat;
    std::cout << "\n";
    while (! memoryStream.eof()){
        std::getline(memoryStream, cat);
        if(cat == CATEGORY_DELIMETER)
            break;
        addCategory(cat);
    }

    //display categories to console

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
        std::cout << "\n";
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

std::set<std::string> PasswordLibrary::getCategories() {
    return categories;
}

void PasswordLibrary::deleteRecordByCategory(const string &categ) {
    int numberOfDeleted = 0;
    auto range_remove = std::ranges::remove_if(records, [categ, numberOfDeleted](const PasswordRecord s) -> bool{categ == s.getCategory();});
    records.erase(range_remove.begin(),range_remove.end());
}

