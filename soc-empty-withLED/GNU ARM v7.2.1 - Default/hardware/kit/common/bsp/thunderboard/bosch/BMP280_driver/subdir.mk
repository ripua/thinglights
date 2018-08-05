################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.c 

OBJS += \
./hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.o 

C_DEPS += \
./hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.o: ../hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-D__StackLimit=0x20000000' '-D__HEAP_SIZE=0xD00' '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-DEFR32MG12P332F1024GL125=1' -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emlib\src" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emlib\inc" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\hardware\kit\common\drivers" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\Device\SiliconLabs\EFR32MG12P\Include" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\hardware\kit\common\bsp" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\CMSIS\Include" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\Device\SiliconLabs\EFR32MG12P\Source\GCC" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\sleep\src" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\Device\SiliconLabs\EFR32MG12P\Source" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\dmadrv\inc" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\gpiointerrupt\src" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\radio\rail_lib\chip\efr32" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\common\inc" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\dmadrv\src" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\radio\rail_lib\common" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\hardware\kit\EFR32MG12_BRD4166A\config" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\uartdrv\inc" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\bootloader\api" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\halconfig\inc\hal-config" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\app\bluetooth\common\stack_bridge" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\emdrv\sleep\inc" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\platform\bootloader" -I"C:\Users\gkellerman\SimplicityStudio\v4_workspace\soc-empty-withLED\hardware\kit\common\bsp\thunderboard" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.d" -MT"hardware/kit/common/bsp/thunderboard/bosch/BMP280_driver/bmp280.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


