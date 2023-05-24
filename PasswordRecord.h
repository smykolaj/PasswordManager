//
// Created by Микола Суконнік on 22.05.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDRECORD_H
#define PASSWORDMANAGER_PASSWORDRECORD_H
#include <iostream>
#include <vector>

using namespace std;
class PasswordRecord {
private:
    string name, pass, category, website, login;
public:
    PasswordRecord(){}

    PasswordRecord(
            const string &name, const string &pass, const string &category, const string &website,const string &login) :
                    name(name), pass(pass), category(category), website(website), login(login) {}

    const string &getName() const {
        return name;
    }

    const string &getPass() const {
        return pass;
    }

    const string &getCategory() const {
        return category;
    }

    const string &getWebsite() const {
        return website;
    }

    const string &getLogin() const {
        return login;
    }

    void setName(const string &name) {
        this->name = name;
    }

    void setPass(const string &pass) {
        this->pass = pass;
    }

    void setCategory(const string &category) {
        this->category = category;
    }

    void setWebsite(const string &website) {
        this->website = website;
    }

    void setLogin(const string &login) {
        this->login = login;
    }

};


#endif //PASSWORDMANAGER_PASSWORDRECORD_H
