#ifndef GPIO_H_
#define GPIO_H_

void Init_GPIO(void);

void setLED1(int onoff);
void setLED2(int onoff);

int getSW1(void);
int getSW2(void);

#endif /* GPIO_H_ */