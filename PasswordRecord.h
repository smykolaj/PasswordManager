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

    const string &getName() const;
    const string &getPass() const;
    const string &getCategory() const;
    const string &getWebsite() const;
    const string &getLogin() const;

    void setName(const string &name);
    void setPass(const string &pass);
    void setCategory(const string &category);
    void setWebsite(const string &website);
    void setLogin(const string &login);

};


#endif //PASSWORDMANAGER_PASSWORDRECORD_H
