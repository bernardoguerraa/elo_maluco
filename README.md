# Elo Maluco

## Descrição

O projeto **Elo Maluco** é uma implementação de um jogo baseado em uma matriz 4x4. O objetivo do jogo é manipular a matriz até atingir um estado objetivo, aplicando uma série de movimentos válidos. A solução do problema é encontrada utilizando o algoritmo de busca A* com heurística de distância de Manhattan.

## Estrutura do Projeto

- `EloMaluco.hpp`: Declaração da classe `EloMaluco` e dos métodos que manipulam o jogo.
- `EloMaluco.cpp`: Implementação da lógica do jogo, incluindo manipulação de matrizes, embaralhamento do estado, cálculo de distância de Manhattan e resolução do jogo.
- `main.cpp`: Arquivo principal que executa o jogo chamando o método `menuPrincipal()`.


## Funcionalidades

- **Estado Inicial**: O estado inicial do jogo pode ser lido de um arquivo XML.
- **Movimentos**: A matriz pode ser manipulada aplicando movimentos válidos como rotações e trocas de elementos.
- **Resolução**: O algoritmo A* é utilizado para resolver o jogo, encontrando a sequência de movimentos que leva ao estado objetivo.
- **Embaralhamento**: O estado inicial pode ser embaralhado aplicando movimentos aleatórios.



