# DeleteInsertEditDistance
El proyecto consiste en crear cuatro algoritmos para resolver el problema "Edit distance" considerando las operaciones "Insert" y "Delete". Cada uno de los algoritmos utilizará un distinto paradigma de programación, los cuales son: recursividad, memoization, programación dinamica y progrmación dinamica con optimización de espacio.

## Instrucciones de compilación y ejecución

Este proyecto contiene dos Makefiles distintos para sistemas Linux, uno para compilar el código principal y otro para los scripts de experimentación.

### 1. Compilación del programa principal

Para compilar el archivo `main.cpp` y los relacionados, utilice el siguiente comando:

```bash
make -f Makefile.main
```


En caso de utilizar Windows, para compilar el main utilice el comando 
```bash
g++ -o main .\src\main.cpp .\src\editDistanceDP.cpp .\src\editDistanceDPO.cpp .\src\memoizationEditDistance.cpp .\src\recursiveEditDistance.cpp
```

Esto retornará un ejecutable llamado ```main``` que tiene dos formatos, uno para importar textos y otro para probar con una lista de cadenas prediseñadas. La ejecución se da por los siguientes parámetros:
Use el formato 1:
```bash
 ./main -a <algoritmo: recursive, memo,DP, DPO> -s <ruta archivo .txt de entrada> -t <ruta archivo .txt objetivo> -i <casos de prueba: textos>
```
O el formato 2:
```bash
./main -a <algoritmo: recursive, memo,DP, DPO> -i <casos de prueba: prueba>
```
