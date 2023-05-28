#include <iostream>
#include <fmt/ranges.h>
#include <filesystem>
#include "PasswordRecord.h"
#include "PasswordLibrary.h"
#include "Crypting.h"
#include <algorithm>
namespace fs = std::filesystem;

void starting_message();

void display_files();
bool file_exists(const fs::path& a);
void create_sample_data();
fs::path read_from();
void askForFilePassword();
void mainFunctionality();
std::string mainMenu();

void createNewCategory();

void deleteCategory();

void addPassword();

void editPassword();

void deletePassword();

void sortPasswords();

void searchPassword();

int main() {

    fs::path our_file = read_from();
    //std::cout << our_file << "\n";
    if(our_file == "")
        return 0;

    lib.setWorkingFileName(our_file);

    if(file_exists(our_file)) {
        askForFilePassword();
        lib.read();
    } else {
        askForFilePassword();
        create_sample_data();
    }
    lib.printAllRecords();
    mainFunctionality();
    lib.write();
    lib.printAllRecords();



    return 0;
}
/**
 * prints out the message asking user to choose the method by which he finds the source file
 */
void starting_message(){
    fmt::print("Greetings!\n"
               "Please choose the source file\n"
               "Press 1 for list of existing files or\n"
               "Press 2 to provide an absolute path to the file\n"
               "Press 3 to create a new file\n"
               "Press 0 to exit\n");
}

std::string mainMenu(){
    fmt::print("Press 1 to add a new category\n"
               "Press 2 to delete a category and all assigned passwords\n"
               "Press 3 to add a password\n"
               "Press 4 to edit a password\n"
               "Press 5 to delete passwords\n"
               "Press 6 to sort passwords\n"
               "Press 7 to search passwords\n"
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
        std::cout << "Successfully found file\n";
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

void askForFilePassword(){
    std::cout << "Please enter the password for the chosen file\n";
    std::string pass;
    std::cin >> pass;
    Crypting::setFilePassword(pass);
}

void mainFunctionality(){
    std::string choice;
    choice = mainMenu();
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
        else if (choice == "0")
            return;
        else {
            std::cout << "Wrong input!";
            continue;
        }
        choice = mainMenu();
    }
}

void searchPassword() {

}

void sortPasswords() {

}

void deletePassword() {

}

void editPassword() {

}

void addPassword() {

}

void deleteCategory() {
    bool finish = false;
    while (!finish) {
        fmt::print("Printing all existing categories\n{}\n", lib.getCategories());
        fmt::print("Enter a name of the new category you would like to delete or enter 0 to exit.\n");
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

void createNewCategory() {
    bool finish = false;
    while (!finish) {
        fmt::print("Printing all existing categories\n{}\n", lib.getCategories());
        fmt::print("Enter a name of the new category you would like to add or enter 0 to exit.\n");
        std::string delCateg;
        std::cin >> delCateg;
        if(delCateg == "0") {
            finish = true;
            break;
        }
        lib.deleteCategory(delCateg);



        fmt::print("Done. Would you like to delete one more? y/n\n");
        std::string choice;
        std::cin >> choice;
        if (choice == "y" || choice == "yes")
            continue;
        else
            finish = true;
    }


}
