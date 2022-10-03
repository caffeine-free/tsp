#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <utility> //funcao swap (para versao anterior a C11 usar <algorithm>)
#include "Arquivos.h"
#include "Construcao.h"
#include "Descida.h"
#include "Util.h"

using namespace std;

float perturbacao(int n, vector<int> &s, float **d, float fo, int nivel)
{
    int ntrocasMax = nivel + 1;
    int ntrocas = 0, i, j;

    while (ntrocas < ntrocasMax)
    {
        ntrocas++;
        // seleciona as posicoes das cidades para trocar
        i = rand() % n;
        do
        {
            j = rand() % n;
        } while (i == j);

        float delta1 = calcula_delta(n, s, d, i, j);
        // Faz o movimento
        swap(s[i], s[j]);
        float delta2 = calcula_delta(n, s, d, i, j);
        // Calcular a nova distancia
        fo = fo - delta1 + delta2;
    }
    return fo;
}

float ILS(
    int n,
    vector<int> &s,
    float **d,
    int nivel, // nro de vezes sem melhora em um dado nivel
    int ILSmax)
{
    int i, j, iter, MelhorIter;
    float fo, fo_viz, fo_2l; 

    clock_t inicio_CPU, fim_CPU;

    fo = calcula_fo(n, s, d);
    fo = fo_viz = melhor_vizinho(n, s, d, fo, &i, &j);
    swap(s[i], s[j]);

    vector<int> s_viz(s);
    s_viz = s;

    iter = MelhorIter = 0;
    nivel = 1;

    limpa_arquivo((char *)"ils.txt");
    inicio_CPU = fim_CPU = clock();

    while (iter - MelhorIter < ILSmax) {
        fo_viz = perturbacao(n, s_viz, d, fo_viz, nivel);
        fo_2l = melhor_vizinho(n, s_viz, d, fo_viz, &i, &j);

        iter++;

        if (fo_2l < fo) {
            swap(s_viz[i], s_viz[j]);
            fo = fo_2l;
            s = s_viz;
            MelhorIter = iter;
            
            nivel = 1;

            fim_CPU = clock();
            imprime_fo(
                (char *)"ils.txt", 
                (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, 
                fo, 
                iter
            );
        } else {
            nivel++;
        }
    }

    return fo;
}

float SmartILS(
    int n,
    vector<int> &s,
    float **d,
    int nivel,
    int nVezesNivel,
    int ILSMax)
{
    int i, j, iter, MelhorIter;
    float fo, fo_viz, fo_2l;

    clock_t inicio_CPU, fim_CPU;

    fo = calcula_fo(n, s, d);
    fo = fo_viz = melhor_vizinho(n, s, d, fo, &i, &j);
    swap(s[i], s[j]);

    vector<int> s_viz(s);
    s_viz = s;

    iter = MelhorIter = 0;
    nivel = nVezesNivel = 1;

    limpa_arquivo((char *)"smartils.txt");
    inicio_CPU = fim_CPU = clock();

    while (iter - MelhorIter < ILSMax) {
        fo_viz = perturbacao(n, s_viz, d, fo_viz, nivel);
        fo_2l = melhor_vizinho(n, s_viz, d, fo_viz, &i, &j);

        iter++;

        if (fo_2l < fo) {
            swap(s_viz[i], s_viz[j]);
            fo = fo_2l;
            s = s_viz;
            MelhorIter = iter;
            
            nivel =  nVezesNivel = 1;

            fim_CPU = clock();
            imprime_fo(
                (char *)"smartils.txt", 
                (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, 
                fo, 
                iter
            );
        } else {
            if (nVezesNivel >= (int) ILSMax / 10) {
                nivel++;
                nVezesNivel = 1;
            } else {
                nVezesNivel++;
            }
        }
    }

    return fo;
}
