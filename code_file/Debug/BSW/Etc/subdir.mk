################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/Etc/etc.c \
../BSW/Etc/my_stdio.c 

COMPILED_SRCS += \
./BSW/Etc/etc.src \
./BSW/Etc/my_stdio.src 

C_DEPS += \
./BSW/Etc/etc.d \
./BSW/Etc/my_stdio.d 

OBJS += \
./BSW/Etc/etc.o \
./BSW/Etc/my_stdio.o 


# Each subdirectory must supply rules for building sources it contributes
BSW/Etc/%.src: ../BSW/Etc/%.c BSW/Etc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Hyundai_Autoever/TC275_Second_Project/TC275 shieldbuddy/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/BSW\/Etc\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

BSW/Etc/%.o: ./BSW/Etc/%.src BSW/Etc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-BSW-2f-Etc

clean-BSW-2f-Etc:
	-$(RM) ./BSW/Etc/etc.d ./BSW/Etc/etc.o ./BSW/Etc/etc.src ./BSW/Etc/my_stdio.d ./BSW/Etc/my_stdio.o ./BSW/Etc/my_stdio.src

.PHONY: clean-BSW-2f-Etc

