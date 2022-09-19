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

float LAHC(int n, vector<int> &s, float **d, int l, int m)
{
    int i, j, r, iter, p, aux;
    float delta1, delta2, fo, fo_viz;

    int melhor_i, melhor_j;
    clock_t inicio_CPU, fim_CPU;

    fo = calcula_fo(n, s, d);

    vector<float> F;
    for (int i = 0; i < l; i++)
        F.push_back(fo);
    
    vector<int> s_star(s);
    float fo_star = fo;

    limpa_arquivo((char *)"lahc.txt");
    inicio_CPU = fim_CPU = clock();

    s = s_star;
    iter = p = r = 0;

    while (r <= m) {
        fo_viz = vizinho_aleatorio(n, s, d, fo, &melhor_i, &melhor_j);

        if (fo_viz <= fo || fo_viz <= F.at(p)) {
            if (fo_viz < fo) r = 0;

            fo = fo_viz;
            swap(s[melhor_i], s[melhor_j]);

            fim_CPU = clock();
            imprime_fo(
                (char *)"lahc.txt", 
                (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC, 
                fo, 
                iter
            );

            if (fo < fo_star) {
                fo_star = fo;
                s_star = s;
            }
        }

        F.at(p) = fo;
        p = (p + 1) % l;
        r++;

        iter++;
    }

    return fo_star;
}
