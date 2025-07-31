################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CAN_PROJ/Can.c \
../Core/Src/CAN_PROJ/Common.c \
../Core/Src/CAN_PROJ/Uart.c 

C_DEPS += \
./Core/Src/CAN_PROJ/Can.d \
./Core/Src/CAN_PROJ/Common.d \
./Core/Src/CAN_PROJ/Uart.d 

OBJS += \
./Core/Src/CAN_PROJ/Can.o \
./Core/Src/CAN_PROJ/Common.o \
./Core/Src/CAN_PROJ/Uart.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/CAN_PROJ/%.o Core/Src/CAN_PROJ/%.su Core/Src/CAN_PROJ/%.cyclo: ../Core/Src/CAN_PROJ/%.c Core/Src/CAN_PROJ/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-CAN_PROJ

clean-Core-2f-Src-2f-CAN_PROJ:
	-$(RM) ./Core/Src/CAN_PROJ/Can.cyclo ./Core/Src/CAN_PROJ/Can.d ./Core/Src/CAN_PROJ/Can.o ./Core/Src/CAN_PROJ/Can.su ./Core/Src/CAN_PROJ/Common.cyclo ./Core/Src/CAN_PROJ/Common.d ./Core/Src/CAN_PROJ/Common.o ./Core/Src/CAN_PROJ/Common.su ./Core/Src/CAN_PROJ/Uart.cyclo ./Core/Src/CAN_PROJ/Uart.d ./Core/Src/CAN_PROJ/Uart.o ./Core/Src/CAN_PROJ/Uart.su

.PHONY: clean-Core-2f-Src-2f-CAN_PROJ

