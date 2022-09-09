//
// Created by Puca Penna on 03/10/19.
//

#include <cmath>
#include <iostream>
#include <ctime>
#include <climits>
#include "GRASP.h"
#include "Construcao.h"
#include "Util.h"
#include "Descida.h"
#include "Arquivos.h"

float GRASP(
    int n, 
    std::vector<int> &s, 
    float **d, 
    float alpha, 
    int GRASP_max /*, int tipo_construcao*/
) {
    vector<int> s_star;
    clock_t inicio_CPU, fim_CPU;
    float fo, fo_star;

    fo = fo_star = INT_MAX;

    limpa_arquivo((char*)"GRASP.txt");
    inicio_CPU = fim_CPU = clock();
    imprime_fo(
        (char*)"GRASP.txt", 
        (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC,
        fo_star,
        0
    );

    int iter = 0;
    int iter_sem_melhora = 0;
    while (iter_sem_melhora <= GRASP_max) {
        constroi_solucao_parcialmente_gulosa_vizinho_mais_proximo(n, s, d, alpha);
        fo = descida_best_improvement(n, s, d);

        if (fo < fo_star) {
            fim_CPU = clock();
            imprime_fo(
                (char*)"GRAPS.txt", 
                (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC,
                fo,
                iter
            );

            s_star = s;
            fo_star = fo;

            iter_sem_melhora = 0;
        } else {
            iter_sem_melhora++;
        }

        iter++;
    }

    fim_CPU = clock();
    imprime_fo(
        (char*)"GRASP.txt", 
        (fim_CPU - inicio_CPU) / CLOCKS_PER_SEC,
        fo_star,
        iter
    );
    
    s = s_star;
    return fo_star;
}

