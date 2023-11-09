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

void printComparisons(const Big& t1, const Big& t2);


int main() {

    //long long num1 = 11;
    //int num2 = 9;

    Big test1("-0");
    Big test2("18");
    std::cout << test1 << " Size: " << test1.getSize() << " Capacity: " << test1.getCapacity() << " Negative?: " << test1.isNegative() << std::endl;
    std::cout << test2 << " Size: " << test2.getSize() << " Capacity: " << test2.getCapacity() << " Negative?: " << test2.isNegative() << std::endl;

    printComparisons(test1,test2);

    
    //std::cout << test1.getValue() << " Size: " << test1.getSize() << " Capacity: " << test1.getCapacity() << " Negative?: " << test1.isNegative() << std::endl;

    //test1 = test1 % test2;

    //std::cout << "Calculated: " << test1.getValue() << " Size: " << test1.getSize() 
    //    << " Capacity: " << test1.getCapacity() << " Negative?: " << test1.isNegative() << std::endl;
    
    // std::cout << "Calculated: " << test << std::endl; 
    // std::cout << "Expected: " << num1 / num2 << std::endl;
    


    std::cout << test1.binary() << std::endl;

    
    return 0;
}


void printComparisons(const Big& t1, const Big& t2){
    if(t1 == t2){
        std::cout << "They are equal" << std::endl;
    }
    if(t1 != t2){
        std::cout << "They are not equal" << std::endl;
    }
    if(t1 > t2){
        std::cout << "Test 1 is greater than test 2" << std::endl;
    }
    if(t1 < t2){
        std::cout << "Test 1 is less than test 2" << std::endl;
    }
    if(t1 >= t2){
        std::cout << "Test 1 is greater than or equal to test 2" << std::endl;
    }
    if(t1 <= t2){
        std::cout << "Test 1 is less than or equal to test 2" << std::endl;
    }
}
