################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/Software_installation/CCSIDE/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/Software_installation/CCSIDE/ti/ccs1230/ccs/ccs_base/arm/include" --include_path="D:/Software_installation/CCSIDE/ti/msp/MSP432Ware_3_40_00_25/driverlib/driverlib/MSP432P4xx" --include_path="D:/Software_installation/CCSIDE/ti/ccs1230/ccs/ccs_base/arm/include/CMSIS" --include_path="E:/Software_workspace/CCS_IDE_work_space/03BoyLuc_key" --include_path="D:/Software_installation/CCSIDE/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


