# Caso de estudo - indústria têxtil

## Organização

1. Pasta docs/ contém os documentos gerados.
2. Pasta brkga/ contém o código da metaheurística.
3. Pasta formulations/ contém o código das formulações.

### Para rodar o brkga basta executar make e depois ./brkga-main

### Para executar a formulação basta executar julia model_v0.jl

Muito do código está hard-code, então precisa ser feita a alteração manual para escolher qual modelo ou formulação rodar.

Código brkga-main.cpp alternar entre linhas 65,66,67 e 77,78,79 para executar problema v0,v1,v2 respectivamente.

Código formulações model_v0.jl. Deixar um dos pares de linha (9,10),(12,13),(15,16) não comentado para executar problema v0,v1,v2 respectivamente.
