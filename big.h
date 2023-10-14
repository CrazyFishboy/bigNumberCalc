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
Big(unsigned long long val) : Big(std::to_string(val)) {}
Big(std::string val);
Big(const Big& right);
~Big();

std::string getValue() const;
int getSize() const {
    return size;
}
int getDigit(int index) const;

friend std::ostream& operator<<(std::ostream& out, const Big& object);
int& operator[ ](int index);

//add [] overload
//add comparison operators (==, >, <, >=, <=, !=)
//add assignment operator




private:
    int * digits;
    int size;



};




#endif