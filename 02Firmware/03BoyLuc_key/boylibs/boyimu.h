/*
 * boyimu.h
 *
 *  Created on: 2023年8月1日
 *      Author: 26491
 */

#ifndef BOYLIBS_BOYIMU_H_
#define BOYLIBS_BOYIMU_H_
#include "exinlibs\headfile.h"
//宏定义区
#define PI 3.1415926f
#define squa( Sq )        (((float)Sq)*((float)Sq))
#define absu16( Math_X )  ((Math_X)<0? -(Math_X):(Math_X))
#define absFloat( Math_X )((Math_X)<0? -(Math_X):(Math_X))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define LIMIT( x, min, max ) ( (x) <= (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
//数据结构声明
typedef struct{
    float roll;
    float pitch;
    float yaw;
}Attitude_t;

typedef struct {  //四元数
  float q0;
  float q1;
  float q2;
  float q3;
} Quaternion;

//Extern引用
extern Attitude_t g_Attitude;    //当前角度姿态值
extern const float AtR;
extern const float RtA;
extern const float Gyro_G;
extern const float Gyro_Gr;

//函数声明
extern float safe_asin(float v);
extern float arcsin(float x);
extern float arctan(float x);
extern float sine(float x);
extern float cosine(float x);
extern float Q_rsqrt(float number);
extern float VariableParameter(float error);

//函数声明
float GetNormAccz(void);
void ATT_Update(const MPU6050Manager_t *pMpu,Attitude_t *pAngE, float dt);
void GetAngle(Attitude_t *pAngE);
void IMU_Reset(void);
#endif /* BOYLIBS_BOYIMU_H_ */
