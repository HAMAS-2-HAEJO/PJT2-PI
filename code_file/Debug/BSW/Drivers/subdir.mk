################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/Drivers/GPT12.c \
../BSW/Drivers/asclin.c 

COMPILED_SRCS += \
./BSW/Drivers/GPT12.src \
./BSW/Drivers/asclin.src 

C_DEPS += \
./BSW/Drivers/GPT12.d \
./BSW/Drivers/asclin.d 

OBJS += \
./BSW/Drivers/GPT12.o \
./BSW/Drivers/asclin.o 


# Each subdirectory must supply rules for building sources it contributes
BSW/Drivers/%.src: ../BSW/Drivers/%.c BSW/Drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Hyundai_Autoever/TC275_Second_Project/TC275 shieldbuddy/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/BSW\/Drivers\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

BSW/Drivers/%.o: ./BSW/Drivers/%.src BSW/Drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-BSW-2f-Drivers

clean-BSW-2f-Drivers:
	-$(RM) ./BSW/Drivers/GPT12.d ./BSW/Drivers/GPT12.o ./BSW/Drivers/GPT12.src ./BSW/Drivers/asclin.d ./BSW/Drivers/asclin.o ./BSW/Drivers/asclin.src

.PHONY: clean-BSW-2f-Drivers

