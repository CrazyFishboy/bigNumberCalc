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

    std::string num = "99999999";
    Big test(num);
    std::cout << test << std::endl;

    ++test;
    std::cout << test << std::endl;

    ++test;
    std::cout << test << std::endl;



    return 0;
}