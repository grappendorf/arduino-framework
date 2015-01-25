################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ps2dev/subdir.mk
-include XXBee/subdir.mk
-include XBee/subdir.mk
-include Wire/utility/subdir.mk
-include Wire/subdir.mk
-include WiFlySerial/subdir.mk
-include WheelEncoder/subdir.mk
-include UsbKeyboard/subdir.mk
-include UsbHost/subdir.mk
-include U8glib/utility/subdir.mk
-include U8glib/subdir.mk
-include TimerOne/subdir.mk
-include Stepper/subdir.mk
-include Sprite/subdir.mk
-include SoftwareSerial/subdir.mk
-include Servo/subdir.mk
-include SRF02/subdir.mk
-include SPI/subdir.mk
-include SD/utility/subdir.mk
-include SD/subdir.mk
-include RotaryEncoder/subdir.mk
-include RealSIDShield/subdir.mk
-include PinChangeInt/subdir.mk
-include PID_AutoTune/subdir.mk
-include PID/subdir.mk
-include OneWire/subdir.mk
-include Nokia_lcd/subdir.mk
-include MsTimer2/subdir.mk
-include Matrix/subdir.mk
-include MIDI/subdir.mk
-include LiquidCrystal440/subdir.mk
-include LiquidCrystal/subdir.mk
-include FrequencyTimer2/subdir.mk
-include Firmata/subdir.mk
-include Fader/subdir.mk
-include Ethernet/utility/subdir.mk
-include Ethernet/subdir.mk
-include EasyVR/subdir.mk
-include EEPROM/subdir.mk
-include Dogm/utility/subdir.mk
-include Dogm/subdir.mk
-include DallasTemperature/subdir.mk
-include CmdMessenger/subdir.mk
-include CMPS03/subdir.mk
-include Bounce/subdir.mk
-include Adafruit_MAX31855/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SIZEDUMMY += \
sizedummy \


# All Target
all: libarduino.a secondary-outputs

# Tool invocations
libarduino.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR Archiver'
	avr-ar -r  "libarduino.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

sizedummy: libarduino.a
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t libarduino.a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(ARCHIVES)$(CPP_DEPS)$(S_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) libarduino.a
	-@echo ' '

secondary-outputs: $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
