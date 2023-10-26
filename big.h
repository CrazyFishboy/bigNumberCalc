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

    static int capacityIncrement;

    // Constructors and Destructors
    Big() : Big("0") {}
    Big(long long val) : Big(std::to_string(val)) {}
    Big(std::string val);
    Big(const Big& right);
    ~Big();

    // Getters
    std::string getValue() const;
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    int getDigit(int index) const;
    bool isNegative() const { return negative;}

    friend std::ostream& operator<<(std::ostream& out, const Big& object);
    int& operator[ ](int index);

    // Assignment operator
    void operator=(const Big& right);

    // Arithmetic operators
    void flipSign() { negative = !negative; }
    friend Big operator+(const Big& left, const Big& right);
    friend Big operator-(const Big& left, const Big& right);
    friend Big operator*(const Big& left, const Big& right);
    Big& operator++();
    Big operator++(int);
    Big& operator--();
    Big operator--(int);

    // Comparison operators
    bool operator==(const Big& object) const;
    bool operator!=(const Big& object) const;
    bool operator>(const Big& object) const;
    bool operator>=(const Big& object) const;
    bool operator<(const Big& object) const;
    bool operator<=(const Big& object) const;


    void add(const Big& right);

protected:
    void addDigit(int num = 1); // Increases the size of the array by one at the beginning
    void appendDigit(int num = 1); // Increases the size of the array by one at the end


private:
    int * digits; // Array of digits
    int size; // Number of digits used
    int capacity; // Number of digits storable in array
    bool negative; // If the number is negative



};




#endif