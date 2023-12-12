################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/STM32F1xx_HAL_Driver/Src/Legacy/stm32f1xx_hal_can.c 

OBJS += \
./HAL/STM32F1xx_HAL_Driver/Src/Legacy/stm32f1xx_hal_can.o 

C_DEPS += \
./HAL/STM32F1xx_HAL_Driver/Src/Legacy/stm32f1xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/STM32F1xx_HAL_Driver/Src/Legacy/%.o HAL/STM32F1xx_HAL_Driver/Src/Legacy/%.su HAL/STM32F1xx_HAL_Driver/Src/Legacy/%.cyclo: ../HAL/STM32F1xx_HAL_Driver/Src/Legacy/%.c HAL/STM32F1xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_HAL_DRIVER -c -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Core/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/CMSIS/Include" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/CMSIS/Device" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Peripherals/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/HAL/STM32F1xx_HAL_Driver/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/HAL" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Application/RTOS" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/CMSIS_RTOS" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/include" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-STM32F1xx_HAL_Driver-2f-Src-2f-Legacy

clean-HAL-2f-STM32F1xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./HAL/STM32F1xx_HAL_Driver/Src/Legacy/stm32f1xx_hal_can.cyclo ./HAL/STM32F1xx_HAL_Driver/Src/Legacy/stm32f1xx_hal_can.d ./HAL/STM32F1xx_HAL_Driver/Src/Legacy/stm32f1xx_hal_can.o ./HAL/STM32F1xx_HAL_Driver/Src/Legacy/stm32f1xx_hal_can.su

.PHONY: clean-HAL-2f-STM32F1xx_HAL_Driver-2f-Src-2f-Legacy

