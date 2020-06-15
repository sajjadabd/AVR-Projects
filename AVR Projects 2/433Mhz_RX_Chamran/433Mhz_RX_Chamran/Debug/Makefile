################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../433Mhz_RX_Chamran.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
433Mhz_RX_Chamran.o


OBJS_AS_ARGS +=  \
433Mhz_RX_Chamran.o


C_DEPS +=  \
433Mhz_RX_Chamran.d


C_DEPS_AS_ARGS +=  \
433Mhz_RX_Chamran.d


OUTPUT_FILE_PATH +=433Mhz_RX_Chamran.elf

OUTPUT_FILE_PATH_AS_ARGS +=433Mhz_RX_Chamran.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler



./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)E:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -mmcu=atmega16a  -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C Linker
	$(QUOTE)E:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="433Mhz_RX_Chamran.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega16a  
	@echo Finished building target: $@
	"E:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "433Mhz_RX_Chamran.elf" "433Mhz_RX_Chamran.hex"
	"E:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "433Mhz_RX_Chamran.elf" "433Mhz_RX_Chamran.eep" || exit 0
	"E:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-objdump.exe" -h -S "433Mhz_RX_Chamran.elf" > "433Mhz_RX_Chamran.lss"
	"E:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-size.exe" -C --mcu=atmega16a  "433Mhz_RX_Chamran.elf"
	




# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "433Mhz_RX_Chamran.hex" "433Mhz_RX_Chamran.lss" "433Mhz_RX_Chamran.eep" "433Mhz_RX_Chamran.map"
	