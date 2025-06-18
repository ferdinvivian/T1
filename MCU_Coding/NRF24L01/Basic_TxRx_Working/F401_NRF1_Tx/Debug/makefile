################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
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


BUILD_ARTIFACT_NAME := F401_NRF1_Tx
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
F401_NRF1_Tx.elf \

MAP_FILES += \
F401_NRF1_Tx.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
F401_NRF1_Tx.list \

OBJCOPY_HEX += \
F401_NRF1_Tx.hex \

OBJCOPY_BIN += \
F401_NRF1_Tx.bin \

OBJCOPY_VERILOG += \
F401_NRF1_Tx.verilog \

OBJCOPY_SREC += \
F401_NRF1_Tx.srec \

OBJCOPY_SYMBOLSREC += \
F401_NRF1_Tx.symbolsrec \


# All Target
all: main-build

# Main-build Target
main-build: F401_NRF1_Tx.elf secondary-outputs

# Tool invocations
F401_NRF1_Tx.elf F401_NRF1_Tx.map: $(OBJS) $(USER_OBJS) C:\Users\Lenovo\STMicroelectronics\SSD_STM32_Workspace\1\F401_NRF1_Tx\STM32F401CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "F401_NRF1_Tx.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Lenovo\STMicroelectronics\SSD_STM32_Workspace\1\F401_NRF1_Tx\STM32F401CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="F401_NRF1_Tx.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

F401_NRF1_Tx.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "F401_NRF1_Tx.list"
	@echo 'Finished building: $@'
	@echo ' '

F401_NRF1_Tx.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "F401_NRF1_Tx.hex"
	@echo 'Finished building: $@'
	@echo ' '

F401_NRF1_Tx.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "F401_NRF1_Tx.bin"
	@echo 'Finished building: $@'
	@echo ' '

F401_NRF1_Tx.verilog: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O verilog $(EXECUTABLES) "F401_NRF1_Tx.verilog"
	@echo 'Finished building: $@'
	@echo ' '

F401_NRF1_Tx.srec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O srec $(EXECUTABLES) "F401_NRF1_Tx.srec"
	@echo 'Finished building: $@'
	@echo ' '

F401_NRF1_Tx.symbolsrec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O symbolsrec $(EXECUTABLES) "F401_NRF1_Tx.symbolsrec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) F401_NRF1_Tx.bin F401_NRF1_Tx.elf F401_NRF1_Tx.hex F401_NRF1_Tx.list F401_NRF1_Tx.map F401_NRF1_Tx.srec F401_NRF1_Tx.symbolsrec F401_NRF1_Tx.verilog default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN) $(OBJCOPY_VERILOG) $(OBJCOPY_SREC) $(OBJCOPY_SYMBOLSREC)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
