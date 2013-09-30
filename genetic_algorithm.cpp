#include"genetic_algorithm.h"
#include"function.h"
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<stdlib.h>


void init(int *individual_num, int *generation_num, double *crossover_rate, double *mutation_rate, 
		  double *range_min, double *range_max)
{
	int individual_num_gly = 0;
	int generation_num_gly = 0;
	double crossover_rate_gly = 0.0f;
	double mutation_rate_gly = 0.0f;
	double range_min_gly = 0.0f;
	double range_max_gly = 0.0f;

	printf("本程序演示用遗传算法求以下函数的极大值：\nf(x) = 0.4 + sinc(4*x) + 1.1*sinc(4*x + 2) + 0.8*sinc(6*x-2) + 0.7*sinc(6*x-4).");
	printf("请输入种群个体数： ");
	scanf("%d", &individual_num_gly);
	printf("请输入世代数： ");
	scanf("%d", &generation_num_gly);
	printf("请输入交叉率(0.2-0.8)： ");
	scanf("%lf", &crossover_rate_gly);  //在f之前加l则 scanf() 为 double 分配数据；
	printf("请输入变异率(0.01-0.05)： ");
	scanf("%lf", &mutation_rate_gly);
	printf("请输入个体取值下限： ");
	scanf("%lf", &range_min_gly);
	printf("请输入个体取值上限： ");
	scanf("%lf", &range_max_gly);

	*individual_num = individual_num_gly;
	*generation_num = generation_num_gly;
	*crossover_rate = crossover_rate_gly;
	*mutation_rate = mutation_rate_gly;
	*range_min = range_min_gly;
	*range_max = range_max_gly;

}; 

void generate_initial_population(int individual_num, //种群的个体数
								 double range_min,//个体取值的下限值
								 double range_max,//个体取值的上限值
								 individual_s *population)
{
	double range = range_max - range_min;
	double interval = range/(individual_num - 1);
	int i = 0;

	population[0].value = range_min;
	population[0].fitness = 0;
	for ( i = 1; i < individual_num; i++)
	{
		population[i].value = population[i-1].value + interval;
		population[i].fitness = 0;
	}
}

void calculate_fitness(int individual_num, individual_s *population, int get_max_or_min)
{
	int i = 0;
	double temp_value = 0;

	if ( get_max_or_min == GET_MAX )
	{
		double min_value = LONG_MAX;
		for (i = 0; i < individual_num; i++)
		{
			temp_value = f(population[i].value);
			if ( temp_value < min_value )
			{
				min_value = temp_value;
			}
		}

		for (i = 0; i < individual_num; i++)
		{
			population[i].fitness = f(population[i].value) - min_value + 1;
		}

	}
	else if (get_max_or_min == GET_MIN)
	{
		double max_value = LONG_MIN;
		for (i = 0; i < individual_num; i++)
		{
			temp_value = f(population[i].value);
			if ( temp_value > max_value)
			{
				max_value = temp_value;
			}
		}

		for (i = 0; i < individual_num; i++)
		{
			population[i].fitness = max_value - f(population[i].value) + 1;
		}

	}

};

void select_operator_roulette(int individual_num,  individual_s **population)
{
	int i = 0;
	double indi_sum = 0.0f, sum = 0.0f;
	double *accu_fitness = (double *)malloc(individual_num * sizeof(double));
	individual_s *new_population = (individual_s*)malloc(individual_num * sizeof(individual_s));

	for ( i = 0; i < individual_num; i++)
	{
		indi_sum += (*population)[i].fitness;
	}

	for (i = 0; i < individual_num; i++)
	{
		sum += (*population)[i].fitness/indi_sum;
		accu_fitness[i] = sum;
	}

	srand(time(NULL)); //设置随机数种子
	for (i = 0; i < individual_num; i++)
	{
		double rand_num = 0;
		int index = 0;

		rand_num = random_with_digit(0.0f, 1.0f, 4); 
		index = GA_binary_search(accu_fitness, rand_num, 0, individual_num-1);

		memset(&(new_population[i]), 0, sizeof(individual_s));
		new_population[i].value = (*population)[index].value;

	}

	free(*population);
	*population = NULL;

	*population = new_population;

	free(accu_fitness);
	accu_fitness = NULL;

}

