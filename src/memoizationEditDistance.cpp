#include <iostream>
#include <algorithm>
#include <climits>
#include "../include/memoizationEditDistance.h"

int editDistanceMemo(const std::string& S, const std::string& T, int n, int m, std::vector<std::vector<ll>>& resultados){

    if (n == 0){
        return m;

    } else if (m == 0){
        return n;

    } else if (S[n-1] == T[m-1]){
        if (resultados[n-1][m-1] == LLONG_MAX){
            resultados[n-1][m-1] = editDistanceMemo(S, T, n-1, m-1, resultados);
        }
        return resultados[n-1][m-1];

    } else{
        if (resultados[n][m-1] == LLONG_MAX){
            resultados[n][m-1] = editDistanceMemo(S, T, n, m-1, resultados);
        }
        if (resultados[n-1][m] == LLONG_MAX){
            resultados[n-1][m] = editDistanceMemo(S, T, n-1, m, resultados);
        }
        return 1 + std::min(
                            resultados[n][m-1],
                            resultados[n-1][m]
                        );
    }
}
