################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AppScheduling.c \
../Blinky_LED.c \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../Driver_Stm.c \
../Driver_Watchdog.c \
../DrvAdc.c \
../GtmTomPwmHlDemo.c \
../MidAdc.c 

COMPILED_SRCS += \
./AppScheduling.src \
./Blinky_LED.src \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./Driver_Stm.src \
./Driver_Watchdog.src \
./DrvAdc.src \
./GtmTomPwmHlDemo.src \
./MidAdc.src 

C_DEPS += \
./AppScheduling.d \
./Blinky_LED.d \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./Driver_Stm.d \
./Driver_Watchdog.d \
./DrvAdc.d \
./GtmTomPwmHlDemo.d \
./MidAdc.d 

OBJS += \
./AppScheduling.o \
./Blinky_LED.o \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./Driver_Stm.o \
./Driver_Watchdog.o \
./DrvAdc.o \
./GtmTomPwmHlDemo.o \
./MidAdc.o 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Hyundai_Autoever/TC275_Second_Project/TC275 shieldbuddy/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./AppScheduling.d ./AppScheduling.o ./AppScheduling.src ./Blinky_LED.d ./Blinky_LED.o ./Blinky_LED.src ./Cpu0_Main.d ./Cpu0_Main.o ./Cpu0_Main.src ./Cpu1_Main.d ./Cpu1_Main.o ./Cpu1_Main.src ./Cpu2_Main.d ./Cpu2_Main.o ./Cpu2_Main.src ./Driver_Stm.d ./Driver_Stm.o ./Driver_Stm.src ./Driver_Watchdog.d ./Driver_Watchdog.o ./Driver_Watchdog.src ./DrvAdc.d ./DrvAdc.o ./DrvAdc.src ./GtmTomPwmHlDemo.d ./GtmTomPwmHlDemo.o ./GtmTomPwmHlDemo.src ./MidAdc.d ./MidAdc.o ./MidAdc.src

.PHONY: clean--2e-

