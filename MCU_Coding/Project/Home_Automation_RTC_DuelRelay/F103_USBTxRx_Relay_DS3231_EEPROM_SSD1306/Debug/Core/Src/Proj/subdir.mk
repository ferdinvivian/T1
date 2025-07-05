################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Proj/Common.c \
../Core/Src/Proj/EEPROM_24C32.c \
../Core/Src/Proj/RTC_DS3231.c \
../Core/Src/Proj/Relay_Code.c \
../Core/Src/Proj/SSD1306_Application.c \
../Core/Src/Proj/SSD1306_Driver.c \
../Core/Src/Proj/USB_TxRx.c 

C_DEPS += \
./Core/Src/Proj/Common.d \
./Core/Src/Proj/EEPROM_24C32.d \
./Core/Src/Proj/RTC_DS3231.d \
./Core/Src/Proj/Relay_Code.d \
./Core/Src/Proj/SSD1306_Application.d \
./Core/Src/Proj/SSD1306_Driver.d \
./Core/Src/Proj/USB_TxRx.d 

OBJS += \
./Core/Src/Proj/Common.o \
./Core/Src/Proj/EEPROM_24C32.o \
./Core/Src/Proj/RTC_DS3231.o \
./Core/Src/Proj/Relay_Code.o \
./Core/Src/Proj/SSD1306_Application.o \
./Core/Src/Proj/SSD1306_Driver.o \
./Core/Src/Proj/USB_TxRx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Proj/%.o Core/Src/Proj/%.su Core/Src/Proj/%.cyclo: ../Core/Src/Proj/%.c Core/Src/Proj/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Proj

clean-Core-2f-Src-2f-Proj:
	-$(RM) ./Core/Src/Proj/Common.cyclo ./Core/Src/Proj/Common.d ./Core/Src/Proj/Common.o ./Core/Src/Proj/Common.su ./Core/Src/Proj/EEPROM_24C32.cyclo ./Core/Src/Proj/EEPROM_24C32.d ./Core/Src/Proj/EEPROM_24C32.o ./Core/Src/Proj/EEPROM_24C32.su ./Core/Src/Proj/RTC_DS3231.cyclo ./Core/Src/Proj/RTC_DS3231.d ./Core/Src/Proj/RTC_DS3231.o ./Core/Src/Proj/RTC_DS3231.su ./Core/Src/Proj/Relay_Code.cyclo ./Core/Src/Proj/Relay_Code.d ./Core/Src/Proj/Relay_Code.o ./Core/Src/Proj/Relay_Code.su ./Core/Src/Proj/SSD1306_Application.cyclo ./Core/Src/Proj/SSD1306_Application.d ./Core/Src/Proj/SSD1306_Application.o ./Core/Src/Proj/SSD1306_Application.su ./Core/Src/Proj/SSD1306_Driver.cyclo ./Core/Src/Proj/SSD1306_Driver.d ./Core/Src/Proj/SSD1306_Driver.o ./Core/Src/Proj/SSD1306_Driver.su ./Core/Src/Proj/USB_TxRx.cyclo ./Core/Src/Proj/USB_TxRx.d ./Core/Src/Proj/USB_TxRx.o ./Core/Src/Proj/USB_TxRx.su

.PHONY: clean-Core-2f-Src-2f-Proj

