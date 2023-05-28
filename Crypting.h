//
// Created by Микола Суконнік on 25.05.2023.
//

#ifndef PASSWORDMANAGER_CRYPTING_H
#define PASSWORDMANAGER_CRYPTING_H
#include <iostream>



class Crypting {
private:
  static std::string filePassword;

public:
    static bool process(std::istream* input, std::ostream* output);

     static std::string getFilePassword();
     static void setFilePassword(std::string pass);
};


#endif //PASSWORDMANAGER_CRYPTING_H
