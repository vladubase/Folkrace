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
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../inc \
../src


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../src/InitSYS.c \
../src/InitI2C.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
src/InitSYS.o \
src/InitI2C.o

OBJS_AS_ARGS +=  \
main.o \
src/InitSYS.o \
src/InitI2C.o

C_DEPS +=  \
main.d \
src/InitSYS.d \
src/InitI2C.d

C_DEPS_AS_ARGS +=  \
main.d \
src/InitSYS.d \
src/InitI2C.d

OUTPUT_FILE_PATH +=DMotor_folkrace.elf

OUTPUT_FILE_PATH_AS_ARGS +=DMotor_folkrace.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\User Programs\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\User Programs\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"D:\Documents\Workspace\Folkrace\DMotor\Program\inc"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\User Programs\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/InitSYS.o: ../src/InitSYS.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\User Programs\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\User Programs\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"D:\Documents\Workspace\Folkrace\DMotor\Program\inc"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\User Programs\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/InitI2C.o: ../src/InitI2C.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\User Programs\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\User Programs\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" -I"D:\Documents\Workspace\Folkrace\DMotor\Program\inc"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\User Programs\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)C:\User Programs\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="DMotor_folkrace.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,-L"D:\Documents\Workspace\Folkrace\DMotor\Program\inc"  -Wl,--gc-sections -mmcu=atmega328p -B "C:\User Programs\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega328p"  
	@echo Finished building target: $@
	"C:\User Programs\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "DMotor_folkrace.elf" "DMotor_folkrace.hex"
	"C:\User Programs\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "DMotor_folkrace.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "DMotor_folkrace.elf" "DMotor_folkrace.a" "DMotor_folkrace.hex" "DMotor_folkrace.lss" "DMotor_folkrace.eep" "DMotor_folkrace.map" "DMotor_folkrace.srec" "DMotor_folkrace.usersignatures"
	