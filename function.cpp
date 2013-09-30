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
	保留n位小数的算法是：
	首先把from和to都乘以10的digit_num次方，得到new_from和new_to。如果此时
	new_from和new_to依然小于10的digit_num次方，则再递归地调用random。如果
	new_from或new_to其中之一大于10的digit_num次方，则无需再做乘方，把digit_num
	设置为0递归带入random。
	然后把random函数返回的随机数转化为int类型，截去随机数的小数，再除以10的
	digit_num次方就得到了digit_num位的数。

	例1：生成100到200之间带有2位小数的随机数。
	算法：
	1）将100和200同时乘以10的2此次方，得10000和20000，此时无需再递归；
	2）假设生成的随机数为15839，则返回到上一层函数将这个随机数取整后再除以
	10的2次方得到158.39，这个就是符合要求的随机数。

	例2：生成0.1到0.2之间的带有2位小数的随机数。
	算法：
	1）将0.1和0.2同时乘以10的2次方，得到10和20，依然比100小，继续递归调用，
	得到1000和2000，此时无需再递归；
	2）假设生成的随机数为1287，则返回到上一层函数将这个随机数取整后再除以10的2次方
	得到12.87；
	3）再返回到上一层函数，将这个数取整后除以10的2次方得到0.12，这个就是符合要求的数。
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


