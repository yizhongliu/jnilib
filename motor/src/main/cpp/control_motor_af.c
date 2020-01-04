/*****************************************
	Copyright  : iview Tech. Co., Ltd.
	Description: Control logic of focusing motor
	Author     : carterli
	Version	   : v1.4
	Date       : 2019-4-30
	History    : V4.0
****************************************/
#include "./include/motor_driver_drv8846.h"
#include "./include/motor_common.h"
#include "./include/control_motor_af.h"
#include <android/log.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <linux/input.h>
#define MOTOR_DRV_AF     "/dev/motor_gpio_af"

#define LOG_TAG    "control_motor_af"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static int fd_motor_af = 0;
static struct motor_a3901 userdata_motor[3];
static struct timeval tv;
static struct timeval ts;
static int iCruTime = 0;

//extern int gAfBackFlag;
//extern int gAfForwardFlag;
//extern double motorSpeedAf;

int gAfBackFlag = 1;
int gAfForwardFlag = 1;
double motorSpeedAf = 2000;

static int motor_power_on_state_af = 0;
//static int motor_prev_dir  = 0;//记录前一个运动方向 1.left 0.right
static int motor_af_left_pi_state = 0;
static int motor_af_right_pi_state = 0;
static struct timeval start;
static struct timeval end;//struct timezone tz; //后面有说明
/*off motor 0:sleep 1:on*/
static int Set_motor_on_off_af(int gpio_num, int gpio_state)
{
	userdata_motor[0].gpio_num   = gpio_num;
	userdata_motor[0].gpio_state = gpio_state;
	if((ioctl(fd_motor_af, VS_SET_MOTOR_ENABLE, &userdata_motor)) < 0)
	{
		LOGE("%s ioctl error1", __FUNCTION__);
		return -1;
	}
	return 1;
}

static unsigned char Get_pi_state_af(int gpio_num, int gpio_state)
{
	userdata_motor[0].gpio_num   = gpio_num;
	userdata_motor[0].gpio_state = gpio_state;
	if((ioctl(fd_motor_af, VS_GET_GPIO, &userdata_motor)) < 0)
	{
		LOGE("%s VIDIOC_DQBUF motor1 error!\n", __FUNCTION__);
		return -1;
	}
	return userdata_motor[0].gpio_state;
}

static int Set_motor_step_af(int motor_step_num, int step)
{
	userdata_motor[0].gpio_num   = motor_step_num;
	userdata_motor[0].gpio_state = step;
	if((ioctl(fd_motor_af, VS_SET_MOTOR_ENABLE, &userdata_motor)) < 0)
	{
		LOGE("%s ioctl error2", __FUNCTION__);
		return -1;
	}
	return 1;
}

static int Set_motor_dir_af(int motor_dir_num, int dir)
{
	userdata_motor[0].gpio_num   = motor_dir_num;
	userdata_motor[0].gpio_state = dir;
	if((ioctl(fd_motor_af, VS_SET_MOTOR_ENABLE, &userdata_motor)) < 0)
	{
		LOGE("%s ioctl error3", __FUNCTION__);
		return -1;
	}
	return 1;
}

