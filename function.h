#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#define PI  3.1415926  //圆周率PI的宏定义。

#ifdef __cplusplus
extern "C"{
#endif

//目标函数
double f(double x);

/*********************************************************************************
参数：
data：待搜索的双精度浮点数数组；
key：搜索键值；
left_index：搜索的起始下标；
right_index：搜索的终止下标；
功能：遗传算法二分搜索法，如果数组data中存在key，则返回key所在的下标，如果出错，
则返回-1，否则返回终止下标。
*********************************************************************************/
int GA_binary_search(double *data, double key, int left_index, int right_index) ;

/********************************************************************************
参数：
from->随机数的下限, to->随机数的上限, digit_num->随机数保留的小数点位数;
功能：生成随机数；
注意：
1). digit_num的大小不小于from和to的最大小数点位数，比如from=0.005, to=0.01时,
digit_num>=3。
***********************************************************************************/
double random_with_digit(double from, double to, int digit_num);

/**********************************************************************************
参数：
from->随机数的下限, to->随机数的上限;
功能：生成随机数，其小数点位数是from和to中最大的位数；
比如：
double rand = 0;
double from = 2.33;  //两位小数；
double to = 3.898878  //六位小数；
rand = random(from, to);  //rand有六位小数；
注意：此函数主要用于小数点位数未知的数求随机数。
***********************************************************************************/
double random(double from, double to);

#ifdef __cplusplus
}
#endif

#endif