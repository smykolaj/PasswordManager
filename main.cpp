#include <iostream>
#include <fmt/ranges.h>
#include <filesystem>
#include "PasswordRecord.h"
#include "PasswordLibrary.h"
#include "Crypting.h"
#include <algorithm>

namespace fs = std::filesystem;

/**
 * prints out the message asking user to choose the method by which he finds the source file
 */
void starting_message();

/**
 * prints out the existing .txt files in this directory
 */
void display_files();

/**
 * returns true, if a file with such path exists
 */
bool file_exists(const fs::path& a);

/**
 * puts sample data with password records into the library
 */
void create_sample_data();

/**
 * returns the name of the file which the application is done on, depending on the user input
 */
fs::path read_from();

/**
 * returns a string where the user sets the password for a file
 */
std::string askForFilePassword();

/**
 * returns true if input is "yes" or "y" and in other cases false
 */
bool askForConfirmation();

//commands

/**
 * starts functions depending on the user input
 */
void mainFunctionality();

/**
 * returns the alias of a function the user chose
 */
std::string showMainMenu();

/**
 * creates a new category
 */
void createNewCategory();

/**
 * deletes the category, and all passwords associated with it
 */
void deleteCategory();

/**
 * creates a new PasswordRecord and put it into the library
 */
void addPassword();

/**
 * changes info of an existing password record
 */
void editPassword();

/**
 * deletes the password record(s)
 */
void deletePassword();

/**
 * sorts records in the library depending on the attributes we se to sort
 */
void sortPasswords();

/**
 * returns a vector of password records that satisfy the search results
 */
std::vector<PasswordRecord*> searchPassword();

/**
 * checks whether all conditions of a safe password are considered in the password the user entered
 */
std::string checkForStrength();

/**
 * returns a generated randomly password depending on what user wants to use in it,
 * if no parameter is chosen, the password returned consists only of digits
 */
std::string createRandomPassword();

int main() {


    fs::path our_file = read_from();

    if(our_file == "")
        return 0;

    lib.setWorkingFileName(our_file);

    const std::string filePassword = askForFilePassword();
    lib.setFilePassword(filePassword);

    if(file_exists(our_file)) {
        if(lib.read()) {
            mainFunctionality();
            lib.write();
        }
    } else {
        //create_sample_data();
        mainFunctionality();
        lib.write();
    }




    return 0;
}

void starting_message(){
    fmt::print("Greetings!\n"
               "Please choose the source file\n"
               "Press 1 for list of existing files or\n"
               "Press 2 to provide an absolute path to the file\n"
               "Press 3 to create a new file\n"
               "Press 0 to exit\n");
}

std::string showMainMenu(){
    fmt::print("Press 1 to add a new category\n"
               "Press 2 to delete a category and all assigned passwords\n"
               "Press 3 to add a password\n"
               "Press 4 to edit a password\n"
               "Press 5 to delete passwords\n"
               "Press 6 to sort passwords\n"
               "Press 7 to search passwords\n"
               "Press 8 to print all passwords\n"
               "Press 0 to exit\n");
    std::string choice;
    std::cin >> choice;
    return choice;
}

void display_files(){
    fs::path directoryPath = fs::current_path().parent_path();

// Iterate over the files in the directory
    for (const auto& file : std::filesystem::directory_iterator(directoryPath)) {

        // Check if the file extension is ".txt"
        if (file.path().extension() == ".txt") {
            // Display the file name
            std::cout << file.path().filename() << "\n";

        }
    }
}

bool file_exists(const fs::path& a){
    if (std::filesystem::exists(a)) {
        return true;
    }
    else {
        std::cerr << "File doesn't exist!\n\n";
        std::cerr.flush();
        return false;
    }
}

