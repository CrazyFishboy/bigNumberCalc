/**
 * @file main.cpp
 * @author Josh Gillum
 * @brief Utility for working with really large numbers
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>

#include "big.h"


int main() {

    //long num = 1234567890;
    std::string num = "1234";
    Big test(num);

    std::cout << test << std::endl;

    std::cout << "Size: " << test.getSize() << std::endl; 
    std::cout << "Digit: " << test.getDigit(1) << std::endl;




    return 0;
}