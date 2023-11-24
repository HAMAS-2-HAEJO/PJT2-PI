#ifndef MOTOR_H_
#define MOTOR_H_

void IsrGpt2T6Handler(void);

void Init_DCMotors(void);

void movChA(int dir);
void movChB(int dir);

void stopChA(void);
void stopChB(void);

void movChA_PWM(int duty, int dir);
void movChB_PWM(int duty, int dir);

#endif /* MOTOR_H_ */
