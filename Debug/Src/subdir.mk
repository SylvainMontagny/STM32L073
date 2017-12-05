################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/callback.c \
../Src/gpio.c \
../Src/main.c \
../Src/print_menu.c \
../Src/rtc.c \
../Src/spi.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/system_stm32l0xx.c \
../Src/tim.c 

OBJS += \
./Src/adc.o \
./Src/callback.o \
./Src/gpio.o \
./Src/main.o \
./Src/print_menu.o \
./Src/rtc.o \
./Src/spi.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/system_stm32l0xx.o \
./Src/tim.o 

C_DEPS += \
./Src/adc.d \
./Src/callback.d \
./Src/gpio.d \
./Src/main.d \
./Src/print_menu.d \
./Src/rtc.d \
./Src/spi.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/system_stm32l0xx.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L073xx -I"C:/Users/Sylvain/Desktop/STM32_Project/STM32L073_Nucleo/Inc" -I"C:/Users/Sylvain/Desktop/STM32_Project/STM32L073_Nucleo/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/Sylvain/Desktop/STM32_Project/STM32L073_Nucleo/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Sylvain/Desktop/STM32_Project/STM32L073_Nucleo/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/Sylvain/Desktop/STM32_Project/STM32L073_Nucleo/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


