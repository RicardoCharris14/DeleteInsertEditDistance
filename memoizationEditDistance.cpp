#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

int editDistanceMemo(const std::string& S, const std::string& T, int n, int m, std::vector<std::vector<ll>>& resultados){

    if (n == 0){
        return m;

    } else if (m == 0){
        return n;

    } else if (S[n-1] == T[m-1]){
        if (resultados[n-1][m-1] == LLONG_MAX){
            resultados[n-1][m-1] = editDistanceMemo(S, T, n-1, m-1, resultados);
        }else{
            std::cout << "Memo" << std::endl;
        }
        return resultados[n-1][m-1];

    } else{
        if (resultados[n][m-1] == LLONG_MAX){
            resultados[n][m-1] = editDistanceMemo(S, T, n, m-1, resultados);
        }else{
            std::cout << "Memo" << std::endl;
        }
        if (resultados[n-1][m] == LLONG_MAX){
            resultados[n-1][m] = editDistanceMemo(S, T, n-1, m, resultados);
        }else{
            std::cout << "Memo" << std::endl;
        }
        return 1 + std::min(
                            resultados[n][m-1],
                            resultados[n-1][m]
                        );
    }
}

int editDistanceDeleteInsert(std::string S, std::string T){
    int n = S.length();
    int m = T.length();
    std::vector<std::vector<ll>> resultados(n+1, std::vector<ll>(m+1, LLONG_MAX));
    return editDistanceMemo(S, T, n, m, resultados);
}




int main(){
    std::string S, T;
    std::cin >> S >> T;
    std::cout << editDistanceDeleteInsert(S, T);

    return 0;
}