#ifndef BSW_IO_BLUETOOTH_H_
#define BSW_IO_BLUETOOTH_H_

void Init_Bluetooth(void);
void setBluetoothName(char *name);
void setBluetoothPswd(char *pswd);

char getBluetoothByte_Blocked(void);
char getBluetoothByte_nonBlocked(void);
void setBluetoothByte_Blocked(unsigned char ch);
void bl_printf(const char *fmt, ...);

#endif /* BSW_IO_BLUETOOTH_H_ */
