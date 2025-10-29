################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
..\cstart.asm \
..\stkinit.asm 

OBJS += \
./cstart.obj \
./stkinit.obj 

ASM_DEPS += \
./cstart.d \
./stkinit.d 


# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.asm
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	ccrl  -asmopt=-MM -asmopt=-MP -asmopt=-MF="$(@:%.obj=%.d)" -asmopt=-MT="$(@:%.obj=%.obj)" -asmopt=-MT="$(@:%.obj=%.d)"  -cpu=S3 -c -dev="C:/Renesas/e2_studio_53/DebugComp/RL78\Common\DR5F11MMF.DVF"  -msg_lang=english -I "C:\PROGRA~2\Renesas\RL78\1_3_0/inc" -character_set=sjis -g   "$<"
	ccrl -o "$(@:%.d=%.obj)" -cpu=S3 -c -dev="C:/Renesas/e2_studio_53/DebugComp/RL78\Common\DR5F11MMF.DVF"  -msg_lang=english -I "C:\PROGRA~2\Renesas\RL78\1_3_0/inc" -character_set=sjis -g   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

