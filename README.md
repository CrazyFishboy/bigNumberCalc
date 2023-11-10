# bigNumberCalc
c++ implementation for working with numbers larger than possible in the supported integer types. The goal
is to make a portable class that can deal with these large numbers very efficiently. 

Still in development...

Will utilize a dynamically allocated array of integers in order to store extremely large numbers.
In theory, it will be able to store a number of 2^64 -1 digits in length.

Currently supports addition, subtraction, multiplication, and division of these numbers. Additional planned features:
  floating point

Can also return or display values in binary, octal, or hexadecimal.

Current steps to run:

  clone the repository:
    `git clone bigNumberCalc`

  Navigate to the repository folder:
    `cd bigNumberCalc`

  Compile and link main.cpp and big.cpp:
    `g++ -Wall main.cpp big.cpp`

  * Note that main.cpp is a test/demo file, replace with your own file

  Run:
    `./a.out`
    
