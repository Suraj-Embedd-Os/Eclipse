################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third-Party/FreeRTOS/org/Source/portable/MemMang/heap_4.c 

OBJS += \
./Third-Party/FreeRTOS/org/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Third-Party/FreeRTOS/org/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Third-Party/FreeRTOS/org/Source/portable/MemMang/%.o: ../Third-Party/FreeRTOS/org/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/StdPeriph_Driver/inc" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/Third-Party/FreeRTOS/org/Source/include" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/Third-Party/SEGGER/Config" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/Third-Party/SEGGER/OS" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/Third-Party/SEGGER/SEGGER" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/Config" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/inc" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/CMSIS/device" -I"E:/Eclipse_Project/Rtos_Project_Workspace/STM32_FreeRTOS_counting_sem_interrupt2/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


