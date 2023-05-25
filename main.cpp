#include <iostream>
#include <fmt/ranges.h>
#include <filesystem>
#include "PasswordRecord.h"
#include "PasswordLibrary.h"
namespace fs = std::filesystem;

void starting_message();

void display_files();
bool file_exists(const fs::path& a);
void create_sample_data();
fs::path read_from();

int main() {

    fs::path our_file = read_from();
    std::cout << our_file << "\n";
    if(our_file == "")
        return 0;

    lib.setWorkingFileName(our_file);
    //lib.create_sample_data();

    if(file_exists(our_file)) {
        lib.read();
    } else create_sample_data();

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
};
void create_sample_data(){

    PasswordRecord one("Twitter", "abobamega123", "Social", "","");
    PasswordRecord two("IKO", "abobamega123", "Banking", "iko.com","sm");
    PasswordRecord three("Tiktok", "abobamega123", "Social", "tiktok.com","sm");
    PasswordRecord four("Snapchat", "abobamega123", "Social", "snapchat.com","sm");
    PasswordRecord five("Messenger", "abobamega123", "Messages", "messenger.com","sm");
    PasswordRecord six("Pinterest", "abobamega123", "Photo", "pinterest.com","sm");
    PasswordRecord seven("Netflix", "abobamega123", "Video", "netflix.com","sm");
    lib.addRecord(one);
    lib.addRecord(two);
    lib.addRecord(three);
    lib.addRecord(four);
    lib.addRecord(five);
    lib.addRecord(six);
    lib.addRecord(seven);

};

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

