#ifndef GENETIC_ALGORITHM_H_INCLUDED
#define GENETIC_ALGORITHM_H_INCLUDED

//�궨�壬GET_MAX��ʾ���Ŵ��㷨�����ֵ��GET_MIN��ʾ���Ŵ��㷨����Сֵ
#define GET_MAX  1
#define GET_MIN  2

#ifdef __cplusplus
extern "C"{
#endif

//��ʾ��Ⱥ�и���Ľṹ��
typedef struct individual
{
	double value;
	double fitness;
}individual_s, *individual_pt;

/**********************************************************************
��ʼ��������
��ʼ����Ⱥ�еĸ��������������������ʣ������ʸ���ȡֵ����ȡ�
**********************************************************************/
void init(int *individual_num, int *generation_num, double *crossover_rate, 
		  double *mutation_rate, double *range_min, double *range_max); 

void GA(int individual_num, int generation_num, double crossover_rate, 
		double mutation_rate, double range_min, double range_max, individual_s **population, int get_max_or_min);

/*********************************************************************
������ʼ��Ⱥ
*********************************************************************/
void generate_initial_population(int individual_num, //��Ⱥ�ĸ�����
								 double range_min,//����ȡֵ������ֵ
							 double range_max,//����ȡֵ������ֵ
							 individual_s *population);

/**********************************************************************
���̶�ѡ������
������
����ÿ����������֮ǰ�����и������Ӧ���ۼӺͣ��γ�һ�������䣬
Ȼ�����һ������������������䵽�ĸ������ѡ���ĸ����塣
������
individual_num : ��Ⱥ�и�����
population : ��Ⱥ
**********************************************************************/
void select_operator_roulette(int individual_num,  individual_s **population);

/**********************************************************************
��Ӣ����ѡ������
������
ѡ�����Ⱥ����Ӧ�����ĸ������Ӧ����С�ĸ��壬��̭��Ӧ����С
�ĸ��壬����Ӧ�����ĸ����������
������
individual_num : ��Ⱥ�и�����
population : ��Ⱥ
**********************************************************************/
void select_operator_elitist_strategy(int individual_num,  individual_s *population);

/**********************************************************************
��������
������
�����ĸ���ֵ��������ʼ����ֵ֮�䡣
������
individual_num : ��Ⱥ�и�����
population : ��Ⱥ
crossover_rate : ������
**********************************************************************/
void crossover_operator(int individual_num, individual_s *population, double crossover_rate);

/**********************************************************************
��������
������
����ʹ��Ⱥ���ֶ����ԡ�
������
individual_num : ��Ⱥ�и�����
population : ��Ⱥ
mutation_rate : ������
range_min : ��������
range_max : ��������
**********************************************************************/
void mutate_operator(int individual_num, individual_s *population, double mutation_rate, 
					 double range_min, double range_max);

/*********************************************************************
������Ⱥ��ÿ���������Ӧ��
������
individual_num : ��Ⱥ�и�����
population : ��Ⱥ
get_max_or_min : ���Ŵ��㷨�������ֵ����Сֵ
*********************************************************************/
void calculate_fitness(int individual_num, individual_s *population, int get_max_or_min);

/*********************************************************************
Ѱ���Ŵ��㷨���������Ѹ�����±�
*********************************************************************/
int find_best_individual_index(int individual_num, individual_s *population);

#ifdef __cplusplus
}
#endif

#endif