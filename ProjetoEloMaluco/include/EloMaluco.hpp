#ifndef ELO_MALUCO_HPP
#define ELO_MALUCO_HPP

#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <cmath>

using namespace std;

const int TAMANHO = 4; // Dimensão da matriz

// Estrutura para representar um estado no A*
struct Estado
{
    string mat[TAMANHO][TAMANHO];
    int custoCaminho; // Custo do caminho
    int estimativa;   // Heurística (Manhattan)
    string passos;    // Caminho percorrido até o estado
    bool operator<(const Estado &outro) const
    {
        return (custoCaminho + estimativa) > (outro.custoCaminho + outro.estimativa);
    }
};

// Declaração da classe EloMaluco
class EloMaluco
{
private:
    string inicial[TAMANHO][TAMANHO];  // Estado inicial
    string objetivo[TAMANHO][TAMANHO]; // Estado final

public:
    EloMaluco();
    void lerEstadoInicialXML(const string &caminhoArquivo);                                                                            
    // Anteriormente `carregarEstadoInicialXML`
    void mostrarMatriz(const string matriz[TAMANHO][TAMANHO]) const;                                                                   
    // Anteriormente `exibirMatriz`
    void embaralharEstado(int movimentos);                                                                                             
    // Anteriormente `gerarEstadoAleatorio`
    int calcularDistanciaManhattan(const string matriz[TAMANHO][TAMANHO]) const;                                                       
    // Anteriormente `calcularManhattan`
    void executarMovimento(const string matriz[TAMANHO][TAMANHO], string novaMatriz[TAMANHO][TAMANHO], const string &movimento) const; 
    // Anteriormente `aplicarMovimento`
    void salvarResultadoXML(const string &caminhoSolucao, const string &caminhoArquivo) const;                                         
    // Anteriormente `salvarXML`
    void resolverJogo(string &caminhoSolucao, bool mostrarPassos);                                                                     
    // Anteriormente `resolverEloMaluco`
    void menuPrincipal();                                                                                                              
    // Anteriormente `menuInicial`
};

#endif
