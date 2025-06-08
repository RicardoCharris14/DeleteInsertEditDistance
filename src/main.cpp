#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>

#include "../include/recursiveEditDistance.h"
#include "../include/memoizationEditDistance.h"
#include "../include/editDistanceDP.h"
#include "../include/editDistanceDPO.h"

int ejecutaAlgoritmo(std::string S, std::string T, std::string algoritmo){
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
    
    return -1;
}

std::string leerArchivo(std::string ruta_archivo){
    std::ifstream archivo(ruta_archivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + ruta_archivo);
    }
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]){
    if (argc != 9 && argc != 5){
        std::cerr << "Use el formato 1: ./main -a <algoritmo: recursive, memo,DP, DPO>" 
        " -s <ruta archivo .txt de entrada> -t <ruta archivo .txt objetivo> -i <casos de prueba: textos>" << std::endl;
        std::cerr << "o el formato 2: ./main -a <algoritmo: recursive, memo,DP, DPO> -i <casos de prueba: prueba>" << std::endl;
        return 1;
    } else {
        std::string ruta_S, ruta_T, S, T, algoritmo, casos_prueba;
        std::vector<std::string> lista_palabras = {"croacia", "avion", "deporte", "urraca"};
        for(int i = 1; i < argc; i++){
            if (std::string(argv[i]) == "-a"){
                algoritmo = argv[++i];
            } else if (std::string(argv[i]) == "-s"){
                ruta_S = argv[++i];
            } else if (std::string(argv[i]) == "-t"){
                ruta_T = argv[++i]; 
            } else if (std::string(argv[i]) == "-i"){
                casos_prueba = argv[++i];
            }
        }

        try {
            if (casos_prueba == "textos"){
                S = leerArchivo(ruta_S);
                T = leerArchivo(ruta_T);
                ejecutaAlgoritmo(S, T, algoritmo);

            } else if (casos_prueba == "prueba"){
                for(int i = 0; i < 4; i++){
                    for (int j = 0; j < 4; j++){
                        if(lista_palabras[i] == lista_palabras[j]) continue;
                        std::cout << "Comparando " << lista_palabras[i] << " con " << lista_palabras[j] << std::endl;
                        ejecutaAlgoritmo(lista_palabras[i], lista_palabras[j], algoritmo);
                    }
                }
            } else {
                std::cerr << "Parámetro -i no reconocido. Utilice el formato: prueba, textos" << std::endl;
            }
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

