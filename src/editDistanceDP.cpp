#include <iostream>
#include <algorithm>
#include <vector>
#include "../include/editDistanceDP.h"

int editDistanceDP(const std::string& S, const std::string& T, int n, int m){
    
    std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 0; i < n + 1; i++){
        for (int j = 0; j < m + 1; j++){
            if (i == 0){
                table[i][j] = j;
                continue;
            } else if (j == 0){
                table[i][j] = i;
                continue;
            } else {
                if (S[i-1] == T[j-1]){
                    table[i][j] = table[i-1][j-1];
                } else {
                    table[i][j] = 1 + std::min(table[i-1][j], table[i][j-1]);
                }
            }
        }
    }
    
    return table[n][m];
}
