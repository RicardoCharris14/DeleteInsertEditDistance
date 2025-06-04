#include <iostream>
#include <string>

int main(int argc, char* argv[]){
    if (argc < 5){
        std::cerr << "Format: ./experimentacion.exe -1 <ruta archivo .txt 1> -2 <ruta archivo .txt 2> -3 <ruta archivo .txt 3> -4 <ruta archivo .txt 4>";
    } else{
        std::string files[4];
        for (int i=1 ; i<argc ; i++){
            if (argv[i] == "-1"){
                files[0] = argv[++i];
            } else if (argv[i] == "-2"){
                files[1] = argv[++i];
            } else if (argv[i] == "-3"){
                files[2] = argv[++i];
            } else if (argv[i] == "-4"){
                files[3] = argv[++i];
            }
        }

        
    }
}