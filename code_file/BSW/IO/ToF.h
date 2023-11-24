#ifndef TOF_H_
#define TOF_H_

static int verifyCheckSum(unsigned char data[]);
static int checkTofStrength(unsigned char data[]);

extern void Init_ToF(void);
extern int getTofDistance(void);

#endif /* TOF_H_ */