void create_sample_data(){

    PasswordRecord one("Twitter", "ADHFNV8Cgood", "Social", "","");
    PasswordRecord two("IKO", "BLYe9buxgood", "Banking", "","+380666999185");
    PasswordRecord three("Tiktok", "yJA7Pjyugood", "Social", "tiktok.com","smykolaj");
    PasswordRecord four("Snapchat", "Z6PfHbZxgood", "Social", "snapchat.com","");
    PasswordRecord five("Messenger", "EZvt7qsJgood", "Messages", "messenger.com","something");
    PasswordRecord six("Pinterest", "kEzeCfsAgood", "Photo", "pinterest.com","loser");
    PasswordRecord seven("Netflix", "rgWb3BMTgood", "Video", "netflix.com","greatwathcher");
    lib.addRecord(one);
    lib.addRecord(two);
    lib.addRecord(three);
    lib.addRecord(four);
    lib.addRecord(five);
    lib.addRecord(six);
    lib.addRecord(seven);
    lib.addCategory("Social");
    lib.addCategory("Banking");
    lib.addCategory("Messages");
    lib.addCategory("Photo");
    lib.addCategory("Video");


}

fs::path read_from(){
    std::string source_choice;

    fs::path our_file;
    std::string file_name;
    std::string project_dir_path = fs::current_path().parent_path();
    std::string file_path;

    while(source_choice != "0") {
        starting_message();
        source_choice="";
        std::cin>>source_choice;

        if (source_choice == "1") {
            display_files();
            std::cin >> file_name;
            file_path = project_dir_path + "/" + file_name;
            our_file = file_path;
            //Users/smykolaj/CLionProjects/Project1/test.txt
            if(file_exists(our_file)) {
                break;
            }
            else {
                continue;
            }

        }

        else if (source_choice == "2") {
            std::cout << "Please provide the ABSOLUTE path to the file\n";
            std::cin >> file_path;
            our_file = file_path;
            if(file_exists(our_file)) {
                break;
            }
            else {
                continue;
            }

        }
        else if (source_choice == "3") {
            std::cout << "Please provide the new name for the file\n";
            std::cin >> file_name;
            file_path = project_dir_path + "/" + file_name;
            our_file = file_path;
            return our_file;

        }

        else if (source_choice == "0") {
            fmt::print("Exit");
            return "";
        }

        else {
            std::cerr << "Wrong input\n\n";
            std::cerr.flush();
        }
    }
    return our_file;
}

std::string askForFilePassword(){
    std::cout << "Please enter the password for the chosen file\n";
    std::string pass;
    std::cin >> pass;
    //Crypting::setFilePassword(pass);
    return pass;
}

void mainFunctionality(){
    std::string choice;
    choice = showMainMenu();
    while (choice != "0") {
        if (choice == "1")
            createNewCategory();
        else if (choice == "2")
            deleteCategory();
        else if (choice == "3")
            addPassword();
        else if (choice == "4")
            editPassword();
        else if (choice == "5")
            deletePassword();
        else if (choice == "6")
            sortPasswords();
        else if (choice == "7")
            searchPassword();
        else if (choice == "8")
            lib.printAllRecords();
        else if (choice == "0")
            return;
        else {
            std::cout << "Wrong input!\n";
            choice="";
        }
        choice = showMainMenu();
    }
}

std::vector<PasswordRecord*> searchPassword() {
    std::string choice;
    fmt::print("By which parameter would you like to get your record?\n"
           "Press 1 to search by name\n"
           "Press 2 to search by password\n"
           "Press 3 to search by category\n"
           "Press 4 to search by website\n"
           "Press 5 to search by login\n"
           "Press 0 to exit\n");

    while (choice != "0") {
        std::cin >> choice;
        if (choice == "1") {
            return lib.searchRecordBy("name");
        }
        else if (choice == "2") {
            return lib.searchRecordBy("password");
        }
        else if (choice == "3") {
            return lib.searchRecordBy("category");
        }
        else if (choice == "4") {
            return lib.searchRecordBy("website");
        }
        else if (choice == "5") {
            return lib.searchRecordBy("login");
        }
        else if (choice == "0")
            return {};
        else {
            std::cout << "Wrong input!\n";
            continue;
        }
    }
}

void sortPasswords() {
    std::vector<std::string> sortBy;

    std::string choice;

    while(choice != "0") {
        std::cout << "Please enter the attribute you would like to sort by:\n"
                     "1 for category,\n"
                     "2 for name,\n"
                     "3 for website\n"
                     "0 to finish\n";

        std::cin >> choice;
        if (choice == "1")
            sortBy.push_back("category");
        if (choice == "2")
            sortBy.push_back("name");
        if (choice == "3")
            sortBy.push_back("website");
    }

    if( !sortBy.empty()) {
        lib.sortRecords(sortBy);
        lib.printAllRecords();
    }
}

