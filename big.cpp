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
        bool nonZeroFound = false;
        int startIndex = 0;
        for(unsigned i = 0; i < val.size(); ++i){
            if(!std::isdigit(val[i])){ // Sets the value to 0 and returns if a character is not a digit
                std::cout << val[i] << " is not a digit, setting value to 0" << std::endl;
                size = 1;
                digits = new int [1] {0};
                return;
            } else {
                if(!nonZeroFound){
                    if(val[i] != '0'){
                        nonZeroFound = true;
                        startIndex = i;
                    }
                }
            }
        }



        // If all the characters are digits, set the size to that of val,
        // then copy the digits to the array
        if(nonZeroFound){
            size = val.size() - startIndex;
            digits = new int [size];
            for(unsigned i = startIndex, digitIndex = 0; i < val.size(); ++i, ++digitIndex){
                digits[digitIndex] = val[i] - '0';
            }
        } else {
            size = 1;
            digits = new int [1] {0};
        }
    } else { // Sets value to 0 if val is empty
        size = 1;
        digits = new int [1] {0};
    }
}


Big::Big(const Big& right) {
    int rightSize = right.getSize();
    if(rightSize > 0){ // Makes sure that the right object has some value

        // Set this-> size to that of the right object and dynamically allocate a new array
        size = rightSize;
        digits = new int[size];

        // Copy each element of the right object to this object
        for(int i = 0; i < size; ++i){
            digits[i] = right.getDigit(i);
        }
    } else { // Sets the value of this object to 0
        size = 1;
        digits = new int [size] {0};
    }
}



//This needs to become the assignment operator
/**
 * @brief Copy constructor for Big object. Takes an already created object as its parameter
 * 
 * @param right, the object being copied
 */
/*
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
*/

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


/**
 * @brief Overload [] operator. Returns the value of the digits
 * array at the specified index
 * 
 * @param index, the desired index
 * @return int&, a reference to the value stored at the specified index
 */
int& Big::operator[ ](int index){
    if(size > 0){ // Ensures that there is something in the array
        if(index >= 0 && index < size){ // Ensures the bounds of the array are not exceeded
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


/**
 * @brief Adds the two values provided as arguments and stores them in a third object, which
 * it returns
 * 
 * @param left, the object on the left side of the plus sign 
 * @param right, the object on the right side of the plus sign
 *      example: left + right
 * @return Big, the object being returned. Stores the sum of left and right
 */
Big operator+(const Big& left, const Big& right){
    int lSize = left.getSize(); // Stores the size of the left object, so repeated calls do not need to be performed
    int rSize = right.getSize(); // Same thing but with the right object
    if(rSize > lSize){
        return right + left;
    }
    if(rSize > 0 && lSize > 0){ // Makes sure that both objects store a value

        std::string value = ""; // Stores the sum as a string. Used as the constructor paramenter for the return object
        int indexL = lSize -1; // left object
        int indexR = rSize - 1; // Other object
        int overflow = 0; // When left + right > 9, this is extra above 9
        int working = 0; // The working sum. Stores the sum of overflow, left, and right, before operations

        while(indexL >= 0){ // Loops through each object 
            if(indexR >= 0){
                working = left.getDigit(indexL) + right.getDigit(indexR) + overflow;
                overflow = working / 10;
                working %= 10;
                value = std::to_string(working) + value;
            } else if(overflow > 0){
                working = left.getDigit(indexL) + overflow;
                overflow = working / 10;
                working %= 10;
                value = std::to_string(working) + value;
            } else {
                working = left.getDigit(indexL);
                value = std::to_string(working) + value;
            }
            --indexL;
            --indexR;
        }   
        std::cout << value << std::endl;
        return Big(value);
    } else {
        return (Big("0"));
    }
}


/**
 * @brief Overloaded prefix ++ operator. Increases the total value of the digits array
 * by 1, starting from the last element
 * 
 * @return Big, a reference to this object
 */
Big& Big::operator++(){
    int index = size;
    do {
        --index;
        if(index < 0){
            addDigit();
            digits[0] = 0;
            index = 0;
        }
        digits[index]++;
        //std::cout << digits[index] << std::endl;
    } while(digits[index] % 10 == 0 && digits[index] != 0);
    for(int i = 0; i < size; ++i){
        digits[i] %= 10;
    }
    return *this;
}


/**
 * @brief Overloads postfix ++ operator. Increases the total value of the digits array
 * by 1, starting from the last element
 * 
 * @return Big, a copy of this object made before incrementing it
 */
Big Big::operator++(int){
    Big temp = *this;
    int index = size;
    do {
        --index;
        if(index < 0){
            addDigit();
            digits[0] = 0;
            index = 0;
        }
        digits[index]++;
        //std::cout << digits[index] << std::endl;
    } while(digits[index] % 10 == 0 && digits[index] != 0);
    for(int i = 0; i < size; ++i){
        digits[i] %= 10;
    }
    return temp;
}


bool Big::operator==(const Big& object) const{
    if(this->size != object.getSize()){
        return false;
    } else {
        for(int i = 0; i < this->size; ++i){
            if(digits[i] != object.getDigit(i)){
                return false;
            }
        }
        return true;
    }
}



bool Big::operator!=(const Big& object) const{
    if(this->size != object.getSize()){
        return true;
    } else {
        for(int i = 0; i < this->size; ++i){
            if(digits[i] != object.getDigit(i)){
                return true;
            }
        }
        return false;
    }
}


bool Big::operator>(const Big& object) const {
    if(size > object.getSize()) {
        return true;
    } else if(size < object.getSize()){
        return false;
    } else {
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                return true;
            } else if(digits[i] < object.getDigit(i)){
                return false;
            }
        }
        return false;
    }
}


bool Big::operator>=(const Big& object) const {
    if(size > object.getSize()) {
        return true;
    } else if(size < object.getSize()){
        return false;
    } else {
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                return true;
            } else if(digits[i] < object.getDigit(i)){
                return false;
            }
        }
        return true;
    }
}