static int Set_motor_pwm_run_af(int motor_step, int motor_num, int motor_dir)
{
    tv.tv_sec = 0;
    tv.tv_usec = motorSpeedAf;
	static int motor_out_pwm = 0;
	Set_motor_step_af(motor_num, motor_out_pwm);

	LOGE("get pi state: %d", Get_pi_state_af(MOTO_SENSOR_AF_1, 0));

	while(motor_step--)
	{
	    if (motor_dir == 0) {
            if (Get_pi_state_af(MOTO_SENSOR_AF_1, 0) == 1) {
                LOGE("reach far end");
                break;
            }
	    }
/*
		if(motor_dir == 1){//left press
            if(Get_pi_state_af(MOTO_SENSOR_AF_1, 0) == 0){
            if(motor_power_on_state_af == 0){
                LOGI("111111");
                break;
            }
            if(motor_af_right_pi_state == 0){
                motor_af_left_pi_state = 1;
                break;
            }
        }
        else{
        		motor_af_right_pi_state = 0;
        		motor_af_left_pi_state = 0;
        	}
        }
        else{//right press
        		  if(Get_pi_state_af(MOTO_SENSOR_AF_1, 0) == 0){
                  if(motor_power_on_state_af == 0){
                            LOGI("3333333");
                            break;
                  }
                  if(motor_af_left_pi_state == 0){
                            motor_af_right_pi_state = 1;
                            break;
                  }
             }
                 else{
                       motor_af_right_pi_state = 0;
                       motor_af_left_pi_state = 0;
                  }

        }
*/
		motor_out_pwm = !motor_out_pwm;
		Set_motor_step_af(motor_num, motor_out_pwm);
		tv.tv_sec = 0;
		tv.tv_usec = motorSpeedAf;
		//select(0, NULL, NULL, NULL, &tv);
		gettimeofday(&start, NULL); //gettimeofday(&start,&tz);结果一样
                        		while(1){
                        		    gettimeofday(&end, NULL);
                        		    if(((end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec)) >=  motorSpeedAf){
                        		        break;
                        		    }
                        		}
		motor_out_pwm = !motor_out_pwm;
		Set_motor_step_af(motor_num, motor_out_pwm);
		tv.tv_sec = 0;
		tv.tv_usec = motorSpeedAf;
		//select(0, NULL, NULL, NULL, &tv);
		gettimeofday(&start, NULL); //gettimeofday(&start,&tz);结果一样
                                		while(1){
                                		    gettimeofday(&end, NULL);
                                		    if(((end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec)) >=  motorSpeedAf){
                                		        break;
                                		    }
                                		}
		motor_power_on_state_af = 1;
		if(gAfBackFlag == 0 && gAfForwardFlag == 0)
		{
		    break;
		}

		LOGE("Set motor pwm run af");
	}
	return 1;
	//return Get_pi_state_af(MOTO_SENSOR4_1, 0);

}

//void thread_drv8846_motor_af(void *arg)
int control_drv8846_motor_af(int motor_step, int motor_dir)
{
	int pi_state;
	fd_motor_af = open(MOTOR_DRV_AF, O_RDWR);
	LOGE("control_drv8846_motor_af %d, %d", motor_step, motor_dir);
	if(fd_motor_af == -1)
	{
		LOGE("%s open af_motor_device error..........!\n", __FUNCTION__);
		return -1;
	}
	Set_motor_on_off_af(MOTO_ENABLE_AF, MOTOR_DISABLE);
	Set_motor_dir_af(MOTO_DIR_AF, motor_dir);
	pi_state = Set_motor_pwm_run_af(motor_step, MOTO_STEP_AF, motor_dir);
	Set_motor_on_off_af(MOTO_ENABLE_AF, MOTOR_ENABLE);
	close(fd_motor_af);
	fd_motor_af = 0;
	return pi_state;
}

jbyte *readAfMotorPiState(void)
{
    static jbyte  pi_buf[2];
    if(fd_motor_af == 0)
    {
            fd_motor_af = open(MOTOR_DRV_AF, O_RDWR);
        	if(fd_motor_af == -1)
        	{
        		LOGE("%s open af_motor_device error..........!\n", __FUNCTION__);
        		return NULL;
        	}
        	//LOGI("%s %d", TAG, fd_motor_af);
        	pi_buf[0] = Get_pi_state_af(MOTO_SENSOR_AF_1, 0);
        	pi_buf[1] = Get_pi_state_af(MOTO_SENSOR_AF_2, 0);
        	close(fd_motor_af);
        	fd_motor_af = 0;
        	return pi_buf;
    }
    else
    {
        pi_buf[0] = Get_pi_state_af(MOTO_SENSOR_AF_1, 0);
        pi_buf[1] = Get_pi_state_af(MOTO_SENSOR_AF_2, 0);
        return pi_buf;
    }
    return pi_buf;
}

int motor_af_close(void)
{

        motor_power_on_state_af = 0;
        //static int motor_prev_dir  = 0;//记录前一个运动方向 1.left 0.right
        motor_af_left_pi_state = 0;
        motor_af_right_pi_state = 0;
        if(fd_motor_af == 0)
        {
                fd_motor_af = open(MOTOR_DRV_AF, O_RDWR);
            	if(fd_motor_af == -1)
            	{
            		LOGE("%s open af_motor_device error..........!\n", __FUNCTION__);
            		return -1;
            	}
            	Set_motor_on_off_af(MOTO_ENABLE_AF, MOTOR_ENABLE);
            	close(fd_motor_af);
            	fd_motor_af = 0;
        }
        else
        {
            Set_motor_on_off_af(MOTO_ENABLE_AF, MOTOR_ENABLE);
        }
        return 1;
}