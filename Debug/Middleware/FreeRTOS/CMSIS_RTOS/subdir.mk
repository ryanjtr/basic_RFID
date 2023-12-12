################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.c 

OBJS += \
./Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.o 

C_DEPS += \
./Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/FreeRTOS/CMSIS_RTOS/%.o Middleware/FreeRTOS/CMSIS_RTOS/%.su Middleware/FreeRTOS/CMSIS_RTOS/%.cyclo: ../Middleware/FreeRTOS/CMSIS_RTOS/%.c Middleware/FreeRTOS/CMSIS_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_HAL_DRIVER -c -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Core/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/CMSIS/Include" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/CMSIS/Device" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Peripherals/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/HAL/STM32F1xx_HAL_Driver/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/HAL" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Application/RTOS" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/CMSIS_RTOS" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/include" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middleware-2f-FreeRTOS-2f-CMSIS_RTOS

clean-Middleware-2f-FreeRTOS-2f-CMSIS_RTOS:
	-$(RM) ./Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.cyclo ./Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.d ./Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.o ./Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.su

.PHONY: clean-Middleware-2f-FreeRTOS-2f-CMSIS_RTOS

