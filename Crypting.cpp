//
// Created by Микола Суконнік on 25.05.2023.
//



#include "Crypting.h"
#include <iostream>



// Function to encode a text file using XOR encryption
bool Crypting::process(std::istream* input, std::ostream* output, int len) // static
{
    std::string password = getFilePassword();
    char ch;
    std::size_t passwordIndex = 0;

    int qty = 0;

    while (input->get(ch) && ( len == 0 || qty < len ) ) {
        ch ^= password[passwordIndex % password.size()];
        output->put(ch);
        ++passwordIndex;
        ++qty;
    }

    return true;
}

std::string Crypting::getFilePassword() {
    return filePassword;
}

void Crypting::setFilePassword(std::string pass) {
    filePassword = pass;
}
