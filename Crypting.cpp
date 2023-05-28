//
// Created by Микола Суконнік on 25.05.2023.
//



#include "Crypting.h"
#include <iostream>

std::string Crypting::filePassword;


// Function to encode a text file using XOR encryption
bool Crypting::process(std::istream* input, std::ostream* output) // static
{
    std::string password = getFilePassword();
    char ch;
    std::size_t passwordIndex = 0;

    while (input->get(ch)) {
        ch ^= password[passwordIndex % password.size()];
        output->put(ch);
        ++passwordIndex;
    }

    return true;
}

std::string Crypting::getFilePassword() {
    return filePassword;
}

void Crypting::setFilePassword(std::string pass) {
    filePassword = pass;
}
