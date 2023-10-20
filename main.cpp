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

    int num1 = -45;
    int num2 = -440;

    Big test(num1);
    Big test2(num2);
    std::cout << test << " " << test.getSize() << " " << test.getCapacity() << test.isNegative() << std::endl;
    std::cout << test2 << " " << test2.getSize() << " " << test2.getCapacity() << test2.isNegative() << std::endl;

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

    
    //test = test * test2;
    //std::cout << test << std::endl;
    //std::cout << "Expected: " << num1*num2 << std::endl;





    return 0;
}