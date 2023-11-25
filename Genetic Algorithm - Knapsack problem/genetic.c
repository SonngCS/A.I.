#include "genetic.h"

void InitPop(Population * pop){ //Initiating population with random genes
    //srand(time(NULL));
    int r = 0;

    for(int i = 0; i < POPSIZE; i++){
        for(int j = 0; j < CHROM; j++){
            r = rand()%2;
            pop[i].chromosome[j] = r;
        }
    }

}

void Evaluate(Population * pop){
    double diff = 0;     //Total volume and weight of the individual minus total allowed
    int notAllowed = 0;  //Used to penalize individual according to constraints broken (weight and/or volume)
    for(int i = 0; i < POPSIZE; i++){
        pop[i].fitnessValue = 0.0;
        pop[i].totalWeight = 0.0;
        pop[i].totalVolume = 0.0;
        pop[i].totalValue = 0.0;
        diff = 0.0;
        for(int j = 0; j < CHROM; j++){  //Updating values
            pop[i].totalValue += itemValues[j]*pop[i].chromosome[j];
            pop[i].totalWeight += itemWeights[j]*pop[i].chromosome[j];
            pop[i].totalVolume += itemVolumes[j]*pop[i].chromosome[j];
        }

        if((pop[i].totalWeight <= WEIGHT && pop[i].totalVolume <= VOLUME)){ //Updating fitness value if no constraints were broken
            pop[i].fitnessValue = pop[i].totalValue/(WEIGHT + VOLUME);
            continue;
        }

        //if(pop[i].totalWeight > WEIGHT) diff += (pop[i].totalWeight - WEIGHT);     -Old method used
        //if(pop[i].totalVolume > VOLUME) diff += (pop[i].totalVolume - VOLUME);

        if(pop[i].totalWeight > WEIGHT){          //Checking if the first constraint was broken
            diff += (pop[i].totalWeight - WEIGHT);
            notAllowed++;

        } 
        if(pop[i].totalVolume > VOLUME){          //Checking if the second constraint was broken
            diff += (pop[i].totalVolume - VOLUME);
            notAllowed++;
        }



        pop[i].fitnessValue = pop[i].totalValue/((WEIGHT + VOLUME + diff*notAllowed*1.991)); //Updating fitness and penalizing member accordingly
        diff = 0.0;
        notAllowed = 0;
        //pop[i].fitnessValue = 0; - Old penalizing strategy used
    }
}

void PopQuickSort(Population * v, int l, int r){ //Quicksort converted to work with the Population struct
    int i = l, j = r;
    double x;
    Population aux;
    x = v[(i + j)/2].fitnessValue;
    do{
        while (v[i].fitnessValue > x) i++;
        while (x > v[j].fitnessValue) j--;
        if(i <= j){
            aux = v[i];
            v[i++] = v[j];
            v[j--] = aux;
        }
    }while (i <= j);
    if (l < j) PopQuickSort(v, l, j);
    if (i < r) PopQuickSort(v, i, r);
}

void PrintPopulation(Population * pop){ //Print a Population struct and all relevant values to the console

    printf("\nITEM VALUE\n");
    for(int i = 0; i < 5; i++){
        printf("%lf ", itemValues[i]);
    }
    
    for(int i = 0; i < POPSIZE; i++){

        printf("\nIndividual %d CHROM: ", i);
        for(int j = 0; j < CHROM; j++){
            printf("%d ", pop[i].chromosome[j]);
        }
        printf("\nFITNESS: %lf ", pop[i].fitnessValue);
        printf("\nVALUE: %lf ", pop[i].totalValue);
        printf("\nWEIGHT\n");
        printf("%lf ", pop[i].totalWeight);
        printf("\nVOLUME\n");
        printf("%lf ", pop[i].totalVolume);
        printf("\n");
    }
}

