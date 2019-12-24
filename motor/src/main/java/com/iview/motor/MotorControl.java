package com.iview.motor;

public class MotorControl {
    static {
        System.loadLibrary("stepmotor");
    }

    public static final int HMotor = 1;
    public static final int VMotor = 2;

    public static final int HMotorLeftDirection = 0;
    public static final int HMotorRightDirection = 1;

    public static final int VMotorUpDirection = 0;
    public static final int VMotorDownDirection = 1;

    public static final int PROJECTOR_ON = 1;
    public static final int PROJECTOR_OFF = 0;

    public static int controlMotor(int motorId, int steps, int dir, int delay) {
        return  controlMotor(motorId, steps, dir, delay, true);
    }

    /**
     * control motor running
     * @param motorId
    {
    @link HMotor horizontal motor
    @link VMotor vertical motor
    }
     * @param steps : numbers of PWM pluse
     * @param dir : direction
     * {
    @link    HMotorLeftDirection
    @link    HMotorRightDirection
    @link    VMotorUpDirection
    @link    VMotorDownDirection
     * }
     * @param delay: pluse duration (unit:ns)
     * @param bCheckLimitSwitch: whether to check photocoupler signal
     * @return  0 success, other:fail
     */
    public static int controlMotor(int motorId, int steps, int dir, int delay, boolean bCheckLimitSwitch) {
        return nativeControlMotor(motorId, steps, dir, delay, bCheckLimitSwitch);
    }

    /**
     * Stop motor running
     * @param motorId
    {
    @link HMotor horizontal motor
    @link VMotor vertical motor
    }
     */
    public static int stopMotorRunning(int motorId) {
        return nativeStopMotorRunning(motorId);
    }


    /**
     * Turn on/off projector
     * @param enable  1: on, 0:off
     */
    public static void swtichProjector(int enable) {
        nativeSwitchProjector(enable);
    }

    /**
     * set keystone
     * @param angle:  -40 ~ 40
     */
    public static void setKeyStone(int angle) {
        nativeSetKeyStone(angle);
    }


    private native static int nativeControlMotor(int motorId, int steps, int dir, int delay, boolean bCheckLimitSwitch);

    private native static int nativeStopMotorRunning(int motorId);

    private native static void nativeSwitchProjector(int enable);

    private native static void nativeSetKeyStone(int angle);
}
