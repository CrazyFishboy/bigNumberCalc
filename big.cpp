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
    for(unsigned i = 0; i < val.size(); ++i){
        if(!std::isdigit(val[i])){
            std::cout << val[i] << " is not a digit, setting value to 0" << std::endl;
            value = "0";
            return;
        }
    }
    value = val;
}