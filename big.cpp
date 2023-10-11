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