void deletePassword() {

for(auto i : searchPassword()){
    std::cerr << "These passwords are being deleted!!!\n"
              << "Are you sure about that?\ny/n\n";

    std::string choice;
    std::cin >> choice;
    if(choice == "y" or choice == "yes")
        lib.deleteRecord(*i);
    else
        continue;
}
}

bool askForConfirmation(){
    fmt::print("Are you sure?");
    std::string choice;
    std::cin >> choice;
    if(choice == "y" or choice == "yes")
        return true;
    else
        return false;
}

void editPassword() {
    for(auto i : searchPassword()){
        std::string choice;
        fmt::print ("Press 1 to edit the name\n"
                    "Press 2 to edit the password\n"
                    "Press 3 to edit the category\n"
                    "Press 4 to edit the website\n"
                    "Press 5 to edit the login\n"
                    "Press 0 to exit\n");
        std::cin >> choice;
        while (choice != "0") {
            std::string newEntry = "";
            std::cout << "What will be the new input?\n";
            std::cin >> newEntry;
            if (choice == "1")
                if (askForConfirmation()) {
                    i->setName(newEntry);
                    break;
                }
            if (choice == "2")
                if(askForConfirmation()) {
                    i->setPass(newEntry);
                    break;
                }
            if (choice == "3")
                if(askForConfirmation() and lib.getCategories().contains(newEntry)) {
                    i->setCategory(newEntry);
                    break;
                }
                else {
                    std::cout << "Such category doesn't exist. It can be created\n";
                    if (askForConfirmation()) {
                        lib.addCategory(newEntry);
                        i->setCategory(newEntry);
                        break;
                    }
                }
            if (choice == "4")
                if(askForConfirmation()) {
                    i->setWebsite(newEntry);
                    break;
                }
            if (choice == "5")
                if(askForConfirmation()) {
                    i->setLogin(newEntry);
                    break;
                }
            if (choice == "0")
                return;
            else {
                std::cout << "Wrong input!";
                continue;
            }
        }

    }


}

void addPassword() {
    std::string name, password, category, website, login, choice;
    std::cout << "Please enter a name for the new record\n";
    std::cin >> name;
    std::cout << "Please enter 1 if you want to enter you own password\n"
    << "Please enter 2 if you want a randomly generated password\n";
    std::cin >> choice;
    if(choice == "1"){
        password = checkForStrength();
    }
    else if (choice == "2"){
        password = createRandomPassword();
    }
    std::cout << "Please enter a category for the new record\n";
    std::cin >> category;
    while(!lib.getCategories().contains(category)) {
        category = "";
        std::cout << "Such category doesn't exist\n";
        createNewCategory();
        std::cout << "Please enter a category for the new record\n";
        std::cin >> category;
    }
    std::cout << "Please enter a website for the new record\n";
    std::cin >> website;
    std::cout << "Please enter a login for the new record\n";
    std::cin >> login;
    std::cout << "Done. Would you like to finish? Enter yes or 0 to exit\n";
    choice = "";
    std::cin >> choice;
    if(choice == "y" or choice == "yes")
        lib.createRecord(name, password, category, website, login);
    else
        return;
}

