#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

void Init_Ultrasonics(void);
float ReadRearUltrasonic_noFilt(void);
float ReadRearUltrasonic_Filt(void);
float ReadLeftUltrasonic_noFilt(void);
float ReadLeftUltrasonic_Filt(void);
float ReadRightUltrasonic_noFilt(void);
float ReadRightUltrasonic_Filt(void);

#define FILT_SIZE 5

#endif /* ULTRASONIC_H_ */