void SaveFile(Population * pop, clock_t start, char * file, double matriz[EPOCHS][3]){  //Saves output and CPU time on a file in the same directory
    FILE * out;
    FILE * data;

    char * numData = "data.txt";

    if((out = fopen(file, "w")) == NULL || pop == NULL){ //Checking for errors when opening output file
        fprintf(stderr, "Writing error!\n");
        exit(1);
    }

    if((data = fopen(numData, "w")) == NULL || pop == NULL){ //Checking for errors when opening output file
        fprintf(stderr, "Writing error!\n");
        exit(1);
    }

    fprintf(out, "KNAPSACK CONSTRAINTS:\n");             //saving knapsack information
    fprintf(out, "WEIGHT: %f\n", (float)WEIGHT);
    fprintf(out, "VOLUME: %f\n\n", (float)VOLUME);

    fprintf(out, "POPSIZE: %d\nTOTAL EPOCHS: %d\n\n", POPSIZE, EPOCHS);

    fprintf(out, "ITEMS:\n");

    for(int i = 0; i < CHROM; i++){                     //Saving item information
        fputs(itemNames[i], out);
        fprintf(out, "VALUE: %lf\n", itemValues[i]);
        fprintf(out, "WEIGHT: %lf\n", itemWeights[i]);
        fprintf(out, "VOLUME: %lf\n\n", itemVolumes[i]);
    }

    for(int i = 0; i < POPSIZE; i++){                  //Saving population stats
        fprintf(out, "\n****Individual %d****\n----CHOSEN ITEMS----\n", i);
        for(int j = 0; j < CHROM; j++){
            if(pop[i].chromosome[j] != 0) fprintf(out, "%s", itemNames[j]);
        }
        fprintf(out, "--NOT CHOSEN ITEMS--\n");
        for(int j = 0; j < CHROM; j++){
            if(pop[i].chromosome[j] == 0) fprintf(out, "%s", itemNames[j]);
        }
        fprintf(out, "--FINAL CHROMOSOMES--\n");
        for(int j = 0; j < CHROM; j++){
            fprintf(out, "%d ", pop[i].chromosome[j]);
        }
        fprintf(out, "\n\nFITNESS: %lf", pop[i].fitnessValue);
        fprintf(out, "\nTOTAL VALUE: %lf", pop[i].totalValue);
        fprintf(out, "\nTOTAL WEIGHT: %lf", pop[i].totalWeight);
        fprintf(out, "\nTOTAL VOLUME: %lf\n\n", pop[i].totalVolume);
    }

    clock_t end = clock();
    double totalTime = (double)(end - start)/CLOCKS_PER_SEC;

    fprintf(out, "\nEXECUTION CPU TIME: %lf SECONDS\n", totalTime); //Execution time

    for(int i = 0; i < EPOCHS; i++){
        fprintf(data, "%lf %lf %lf %d\n", matriz[i][0],matriz[i][1],matriz[i][2], i);
    }

    fclose(out);
    fclose(data);

}

void SelectionRoulette(Population * pop, int * idx){  //Random roulette was the selection method used for this code
    double cumSum = 0.0;     //Cumulative sum
    double cumProb[POPSIZE]; //Cumulative probability
    //srand(time(NULL));
    double r = 0;

    for(int i = 0; i < POPSIZE; i++) cumSum = cumSum + pop[i].fitnessValue;

    cumProb[0] = pop[0].fitnessValue/cumSum;

    for(int i = 1; i < POPSIZE; i++) cumProb[i] = (pop[i].fitnessValue/cumSum) + cumProb[i - 1];

    for(int i = 0; i < POPSIZE; i++){
        r = (rand()%100/100.0);
        for(int j = 0; j < POPSIZE; j++){
            if(cumProb[j] >= r){
                idx[i] = j;
                if((i > 0 && idx[i-1] == idx[i]) && (i % 2 == 1)){ //One parent should not mate with itself, chosen members are sequentially paired (0 with 1, 2 with 3 and so on)
                    i--;                         //If the chosed pair is equal, it will repeat this iteration
                    break;                       
                }
                break;
            }

        }
    }
}

void CrossOver(Population * pop, Population * newPop, int * idx){
    double mate, cut1, cut2;

    //srand(time(NULL));

    if(ELITISM != 0) for(int i = 0; i < ELITISM; i++) newPop[i] = pop[i];  //Copies the best members to the next generation if ELITISM is not 0

    int index = 0;

    for(int i = ELITISM; i < POPSIZE; i+=2){
        mate = rand()%100;

        if(mate > 84){  //80% of mating chance, or else the parents are also copies to the next generation
            newPop[i] = pop[idx[index]];
            newPop[i+1] = pop[idx[index+1]];
            continue;
        }

        cut1 = rand()%CHROM;             //Cut values are chosed randomly to increase gene diversity
        cut2 = rand()%CHROM;

        for(int j = 0; j < CHROM; j++){  //First child will start with genes from the first parent and second child will start with the second parent
            if(j <= cut1) newPop[i].chromosome[j] = pop[idx[index]].chromosome[j];
            else newPop[i].chromosome[j] = pop[idx[index+1]].chromosome[j];
            Mutation(newPop, i, j);      //Checks for mutation in the first child                     

            if(j <= cut2) newPop[i+1].chromosome[j] = pop[idx[index+1]].chromosome[j];
            else newPop[i+1].chromosome[j] = pop[idx[index]].chromosome[j];
            Mutation(newPop, (i+1), j);  //Checks for mutation in the second child
        }
        idx +=2;
    }
}

void Mutation(Population * pop, int i, int j){ //Simple mutation function

   // srand(time(NULL));

    double mutation = (rand()%100/100.0);

    if(mutation < 0.0367){ //If random number between 0 and 1 is less than 0.04, the gene will be inversed (mutation will be executed)
        pop[i].chromosome[j] = (pop[i].chromosome[j] + 1)%2;
    }
}

void CalcValues(double matrix[EPOCHS][3], Population * pop, int idx){//Only adds the correct values to the original matrix
    matrix[idx][0] = pop[0].fitnessValue;
    matrix[idx][1] = 0;
    for(int j = 0; j < POPSIZE; j++) matrix[idx][1] += pop[j].fitnessValue;
    matrix[idx][1] /=POPSIZE;
    matrix[idx][2] = pop[POPSIZE-1].fitnessValue;
}