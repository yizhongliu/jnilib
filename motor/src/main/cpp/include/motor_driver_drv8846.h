#ifndef _MOTOR_H
#define _MOTOR_H
//int Get_electric_focuse_project(int dir, int step, int delay);
//int Set_motor_pwm_run(int speed, int dir, int motor_step);
int Set_motor_mode(int mode0, int mode1);
int Set_motor_pwm_run(int speed, int motor_step, int motor_num);
int Set_motor_step(int motor_step_num, int step);
int Get_pi_state(int gpio_num, int gpio_state);
int Set_motor_on_off(int gpio_num, int gpio_state);
int Init_motor_return(int dir);
int init_motor(void);
#endif

