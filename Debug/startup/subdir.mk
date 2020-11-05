################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32l073xx.s 

OBJS += \
./startup/startup_stm32l073xx.o 

S_DEPS += \
./startup/startup_stm32l073xx.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_stm32l073xx.o: ../startup/startup_stm32l073xx.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp -MMD -MP -MF"startup/startup_stm32l073xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

