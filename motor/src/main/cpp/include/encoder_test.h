#ifndef ENCODER_HHH
#define ENCODER_HHH
int getEncoder0Data(int dir);
int getEncoder1Data(int dir);
int setEncoder1Data(int dir);
int setEncoder0Data(int dir);

int setEncoder0(int dir, int value);
int setEncoder1(int dir, int value);
#endif