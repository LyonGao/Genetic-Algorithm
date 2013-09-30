#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include"function.h"
#include"genetic_algorithm.h"

/*********************************************************************



*********************************************************************/

void main()
{
	int i = 0, max_index = -1;
	int individual_num = 0;
	int generation_num = 0;
	double crossover_rate = 0.0f, mutation_rate = 0.0f, range_min = 0.0f, range_max = 0.0f;
	individual_s *population = NULL;
	
	init(&individual_num, &generation_num, &crossover_rate, &mutation_rate, &range_min, &range_max);

	GA(individual_num, generation_num, crossover_rate, mutation_rate, range_min, range_max, &population, GET_MAX);
	
	for (i = 0; i < individual_num; i++)
	{
		printf("%f\n", population[i].fitness);
	}

	max_index = find_best_individual_index(individual_num, population);

	printf("f-value : %f---value : %f---fitness : %f", f(population[max_index].value), 
		population[max_index].value, population[max_index].fitness);

	free(population);
	population = NULL;

	while (1);

}