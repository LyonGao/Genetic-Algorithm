#ifndef GENETIC_ALGORITHM_H_INCLUDED
#define GENETIC_ALGORITHM_H_INCLUDED

//宏定义，GET_MAX表示此遗传算法求最大值，GET_MIN表示此遗传算法求最小值
#define GET_MAX  1
#define GET_MIN  2

#ifdef __cplusplus
extern "C"{
#endif

//表示种群中个体的结构体
typedef struct individual
{
	double value;
	double fitness;
}individual_s, *individual_pt;

/**********************************************************************
初始化函数；
初始化种群中的个体数，世代数，交叉率，变异率个体取值区间等。
**********************************************************************/
void init(int *individual_num, int *generation_num, double *crossover_rate, 
		  double *mutation_rate, double *range_min, double *range_max); 

void GA(int individual_num, int generation_num, double crossover_rate, 
		double mutation_rate, double range_min, double range_max, individual_s **population, int get_max_or_min);

/*********************************************************************
产生初始种群
*********************************************************************/
void generate_initial_population(int individual_num, //种群的个体数
								 double range_min,//个体取值的下限值
							 double range_max,//个体取值的上限值
							 individual_s *population);

/**********************************************************************
轮盘赌选择算子
概述：
计算每个个体与其之前的所有个体的适应度累加和，形成一个个区间，
然后产生一个随机数，这个随机数落到哪个区间就选中哪个个体。
参数：
individual_num : 种群中个体数
population : 种群
**********************************************************************/
void select_operator_roulette(int individual_num,  individual_s **population);

/**********************************************************************
精英策略选择算子
概述：
选择出种群中适应度最大的个体和适应度最小的个体，淘汰适应度最小
的个体，用适应度最大的个体代替它。
参数：
individual_num : 种群中个体数
population : 种群
**********************************************************************/
void select_operator_elitist_strategy(int individual_num,  individual_s *population);

/**********************************************************************
交叉算子
概述：
交叉后的个体值在两个初始个体值之间。
参数：
individual_num : 种群中个体数
population : 种群
crossover_rate : 交叉率
**********************************************************************/
void crossover_operator(int individual_num, individual_s *population, double crossover_rate);

/**********************************************************************
变异算子
概述：
变异使种群保持多样性。
参数：
individual_num : 种群中个体数
population : 种群
mutation_rate : 变异率
range_min : 区间下限
range_max : 区间上限
**********************************************************************/
void mutate_operator(int individual_num, individual_s *population, double mutation_rate, 
					 double range_min, double range_max);

/*********************************************************************
计算种群中每个个体的适应度
参数：
individual_num : 种群中个体数
population : 种群
get_max_or_min : 此遗传算法是求最大值或最小值
*********************************************************************/
void calculate_fitness(int individual_num, individual_s *population, int get_max_or_min);

/*********************************************************************
寻找遗传算法结束后的最佳个体的下标
*********************************************************************/
int find_best_individual_index(int individual_num, individual_s *population);

#ifdef __cplusplus
}
#endif

#endif