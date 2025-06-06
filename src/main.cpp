#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>

#include "../include/recursiveEditDistance.h"
#include "../include/memoizationEditDistance.h"
#include "../include/editDistanceDP.h"
#include "../include/editDistanceDPO.h"

int main(int argc, char* argv[]){
    if (argc < 4){
        std::cerr << "Use el formato: ./main -a <algoritmo: recursive, memo,DP, DPO>" 
        " -s <ruta archivo .txt de entrada> -t <ruta archivo .txt objetivo>" << std::endl;
    } else {
        std::string ruta_S, ruta_T, S, T, algoritmo;
        for(int i = 1; i < argc; i++){
            if (std::string(argv[i]) == "-a"){
                algoritmo = argv[++i];
            } else if (std::string(argv[i]) == "-s"){
                ruta_S = argv[++i];
                std::ifstream archivo_S(ruta_S);

                if (!archivo_S.is_open()) {
                    std::cerr << "No se pudo abrir el archivo." << std::endl;
                    return 1;
                }

                std::stringstream buffer;
                buffer << archivo_S.rdbuf();  
                S = buffer.str();  

            } else if (std::string(argv[i]) == "-t"){
                ruta_T = argv[++i];
                std::ifstream archivo_T(ruta_T);

                if (!archivo_T.is_open()) {
                    std::cerr << "No se pudo abrir el archivo." << std::endl;
                    return 1;
                }

                std::stringstream buffer;
                buffer << archivo_T.rdbuf();  
                T = buffer.str();  
            }
        }

        if (algoritmo == "recursive"){
            std::cout << editDistanceRecursive(S, T, S.length(), T.length()) << std::endl;

        } else if (algoritmo == "memo"){
            std::vector<std::vector<ll>> resultados(S.length()+1, std::vector<ll>(T.length()+1, LLONG_MAX));
            std::cout << editDistanceMemo(S, T, S.length(), T.length(), resultados) << std::endl;

        } else if (algoritmo == "DP"){
            std::cout << editDistanceDP(S, T, S.length(), T.length()) << std::endl;

        } else if (algoritmo == "DPO"){
            std::cout << editDistanceDPOptimized(S, T, S.length(), T.length()) << std::endl;

        } else {
            std::cerr << "Algoritmo no válido." << std::endl;
        }
    }
}