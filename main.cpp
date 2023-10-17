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

    std::string num = "00";
    Big test(num);
    Big test2("1");
    std::cout << test << std::endl;
    std::cout << test2 << std::endl;

    if(test == test2){
        std::cout << "They are equal" << std::endl;
    }
    if(test != test2){
        std::cout << "They are not equal" << std::endl;
    }
    if(test > test2){
        std::cout << "Test 1 is greater than test 2" << std::endl;
    }
    if(test < test2){
        std::cout << "Test 1 is less than test 2" << std::endl;
    }
    if(test >= test2){
        std::cout << "Test 1 is greater than or equal to test 2" << std::endl;
    }
    if(test <= test2){
        std::cout << "Test 1 is less than or equal to test 2" << std::endl;
    }

    test.add(test2);
    std::cout << test << std::endl;




    return 0;
}