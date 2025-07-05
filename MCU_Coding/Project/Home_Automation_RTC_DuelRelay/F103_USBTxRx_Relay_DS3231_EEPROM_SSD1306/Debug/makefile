################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/Proj/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.elf \

MAP_FILES += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.list \

OBJCOPY_HEX += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.hex \

OBJCOPY_BIN += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.bin \

OBJCOPY_VERILOG += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.verilog \

OBJCOPY_SREC += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.srec \

OBJCOPY_SYMBOLSREC += \
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.symbolsrec \


# All Target
all: main-build

# Main-build Target
main-build: F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.elf secondary-outputs

# Tool invocations
F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.elf F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.map: $(OBJS) $(USER_OBJS) C:\Users\Lenovo\STMicroelectronics\SSD_STM32_Workspace\1\F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Lenovo\STMicroelectronics\SSD_STM32_Workspace\1\F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.list"
	@echo 'Finished building: $@'
	@echo ' '

F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.hex"
	@echo 'Finished building: $@'
	@echo ' '

F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.bin"
	@echo 'Finished building: $@'
	@echo ' '

F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.verilog: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O verilog $(EXECUTABLES) "F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.verilog"
	@echo 'Finished building: $@'
	@echo ' '

F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.srec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O srec $(EXECUTABLES) "F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.srec"
	@echo 'Finished building: $@'
	@echo ' '

F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.symbolsrec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O symbolsrec $(EXECUTABLES) "F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.symbolsrec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.bin F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.elf F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.hex F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.list F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.map F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.srec F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.symbolsrec F103_USBTxRx_Relay_DS3231_EEPROM_SSD1306.verilog default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN) $(OBJCOPY_VERILOG) $(OBJCOPY_SREC) $(OBJCOPY_SYMBOLSREC)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
