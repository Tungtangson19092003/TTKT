################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/r_cg_12adc.c \
..\src/r_cg_12adc_user.c \
..\src/r_cg_cgc.c \
..\src/r_cg_cgc_user.c \
..\src/r_cg_iica.c \
..\src/r_cg_iica_user.c \
..\src/r_cg_intp.c \
..\src/r_cg_intp_user.c \
..\src/r_cg_it.c \
..\src/r_cg_it_user.c \
..\src/r_cg_lcd.c \
..\src/r_cg_lcd_user.c \
..\src/r_cg_main.c \
..\src/r_cg_port.c \
..\src/r_cg_port_user.c \
..\src/r_cg_sau.c \
..\src/r_cg_sau_user.c \
..\src/r_cg_systeminit.c \
..\src/r_cg_tau.c \
..\src/r_cg_tau_user.c 

C_DEPS += \
./src/r_cg_12adc.d \
./src/r_cg_12adc_user.d \
./src/r_cg_cgc.d \
./src/r_cg_cgc_user.d \
./src/r_cg_iica.d \
./src/r_cg_iica_user.d \
./src/r_cg_intp.d \
./src/r_cg_intp_user.d \
./src/r_cg_it.d \
./src/r_cg_it_user.d \
./src/r_cg_lcd.d \
./src/r_cg_lcd_user.d \
./src/r_cg_main.d \
./src/r_cg_port.d \
./src/r_cg_port_user.d \
./src/r_cg_sau.d \
./src/r_cg_sau_user.d \
./src/r_cg_systeminit.d \
./src/r_cg_tau.d \
./src/r_cg_tau_user.d 

OBJS += \
./src/r_cg_12adc.obj \
./src/r_cg_12adc_user.obj \
./src/r_cg_cgc.obj \
./src/r_cg_cgc_user.obj \
./src/r_cg_iica.obj \
./src/r_cg_iica_user.obj \
./src/r_cg_intp.obj \
./src/r_cg_intp_user.obj \
./src/r_cg_it.obj \
./src/r_cg_it_user.obj \
./src/r_cg_lcd.obj \
./src/r_cg_lcd_user.obj \
./src/r_cg_main.obj \
./src/r_cg_port.obj \
./src/r_cg_port_user.obj \
./src/r_cg_sau.obj \
./src/r_cg_sau_user.obj \
./src/r_cg_systeminit.obj \
./src/r_cg_tau.obj \
./src/r_cg_tau_user.obj 


# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrl  -MM -MP -o "$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)"  -cpu=S3 -dev="C:/Renesas/e2_studio_53/DebugComp/RL78\Common\DR5F11MMF.DVF"  -msg_lang=english -I "C:\PROGRA~2\Renesas\RL78\1_3_0/inc" -I "..\src" -I "..\..\..\..\rBLE\include" -I "..\..\..\..\rBLE\include\host" -I "..\..\..\..\rBLE\rscip" -I "..\..\..\..\Platform\include" -I "..\..\..\..\Platform\driver\lcd" -I "..\..\..\..\Platform\driver\plf" -I "..\..\..\..\Platform\driver\serial" -I "..\..\..\..\Platform\driver\timer" -character_set=sjis -g -memory_model=medium -signed_char -no_warning_num=23082  -D USE_SAMPLE_PROFILE,noUSE_RSK_LCD,noUSE_RSK_SW,noUSE_RSK_LED,noUSE_RSK_ADC,_USE_CCRL_RL78,USE_PAIRING_JUSTWORKS   "$<"
	ccrl -o "$(@:%.d=%.obj)" -cpu=S3 -c -dev="C:/Renesas/e2_studio_53/DebugComp/RL78\Common\DR5F11MMF.DVF"  -msg_lang=english -I "C:\PROGRA~2\Renesas\RL78\1_3_0/inc" -I "..\src" -I "..\..\..\..\rBLE\include" -I "..\..\..\..\rBLE\include\host" -I "..\..\..\..\rBLE\rscip" -I "..\..\..\..\Platform\include" -I "..\..\..\..\Platform\driver\lcd" -I "..\..\..\..\Platform\driver\plf" -I "..\..\..\..\Platform\driver\serial" -I "..\..\..\..\Platform\driver\timer" -character_set=sjis -g -memory_model=medium -signed_char -no_warning_num=23082  -D USE_SAMPLE_PROFILE,noUSE_RSK_LCD,noUSE_RSK_SW,noUSE_RSK_LED,noUSE_RSK_ADC,_USE_CCRL_RL78,USE_PAIRING_JUSTWORKS   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

