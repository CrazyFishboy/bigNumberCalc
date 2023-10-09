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

short num = 1;
Big test(num);

std::cout << test.getValue() << std::endl;
std::cout << sizeof(long) << std::endl;



    return 0;
}