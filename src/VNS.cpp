#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "Arquivos.h"
#include "Construcao.h"
#include "Util.h"
#include "Descida.h"
#include "VNS.h"

float VNS(int n, vector<int> &s, float **d, int VNS_max, int r) {

    int i, j, k, iter, MelhorIter;
    float fo, fo_viz;

    clock_t inicio_CPU, fim_CPU;

    fo = calcula_fo(n, s, d);
    printf("Iter VNS = %3d \t  fo_star = %10.4f \n", iter, fo);

    vector<int> s_viz(s);
    s_viz = s;

    limpa_arquivo((char *)"vns.txt");
    inicio_CPU = fim_CPU = clock();

    // loop principal do VNS
    while (iter - MelhorIter < VNS_max) {
        iter++;
        k = 1; // comeca pela vizinhanca 1

        // loop das vizinhancas
        while (k <= r) {
            fo_viz = gera_um_vizinho_qualquer(n, s_viz, d, fo, k);
            
            if (fo_viz < fo) {
                s = s_viz;
                fo = fo_viz;

                MelhorIter = iter;
                k = 1;

                fim_CPU = clock();
                imprime_fo(
                    (char *)"smartils.txt", 
                    (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, 
                    fo, 
                    iter
                );
            } else {
                k++;
            }
        }

        return fo;
    }
}

float gera_um_vizinho_qualquer(int n, vector<int> &s, float **d, float fo, int k) {
    float fo_viz;

    switch (k) {
    case 1:
        fo_viz = vizinho_troca_qualquer(n, s, d, fo);
        break;
    case 2:
        fo_viz = vizinho_reinsercao1_qualquer(n, s, d, fo);
        break;
    case 3:
        fo_viz = vizinho_reinsercao2_qualquer(n, s, d, fo);
        break;
    }

    return fo_viz;

} // fim gera_k_vizinhos_aleatorios

// Gera um vizinho qualquer usando o movimento de troca
float vizinho_troca_qualquer(int n, vector<int> &s, float **d, float fo)
{ // Metodo vizinho_aleatorio usado nas descidas, aqui alterado para retornar o vizinho gerado

    float fo_viz = fo;
    int i, j, aux;
    float delta1, delta2;

    // sorteia a posição para troca
    j = rand() % n;
    do
    {
        i = rand() % n;
    } while (i == j);

    delta1 = calcula_delta(n, s, d, i, j);

    // Faz o movimento
    swap(s[i], s[j]);

    delta2 = calcula_delta(n, s, d, i, j);

    // calcula o no fo
    fo_viz = fo - delta1 + delta2;

    // retornar a distancia do  vizinho, a solucao s eh retornada por referencia
    return fo_viz;

} // vizinho_troca_qualquer

// Gera um vizinho qualquer usando o movimento de re-inserir
// um cliente em outra posicao da rota
float vizinho_reinsercao1_qualquer(int n, vector<int> &s, float **d, float fo) {
    double fo_viz;

    int rand_index = rand() % s.size();
    int cidade_aleatoria = s.at(rand_index);

    s.erase(s.begin() + rand_index);

    rand_index = rand() % s.size();
    s.insert(s.begin() + rand_index, cidade_aleatoria);

    fo_viz = calcula_fo(n, s, d);
    return fo_viz;
}

// Gera um vizinho qualquer usando o movimento de re-inserir
// dois clientes consecutivos em outra posicao da rota
float vizinho_reinsercao2_qualquer(int n, vector<int> &s, float **d, float fo) {
double fo_viz;

    int rand_index = rand() % (s.size() - 1);
    int cidade_aleatoria = s.at(rand_index);
    int cidade_aleatoria_2 = s.at(rand_index + 1);

    s.erase(s.begin() + rand_index);
    s.erase(s.begin() + rand_index, s.begin() + rand_index + 1);

    rand_index = rand() % s.size();
    s.insert(s.begin() + rand_index, cidade_aleatoria);

    rand_index = rand() % s.size();
    s.insert(s.begin() + rand_index, cidade_aleatoria_2);

    fo_viz = calcula_fo(n, s, d);
    return fo_viz;
}
