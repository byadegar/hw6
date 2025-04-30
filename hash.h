#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0,0}; //place to store the converted 
        int length = k.length(); //get length of onput string 

        int g = 4; //group 4 is last group of characters so start filling
        //process characters backwards 
        int lengthCopy = length; 
        while (lengthCopy - 1 >=0 ){
            //while u have it 
            unsigned long long finalNumberGroup = 0; 
            unsigned long long power = 1; //use to build base 36 manually 
            //process one group of up to 6 characters, start from end of string
            int i = 0; //how many chaeacters have been processed 
            while (i < 6 && lengthCopy >= 0 ){
                char character = std::tolower(k[lengthCopy -1]); //make everything lowercase
                HASH_INDEX_T number = letterDigitToNumber(character); //do the actual mapping
                finalNumberGroup += power * number; //weightted value
                power *= 36;  // change for next value
                lengthCopy--; //go to next characer
                i++; //you have processed this many now 

            }
            //save completed group's number  
            w[g] = finalNumberGroup; 
            //move ro next group 
            g--; 
        }
        //use values to get final 
        unsigned long long finalHash = 0; 
        for (int i = 0; i < 5; i++){
            finalHash += w[i] * rValues[i];
        }
        return finalHash; 

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //character to number to be in base 36
        if (letter >= 'a' && letter <= 'z'){
            //subtract a to give correct number for mapping
            return letter - 'a'; 
        }
        else if (letter >= '0' && letter <= '9'){ // if single digit need to convert to base 36
            //check if digit 
            return 26 +(letter - '0'); 
        }
        else {
            //character isn't a letter or a digit 
            //it must be one of them so thisshouldnt' happen
            //throw???
            return 0; 
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
