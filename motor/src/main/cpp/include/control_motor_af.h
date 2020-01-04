#ifndef _MOTOR_AF_H
#define _MOTOR_AF_H
#include <jni.h>
int control_drv8846_motor_af(int motor_step, int motor_dir);
jbyte *readAfMotorPiState(void);
int motor_af_close(void);
#endif

