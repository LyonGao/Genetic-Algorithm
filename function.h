#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#define PI  3.1415926  //Բ����PI�ĺ궨�塣

#ifdef __cplusplus
extern "C"{
#endif

//Ŀ�꺯��
double f(double x);

/*********************************************************************************
������
data����������˫���ȸ��������飻
key��������ֵ��
left_index����������ʼ�±ꣻ
right_index����������ֹ�±ꣻ
���ܣ��Ŵ��㷨�������������������data�д���key���򷵻�key���ڵ��±꣬���������
�򷵻�-1�����򷵻���ֹ�±ꡣ
*********************************************************************************/
int GA_binary_search(double *data, double key, int left_index, int right_index) ;

/********************************************************************************
������
from->�����������, to->�����������, digit_num->�����������С����λ��;
���ܣ������������
ע�⣺
1). digit_num�Ĵ�С��С��from��to�����С����λ��������from=0.005, to=0.01ʱ,
digit_num>=3��
***********************************************************************************/
double random_with_digit(double from, double to, int digit_num);

/**********************************************************************************
������
from->�����������, to->�����������;
���ܣ��������������С����λ����from��to������λ����
���磺
double rand = 0;
double from = 2.33;  //��λС����
double to = 3.898878  //��λС����
rand = random(from, to);  //rand����λС����
ע�⣺�˺�����Ҫ����С����λ��δ֪�������������
***********************************************************************************/
double random(double from, double to);

#ifdef __cplusplus
}
#endif

#endif