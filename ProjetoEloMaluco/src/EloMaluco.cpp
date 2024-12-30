#include "EloMaluco.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Construtor padrão para inicializar estado final
EloMaluco::EloMaluco()
{
    string final[TAMANHO][TAMANHO] = {
        {"vms", "ams", "vds", "brs"},
        {"vmm", "amm", "vdm", "brm"},
        {"vmm", "amm", "vdm", "bri"},
        {"vmi", "ami", "vdi", "vzo"}};
    memcpy(objetivo, final, sizeof(final));
}

// Implementação dos métodos da classe EloMaluco
void EloMaluco::lerEstadoInicialXML(const string &caminhoArquivo)
{
    ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << endl;
        exit(1);
    }

    string linha, textoAtual;
    int linhaMatriz = 0, colunaMatriz = 0;
    ostringstream conteudo;
    while (getline(arquivo, linha))
    {
        conteudo << linha;
    }
    arquivo.close();

    bool dentroColuna = false;
    string conteudoXML = conteudo.str();

    for (size_t i = 0; i < conteudoXML.size(); ++i)
    {
        if (conteudoXML.substr(i, 5) == "<col>")
        {
            dentroColuna = true;
            i += 4;
        }
        else if (conteudoXML.substr(i, 6) == "</col>")
        {
            dentroColuna = false;
            inicial[linhaMatriz][colunaMatriz] = textoAtual;
            textoAtual.clear();
            colunaMatriz = (colunaMatriz + 1) % TAMANHO;
            if (colunaMatriz == 0)
                linhaMatriz++;
            i += 5;
        }
        else if (dentroColuna)
        {
            textoAtual += conteudoXML[i];
        }
    }
}

void EloMaluco::mostrarMatriz(const string matriz[TAMANHO][TAMANHO]) const
{
    for (int i = 0; i < TAMANHO; ++i)
    {
        for (int j = 0; j < TAMANHO; ++j)
        {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void EloMaluco::embaralharEstado(int movimentos)
{
    string matriz[TAMANHO][TAMANHO];
    memcpy(matriz, objetivo, sizeof(objetivo));

    string movimentosValidos[] = {"rsd", "rse", "rid", "rie", "mfc", "mfb"};
    srand(time(0));

    for (int i = 0; i < movimentos; ++i)
    {
        int movimentoAleatorio = rand() % 6;
        string novaMatriz[TAMANHO][TAMANHO];
        executarMovimento(matriz, novaMatriz, movimentosValidos[movimentoAleatorio]);
        memcpy(matriz, novaMatriz, sizeof(novaMatriz));
    }

    memcpy(inicial, matriz, sizeof(matriz));
}

int EloMaluco::calcularDistanciaManhattan(const string matriz[TAMANHO][TAMANHO]) const
{
    int distancia = 0;
    for (int i = 0; i < TAMANHO; ++i)
    {
        for (int j = 0; j < TAMANHO; ++j)
        {
            for (int x = 0; x < TAMANHO; ++x)
            {
                for (int y = 0; y < TAMANHO; ++y)
                {
                    if (matriz[i][j] == objetivo[x][y])
                    {
                        distancia += abs(i - x) + abs(j - y);
                    }
                }
            }
        }
    }
    return distancia;
}

void EloMaluco::executarMovimento(const string matriz[TAMANHO][TAMANHO], string novaMatriz[TAMANHO][TAMANHO], const string &movimento) const
{
    memcpy(novaMatriz, matriz, sizeof(string) * TAMANHO * TAMANHO);

    if (movimento == "rsd")
    {
        string temp = novaMatriz[0][3];
        for (int i = 3; i > 0; --i)
        {
            novaMatriz[0][i] = novaMatriz[0][i - 1];
        }
        novaMatriz[0][0] = temp;
    }
    else if (movimento == "rse")
    {
        string temp = novaMatriz[0][0];
        for (int i = 0; i < 3; ++i)
        {
            novaMatriz[0][i] = novaMatriz[0][i + 1];
        }
        novaMatriz[0][3] = temp;
    }
}

void EloMaluco::resolverJogo(string &caminhoSolucao, bool mostrarPassos)
{
    priority_queue<Estado> filaPrioridade;

    Estado inicialEstado = {inicial, 0, calcularDistanciaManhattan(inicial), ""};
    filaPrioridade.push(inicialEstado);

    while (!filaPrioridade.empty())
    {
        Estado atual = filaPrioridade.top();
        filaPrioridade.pop();

        if (mostrarPassos)
        {
            cout << "\nEstado atual do mat (custo=" << atual.custoCaminho << "):\n";
            mostrarMatriz(atual.mat);
        }

        if (memcmp(atual.mat, objetivo, sizeof(objetivo)) == 0)
        {
            caminhoSolucao = atual.passos;
            return;
        }
    }
}
