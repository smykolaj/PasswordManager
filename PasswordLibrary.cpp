//
// Created by Микола Суконнік on 22.05.2023.
//

#include <fstream>
#include "PasswordLibrary.h"
#include <fmt/ranges.h>


PasswordLibrary lib;


void PasswordLibrary::add_record(const PasswordRecord &rec) {
records.push_back(rec);
}



void PasswordLibrary::write(const fs::path& file) {
    std::ofstream outFile(file);

    // categories
    std::string cat;

    for(std::string a : categories){
        outFile << a << "\n";
    }
    outFile << "@@@categ_end!!!" << "\n";

    // passwords
    for(auto i : records ) {
        outFile << i.getName() << "\n";
        outFile << i.getPass()<< "\n";
        outFile << i.getCategory()<< "\n";
        outFile << i.getWebsite()<< "\n";
        outFile << i.getLogin()<< "\n";
    }
    outFile.close();

}
bool PasswordLibrary::read(const fs::path& fileName) {
    std::ifstream inFile(fileName);

    // categories
    std::string cat;

    for(std::getline(inFile, cat); cat != "@@@categ_end!!!"; std::getline(inFile, cat)){
        categories.insert(cat);
    }

    for(std::string a : categories)
        std::cout << a;


    // passwords
    while (! inFile.eof()){
        PasswordRecord rec;

        std::string s;

        std::getline(inFile, s);
        rec.setName( s );

        if(inFile.eof())
            break;

        std::getline(inFile, s);
        rec.setPass( s );

        std::getline(inFile, s);
        rec.setCategory( s );

        std::getline(inFile, s);
        rec.setWebsite( s );

        std::getline(inFile, s);
        rec.setLogin( s );



        add_record(rec);
    }


}
void PasswordLibrary::printAllRecords(){
    for(auto i : records ) {
        std::cout << i.getName() << "\n";
        std::cout << i.getPass()<< "\n";
        std::cout << i.getCategory()<< "\n";
        std::cout << i.getWebsite()<< "\n";
        std::cout << i.getLogin()<< "\n";
    }
};
