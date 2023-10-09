/**
 * @file big.h
 * @author Josh Gillum
 * @brief Class definition for big number class. Class allows mathematical operations on a long
 * string of numbers
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */



#ifndef BIG_H
#define BIG_H

#include <string>
#include <iostream>

class Big {

public:

Big() : Big("0") {}
Big(std::string val);

Big(unsigned long long val){
    value = std::to_string(val);
}

std::string getValue() const {
    return value;
}




private:
    std::string value;



};




#endif