std::string createRandomPassword() {
    std::vector<char> uppercaseLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    std::vector<char> lowercaseLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                          'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::vector<char> specialChars = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '-', '=',
                                      '[', ']', '{', '}', '<', '>', '?'};
    std::vector<char> digits = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    std::string createdPassword;
    bool includeChar = false;
    bool includeUpper = false;
    bool includeLower = false;
    int length;

    std::cout << "Please enter the length of your generated password\n";
    std::cin >> length;
    std::string choice;

    std::cout << "Please say if you want to include special characters\n";
    std::cin >> choice;
    if(choice == "yes" or choice == "y")
        includeChar = true;

    choice = "";
    std::cout << "Please say if you want to include upper-case characters\n";
    std::cin >> choice;
    if(choice == "yes" or choice == "y")
        includeUpper = true;

    choice = "";
    std::cout << "Please say if you want to include lower-case characters\n";
    std::cin >> choice;
    if(choice == "yes" or choice == "y")
        includeLower = true;

    std::vector<char> collection;
    collection.insert(collection.end(), digits.begin(), digits.end());

    if(includeChar) {
        createdPassword.push_back(specialChars.at(std::rand() % specialChars.size()));
        collection.insert(collection.end(), specialChars.begin(), specialChars.end());
    }
    if(includeUpper) {
        createdPassword.push_back(uppercaseLetters.at(std::rand() % uppercaseLetters.size()));
        collection.insert(collection.end(), uppercaseLetters.begin(), uppercaseLetters.end());
    }
    if(includeLower) {
        createdPassword.push_back(lowercaseLetters.at(std::rand() % lowercaseLetters.size()));
        collection.insert(collection.end(), lowercaseLetters.begin(), lowercaseLetters.end());
    }
    std::srand((unsigned) time(nullptr));
    for(int i = createdPassword.size(); i < length; i++ ){
        int rand = std::rand() % collection.size();
        createdPassword.push_back(collection.at(rand));

    }
    return createdPassword;
}

void createNewCategory() {
    bool finish = false;
    while (!finish) {
        fmt::print("Printing all existing categories\n{}\n", lib.getCategories());
        fmt::print("Enter a name of the new category you would like to add or enter 0 to exit.\n");
        std::string newCateg;
        std::cin >> newCateg;
        if (newCateg == "0") {
            finish = true;
            break;
        }

        lib.addCategory(newCateg);
        fmt::print("Done. Would you like to add one more? y/n\n");
        std::string choice;
        std::cin >> choice;
        if (choice == "y" || choice == "yes")
            continue;
        else
            finish = true;

    }
}

void deleteCategory() {
    bool finish = false;
    while (!finish) {
        fmt::print("Printing all existing categories\n{}\n", lib.getCategories());
        fmt::print("Enter a name of the new category you would like to delete or enter 0 to exit.\n");
        std::string delCateg;
        std::cin >> delCateg;
        if(delCateg == "0") {
            finish = true;
            break;
        }
        lib.deleteCategory(delCateg);
        lib.deleteRecordByCategory(delCateg);


        fmt::print("Done. Would you like to delete one more? y/n\n");
        std::string choice;
        std::cin >> choice;
        if (choice == "y" || choice == "yes")
            continue;
        else
            finish = true;
    }


}

std::string checkForStrength(){
    std::string forChecking;
    std::cout << "Please enter a password for the new record\n";
    std:: cin >> forChecking;
    bool goodLength = false;
    bool hasLower = false;
    bool hasUpper = false;
    bool hasNumber = false;
    bool hasChar = false;
    bool isUnique = lib.isUnique(forChecking);
    for(char i : forChecking){
        if(islower(i))
            hasLower = true;
        else if(isdigit(i))
            hasNumber = true;
        else if(isupper(i))
            hasUpper = true;
        else
            hasChar = true;
    }
    if(forChecking.length() >= 8 )
        goodLength = true;
    if(hasChar && hasUpper && hasNumber && hasLower && goodLength && isUnique) {
        std::cout << "Wow! Such a strong password)\n";
        return forChecking;
    }
    else{
        std::cout << "Your password is weak. ";
        if(!isUnique)
            std::cout << "Already used before. ";
        if(!hasLower)
            std::cout << "Doesn't have lower-case letter. ";
        if(!hasNumber)
            std::cout << "Doesn't have a number. ";
        if(!hasUpper)
            std::cout << "Doesn't have upper-case letter. ";
        if(!goodLength)
            std::cout << "Doesn't have at least 9 characters. ";
        if(!hasChar)
            std::cout << "Doesn't have a special character. ";
        std::string choice;
        std::cout << "\nWould you like to use it anyway?\n";
        std::cin >> choice;
        if(choice == "yes" or choice == "y")
            return forChecking;
        else{
            return checkForStrength();
        }
    }
}
