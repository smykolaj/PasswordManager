//
// Created by Микола Суконнік on 25.05.2023.
//

#ifndef PASSWORDMANAGER_CRYPTING_H
#define PASSWORDMANAGER_CRYPTING_H
#include <iostream>



class Crypting {
private:
   std::string filePassword;

public:

     bool process(std::istream* input, std::ostream* output, int len = 0);

      std::string getFilePassword();
      void setFilePassword(std::string pass);
};


#endif //PASSWORDMANAGER_CRYPTING_H
