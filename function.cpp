#include"function.h"
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

double sinc(double x)
{
	if (x == 0)
	{
		return 1;
	}
	else
	{
		return sin(PI*x)/(PI*x);
	}
}

double f(double x)
{
	return 0.4 + sinc(4*x) + 1.1*sinc(4*x + 2) + 0.8*sinc(6*x-2) + 0.7*sinc(6*x-4);
}

int GA_binary_search(double *data, double key, int left_index, int right_index) 
{
	int middle_index ;//the middle index of left_index and right_index

	//validate the input parameter
	if (data == NULL || left_index < 0 )
	{
		return -1;
	}

	//invalid index
	if (right_index == left_index)
	{
		return -1;
	}

	//sort the index
	if (left_index > right_index)
	{
		int temp = left_index;
		left_index = right_index;
		right_index = temp;
	}

	//if there are only two numbers left, then directly compares that two number to the key,
	//and then return a appropriate one.
	if (right_index - left_index == 1)
	{
		if (data[left_index] == key)
		{
			return left_index;
		}
		else if (data[right_index] == key)
		{
			return right_index;
		}
		else if(data[left_index] > key)
		{
			return left_index;
		}
		else
		{
			return right_index;
		}
	}

	middle_index = (left_index + right_index)/2;

	if (data[middle_index] == key)
	{
		return middle_index;
	}
	else if(data[middle_index] > key)
	{
		return data[left_index]>data[right_index] ? GA_binary_search(data, key, middle_index, right_index) : 
			GA_binary_search(data, key, left_index, middle_index) ;
	}
	else
	{
		return data[left_index]>data[right_index] ? GA_binary_search(data, key, left_index, middle_index) :
			GA_binary_search(data, key, middle_index, right_index);
	}

}

double random_with_digit(double from, double to, int digit_num)
{
	/***********************************************************************************
	����nλС�����㷨�ǣ�
	���Ȱ�from��to������10��digit_num�η����õ�new_from��new_to�������ʱ
	new_from��new_to��ȻС��10��digit_num�η������ٵݹ�ص���random�����
	new_from��new_to����֮һ����10��digit_num�η��������������˷�����digit_num
	����Ϊ0�ݹ����random��
	Ȼ���random�������ص������ת��Ϊint���ͣ���ȥ�������С�����ٳ���10��
	digit_num�η��͵õ���digit_numλ������

	��1������100��200֮�����2λС�����������
	�㷨��
	1����100��200ͬʱ����10��2�˴η�����10000��20000����ʱ�����ٵݹ飻
	2���������ɵ������Ϊ15839���򷵻ص���һ�㺯������������ȡ�����ٳ���
	10��2�η��õ�158.39��������Ƿ���Ҫ����������

	��2������0.1��0.2֮��Ĵ���2λС�����������
	�㷨��
	1����0.1��0.2ͬʱ����10��2�η����õ�10��20����Ȼ��100С�������ݹ���ã�
	�õ�1000��2000����ʱ�����ٵݹ飻
	2���������ɵ������Ϊ1287���򷵻ص���һ�㺯������������ȡ�����ٳ���10��2�η�
	�õ�12.87��
	3���ٷ��ص���һ�㺯�����������ȡ�������10��2�η��õ�0.12��������Ƿ���Ҫ�������
	************************************************************************************/

	if (digit_num > 0)
	{
		int next_digit_num = 0;
		double next_from = 0;
		double next_to = 0;

		double base = pow(10.0f, digit_num);

		next_from = from *  base;
		next_to = to * base;

		if ( (next_from >= base || next_to >= base || (-next_from) >= base || (-next_to) >= base) )
		{
			next_digit_num = 0;
		}
		else
		{
			next_digit_num = digit_num;
		}

		return ( (int)random_with_digit( next_from, next_to, next_digit_num) ) / base;
	}
	else
	{
		double interval = 0, rounded_from = 0, rounded_to = 0;
		int yushi = 0;

		if (from == to)
		{
			return from;
		}

		if (from > to)
		{
			int temp = from;
			from = to;
			to = temp;
		}

		rounded_from = ceil(from);
		rounded_to = ceil(to);

		interval = rounded_to - rounded_from;
		yushi = (int)interval;
		return from + rand()%yushi; 
	}

};

double random(double from, double to)
{
	int digit_num = 0;
	double temp_from = from;
	double temp_to = to;

	while ( (ceil(from) != from) || (ceil(to) != to) )
	{
		digit_num ++;
		from *= 10.0;
		to *= 10.0;
	}

	return random_with_digit(temp_from, temp_to, digit_num);

};


