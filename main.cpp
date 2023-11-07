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

void printComparisons(const test& t1, const test& t2);


int main() {

    long long num1 = 100000000000;
    int num2 = 9;

    Big test("1000000000000000000000000000000");
    Big test2("9");
    std::cout << test << " Size: " << test.getSize() << " Capacity: " << test.getCapacity() << " Negative?: " << test.isNegative() << std::endl;
    std::cout << test2 << " Size: " << test2.getSize() << " Capacity: " << test2.getCapacity() << " Negative?: " << test2.isNegative() << std::endl;

    printComparisons(test1,test2);

    
    std::cout << test.getValue() << " Size: " << test.getSize() << " Capacity: " << test.getCapacity() << " Negative?: " << test.isNegative() << std::endl;

    test = test / test2; // Should be 30 1's

    std::cout << "Calculated: " << test.getValue() << " Size: " << test.getSize() 
        << " Capacity: " << test.getCapacity() << " Negative?: " << test.isNegative() << std::endl;
    
    // std::cout << "Calculated: " << test << std::endl; 
    // std::cout << "Expected: " << num1 / num2 << std::endl;
    
    return 0;
}


void printComparisons(const test& t1, const test& t2){
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
