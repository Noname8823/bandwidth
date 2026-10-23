################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/trace/adv_trace/subdir.mk
-include Utilities/timer/subdir.mk
-include Utilities/sequencer/subdir.mk
-include Utilities/misc/subdir.mk
-include Utilities/lpm/tiny_lpm/subdir.mk
-include SubGHz_Phy/Target/subdir.mk
-include SubGHz_Phy/App/subdir.mk
-include Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver/subdir.mk
-include Drivers/STM32WLxx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/RAK3172_board/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Feather_RAK3172_Phy_PingPong
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Feather_RAK3172_Phy_PingPong.elf \

MAP_FILES += \
Feather_RAK3172_Phy_PingPong.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Feather_RAK3172_Phy_PingPong.list \

OBJCOPY_BIN += \
Feather_RAK3172_Phy_PingPong.bin \


# All Target
all: main-build

# Main-build Target
main-build: Feather_RAK3172_Phy_PingPong.elf secondary-outputs

# Tool invocations
Feather_RAK3172_Phy_PingPong.elf Feather_RAK3172_Phy_PingPong.map: $(OBJS) $(USER_OBJS) C:\Users\tranquocvu2\Downloads\TEST_function-5b57242bda424c78a37240548ac4adc7cd51cbf1\TEST_function-5b57242bda424c78a37240548ac4adc7cd51cbf1\STM32WLE5CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Feather_RAK3172_Phy_PingPong.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\tranquocvu2\Downloads\TEST_function-5b57242bda424c78a37240548ac4adc7cd51cbf1\TEST_function-5b57242bda424c78a37240548ac4adc7cd51cbf1\STM32WLE5CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Feather_RAK3172_Phy_PingPong.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Feather_RAK3172_Phy_PingPong.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Feather_RAK3172_Phy_PingPong.list"
	@echo 'Finished building: $@'
	@echo ' '

Feather_RAK3172_Phy_PingPong.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Feather_RAK3172_Phy_PingPong.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Feather_RAK3172_Phy_PingPong.bin Feather_RAK3172_Phy_PingPong.elf Feather_RAK3172_Phy_PingPong.list Feather_RAK3172_Phy_PingPong.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
