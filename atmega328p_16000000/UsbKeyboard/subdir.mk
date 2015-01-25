################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UsbKeyboard/oddebug.c \
../UsbKeyboard/usbdrv.c 

S_UPPER_SRCS += \
../UsbKeyboard/usbdrvasm.S 

ASM_SRCS += \
../UsbKeyboard/usbdrvasm.asm 

OBJS += \
./UsbKeyboard/oddebug.o \
./UsbKeyboard/usbdrv.o \
./UsbKeyboard/usbdrvasm.o 

C_DEPS += \
./UsbKeyboard/oddebug.d \
./UsbKeyboard/usbdrv.d 

ASM_DEPS += \
./UsbKeyboard/usbdrvasm.d 

S_UPPER_DEPS += \
./UsbKeyboard/usbdrvasm.d 


# Each subdirectory must supply rules for building sources it contributes
UsbKeyboard/%.o: ../UsbKeyboard/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/grappendorf/workspace-arduino/arduino-framework" -DARDUINO=100 -Wall -Os -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections  -Wno-strict-aliasing -Wno-unused-function -Wno-unused-variable -Wno-uninitialized -Wno-unused-but-set-variable -Wno-attributes -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

UsbKeyboard/%.o: ../UsbKeyboard/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -I"/home/grappendorf/workspace-arduino/arduino-framework" -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

UsbKeyboard/%.o: ../UsbKeyboard/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -I"/home/grappendorf/workspace-arduino/arduino-framework" -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


