//
// Created by Микола Суконнік on 25.05.2023.
//



#include "Crypting.h"
#include <iostream>

std::string password = "123";

// Function to encode a text file using XOR encryption
bool Crypting::process(std::istream* input, std::ostream* output) // static
{

    char ch;
    std::size_t passwordIndex = 0;

    while (input->get(ch)) {
        ch ^= password[passwordIndex % password.size()];
        output->put(ch);
        ++passwordIndex;
    }

    return true;
}