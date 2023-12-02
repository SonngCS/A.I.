#ifndef _GENETIC_H
#define _GENETIC_H

#define POPSIZE 150  //Population size (choose a multiple of two)
#define CHROM 35     //Chromosome size (size of item array)
#define WEIGHT 50    //Knapsack max weight
#define VOLUME 60    //Knapsack max volume
#define ELITISM 2    //Elitism (choose a multiple of two)
#define EPOCHS 300   //Total iterations

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static const char itemNames[CHROM][1000] = {                 //Items to be chosed
                                    "sleeping bag\n", 
                                    "Water bottle\n",
                                    "Food\n",
                                    "Toothpaste\n",
                                    "Toothbrush\n",
                                    "Survival Knife\n",
                                    "Flare gun\n",
                                    "Lighter\n",
                                    "Lantern\n",
                                    "Tent\n",
                                    "Fishing net\n",
                                    "Insect repellent\n",
                                    "Sunscreen\n",
                                    "Phone\n",
                                    "Rope\n",
                                    "First aid kit\n",
                                    "Toilet paper\n",
                                    "Cook pots\n",
                                    "Rainwear\n",
                                    "Towel\n",
                                    "Portable charger\n",
                                    "Books\n",
                                    "Water purifier\n",
                                    "Camping Shovel\n",
                                    "Camping pillow\n",
                                    "Blanket\n",
                                    "Camping chair\n",
                                    "Headphones\n",
                                    "Laptop\n",
                                    "Watch\n",
                                    "Compass\n",
                                    "Spair boots\n",
                                    "Binoculars\n",
                                    "Portable stove\n",
                                    "Umbrella\n"
                                  };

static const double itemValues[] =  {22,  25,    25,    4,     5,  10,   12,  10,   9,  30,   3,   9,   7,  11,  8,  20,  6,   7,  10,  5,  9,  2,  16,  11,  8, 11,  5, 10, 13, 3, 14, 9, 8, 15, 7};
static const double itemWeights[] = { 7,   2,     8,    1,     1,   6,    9,   1,   5,  15,  10,   1,   1,   2,  6,  10,  1,  15,   2,  1,  1,  6,   1,  12,  1,  1, 15,  1,  7, 1,  1, 5, 1, 17, 1};
static const double itemVolumes[] = { 9,   3,     7,    1,     1,   6,    7,   1,   8,  13,  15,   1,   1,   1,  3,   7,  2,  20,   2,  1,  1,  5,   1,  13,  5,  2, 20,  1,  5, 1,  1, 5, 2, 15, 3};

typedef struct{                //Population struct (Use an array with size of POPSIZE)
    int chromosome[CHROM];
    double fitnessValue;       //Fitness value according to the evaluation of the individual
    double totalValue;         //Sum of the value of all items of this individual
    double totalWeight;        //Sum of the weight of all items of this individual
    double totalVolume;        //Sum of the volume of all items of this individual
} Population;

//Function to initialize population
void InitPop(Population *);

//Function to evaluate members of current population
void Evaluate(Population *);

//Population quicksort
void PopQuickSort(Population *, int, int);

//Print function to show population on console
void PrintPopulation(Population *);

//Saves current results on a file in the same directory
void SaveFile(Population *, clock_t, char *, double matriz[EPOCHS][3]);

//Selection function for parents
void SelectionRoulette(Population *, int *);

//Mating function
void CrossOver(Population *, Population *, int *);

//Mutation function to change gene if threshold is met
void Mutation(Population *, int, int);

//Calcultating and saving Highest, lowest and an average of all individuals
void CalcValues(double matrix[EPOCHS][3], Population *, int);

#endif