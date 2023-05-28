//
// Created by Микола Суконнік on 22.05.2023.
//

#include "PasswordRecord.h"

const string &PasswordRecord::getName() const {
    return name;
}

const string &PasswordRecord::getPass() const {
    return pass;
}

const string &PasswordRecord::getCategory() const {
    return category;
}

const string &PasswordRecord::getWebsite() const {
    return website;
}

const string &PasswordRecord::getLogin() const {
    return login;
}

void PasswordRecord::setName(const string &name) {
    this->name = name;

}

void PasswordRecord::setPass(const string &pass) {
    this->pass = pass;
}

void PasswordRecord::setCategory(const string &category) {
    this->category = category;
}

void PasswordRecord::setWebsite(const string &website) {
    this->website = website;
}

void PasswordRecord::setLogin(const string &login) {
    this->login = login;
}

