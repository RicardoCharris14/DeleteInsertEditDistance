#include <iostream>
#include <algorithm>
#include "recursiveEditDistance.h"

int editDistanceRecursive(std::string S, std::string T, int n, int m){

    if (n == 0){
        return m;
    } else if (m == 0){
        return n;
    } else if (S[n-1] == T[m-1]){
        return editDistanceRecursive(S, T, n-1, m-1);
    } else{
        return 1 + std::min(
                            editDistanceRecursive(S, T, n, m-1),
                            editDistanceRecursive(S, T, n-1, m)
                        );
    }
}
