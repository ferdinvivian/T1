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
-include Core/Src/Source_Files/subdir.mk
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


BUILD_ARTIFACT_NAME := Dec2025_School_Christmas
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Dec2025_School_Christmas.elf \

MAP_FILES += \
Dec2025_School_Christmas.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Dec2025_School_Christmas.list \

OBJCOPY_HEX += \
Dec2025_School_Christmas.hex \

OBJCOPY_BIN += \
Dec2025_School_Christmas.bin \

OBJCOPY_VERILOG += \
Dec2025_School_Christmas.verilog \

OBJCOPY_SREC += \
Dec2025_School_Christmas.srec \

OBJCOPY_SYMBOLSREC += \
Dec2025_School_Christmas.symbolsrec \


# All Target
all: main-build

# Main-build Target
main-build: Dec2025_School_Christmas.elf secondary-outputs

# Tool invocations
Dec2025_School_Christmas.elf Dec2025_School_Christmas.map: $(OBJS) $(USER_OBJS) C:\Users\Lenovo\STMicroelectronics\SSD_STM32_Workspace\Gabi_Proj\Dec2025_School_Christmas\STM32F401CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Dec2025_School_Christmas.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Lenovo\STMicroelectronics\SSD_STM32_Workspace\Gabi_Proj\Dec2025_School_Christmas\STM32F401CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Dec2025_School_Christmas.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Dec2025_School_Christmas.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Dec2025_School_Christmas.list"
	@echo 'Finished building: $@'
	@echo ' '

Dec2025_School_Christmas.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Dec2025_School_Christmas.hex"
	@echo 'Finished building: $@'
	@echo ' '

Dec2025_School_Christmas.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Dec2025_School_Christmas.bin"
	@echo 'Finished building: $@'
	@echo ' '

Dec2025_School_Christmas.verilog: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O verilog $(EXECUTABLES) "Dec2025_School_Christmas.verilog"
	@echo 'Finished building: $@'
	@echo ' '

Dec2025_School_Christmas.srec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O srec $(EXECUTABLES) "Dec2025_School_Christmas.srec"
	@echo 'Finished building: $@'
	@echo ' '

Dec2025_School_Christmas.symbolsrec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O symbolsrec $(EXECUTABLES) "Dec2025_School_Christmas.symbolsrec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Dec2025_School_Christmas.bin Dec2025_School_Christmas.elf Dec2025_School_Christmas.hex Dec2025_School_Christmas.list Dec2025_School_Christmas.map Dec2025_School_Christmas.srec Dec2025_School_Christmas.symbolsrec Dec2025_School_Christmas.verilog default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN) $(OBJCOPY_VERILOG) $(OBJCOPY_SREC) $(OBJCOPY_SYMBOLSREC)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
