/**
Problem description : 
  given a binary string and a number, flip one bit of the string
  in a way that you can retrieve the number back from the string

observations : 
  1. xor of all numbers from 0 to 63 = 0
  2. max xor of two or more numbers in range [0 ,63] is 63

let's convert the binary string to vector of integers such that
if the i-th element of string is 1 then add number i to the vector
and the flip operation is eqaul to :
*adding a new number to the vector if it was not present.
*removing a number if it was already present in the vector.
the xor of numbers in the vector is at most 63 (obs.2)

now we want to add one element to the vector to make its xor equal to c
let 'x' = xor of numbers in the vector and 'r' the required number such that
x^r = c
x^c = r
and since c <= 63 then x^c is also <= 63

so we only need to add r to the vector if it wasn't existing in vector or remove it.
*/

#include "coins.h"
//#include "grader.cpp"

std::vector<int> coin_flips(std::vector<int> b, int c) {
    int x = 0;
    for(int i=0; i<64; i++)
        x ^= (b[i]*i);
    return {x^c};
}

int find_coin(std::vector<int> b) {
    int ans = 0;
    for(int i=0; i<64; i++)
        ans ^= (b[i]*i);
    return ans;
}
