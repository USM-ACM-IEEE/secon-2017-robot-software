################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/RGBShield/Adafruit_RGBLCDShield.cpp 

LINK_OBJ += \
./libraries/RGBShield/Adafruit_RGBLCDShield.cpp.o 

CPP_DEPS += \
./libraries/RGBShield/Adafruit_RGBLCDShield.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/RGBShield/Adafruit_RGBLCDShield.cpp.o: ../libraries/RGBShield/Adafruit_RGBLCDShield.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/luc_lagarde/Archive/Applications/Eclipse/Eclipse (Sloeber)//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/luc_lagarde/Archive/Applications/Eclipse/Eclipse (Sloeber)/arduinoPlugin/packages/arduino/hardware/avr/1.6.17/cores/arduino" -I"/home/luc_lagarde/Archive/Applications/Eclipse/Eclipse (Sloeber)/arduinoPlugin/packages/arduino/hardware/avr/1.6.17/variants/mega" -I"/home/luc_lagarde/Archive/Applications/Eclipse/Eclipse (Sloeber)/arduinoPlugin/packages/arduino/hardware/avr/1.6.17/libraries/Wire" -I"/home/luc_lagarde/Archive/Applications/Eclipse/Eclipse (Sloeber)/arduinoPlugin/packages/arduino/hardware/avr/1.6.17/libraries/Wire/src" -I"/home/luc_lagarde/Archive/Applications/Eclipse/Eclipse (Sloeber)/arduinoPlugin/libraries/Servo/1.1.1" -I"/home/luc_lagarde/Archive/Applications/Eclipse/Eclipse (Sloeber)/arduinoPlugin/libraries/Servo/1.1.1/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


