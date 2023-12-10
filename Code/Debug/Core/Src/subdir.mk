################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Scheduler.c \
../Core/Src/auto_fsm.c \
../Core/Src/button.c \
../Core/Src/buzzer.c \
../Core/Src/global.c \
../Core/Src/light_traffic.c \
../Core/Src/main.c \
../Core/Src/main_fsm.c \
../Core/Src/manual_fsm.c \
../Core/Src/pedestrian_fsm.c \
../Core/Src/software_timer.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tuning_fsm.c 

C_DEPS += \
./Core/Src/Scheduler.d \
./Core/Src/auto_fsm.d \
./Core/Src/button.d \
./Core/Src/buzzer.d \
./Core/Src/global.d \
./Core/Src/light_traffic.d \
./Core/Src/main.d \
./Core/Src/main_fsm.d \
./Core/Src/manual_fsm.d \
./Core/Src/pedestrian_fsm.d \
./Core/Src/software_timer.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tuning_fsm.d 

OBJS += \
./Core/Src/Scheduler.o \
./Core/Src/auto_fsm.o \
./Core/Src/button.o \
./Core/Src/buzzer.o \
./Core/Src/global.o \
./Core/Src/light_traffic.o \
./Core/Src/main.o \
./Core/Src/main_fsm.o \
./Core/Src/manual_fsm.o \
./Core/Src/pedestrian_fsm.o \
./Core/Src/software_timer.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tuning_fsm.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

