################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_sofware_timer_one_shot_auto_reload/StdPeriph_Driver/inc" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_sofware_timer_one_shot_auto_reload/inc" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_sofware_timer_one_shot_auto_reload/CMSIS/device" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_sofware_timer_one_shot_auto_reload/CMSIS/core" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


