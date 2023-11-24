#ifndef BUZZER_H_
#define BUZZER_H_

void IsrGpt120T3Handler_Beep(void);
void Init_Buzzer(void);
void setBeepCycle(int cycle);
void Beep(unsigned int hz);
void delay_ms(unsigned int delay_time);

#endif /* BUZZER_H_ */
