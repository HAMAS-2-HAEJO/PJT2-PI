################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/IO/Bluetooth.c \
../BSW/IO/Buzzer.c \
../BSW/IO/GPIO.c \
../BSW/IO/Motor.c \
../BSW/IO/ToF.c \
../BSW/IO/Ultrasonic.c 

COMPILED_SRCS += \
./BSW/IO/Bluetooth.src \
./BSW/IO/Buzzer.src \
./BSW/IO/GPIO.src \
./BSW/IO/Motor.src \
./BSW/IO/ToF.src \
./BSW/IO/Ultrasonic.src 

C_DEPS += \
./BSW/IO/Bluetooth.d \
./BSW/IO/Buzzer.d \
./BSW/IO/GPIO.d \
./BSW/IO/Motor.d \
./BSW/IO/ToF.d \
./BSW/IO/Ultrasonic.d 

OBJS += \
./BSW/IO/Bluetooth.o \
./BSW/IO/Buzzer.o \
./BSW/IO/GPIO.o \
./BSW/IO/Motor.o \
./BSW/IO/ToF.o \
./BSW/IO/Ultrasonic.o 


# Each subdirectory must supply rules for building sources it contributes
BSW/IO/%.src: ../BSW/IO/%.c BSW/IO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Hyundai_Autoever/TC275_Second_Project/TC275 shieldbuddy/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/BSW\/IO\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

BSW/IO/%.o: ./BSW/IO/%.src BSW/IO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-BSW-2f-IO

clean-BSW-2f-IO:
	-$(RM) ./BSW/IO/Bluetooth.d ./BSW/IO/Bluetooth.o ./BSW/IO/Bluetooth.src ./BSW/IO/Buzzer.d ./BSW/IO/Buzzer.o ./BSW/IO/Buzzer.src ./BSW/IO/GPIO.d ./BSW/IO/GPIO.o ./BSW/IO/GPIO.src ./BSW/IO/Motor.d ./BSW/IO/Motor.o ./BSW/IO/Motor.src ./BSW/IO/ToF.d ./BSW/IO/ToF.o ./BSW/IO/ToF.src ./BSW/IO/Ultrasonic.d ./BSW/IO/Ultrasonic.o ./BSW/IO/Ultrasonic.src

.PHONY: clean-BSW-2f-IO

