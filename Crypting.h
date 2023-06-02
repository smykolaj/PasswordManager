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
    /**
 *
 * This function processes the input stream and encrypts/decrypts the data using the file password.
 * It reads characters from the input stream and performs bitwise XOR operation with the corresponding character
 * from the file password. The resulting character is then written to the output stream.
 * The process continues until the end of the input stream is reached or the specified length is reached (if len is non-zero).
 *
 * @param input  Pointer to the input stream to read data from.
 * @param output Pointer to the output stream to write the processed data to.
 * @param len    The maximum length of data to process. Set to 0 to process the entire input stream.
 *
 * @return True if the processing is successful, false otherwise.
 */
     bool process(std::istream* input, std::ostream* output, int len = 0);

      std::string getFilePassword();
      void setFilePassword(std::string pass);
};


#endif //PASSWORDMANAGER_CRYPTING_H
