################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.h *.lbk *.abs *.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include C\ Source\ Files/Platform/driver/lcd/subdir.mk
-include C\ Source\ Files/Platform/driver/plf/subdir.mk
-include C\ Source\ Files/Platform/driver/serial/subdir.mk
-include C\ Source\ Files/Platform/driver/timer/subdir.mk
-include C\ Source\ Files/rBLE/host/gap/subdir.mk
-include C\ Source\ Files/rBLE/host/gatt/subdir.mk
-include C\ Source\ Files/rBLE/host/subdir.mk
-include C\ Source\ Files/rBLE/host/sm/subdir.mk
-include C\ Source\ Files/rBLE/host/vs/subdir.mk
-include C\ Source\ Files/rBLE/rscip/subdir.mk
-include C\ Source\ Files/rBLE/sample_app/subdir.mk
-include C\ Source\ Files/rBLE/sample_profile/scp/subdir.mk
-include subdir.mk
-include src/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OBJ_DEPS)),)
-include $(OBJ_DEPS)
endif
ifneq ($(strip $(ABS_DEPS)),)
-include $(ABS_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(O_DEPS)),)
-include $(O_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
CONVERTOR_OUTPUT_OUTPUTS += \
HostSample.hex \

LINKER_OUTPUT_OUTPUTS += \
HostSample.abs \

# All Target
all: HostSample.hex
	@echo 'Build complete.'

# Tool invocations
HostSample.hex: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Converter'
	rlink   -form=hexadecimal "HostSample.abs" -output="HostSample.hex" -byte_count=FF -nomessage -nologo
	@echo 'Finished building target:'
	@echo.
	$(MAKE) --no-print-directory post-build

HostSample.abs: $(OBJS) $(ALL_ASMS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	rlink  -subcommand="LinkerSubCommand.tmp"  -list="HostSample.map" -show=all -nooptimize -entry=_start -auto_section_layout -security_id=00000000000000000000 -ocdbg=84 -debug_monitor=17e00-17fff -user_opt_byte=eeffe0 -output="HostSample.abs" -debug -nocompress -rom=.data=.dataR,.sdata=.sdataR -stack -nomessage -device="C:/Renesas/e2_studio_53/DebugComp/RL78\Common\DR5F11MMF.DVF" -nologo
	@echo 'Finished building:'
	@echo.

# Other Targets
clean:
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp , $(OBJS))
	-@ xargs -s 6000 -t -a clean_OBJS.tmp $(RM)
	-@$(RM) clean_OBJS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp , $(C_DEPS))
	-@ xargs -s 6000 -t -a clean_C_DEPS.tmp $(RM)
	-@$(RM) clean_C_DEPS.tmp
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
	-$(file > clean_C_UPPER_DEPS.tmp , $(C_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_C_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_C_UPPER_DEPS.tmp
endif
ifneq ($(strip $(ASM_PRNS)),)
	-$(file > clean_ASM_PRNS.tmp , $(ASM_PRNS))
	-@ xargs -s 6000 -t -a clean_ASM_PRNS.tmp $(RM)
	-@$(RM) clean_ASM_PRNS.tmp
endif
ifneq ($(strip $(OBJ_DEPS)),)
	-$(file > clean_OBJ_DEPS.tmp , $(OBJ_DEPS))
	-@ xargs -s 6000 -t -a clean_OBJ_DEPS.tmp $(RM)
	-@$(RM) clean_OBJ_DEPS.tmp
endif
ifneq ($(strip $(ABS_DEPS)),)
	-$(file > clean_ABS_DEPS.tmp , $(ABS_DEPS))
	-@ xargs -s 6000 -t -a clean_ABS_DEPS.tmp $(RM)
	-@$(RM) clean_ABS_DEPS.tmp
endif
ifneq ($(strip $(O_DEPS)),)
	-$(file > clean_O_DEPS.tmp , $(O_DEPS))
	-@ xargs -s 6000 -t -a clean_O_DEPS.tmp $(RM)
	-@$(RM) clean_O_DEPS.tmp
endif
ifneq ($(strip $(S_DEPS)),)
	-$(file > clean_S_DEPS.tmp , $(S_DEPS))
	-@ xargs -s 6000 -t -a clean_S_DEPS.tmp $(RM)
	-@$(RM) clean_S_DEPS.tmp
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
	-$(file > clean_S_UPPER_DEPS.tmp , $(S_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_S_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_S_UPPER_DEPS.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp , $(ASM_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
	-$(file > clean_ASM_UPPER_DEPS.tmp , $(ASM_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_UPPER_DEPS.tmp
endif
ifneq ($(strip $(ASM_PATH_OUT)),)
	-$(file > clean_ASM_PATH_OUT.tmp , $(ASM_PATH_OUT))
	-@ xargs -s 6000 -t -a clean_ASM_PATH_OUT.tmp $(RM)
	-@$(RM) clean_ASM_PATH_OUT.tmp
endif
	-$(RM) $(CONVERTOR_OUTPUT_OUTPUTS) 
	-rm -rf "C Source Files/Platform/driver/lcd"/*.obj "C Source Files/Platform/driver/lcd"/*.d "C Source Files/Platform/driver/lcd"/*.src "C Source Files/Platform/driver/lcd"/*.p "C Source Files/Platform/driver/lcd"/*.pp "C Source Files/Platform/driver/lcd"/*.mrc "C Source Files/Platform/driver/lcd"/*.prn "C Source Files/Platform/driver/lcd"/*.asm "C Source Files/Platform/driver/lcd"/*.lst
	-rm -rf "C Source Files/Platform/driver/plf"/*.obj "C Source Files/Platform/driver/plf"/*.d "C Source Files/Platform/driver/plf"/*.src "C Source Files/Platform/driver/plf"/*.p "C Source Files/Platform/driver/plf"/*.pp "C Source Files/Platform/driver/plf"/*.mrc "C Source Files/Platform/driver/plf"/*.prn "C Source Files/Platform/driver/plf"/*.asm "C Source Files/Platform/driver/plf"/*.lst
	-rm -rf "C Source Files/Platform/driver/serial"/*.obj "C Source Files/Platform/driver/serial"/*.d "C Source Files/Platform/driver/serial"/*.src "C Source Files/Platform/driver/serial"/*.p "C Source Files/Platform/driver/serial"/*.pp "C Source Files/Platform/driver/serial"/*.mrc "C Source Files/Platform/driver/serial"/*.prn "C Source Files/Platform/driver/serial"/*.asm "C Source Files/Platform/driver/serial"/*.lst
	-rm -rf "C Source Files/Platform/driver/timer"/*.obj "C Source Files/Platform/driver/timer"/*.d "C Source Files/Platform/driver/timer"/*.src "C Source Files/Platform/driver/timer"/*.p "C Source Files/Platform/driver/timer"/*.pp "C Source Files/Platform/driver/timer"/*.mrc "C Source Files/Platform/driver/timer"/*.prn "C Source Files/Platform/driver/timer"/*.asm "C Source Files/Platform/driver/timer"/*.lst
	-rm -rf "C Source Files/rBLE/host/gap"/*.obj "C Source Files/rBLE/host/gap"/*.d "C Source Files/rBLE/host/gap"/*.src "C Source Files/rBLE/host/gap"/*.p "C Source Files/rBLE/host/gap"/*.pp "C Source Files/rBLE/host/gap"/*.mrc "C Source Files/rBLE/host/gap"/*.prn "C Source Files/rBLE/host/gap"/*.asm "C Source Files/rBLE/host/gap"/*.lst
	-rm -rf "C Source Files/rBLE/host/gatt"/*.obj "C Source Files/rBLE/host/gatt"/*.d "C Source Files/rBLE/host/gatt"/*.src "C Source Files/rBLE/host/gatt"/*.p "C Source Files/rBLE/host/gatt"/*.pp "C Source Files/rBLE/host/gatt"/*.mrc "C Source Files/rBLE/host/gatt"/*.prn "C Source Files/rBLE/host/gatt"/*.asm "C Source Files/rBLE/host/gatt"/*.lst
	-rm -rf "C Source Files/rBLE/host"/*.obj "C Source Files/rBLE/host"/*.d "C Source Files/rBLE/host"/*.src "C Source Files/rBLE/host"/*.p "C Source Files/rBLE/host"/*.pp "C Source Files/rBLE/host"/*.mrc "C Source Files/rBLE/host"/*.prn "C Source Files/rBLE/host"/*.asm "C Source Files/rBLE/host"/*.lst
	-rm -rf "C Source Files/rBLE/host/sm"/*.obj "C Source Files/rBLE/host/sm"/*.d "C Source Files/rBLE/host/sm"/*.src "C Source Files/rBLE/host/sm"/*.p "C Source Files/rBLE/host/sm"/*.pp "C Source Files/rBLE/host/sm"/*.mrc "C Source Files/rBLE/host/sm"/*.prn "C Source Files/rBLE/host/sm"/*.asm "C Source Files/rBLE/host/sm"/*.lst
	-rm -rf "C Source Files/rBLE/host/vs"/*.obj "C Source Files/rBLE/host/vs"/*.d "C Source Files/rBLE/host/vs"/*.src "C Source Files/rBLE/host/vs"/*.p "C Source Files/rBLE/host/vs"/*.pp "C Source Files/rBLE/host/vs"/*.mrc "C Source Files/rBLE/host/vs"/*.prn "C Source Files/rBLE/host/vs"/*.asm "C Source Files/rBLE/host/vs"/*.lst
	-rm -rf "C Source Files/rBLE/rscip"/*.obj "C Source Files/rBLE/rscip"/*.d "C Source Files/rBLE/rscip"/*.src "C Source Files/rBLE/rscip"/*.p "C Source Files/rBLE/rscip"/*.pp "C Source Files/rBLE/rscip"/*.mrc "C Source Files/rBLE/rscip"/*.prn "C Source Files/rBLE/rscip"/*.asm "C Source Files/rBLE/rscip"/*.lst
	-rm -rf "C Source Files/rBLE/sample_app"/*.obj "C Source Files/rBLE/sample_app"/*.d "C Source Files/rBLE/sample_app"/*.src "C Source Files/rBLE/sample_app"/*.p "C Source Files/rBLE/sample_app"/*.pp "C Source Files/rBLE/sample_app"/*.mrc "C Source Files/rBLE/sample_app"/*.prn "C Source Files/rBLE/sample_app"/*.asm "C Source Files/rBLE/sample_app"/*.lst
	-rm -rf "C Source Files/rBLE/sample_profile/scp"/*.obj "C Source Files/rBLE/sample_profile/scp"/*.d "C Source Files/rBLE/sample_profile/scp"/*.src "C Source Files/rBLE/sample_profile/scp"/*.p "C Source Files/rBLE/sample_profile/scp"/*.pp "C Source Files/rBLE/sample_profile/scp"/*.mrc "C Source Files/rBLE/sample_profile/scp"/*.prn "C Source Files/rBLE/sample_profile/scp"/*.asm "C Source Files/rBLE/sample_profile/scp"/*.lst
	-rm -rf ""*.obj ""*.d ""*.src ""*.p ""*.pp ""*.mrc ""*.prn ""*.asm ""*.lst
	-rm -rf "src"/*.obj "src"/*.d "src"/*.src "src"/*.p "src"/*.pp "src"/*.mrc "src"/*.prn "src"/*.asm "src"/*.lst
	@echo.
	@echo 'Clean complete.'

post-build:
	@echo.
	-C:\Renesas\E2_STU~2\DEBUGC~1\RENESA~1.EXE HostSample.abs HostSample.x 
	@echo.

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
