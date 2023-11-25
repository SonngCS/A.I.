#include "genetic.h"

int main(void){

    if(POPSIZE % 2 != 0){
        fprintf(stderr, "Population size is not a multiple of two!\n");
        exit(1);
    }

    if(ELITISM % 2 != 0){
        fprintf(stderr, "Elitism is not a multiple of two!\n");
        exit(1);
    }

    srand(time(NULL));

    clock_t begin = clock();

    static double values[EPOCHS+1][3];

    int selectedParents[POPSIZE];

    Population pop1[POPSIZE];
    Population auxPop[POPSIZE];
    
    InitPop(pop1);
    Evaluate(pop1);
    PopQuickSort(pop1, 0, POPSIZE - 1);

    for(int i = 0; i < EPOCHS; i++){

        SelectionRoulette(pop1, selectedParents);
        CrossOver(pop1, auxPop, selectedParents);
        for(int j = 0; j < POPSIZE; j++) pop1[j] = auxPop[j];
        Evaluate(pop1);
        PopQuickSort(pop1, 0, POPSIZE - 1);
        CalcValues(values, pop1, i);
    }

    char * file = "Results.txt";

    SaveFile(pop1, begin, file, values);

    return 0;
}