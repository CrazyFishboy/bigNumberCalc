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

    std::string num = "9999999";
    Big test(num);
    Big test2("999999999999999");
    std::cout << test << std::endl;
    std::cout << test2 << std::endl;

    test.add(test2);
    std::cout << test << std::endl;



    return 0;
}