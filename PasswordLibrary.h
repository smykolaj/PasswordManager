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
    void setFilePassword(const string &filePassword);

    // Records
    /**
 *
 * This function adds the specified password record to the library's collection of records.
 *
 * @param rec The password record to be added.
 */
    void addRecord(const PasswordRecord& rec );

/**
 * This function creates a new password record using the provided information and adds it to the library's collection of records.
 *
 * @param name The name associated with the password record.
 * @param password The password for the record.
 * @param category The category of the password record.
 * @param website The website associated with the password record.
 * @param login The login or username associated with the password record.
 */
    void createRecord(std::string name, std::string password, std::string category, std::string website, std::string login);

    /**
 * This function deletes the specified password record from the library's collection of records.
 *
 * @param rec The password record to be deleted.
 */
    void deleteRecord(const PasswordRecord& rec);

    /**
 * This function deletes all password records that match the specified category from the library's collection of records.
 *
 * @param categ The category of password records to be deleted.
 */
    void deleteRecordByCategory(const std::string& categ);

    /**
     *
     * This function writes the password library, including password records and categories, to a file.
    * The library is encrypted using the specified file password.
    * The last read time of the library is also updated before writing.
     */
    void write() const;

    /**
     *
     * This function writes the last read time of the password library to a file.
     * The last read time is formatted as "%Y-%m-%d %H:%M:%S" and encrypted using the specified file password.
     */
    void writeLastReadTime() const;

    /**
     *
     * This function reads the password library from a file, including password records and categories.
     * The file is decrypted using the specified file password.
     * It updates the library's last read time and adds the read records and categories to the library.
     *
     * @return True if the read operation is successful, false otherwise.
     */
    bool read();

    /**
 *
 * This function prints the details of a password record, including the name, password, category, website, and login.
 *
 * @param rec The password record to be printed.
 */
    void printRecord(PasswordRecord rec) const;

    /**
 *
 * This function prints all password records in the library by iterating over the collection of records
 * and calling the `printRecord` function for each record.
 */
    void printAllRecords() const;

    /**
 *
 * This function allows the user to search for password records by a specified attribute, such as name, password, category, website, or login.
 * The user is prompted to enter the data for the search. The function iterates over the records and checks if the attribute matches the entered data.
 * If a match is found, the record is printed using the `printRecord` function and added to the vector of found records.
 *
 * @param attribute The attribute to search by (name, password, category, website, or login).
 * @return A vector of pointers to the found password records. Empty if no records are found.
 */
    std::vector<PasswordRecord*> searchRecordBy(const std::string& attribute)const;


        /**
     *
     * This function checks if the given password is unique among the existing password records.
     * It iterates over the records and compares the password with each record's password.
     * If a match is found, indicating that the password is not unique, the function returns false.
     * Otherwise, if no matches are found, it returns true.
     *
     * @param pass The password to check for uniqueness.
     * @return True if the password is unique, false otherwise.
     */
    bool isUnique(const std::string& pass)const;

/**
 *
 * This function sorts the password records in the library based on the specified sorting criteria.
 * It uses the std::sort algorithm along with the SortCompare functor to perform the sorting.
 *
 * @param sortBy A vector of strings specifying the attributes to sort by.
 */
    void sortRecords(const std::vector<std::string>& sortBy);

        // Categories
    void addCategory(const std::string& category);
    void deleteCategory(const std::string& category);
    std::set <std::string> getCategories();

    // Last read time
    /**
 *
 * This function updates the last read time of the password library to the current system time.
 * It uses the std::time function to retrieve the current time in seconds since the epoch and assigns it to the lastReadTime member variable.
 */
    void setLastReadTimeToNow();

    std::time_t getLastReadTime() const;
};

extern PasswordLibrary lib;

#endif //PASSWORDMANAGER_PASSWORDLIBRARY_H
