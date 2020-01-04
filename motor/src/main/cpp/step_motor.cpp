//
// Created by llm on 19-8-13.
//
#include <jni.h>
#include <android/log.h>

extern "C"{
#include "motor_common.h"
}

#define LOG_TAG    "step_motor"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define H_MOTOR_ID 1
#define V_MOTOR_ID 2

extern "C" JNIEXPORT jint
Java_com_iview_motor_MotorControl_nativeControlMotor(
        JNIEnv *env,
        jobject /* this */,jint motorId, jint steps, jint dir, jint delay, jboolean bCheckLimitSwitch) {
    LOGD("nativeControlMotor");
    if (motorId == H_MOTOR_ID) {
        return controlHorizontalMotor(steps, dir, delay, bCheckLimitSwitch);
    } else if (motorId == V_MOTOR_ID) {
        return controlVerticalMotor(steps, dir, delay, bCheckLimitSwitch);
    }
}

extern "C" JNIEXPORT jint
Java_com_iview_motor_MotorControl_nativeSetMotorSpeed(
        JNIEnv *env,
        jobject /* this */,jint motorId, jint delay) {
    LOGD("nativeSetMotorSpeed");
    if (motorId == H_MOTOR_ID) {
        return setHorizontalMotorSpeed(delay);
    } else if (motorId == V_MOTOR_ID) {
        return setVerticalMotorSpeed(delay);
    }
}

extern "C" JNIEXPORT jint
Java_com_iview_motor_MotorControl_nativeSetMotorDirection(
        JNIEnv *env,
        jobject /* this */,jint motorId, jint direction) {
    LOGD("nativeSetMotorDirection");
    if (motorId == H_MOTOR_ID) {
        return setHorizontalMotorDirection(direction);
    } else if (motorId == V_MOTOR_ID) {
        return setVerticalMotorDirection(direction);
    }
}

extern "C" JNIEXPORT jint
Java_com_iview_motor_MotorControl_nativeStartMotorRunning(
        JNIEnv *env,
        jobject /* this */,jint motorId, jboolean bCheckLimitSwitch) {
    LOGD("nativeStartMotorRunning");
    if (motorId == H_MOTOR_ID) {
        return startHMotorRunning(bCheckLimitSwitch);
    } else if (motorId == V_MOTOR_ID) {
        return startVMotorRunning(bCheckLimitSwitch);
    }
}

extern "C" JNIEXPORT jint
Java_com_iview_motor_MotorControl_nativeStopMotorRunning(
        JNIEnv *env,
        jobject /* this */,jint motorId) {
    LOGD("nativeStopMotorRunning");
    if (motorId == H_MOTOR_ID) {
        return stopHMotorRunning();
    } else if (motorId == V_MOTOR_ID) {
        return stopVMotorRunning();
    }
}

extern "C" JNIEXPORT jboolean
Java_com_iview_motor_MotorControl_nativeGetMotorEnable(
        JNIEnv *env,
        jobject /* this */,jint motorId) {
    LOGD("nativeGetMotorEnable");
    if (motorId == H_MOTOR_ID) {
        return getHMotorEnable();
    } else if (motorId == V_MOTOR_ID) {
        return getVMotorEnable();
    }
}

extern "C" JNIEXPORT void
Java_com_iview_motor_MotorControl_nativeControlMultiMotors(
        JNIEnv *env,
        jobject /* this */,jint hSteps, jint vSteps, jint hDir, jint vDir, jint delay, jboolean bCheckLimitSwitch) {
    LOGD("nativeControlMotor %d, %d, %d", hSteps, vSteps, delay);
    if (hSteps == 0 || vSteps == 0) {
        return;
    }

    controlMultipleMotors(hSteps, vSteps, hDir, vDir, delay, bCheckLimitSwitch);
}

extern "C" JNIEXPORT void
Java_com_iview_motor_MotorControl_nativeStopMultiMotors(
        JNIEnv *env,
        jobject /* this */) {
    LOGD("nativeStopMultiMotors");

    stopMultipleMotors();
}

extern "C" JNIEXPORT jint
Java_com_iview_motor_MotorControl_nativeGetMotorSteps(
        JNIEnv *env,
        jobject /* this */, jint motorId) {
    LOGD("nativeGetMotorSteps");

    if (motorId == H_MOTOR_ID) {
        return getHMotorSteps();
    } else if (motorId == V_MOTOR_ID) {
        return getVMotorSteps();
    }
}




