################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Source_Files/DF_Mini.c \
../Core/Src/Source_Files/Proj_Source.c 

C_DEPS += \
./Core/Src/Source_Files/DF_Mini.d \
./Core/Src/Source_Files/Proj_Source.d 

OBJS += \
./Core/Src/Source_Files/DF_Mini.o \
./Core/Src/Source_Files/Proj_Source.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Source_Files/%.o Core/Src/Source_Files/%.su Core/Src/Source_Files/%.cyclo: ../Core/Src/Source_Files/%.c Core/Src/Source_Files/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Source_Files

clean-Core-2f-Src-2f-Source_Files:
	-$(RM) ./Core/Src/Source_Files/DF_Mini.cyclo ./Core/Src/Source_Files/DF_Mini.d ./Core/Src/Source_Files/DF_Mini.o ./Core/Src/Source_Files/DF_Mini.su ./Core/Src/Source_Files/Proj_Source.cyclo ./Core/Src/Source_Files/Proj_Source.d ./Core/Src/Source_Files/Proj_Source.o ./Core/Src/Source_Files/Proj_Source.su

.PHONY: clean-Core-2f-Src-2f-Source_Files

