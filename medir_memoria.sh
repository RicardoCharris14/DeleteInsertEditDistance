#!/bin/bash

# Archivos posibles para S y T
files=("textos/file1.txt" "textos/file2.txt" "textos/file3.txt" "textos/file4.txt")

# Algoritmos posibles
algos=("memo" "DP" "DPO")

# Archivo CSV de salida
output="uso_memoria_algoritmos.csv"

# Escribir encabezado CSV
echo "algoritmo,S,T,memoria_usada" > "$output"

# Iterar sobre algoritmos
for a in "${algos[@]}"; do
  # Iterar sobre S
  for s in "${files[@]}"; do
    # Iterar sobre T
    for t in "${files[@]}"; do
      # Evitar que S y T sean iguales
      if [[ "$s" != "$t" ]]; then
        # Ejecutar el comando y obtener la memoria usada
        mem=$(command time -v ./bin/main -a "$a" -s "$s" -t "$t" 2>&1 | grep "Maximum resident set size " | awk '{print $6}')
        
        # Guardar en CSV
        echo "$a,$s,$t,$mem" >> "$output"
      fi
    done
  done
done

echo "Ejecución finalizada. Resultados guardados en $output"
