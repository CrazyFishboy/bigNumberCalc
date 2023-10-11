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


Big::Big(std::string val){
    size = 0;
    digits = nullptr;
    if(val.size() > 0){
        for(unsigned i = 0; i < val.size(); ++i){
            if(!std::isdigit(val[i])){
                std::cout << val[i] << " is not a digit, setting value to 0" << std::endl;
                size = 1;
                digits = new int [1] {0};
                return;
            }
        }

        size = val.size();
        digits = new int [size];
        for(unsigned i = 0; i < val.size(); ++i){
            digits[i] = val[i] - '0';
        }
    } else {
        size = 1;
        digits = new int [1] {0};
    }
}


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


std::string Big::getValue() const {
    if(size > 0){
        std::string value = "";
        for(int i = 0; i < size; ++i){
            value += digits[size];
        }
        return value;
    } else { return "0"; }
}

int Big::getDigit(int index) const {
    if(index >= 0 && index < size){
        return digits[index];
    } else {
        std::cout << "Index out of bounds" << std::endl;
        exit(1);
    }
}







std::ostream& operator<<(std::ostream& out, const Big& object){
    for(int i = 0; i < object.size; ++i){
        out << object.digits[i];
    }
    return out;
}