#include <iostream>
#include <vector>
#include "editDistanceDPO.h"

int editDistanceDPOptimized(std::string S, std::string T, int n, int m){
    std::vector<int> fila1(m+1);
    std::vector<int> fila2(m+1);

    for (int i = 0; i < n + 1; i++){
        for (int j = 0; j < m + 1; j++){
            if (i == 0){
                fila1[j] = j;
                continue;
            } else if (j == 0){
                if (i % 2 == 0){
                    fila1[j] = i; 
                } else {
                    fila2[j] = i;
                }
                continue;
            } else {
                if (S[i-1] == T[j-1]){
                    if (i % 2 == 0){
                        fila1[j] = fila2[j-1]; 
                    } else {
                        fila2[j] = fila1[j-1];
                    }
                } else {
                    if (i % 2 == 0){
                        fila1[j] = 1 + std::min(fila2[j], fila1[j-1]); 
                    } else {
                        fila2[j] = 1 + std::min(fila1[j], fila2[j-1]); 
                    }
                }
            }
        }
    } 

    if (n % 2 == 0) return fila1[m];
    else return fila2[m];
}

