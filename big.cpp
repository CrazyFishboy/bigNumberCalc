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

int Big::capacityIncrement = 20;


/**
 * @brief Convert constructor for big object. Takes a string representing an integer as an argument
 * 
 * @param val, the string representing the integer
 */
Big::Big(std::string val){
    // Initialization
    size = 0;
    capacity = capacityIncrement;
    digits = nullptr;
    negative = false;
    base = dec;
    displayBase = false;
    if(val.size() > 0){ // Makes sure that val is non-empty
        // Loops through each character in val, making sure that they are all digits
        bool nonZeroFound = false;
        int startIndex = 0;
        for(unsigned i = 0; i < val.size(); ++i){
            if(!std::isdigit(val[i])){ // Sets the value to 0 and returns if a character is not a digit
                if(val[i] == '-' && !negative){
                    negative = true;
                } else {
                    size = 1;
                    negative = false;
                    digits = new int [capacity] {0};
                    throw InvalidCharacter();
                }
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
            if(size > capacity){
                capacity = size;
            }
            digits = new int [capacity];
            for(unsigned i = startIndex, digitIndex = 0; i < val.size(); ++i, ++digitIndex){
                digits[digitIndex] = val[i] - '0';
            }
        } else {
            size = 1;
            negative = false;
            digits = new int [capacity] {0};
        }
    } else { // Sets value to 0 if val is empty
        size = 1;
        negative = false;
        digits = new int [capacity] {0};
    }
}


Big::Big(const Big& right) {
    int rightSize = right.getSize();
    if(rightSize > 0){ // Makes sure that the right object has some value
        base = right.getBase();
        base = right.baseShown();

        // Set this-> size to that of the right object and dynamically allocate a new array
        size = rightSize;
        capacity = right.getCapacity();
        if(capacity < capacityIncrement){
            capacity = capacityIncrement;
        }
        negative = right.isNegative();
        digits = new int[capacity];

        // Copy each element of the right object to this object
        for(int i = 0; i < size; ++i){
            digits[i] = right.getDigit(i);
        }
    } else { // Sets the value of this object to 0
        size = 1;
        capacity = capacityIncrement;
        negative = false;
        digits = new int [capacity] {0};
        base = dec;
        displayBase = false;
        throw EmptyArray();
    }
}



Big::~Big(){
    if(digits != nullptr){
        delete [] digits;
    }
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
        if(negative){
            value = "-";
        }


        if(base == Big::bin){ //binary
        if(displayBase){
            value += "0b";
        }
        value += binary();
    } else if(base == Big::oct){ // octal
        if(displayBase){
            value += "0";
        }
        value += octal();
    } else if(base == Big::hex){ // hexadecimal
        if(displayBase){
            value += "0x";
        }
        value += hexadecimal();
    } else { // decimal
        for(int i = 0; i < size; ++i){
            value += std::to_string(digits[i]);
        }
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
        throw OutOfBounds();
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

    if(object.isNegative()){
        out << "-";
    }

    if(object.getBase() == Big::bin){ //binary
        if(object.baseShown()){
            out << "0b";
        }
        out << object.binary();
    } else if(object.getBase() == Big::oct){ // octal
        if(object.baseShown()){
            out << "0";
        }
        out << object.octal();
    } else if(object.getBase() == Big::hex){ // hexadecimal
        if(object.baseShown()){
            out << "0x";
        }
        out << object.hexadecimal();
    } else { // decimal
        for(int i = 0; i < object.size; ++i){
            out << object.digits[i];
        }
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
            throw OutOfBounds();
        }
    } else {
            throw EmptyArray();
    }
}


/**
 * @brief Assigns the value of the right object to this object
 * 
 * @param right, the object being copied
 */
void Big::operator=(const Big& right){
    int rightSize = right.getSize();
    if(rightSize > 0){ // Makes sure that the right object has some value
        if(size != rightSize){ // If this object is a different size than the right object
            if(digits != nullptr){ // If digits points to an array
                delete [] digits;
            }

            // Set this-> size to that of the right object and dynamically allocate a new array
            size = rightSize;
            capacity = right.getCapacity();
            if(capacity < capacityIncrement) {
                capacity = capacityIncrement;
            }
            digits = new int[capacity] {0};
        }

        negative = right.isNegative();
        // Copy each element of the right object to this object
        for(int i = 0; i < size; ++i){
            digits[i] = right.getDigit(i);
        }
    } else { // Sets the value of this object to 0
        if(digits != nullptr){
            delete [] digits;
        }
        size = 1;
        capacity = capacityIncrement;
        negative = false;
        digits = new int [capacity] {0};
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
    if(rSize > lSize){ // Ensures that the left object is always >= right object, in size
        return right + left;
    }
    if(!left.isNegative() && right.isNegative()){
        return left - right;
    } else if(left.isNegative() && !right.isNegative()){
        return right - left;
    } else if(left.isNegative() && right.isNegative()){
        Big rCopy(right);
        rCopy.flipSign();
        Big lCopy(left);
        lCopy.flipSign();
        Big val(lCopy + rCopy);
        val.flipSign();
        return val;
    } else {
        if(rSize > 0 && lSize > 0){ // Makes sure that both objects store a value
            std::string value = ""; // Stores the sum as a string. Used as the constructor paramenter for the return object
            int indexL = lSize -1; // left object
            int indexR = rSize - 1; // Other object
            int overflow = 0; // When left + right > 9, this is extra above 9
            int working = 0; // The working sum. Stores the sum of overflow, left, and right, before operations

            while(indexL >= 0 || overflow > 0){ // Loops through each object 
                if(indexR >= 0){ // If there is still a value in the right object
                    working = left.getDigit(indexL) + right.getDigit(indexR) + overflow; // Get the sum
                    overflow = working / 10; // Find value for next power of 10
                    working %= 10; // Find leftover for this value
                    value = std::to_string(working) + value; // Add value to string
                } else if(indexL >= 0){ // If there are no more values in right object, but still values in overflow
                    working = left.getDigit(indexL) + overflow; // Sums left and overflow
                    overflow = working / 10;
                    working %= 10;
                    value = std::to_string(working) + value;
                } else { // If there are only values left in the left object
                    working = overflow;
                    overflow /= 10;
                    working %= 10;
                    value = std::to_string(working) + value;
                }
                --indexL;
                --indexR;
            }   
            return Big(value); // Creates a big object with the sum as its value
        } else {
            return (Big("0"));
        }
    }
}

/**
 * @brief Adds the two values provided as arguments and stores them in a third object, which
 * it returns
 * 
 * @param left, the object on the left side of the plus sign 
 * @param right, the object on the right side of the plus sign
 *      example: left - right
 * @return Big, the object being returned. Stores the sum of left and right
 */
Big operator-(const Big& left, const Big& right){
    int lSize = left.getSize(); // Stores the size of the left object, so repeated calls do not need to be performed
    int rSize = right.getSize(); // Same thing but with the right object
    if(rSize > lSize){ // Ensures that the left object is always >= right object, in size
        Big valBig(right - left);
        valBig.flipSign();
        return valBig;
    }

    // Checks negative signs and changes the equation accordingly
    if(!left.isNegative() && right.isNegative()){ // positive - negative
        Big rCopy(right);
        rCopy.flipSign();
        return left + rCopy;
    } else if(left.isNegative() && !right.isNegative()){ // negative - positive
        Big valBig(left + right);
        valBig.flipSign();
        return valBig;
    } else if(left.isNegative() && right.isNegative()){ // negative - negative
        Big rCopy(right);
        rCopy.flipSign();
        Big lCopy(left);
        lCopy.flipSign();
        return rCopy - lCopy;
    } else { // Actual subtraction operation
        if(rSize > 0 && lSize > 0){ // Makes sure that both objects store a value
            int indexL = lSize -1; // left object
            int indexR = rSize - 1; // Other object
            Big val(left); // Object that will be returned

            while(indexL >= 0 || indexR >= 0){ // Loops through each object
                if(indexL < 0){
                    val.addDigit();
                    val[0] = right.getDigit(indexR);
                } else if(indexR >= 0){ // If there is still a value in the right object
                    if(val[indexL] >= right.getDigit(indexR)){ // If the current index can subtract the right index
                        val[indexL] -= right.getDigit(indexR);
                    } else { // Borrow from next digit
                        int counter = 1;
                        while(val[indexL - counter] == 0){ // Determines how many places over to go
                            if(indexL - counter == 0 && val[indexL - counter] == 0){
                                throw Big::OutOfBounds();
                            }
                            ++counter;
                        }
                        --val[indexL - counter]; // Takes 1 from the digit being borrowed from
                        --counter;
                        while(counter > 0){ // Sets the digits inbetween to 9
                            val[indexL - counter] = 9;
                            --counter;
                        }
                        val[indexL] += 10; // Adds 10 to the current digit
                        --counter;

                        val[indexL] -= right.getDigit(indexR);
                    }
                }
                --indexL;
                --indexR;
            }

            // Removes leading zeros from the number in the case where the difference has less digits the larger term
            int counter = 0;
            int index = 0;
            while(val.digits[index] == 0 && index < (val.size - 1)){ // Finds how many leading zeros there are
                ++counter;
                ++index;
            }
            val.size -= counter; // Updates size to not include the non-leading zeros
            for(int i = 0; i < val.size; ++i, ++index){ // Moves the non-zeros to the beginning of the array
                val.digits[i] = val.digits[index];
            }
            return val;
        } else {
            return (Big("0"));
        }
    }
}


/**
 * @brief Returns an object that is the prduct of the two arguments
 * 
 * @param left, the left term in the operation
 * @param right, the right term in the operation
 * @return Big, a big object, whose value is the product of left and right
 */
Big operator*(const Big& left, const Big& right){
    int lSize = left.getSize();
    int rSize = right.getSize();
    if(rSize > lSize){
        return right * left;
    }
    const int productsSize = 20; // Number of elements in the products array
    Big * products = new Big [productsSize];
    int productsIndex = 0; // Current index in products array
    for(int leftIndex = lSize - 1; leftIndex >= 0; --leftIndex){ // Loops through each digit of the left
        for(int rightIndex = rSize -1; rightIndex >= 0; --rightIndex){ // Loops through each digit of the right
            if(productsIndex >= productsSize){ // If the array of products is full, condense it
                for(int i = 1; i < productsSize; ++i){
                    products[0] = products[0] + products[i];
                }
                productsIndex = 1;
            }
            //Big leftVal = left.getDigit(leftIndex);
            int leftPower = lSize - 1 - leftIndex; // The power of the digit of the left object
            //leftVal.appendDigit(leftPower);

            //Big rightVal = right.getDigit(rightIndex);
            int rightPower = rSize - 1 - rightIndex; // The power of the digit of the right object
            //rightVal.appendDigit(rightPower);

            int product = left.getDigit(leftIndex) * right.getDigit(rightIndex);
            Big tempProduct(product);
            tempProduct.appendDigit(leftPower + rightPower); // Adds a number of 0's to the end of the number equal to the sum of the powers
            products[productsIndex] = tempProduct;
            
            //std::cout << left.getDigit(leftIndex) << " ( " << leftVal << " ) * " << right.getDigit(rightIndex) << " ( " 
            //<< rightVal << " ) = " << products[productsIndex] << std::endl;
            ++productsIndex;
        }
    }
    for(int i = 1; i < productsIndex; ++i){
        products[0] = products[0] + products[i];
        /*
        std::cout << products[0];
        if(i >= productsIndex -1){
            std::cout << std::endl;
        } else {
            std::cout << ',' << std::flush;
        }
        */
    }
    //std::cout << std::endl;

    if((left.isNegative() && !right.isNegative()) || (!left.isNegative() && right.isNegative())){
        if(!products[0].isNegative()){
            products[0].flipSign();
        }
    } else {
        if(products[0].isNegative()){
            products[0].flipSign();
        }
    }
    return products[0];
}


/**
 * @brief Division operator. Performs division, dividing the left object by the right, and returns an object for the result
 * Note that division is performed in a similar fashion to integer division, such that, any remainder is discarded.
 * Ex: 5 / 2 = 2 ... 27 / 8 = 3 ... 27 / 9 = 3
 * 
 * @param left, the object on the left of the '/' sign. The number being divided
 * @param right, the object on the right of the '/' sign. The number being divided into
 * @return Big, an object storing the result
 */
Big operator/(const Big& left, const Big& right){
    if(left.negative || right.negative){ // Accordingly flips the signs and recalls the division function
        Big lCopy = left;
        Big rCopy = right;
        if(left.negative){
            lCopy.flipSign();
        }
        if(right.negative){
            rCopy.flipSign();
        }
        Big answer = lCopy / rCopy;
        if(!(left.negative && right.negative)){
            answer.flipSign();
        }
        return answer;
    }
    if(right > left){ // If the divisor is larger than the divided, it can't possibly be greater than 0
        return 0;
    } else if (right == left){ // If they are equal, it must be 1
        return 1;
    } else {
        Big check = right;
        Big divisor = 0;
        Big counter = 0;
        Big power = 1; // Used for tracking the number of the value being worked with
        while(check < left){ // Finds the largest value such that check * 10^x is smaller than the left object
            check.appendDigit(); // Multiplies by 10
            power.appendDigit();
        }
        check.truncate(); // Power of 10 is one higher than it should be, so these fix it
        power.truncate();
        while(check >= right){ // Ensures that check is never less than the original divisor
            // std::cout << "Check: " << check << std::endl;
            while(divisor + check <= left){ // Continues while the working value is less than the divided
                
                divisor = divisor + check; // Adds 10^power copies of left to the divispr 
                counter = counter + power;
                // std::cout << "Divisor: " << divisor << std::endl;
            }
            power.truncate(); // Divides each value by 10
            check.truncate();
        }
        return counter;
    }
}



Big operator%(const Big& left, const Big& right){
    if(left.negative || right.negative){ // Accordingly flips the signs and recalls the division function
        Big lCopy = left;
        Big rCopy = right;
        if(left.negative){
            lCopy.flipSign();
        }
        if(right.negative){
            rCopy.flipSign();
        }
        Big answer = lCopy / rCopy;
        if(!(left.negative && right.negative)){
            answer.flipSign();
        }
        return answer;
    }
    if(right > left){ 
        return left;
    } else if (right == left){ 
        return 0;
    } else {
        Big check = right;
        Big divisor = 0;
        Big counter = 0;
        Big power = 1; // Used for tracking the number of the value being worked with
        while(check < left){ // Finds the largest value such that check * 10^x is smaller than the left object
            check.appendDigit(); // Multiplies by 10
            power.appendDigit();
        }
        check.truncate(); // Power of 10 is one higher than it should be, so these fix it
        power.truncate();
        while(check >= right){ // Ensures that check is never less than the original divisor
            // std::cout << "Check: " << check << std::endl;
            while(divisor + check <= left){ // Continues while the working value is less than the divided
                
                divisor = divisor + check; // Adds 10^power copies of left to the divispr 
                counter = counter + power;
                // std::cout << "Divisor: " << divisor << std::endl;
            }
            power.truncate(); // Divides each value by 10
            check.truncate();
        }
        return left - divisor;
    }
}


/**
 * @brief Overloaded prefix ++ operator. Increases the total value of the digits array
 * by 1, starting from the last element
 * 
 * @return Big, a reference to this object
 */
Big& Big::operator++(){
    if(negative == true){
        negative = false;
        --*this;
        negative = true;
        return *this;
    }
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
    ++*this;
    return temp;
}


Big& Big::operator--(){
    if(negative == true){
        negative = false;
        ++*this;
        negative = true;
        return *this;
    }
    if(size > 0){ // Makes sure that this object stores a value
        int index = size -1;
        if(size == 1 && negative == false && digits[0] == 0){
            negative = true;
            digits[0] = 1;
        } else if(digits[index] > 0){
            --digits[index];
        } else {
            int counter = 1;
            while(digits[index - counter] == 0){ // Determines how many places over to go
                if(index - counter == 0 && digits[index - counter] == 0){
                    throw OutOfBounds();
                }
                ++counter;
            }
            --digits[index - counter]; // Takes 1 from the digit being borrowed from
            --counter;
            while(counter > 0){ // Sets the digits inbetween to 9
                digits[index - counter] = 9;
                --counter;
            }
            digits[index] += 10; // Adds 10 to the current digit
            --counter;

            --digits[index];
        }

        int counter = 0;
        index = 0;
        while(digits[index] == 0 && index < (size - 2)){
            ++counter;
            ++index;
        }
        size -= counter;
        for(int i = 0; i < size; ++i, ++index){
            digits[i] = digits[index];
        }
        return *this;
    } else {
        throw EmptyArray();
    }
}

Big Big::operator--(int){
    Big temp(*this);
    --*this;
    return temp;
}



/**
 * @brief Allows comparison between two big objects, as to whether they store equal values
 * 
 * @param object, the object being compared to the current one
 * @return true, they are the same
 * @return false, they are not the same
 */
bool Big::operator==(const Big& object) const{
    if(this->size != object.getSize()){ // If the two objects are different sizes, there is no way for them to be the same value
        return false;
    } else if(this->negative != object.isNegative()){
        return false;
    } else {
        // Checks each value in each array, as to whether they are the same
        for(int i = 0; i < this->size; ++i){
            if(digits[i] != object.getDigit(i)){
                return false;
            }
        }
        return true;
    }
}



/**
 * @brief Checks whether this object is not equal to another object
 * 
 * @param object, the object comparing with
 * @return true, the objects are not equal
 * @return false, the objects are equal
 */
bool Big::operator!=(const Big& object) const{
    if(this->size != object.getSize()){ // If they are not the same size, they can not possibly be qual
        return true;
    } else if(this->negative != object.isNegative()){
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


/**
 * @brief Checks whether this object is greater than a provided object
 * 
 * @param object, the object comparing with
 * @return true, this object is greater
 * @return false, this object is equal to or less than the other
 */
bool Big::operator>(const Big& object) const {
    if(!negative && object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return true;
    } else if(negative && !object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return false;
    } else if(size > object.getSize()){ // If this object is greater in size, it must be greater in value
        if(negative){
            return false;
        } else {
            return true;
        }
    } else if(size < object.getSize()){ // Likewise, if it is smaller in size, it must be lesser in value
        if(negative){
            return true;
        } else {
            return false;
        }
    } else {
        // For loop ends early if the two digits are not the same
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                if(negative){
                    return false;
                } else {
                    return true;
                }
            } else if(digits[i] < object.getDigit(i)){
                if(negative){
                    return true;
                } else {
                    return false;
                }
            }
        }
        // If the loop does not end early, the objects must be the same, meaning
        // that this object is not greater
        return false;
    }
}


/**
 * @brief Checks whether this object is greater than or equal to a provided object
 * 
 * @param object, the object comparing with
 * @return true, this object is greater than or equal to the provided one
 * @return false, this object is less than the provided object
 */
bool Big::operator>=(const Big& object) const {
    if(!negative && object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return true;
    } else if(negative && !object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return false;
    } else if(size > object.getSize()){ // If this object is greater in size, it must be greater in value
        if(negative){
            return false;
        } else {
            return true;
        }
    } else if(size < object.getSize()){ // Likewise, if it is smaller in size, it must be lesser in value
        if(negative){
            return true;
        } else {
            return false;
        }
    } else {
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                if(negative){
                    return false;
                } else {
                    return true;
                }
            } else if(digits[i] < object.getDigit(i)){
                if(negative){
                    return true;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
}



/**
 * @brief Checks whether this object is less than the provided object
 * 
 * @param object, the object comparing with
 * @return true, this object is less than the provided one
 * @return false, this object is greater than the provided object
 */
bool Big::operator<(const Big& object) const {
    if(!negative && object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return false;
    } else if(negative && !object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return true;
    } else if(size > object.getSize()){ // If this object is greater in size, it must be greater in value
        if(negative){
            return true;
        } else {
            return false;
        }
    } else if(size < object.getSize()){ // Likewise, if it is smaller in size, it must be lesser in value
        if(negative){
            return false;
        } else {
            return true;
        }
    } else {
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                if(negative){
                    return true;
                } else {
                    return false;
                }
            } else if(digits[i] < object.getDigit(i)){
                if(negative){
                    return false;
                } else {
                    return true;
                }
            }
        }
        return false;
    }
}



/**
 * @brief Checks whether this object is less than or equal to the provided object
 * 
 * @param object, the object comparing with
 * @return true, this object is less than or equal to the provided one
 * @return false, this object is greater than the provided object
 */
bool Big::operator<=(const Big& object) const {
    if(!negative && object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return false;
    } else if(negative && !object.isNegative()){ // Likewise, if it is smaller in size, it must be lesser in value
        return true;
    } else if(size > object.getSize()){ // If this object is greater in size, it must be greater in value
        if(negative){
            return true;
        } else {
            return false;
        }
    } else if(size < object.getSize()){ // Likewise, if it is smaller in size, it must be lesser in value
        if(negative){
            return false;
        } else {
            return true;
        }
    } else {
        for(int i = 0; i < size; ++i){
            if(digits[i] > object.getDigit(i)){
                if(negative){
                    return true;
                } else {
                    return false;
                }
            } else if(digits[i] < object.getDigit(i)){
                if(negative){
                    return false;
                } else {
                    return true;
                }
            }
        }
        return true;
    }
}



/**
 * @brief Adds the value of another Big object to this one
 * 
 * @param right, the object whose value is being added to this one
 */
void Big::add(const Big& right){
    int rSize = right.getSize(); // Saves the size of the right object for future use
    if(rSize > 0 && this->size > 0){ // Makes sure that both objects have a value
        if(rSize > this->size){ // Preemptively increases the size of this object's array if the other object is larger in size
            addDigit(rSize-(this->size));
        }
        int indexL = this->size -1; // Index for this object's array
        int indexR = rSize - 1; // Index for the right object's array
        int overflow = 0; // When left + right > 9, this is extra above 9, so the max value stored in array is 9

        while(indexL >= 0){ // Loops through every element of this object's array
            if(indexR >= 0){ // If there are still values in the right object
                // Adds the right object's value at the index as well as the overflow from the previous
                // index to this object's array
                digits[indexL] += right.getDigit(indexR) + overflow;
                // Removes excess over 9, and stores it for the next index
                overflow = digits[indexL] / 10;
                digits[indexL] %= 10;
            } else if(overflow > 0){ // If there are no values left in the right object, but still a value in overflow
                digits[indexL] += overflow;
                overflow = digits[indexL] / 10;
                digits[indexL] %= 10;
            } else {
                break;
            }
            --indexL;
            --indexR;

            // Array sizing management
            if(indexL < 0 && indexR >= 0){ // If the end of this object's array has been reached, and the right object still has more values
                addDigit();
                indexL = 0;
            }
            if(indexL == 0){
                if(indexR >= 0){ // Checks whether overflow will occur in the next operation
                    int temp = digits[indexL] + right.getDigit(indexR) + overflow;
                    if(temp > 9){
                        addDigit();
                        indexL = 1;
                    }
                } else { // Checks if overflow will occur in the next operation, if the end of the right object has been reached
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


/**
 * @brief Changes the size of the array, effectively dividing by 10^num
 * 
 * @param num, How much to decrease size by
 */
void Big::truncate(int num){
    if(size <= num){
        size = 0;
    } else {
        size -= num;
    }
}


void Big::displayArray(){
    for(int i = 0; i < capacity; ++i){
        std::cout << *(digits+i) << std::flush;
    }
    std::cout << std::endl;
}



bool Big::setBase(int base){
    if(base == bin){
        this->base = bin;
        return true;
    } else if(base == oct){
        this->base = oct;
        return true;
    } else if(base == dec){
        this->base = dec;
        return true;
    } else if(base == hex){
        this->base = hex;
        return true;
    } else {
        return false;
    }
}



std::string Big::binary() const{
    std::string value = "";
    Big twos(1);
    std::stack<Big> powers;
    Big check(*this);
    if(check.isNegative()){
        check.flipSign();
        value = "-";
    }
    while(twos <= check){
        powers.push(twos);
        twos = twos * 2;
    }

    while(!powers.empty()){
        if(powers.top() <= check){
            check = check - powers.top();
            value = value + "1";
            powers.pop();
        } else {
            value = value + "0";
            powers.pop();
        }
    }

    if(value.empty() || value == "-"){
        return "0";
    } else {
        return value;
    }
}


std::string Big::octal() const{
    {
    const std::string convert[2][8] = {{"000","001","010","011","100","101","110","111"},
                                       {"0","1","2","3","4","5","6","7"}};
    std::string value = binary();
    if(value[0] == '-'){
        value = value.substr(1);
    }

    std::string nibble;
    int padding = 3 - (value.size() % 3);
    if(padding != 3){
        for(int i = 0; i < padding; ++i){
            value = "0" + value;
        }
    }

    std::string hex = "";

    for(unsigned i = 0; i < value.size() - 2; i += 3){
        nibble = value.substr(i,3);
        for(int j = 0; j < 8; ++j){
            if(nibble == convert[0][j]){
                hex = hex + convert[1][j];
                break;
            }
        }
    }

    return hex;


}
}


std::string Big::hexadecimal() const{
    const std::string convert[2][16] = {{"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"},
                                       {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"}};
    std::string value = binary();
    if(value[0] == '-'){
        value = value.substr(1);
    }

    std::string nibble;
    int padding = 4 - (value.size() % 4);
    if(padding != 4){
        for(int i = 0; i < padding; ++i){
            value = "0" + value;
        }
    }

    std::string hex = "";

    for(unsigned i = 0; i < value.size() - 3; i += 4){
        nibble = value.substr(i,4);
        for(int j = 0; j < 16; ++j){
            if(nibble == convert[0][j]){
                hex = hex + convert[1][j];
                break;
            }
        }
    }

    return hex;


}




