/**
 * @file big.cpp
 * @author Josh Gillum
 * @brief Function definitions for big class
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "big.h"


/**
 * @brief Convert constructor for big object. Takes a string representing an integer as an argument
 * 
 * @param val, the string representing the integer
 */
Big::Big(std::string val){
    // Initialization
    size = 0;
    digits = nullptr;
    if(val.size() > 0){ // Makes sure that val is non-empty
        // Loops through each character in val, making sure that they are all digits
        for(unsigned i = 0; i < val.size(); ++i){
            if(!std::isdigit(val[i])){ // Sets the value to 0 and returns if a character is not a digit
                std::cout << val[i] << " is not a digit, setting value to 0" << std::endl;
                size = 1;
                digits = new int [1] {0};
                return;
            }
        }

        // If all the characters are digits, set the size to that of val,
        // then copy the digits to the array
        size = val.size();
        digits = new int [size];
        for(unsigned i = 0; i < val.size(); ++i){
            digits[i] = val[i] - '0';
        }
    } else { // Sets value to 0 if val is empty
        size = 1;
        digits = new int [1] {0};
    }
}


/**
 * @brief Copy constructor for Big object. Takes an already created object as its parameter
 * 
 * @param right, the object being copied
 */
Big::Big(const Big& right) {
    int rightSize = right.getSize();
    if(rightSize > 0){ // Makes sure that the right object has some value
        if(size != rightSize){ // If this object is a different size than the right object
            if(digits != nullptr){ // If digits points to an array
                delete [] digits;
            }

            // Set this-> size to that of the right object and dynamically allocate a new array
            size = rightSize;
            digits = new int[size];
        }

        // Copy each element of the right object to this object
        for(int i = 0; i < size; ++i){
            digits[i] = right.getDigit(i);
        }
    } else { // Sets the value of this object to 0
        if(digits != nullptr){
            delete [] digits;
        }
        size = 1;
        digits = new int [size] {0};
    }
}

Big::~Big(){
    delete [] digits;
    digits = nullptr;
}


/**
 * @brief Returns the value stored in digits as a string
 * 
 * @return std::string, the value as a string
 */
std::string Big::getValue() const {
    if(size > 0 && digits != nullptr){ // makes sure digits is storing something
        std::string value = "";
        // Adds each value to the string to be returned
        for(int i = 0; i < size; ++i){
            value += digits[size];
        }
        return value;
    } else { return "0"; }
}


/**
 * @brief Returns the digit at a specific index
 * 
 * @param index, the index whose value is to be returned
 * @return int, the value at the index
 */
int Big::getDigit(int index) const {
    if(index >= 0 && index < size){ // Ensures that the index is within the bounds of the array
        return digits[index];
    } else {
        std::cout << "Index out of bounds" << std::endl;
        exit(1);
    }
}


/**
 * @brief Overloads the << operator, allowing easy display of the contents of digits
 * 
 * @param out, the ostream object being modified
 * @param object, the object being added to the string
 * @return std::ostream&, the same ostream object being modified
 */
std::ostream& operator<<(std::ostream& out, const Big& object){
    // Adds each value in digits to the ostream
    for(int i = 0; i < object.size; ++i){
        out << object.digits[i];
    }
    return out;
}

int& Big::operator[ ](int index){
    if(size > 0){
        if(index < size){
            return digits[index];
        } else {
            std::cout << "Index out of bounds" << std::endl;
            exit(1);
        }
    } else {
            std::cout << "Size is 0" << std::endl;
            exit(1);
    }
}