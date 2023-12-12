################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/exti.c \
../Peripherals/Src/flash.c \
../Peripherals/Src/gpio.c \
../Peripherals/Src/lcd_4bit.c \
../Peripherals/Src/rc522.c \
../Peripherals/Src/rcc.c \
../Peripherals/Src/spi.c 

OBJS += \
./Peripherals/Src/exti.o \
./Peripherals/Src/flash.o \
./Peripherals/Src/gpio.o \
./Peripherals/Src/lcd_4bit.o \
./Peripherals/Src/rc522.o \
./Peripherals/Src/rcc.o \
./Peripherals/Src/spi.o 

C_DEPS += \
./Peripherals/Src/exti.d \
./Peripherals/Src/flash.d \
./Peripherals/Src/gpio.d \
./Peripherals/Src/lcd_4bit.d \
./Peripherals/Src/rc522.d \
./Peripherals/Src/rcc.d \
./Peripherals/Src/spi.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/%.o Peripherals/Src/%.su Peripherals/Src/%.cyclo: ../Peripherals/Src/%.c Peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_HAL_DRIVER -c -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Core/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/CMSIS/Include" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/CMSIS/Device" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Peripherals/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/HAL/STM32F1xx_HAL_Driver/Inc" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/HAL" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Application/RTOS" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/CMSIS_RTOS" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/include" -I"D:/STM32project/STM32F103C8T6/CODE/HAL_introduction/Middleware/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Peripherals-2f-Src

clean-Peripherals-2f-Src:
	-$(RM) ./Peripherals/Src/exti.cyclo ./Peripherals/Src/exti.d ./Peripherals/Src/exti.o ./Peripherals/Src/exti.su ./Peripherals/Src/flash.cyclo ./Peripherals/Src/flash.d ./Peripherals/Src/flash.o ./Peripherals/Src/flash.su ./Peripherals/Src/gpio.cyclo ./Peripherals/Src/gpio.d ./Peripherals/Src/gpio.o ./Peripherals/Src/gpio.su ./Peripherals/Src/lcd_4bit.cyclo ./Peripherals/Src/lcd_4bit.d ./Peripherals/Src/lcd_4bit.o ./Peripherals/Src/lcd_4bit.su ./Peripherals/Src/rc522.cyclo ./Peripherals/Src/rc522.d ./Peripherals/Src/rc522.o ./Peripherals/Src/rc522.su ./Peripherals/Src/rcc.cyclo ./Peripherals/Src/rcc.d ./Peripherals/Src/rcc.o ./Peripherals/Src/rcc.su ./Peripherals/Src/spi.cyclo ./Peripherals/Src/spi.d ./Peripherals/Src/spi.o ./Peripherals/Src/spi.su

.PHONY: clean-Peripherals-2f-Src

