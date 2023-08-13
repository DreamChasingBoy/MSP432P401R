/*
 * boyultrasonic.c
 *
 *  Created on: 2023��7��14��
 *      Author: BoyLuc׷����������
 */
#include "boyultrasonic.h"
/*************************************************
 * ��  ��  ��:boy_ultrasonic_init
 * ��       ��:��ʼ��������
 * ��       ��:��
 * ע �� �� �� :Ҫ�ǵý��δ�ʱ��ʹ�ܣ����������Ҫ�õ�
 *************************************************/
void boy_ultrasonic_init()
{
    systic_init();
    gpio_init(TRIG_PORT,TRIG_PIN,GPO,1);
    gpio_init(ECHO_PORT,ECHO_PIN,GPI,0);//��ʼ�����ͺͽ�������
}
/*************************************************
 * ��  ��  ��:boy_swap
 * ��       ��:�򵥵Ľ�����������
 * ��       ��:����Ҫ��������
 * ע �� �� �� :��
 *************************************************/
void boy_swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}
/*************************************************
 * ��  ��  ��:boy_bubbleSort
 * ��       ��:�򵥵�ð������
 * ��       ��:�������������С
 * ע �� �� �� :��
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
 * ��  ��  ��:boy_ultrasonic_median_filter
 * ��       ��:�򵥵���ֵ�˲�
 * ��       ��:�������������С
 * ע �� �� �� :��
 *************************************************/
float boy_ultrasonic_median_filter(float *data, int size)
{
    float sortedData[BOYULTRASONICBUFFSIZE];
    int i;
    // �������ݵ�������
    for (i = 0; i < size; i++)
    {
        sortedData[i] = data[i];
    }
    // ���������������
    boy_bubbleSort(sortedData, size);
    // ������ֵ
    if (size % 2 == 0)
    {// ���Ԫ�ظ���Ϊż���������м���������ƽ��ֵ
        return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2;
    }
    else
    {// ���Ԫ�ظ���Ϊ�����������м���
        return sortedData[size / 2];
    }
}
/*************************************************
 * ��  ��  ��:boy_ultrasonic_get_distance
 * ��       ��:��ȡ��ξ��룬ȡ��ֵ
 * ��       ��:�����С
 * ע �� �� �� :��
 *************************************************/
float boy_ultrasonic_get_distance(int size)
{
    float* distance = (float*)malloc(size * sizeof(float));  // ��̬�ڴ����
    float distance_out;
    int i;
    for (i = 0; i < size; i++)
    {
        distance[i] = HC_SR04_dis();
    }
    distance_out = boy_ultrasonic_median_filter(distance, size);
    free(distance);  // �ͷ��ڴ�
    return distance_out;
}