bool Big::operator<(const Big& object) const {
    if(size > object.getSize()) {
        return false;
    } else if(size < object.getSize()){
        return true;
    } else {
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                return false;
            } else if(digits[i] < object.getDigit(i)){
                return true;
            }
        }
        return false;
    }
}


bool Big::operator<=(const Big& object) const {
    if(size > object.getSize()) {
        return false;
    } else if(size < object.getSize()){
        return true;
    } else {
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                return false;
            } else if(digits[i] < object.getDigit(i)){
                return true;
            }
        }
        return true;
    }
}


void Big::add(const Big& right){
    int rSize = right.getSize();
    if(rSize > 0 && this->size > 0){
        if(rSize > this->size){
            addDigit(rSize-(this->size));
        }
        int indexL = this->size -1; // This object
        int indexR = rSize - 1; // Other object
        int overflow = 0; // When left + right > 9, this is extra above 9

        while(indexL >= 0){
            if(indexR >= 0){
                digits[indexL] += right.getDigit(indexR) + overflow;
                overflow = digits[indexL] / 10;
                digits[indexL] %= 10;
            } else if(overflow > 0){
                digits[indexL] += overflow;
                overflow = digits[indexL] / 10;
                digits[indexL] %= 10;
            } else {
                break;
            }
            --indexL;
            --indexR;
            if(indexL < 0 && indexR >= 0){
                addDigit();
                indexL = 0;
            }
            if(indexL == 0){
                if(indexR >= 0){
                    int temp = digits[indexL] + right.getDigit(indexR) + overflow;
                    if(temp > 9){
                        addDigit();
                        indexL = 1;
                    }
                } else {
                    int temp = digits[indexL] + overflow;
                    if(temp > 9){
                        addDigit();
                        indexL = 1;
                    }
                }
            }
        }   
    }
}



/**
 * @brief Increases the size of the array, with all the new elements
 * at the beginning of the array
 * 
 * @param num, the number of elements to increase the array by
 */
void Big::addDigit(int num){
    int * temp = digits; // Holds the address of the current array
    digits = new int [size+num]; // Allocates a new array of the correct size

    // Copies all of the elements from the old array to the new one
    for(int i = 0; i < size+num; ++i){
        if(i < num){ // If the elements are before the start of the old array, fill with 0's
            *(digits+i) = 0;
        } else {
            *(digits+i) = *(temp+i-num);
        }
    }
    // Frees the old array
    delete [] temp;
    temp = nullptr;
    size += num;
}



/**
 * @brief Increases the size of the array, with all the new elements
 * at the end of the array
 * 
 * @param num, the number of elements to increase the array by
 */
void Big::appendDigit(int num){
    int * temp = new int [size+num]; // The new array

    // Copies the old elements to the new array
    for(int i = 0; i < size + num; ++i){
        if(i >= size){ // Add trailing zeros
            *(temp+i) = 0;
        } else {
            *(temp+i) = *(digits+i);
        }
    }

    delete [] digits; // Frees the old array
    digits = temp; // Updates the pointer, to point to the new array
    size += num;
}
