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

void PasswordLibrary::writeLastReadTime() const {
    std::fstream outFile(workingFileName);
    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&lastReadTime));

    std::stringstream memoryStream;
    memoryStream << buff;
    //outFile << buff;

    Crypting crypting;
    crypting.setFilePassword("123");
    crypting.process(&memoryStream, &outFile);

    outFile.close();
};


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
    lib.setLastReadTimeToNow();

    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&lastReadTime));

    std::stringstream timeStream;
    timeStream << buff;
    //outFile << buff;

    Crypting timeCrypting;
    timeCrypting.setFilePassword("123");
    timeCrypting.process(&timeStream, &outFile);

    Crypting crypting;
    crypting.setFilePassword(filePassword);
    crypting.process(&memoryStream, &outFile);

    outFile.close();
}

bool PasswordLibrary::read() {

    std::ifstream inFile(workingFileName);

    // load last read time
    char buff[20];
    inFile.get(buff, 20);
    //std::cout << buff << "\n";

    // decode whole file to memory stream
    std::stringstream memoryStream;
    Crypting crypting;
    crypting.setFilePassword(filePassword);

    if(!crypting.process(&inFile, &memoryStream)){
        return false;
    }

    inFile.close();

    //Line for checking the right password
    std::string identifier;
    std::getline(memoryStream, identifier);
   // std::cout << identifier;
    if(identifier != CRYPTING_IDENTIFIER) {
        std::cout << "The password you entered is wrong, try again!";
        lib.setLastReadTimeToNow();
        lib.writeLastReadTime();
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
/*
    for(std::string a : categories)
        std::cout << a << "\n";

*/
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
        PasswordLibrary::printRecord(i);
    }
}

void PasswordLibrary::printRecord(PasswordRecord rec) const {
    fmt::print("-------------------------------------------------\n");
    std::cout << "Name:     " << rec.getName() << "\n";
    std::cout << "Password: " << rec.getPass()<< "\n";
    std::cout << "Category: " << rec.getCategory()<< "\n";
    std::cout << "Website:  " << rec.getWebsite()<< "\n";
    std::cout << "Login:    " << rec.getLogin()<< "\n";
    fmt::print("-------------------------------------------------\n");

}

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
    auto range_remove = std::ranges::remove_if(records, [categ](const PasswordRecord s) -> bool{categ == s.getCategory();});
    records.erase(range_remove.begin(),range_remove.end());
}

std::vector<PasswordRecord*> PasswordLibrary::searchRecordBy(const std::string& attribute) const  {
    fmt::print ("Please enter the data for search\n");
    std::string data;
    std::cin >> data;
    std::vector<PasswordRecord*> foundRecordsByAttribute;

    // copy_if

    for(auto it = records.begin(); it != records.end(); ++it ){
        PasswordRecord* rec = const_cast< PasswordRecord* >( &(*it) );

        if(attribute == "name"){
            if(rec->getName() == data){
                printRecord(*rec);
                foundRecordsByAttribute.push_back(rec);
            }
        }
        else if(attribute == "password"){
            if(rec->getPass() == data){
                printRecord(*rec);
                foundRecordsByAttribute.push_back(rec);
            }
        }
        else if(attribute == "category"){
            if(rec->getCategory() == data){
                printRecord(*rec);
                foundRecordsByAttribute.push_back(rec);
            }
        }
        else if(attribute == "website"){
            if(rec->getWebsite() == data){
                printRecord(*rec);
                foundRecordsByAttribute.push_back(rec);
            }
        }
        else if(attribute == "login"){
            if(rec->getLogin() == data){
                printRecord(*rec);
                foundRecordsByAttribute.push_back(rec);
            }
        }
        else
            std::cout << "Wrong input!!!\n";
    }
    if (foundRecordsByAttribute.empty())
        std::cout << "Not found\n";
    return foundRecordsByAttribute;
}

void PasswordLibrary::deleteRecord( const PasswordRecord& rec) {
    auto range_remove =
            std::ranges::remove_if(records, [rec](const PasswordRecord& s) ->
                bool{ (s.getName() == rec.getName() && s.getPass()==rec.getPass());});
    records.erase(range_remove.begin(),range_remove.end());

}

void PasswordLibrary::setFilePassword(const string &filePassword) {
    PasswordLibrary::filePassword = filePassword;
}

bool PasswordLibrary::isUnique(const std::string& pass)const{
    for(auto i : records)
        if (i.getPass() == pass)
            return false;
    return true;

}

class SortCompare
{
private:
    std::vector<std::string> sortBy;
public:
    SortCompare(const std::vector<std::string> &sortBy)
      : sortBy(sortBy){}

      bool operator()(const PasswordRecord& rec1, const PasswordRecord& rec2) const
      {
        for(auto i : sortBy){
            if(i == "name")
            {
                if (rec1.getName()  != rec2.getName())
                    return rec1.getName() < rec2.getName();
            }

            if(i == "category")
            {
                if (rec1.getCategory() != rec2.getCategory())
                    return rec1.getCategory() < rec2.getCategory();
            }

            if(i == "website")
            {
                if (rec1.getWebsite() != rec2.getWebsite())
                    return rec1.getWebsite() < rec2.getWebsite();
            }
        }

        return true;
      }
};


void PasswordLibrary::sortRecords(const std::vector<std::string> &sortBy) {
    std::sort(records.begin(), records.end(), SortCompare(sortBy));
}

void PasswordLibrary::createRecord(std::string name, std::string password, std::string category, std::string website,
                                   std::string login) {
    addRecord(PasswordRecord(name,password,category,website,login));

}