void select_operator_elitist_strategy(int individual_num,  individual_s *population)
{
	int i = 0, min_fitness_index = -1, max_fitness_index = -1;
	double min_fitness = LONG_MAX, max_fitness = LONG_MIN, temp_fitness= 0;

	for (i = 0; i < individual_num; i++)
	{
		temp_fitness = population[i].fitness;
		if (temp_fitness < min_fitness)
		{
			min_fitness = temp_fitness;
			min_fitness_index = i;
		}
		if (temp_fitness > max_fitness)
		{
			max_fitness = temp_fitness;
			max_fitness_index = i;
		}
	}

	//replace the individual with minimum fitness by the individual with maximum fitness
	population[min_fitness_index].value = population[max_fitness_index].value;

};

void crossover_operator(int individual_num, individual_s *population, double crossover_rate)
{
	int i = 0;//循环变量；
	int cross_times = (int)(individual_num * crossover_rate);//交叉的次数；

	srand(time(NULL));

	for (i = 0; i < cross_times; i++)
	{
		int rand_1 = random(0, individual_num);
		int rand_2 = random(0, individual_num);
		double temp = 0;
		double cross_factor = random_with_digit(0.0, 1.0, 3);

		temp = population[rand_1].value;
		population[rand_1].value = cross_factor * population[rand_1].value + (1 - cross_factor) * population[rand_2].value;
		population[rand_2].value = (1 - cross_factor) * temp + cross_factor * population[rand_2].value;
	}
};

void mutate_operator(int individual_num, individual_s *population, double mutation_rate, double range_min, double range_max)
{
	int mutate_times = (int)(individual_num * mutation_rate), i = 0, rand_indi_index = 0;
	double rand_muta_factor = 0;

	if (range_max < range_min)
	{
		double temp = range_max;
		range_max = range_min;
		range_min = temp;
	}

	srand(time(NULL));

	for (i = 0; i < mutate_times; i++)
	{
		rand_muta_factor = random_with_digit(0.0f, 1.0f, 4);
		rand_indi_index = (int)random(0, individual_num);

		//x' = x + 2(a - 0.5)Xmax;
		population[rand_indi_index].value = population[rand_indi_index].value + 2 * (rand_muta_factor - 0.5) * (range_max - range_min);
	}
};

void GA(int individual_num, int generation_num, double crossover_rate, 
		double mutation_rate, double range_min, double range_max, individual_s **population, int get_max_or_min)
{
	int i = 0;

	*population = (individual_s*)malloc(individual_num*sizeof(individual_s));

	generate_initial_population(individual_num, range_min, range_max, *population);
	for ( i = 0; i < generation_num; i++)
	{
		calculate_fitness(individual_num, *population, get_max_or_min);
		//select_operator(individual_num, &population);
		select_operator_elitist_strategy(individual_num, *population);
		crossover_operator(individual_num, *population, crossover_rate);
		mutate_operator(individual_num, *population, mutation_rate, range_min, range_max);
	}

	calculate_fitness(individual_num, *population, get_max_or_min);
};

int find_best_individual_index(int individual_num, individual_s *population)
{
	double max_fitness = LONG_MIN;
	double instant_fitness = 0;
	int i = 0, max_fitness_index = -1;

	for (i = 0; i < individual_num; i++)
	{
		instant_fitness = population[i].fitness;
		if (instant_fitness > max_fitness)
		{
			max_fitness = instant_fitness;
			max_fitness_index = i;
		}
	}

	return max_fitness_index;

};

