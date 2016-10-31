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
../include/ \
../include/libraries/ \
../include/libraries/MsTimer2/ \
../src/ \
../src/libraries/ \
../src/libraries/MsTimer2/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Sketch.cpp \
../src/libraries/MsTimer2/MsTimer2.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Sketch.o \
src/libraries/MsTimer2/MsTimer2.o

OBJS_AS_ARGS +=  \
Sketch.o \
src/libraries/MsTimer2/MsTimer2.o

C_DEPS +=  \
Sketch.d \
src/libraries/MsTimer2/MsTimer2.d

C_DEPS_AS_ARGS +=  \
Sketch.d \
src/libraries/MsTimer2/MsTimer2.d

OUTPUT_FILE_PATH +=FlashLed.elf

OUTPUT_FILE_PATH_AS_ARGS +=FlashLed.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+=  \
C:/Users/Mark/Documents/Atmel\ Studio/7.0/Custom\ Project/Reference/MsTimer2\ Reference/MsTimer2\ Reference/ArduinoCore/Debug/libArduinoCore.a

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler





./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -DUSB_VID=0x2341 -DUSB_PID=0x0043 -DUSB_MANUFACTURER="\"Arduino LLC\""  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\include" -I"..\\..\ArduinoCore\include\core" -I"..\\..\ArduinoCore\include\variants\standard" -I"..\include\libraries\MsTimer2"  -Os -fno-threadsafe-statics -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -w -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\gcc\dev\atmega328p" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/libraries/MsTimer2/%.o: ../src/libraries/MsTimer2/%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -DUSB_VID=0x2341 -DUSB_PID=0x0043 -DUSB_MANUFACTURER="\"Arduino LLC\""  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\include" -I"..\\..\ArduinoCore\include\core" -I"..\\..\ArduinoCore\include\variants\standard" -I"..\include\libraries\MsTimer2"  -Os -fno-threadsafe-statics -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -w -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\gcc\dev\atmega328p" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR8/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="FlashLed.map" -Wl,--start-group -Wl,-lm -Wl,-lArduinoCore  -Wl,--end-group -Wl,-L"C:\Users\Mark\DOCUME~1\ATMELS~1\7.0\CUSTOM~1\REFERE~1\MSTIME~1\MSTIME~1\ARDUIN~1\Debug"  -Wl,--gc-sections -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.98\gcc\dev\atmega328p" -Os  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "FlashLed.elf" "FlashLed.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "FlashLed.elf" "FlashLed.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "FlashLed.elf" > "FlashLed.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "FlashLed.elf" "FlashLed.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "FlashLed.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "FlashLed.elf" "FlashLed.a" "FlashLed.hex" "FlashLed.lss" "FlashLed.eep" "FlashLed.map" "FlashLed.srec" "FlashLed.usersignatures"
	