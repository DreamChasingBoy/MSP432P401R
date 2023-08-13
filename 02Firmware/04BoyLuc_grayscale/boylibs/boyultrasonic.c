/*
 * boyultrasonic.c
 *
 *  Created on: 2023年7月14日
 *      Author: BoyLuc追梦少年南南
 */
#include "boyultrasonic.h"
/*************************************************
 * 函  数  名:boy_ultrasonic_init
 * 功       能:初始化超声波
 * 参       数:无
 * 注 意 事 项 :要记得将滴答定时器使能，接下来测距要用到
 *************************************************/
void boy_ultrasonic_init()
{
    systic_init();
    gpio_init(TRIG_PORT,TRIG_PIN,GPO,1);
    gpio_init(ECHO_PORT,ECHO_PIN,GPI,0);//初始化发送和接收引脚
}
/*************************************************
 * 函  数  名:boy_swap
 * 功       能:简单的交换两个变量
 * 参       数:两个要交换的数
 * 注 意 事 项 :无
 *************************************************/
void boy_swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}
/*************************************************
 * 函  数  名:boy_bubbleSort
 * 功       能:简单的冒泡排序
 * 参       数:数组名，数组大小
 * 注 意 事 项 :无
 *************************************************/
void boy_bubbleSort(float *data, int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                boy_swap(&data[j], &data[j + 1]);
            }
        }
    }
}
/*************************************************
 * 函  数  名:boy_ultrasonic_median_filter
 * 功       能:简单的中值滤波
 * 参       数:数组名，数组大小
 * 注 意 事 项 :无
 *************************************************/
float boy_ultrasonic_median_filter(float *data, int size)
{
    float sortedData[BOYULTRASONICBUFFSIZE];
    int i;
    // 复制数据到新数组
    for (i = 0; i < size; i++)
    {
        sortedData[i] = data[i];
    }
    // 对新数组进行排序
    boy_bubbleSort(sortedData, size);
    // 返回中值
    if (size % 2 == 0)
    {// 如果元素个数为偶数，返回中间两个数的平均值
        return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2;
    }
    else
    {// 如果元素个数为奇数，返回中间数
        return sortedData[size / 2];
    }
}
/*************************************************
 * 函  数  名:boy_ultrasonic_get_distance
 * 功       能:读取多次距离，取中值
 * 参       数:数组大小
 * 注 意 事 项 :无
 *************************************************/
float boy_ultrasonic_get_distance(int size)
{
    float* distance = (float*)malloc(size * sizeof(float));  // 动态内存分配
    float distance_out;
    int i;
    for (i = 0; i < size; i++)
    {
        distance[i] = HC_SR04_dis();
    }
    distance_out = boy_ultrasonic_median_filter(distance, size);
    free(distance);  // 释放内存
    return distance_out;
}
