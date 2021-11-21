# AVR project Makefile
# wykys, Tomas Fryza 2018-Present


######################################
# project variables
######################################
# target name
TARGET = DEMO
# chip
CHIP = atmega328pb
# usb to uart
USB_TO_UART = CP2102
# baudrate
BAUDRATE = 38400
# programmer: -b baudrate, -P port, -d system name of the usb serial converter
#PROGRAMMER = arduino -b 57600 -P $(shell $(WFS) -d $(USB_TO_UART))
# optimalization
OPT = -Os
# build dir
BUILD_DIR = build
# source dir
SRC = library
# includes
INC = -I$(SRC)/include



######################################
# source
######################################
# C++ sources
CPP_SOURCES := $(wildcard *.cpp)
CPP_SOURCES += $(wildcard $(SRC)/*.cpp)
# C sources
C_SOURCES := $(wildcard $(SRC)/*.c)
# ASM sources
ASM_SOURCES := $(wildcard $(SRC)/*.S)


#######################################
# toolchain
#######################################
#SCRIPTS_DIR = .scripts/
#RUN_ANSI_C = $(SCRIPTS_DIR)run-ansi-c.sh
#RUN_PYTHON = $(SCRIPTS_DIR)run-python.sh
# atmel tools
PREFIX = /opt/avr8-gnu-toolchain-linux_x86_64
#BINPATH = $(TOOLCHAIN_PATH)/bin/
BINDIR = $(PREFIX)/bin
CC      = $(BINDIR)/avr-gcc -fdiagnostics-color=always
CPP     = $(BINDIR)/avr-g++ -fdiagnostics-color=always
AS      = $(BINDIR)/avr-gcc -fdiagnostics-color=always -x assembler-with-cpp
OBJDUMP = $(BINDIR)/avr-objdump
OBJCOPY = $(BINDIR)/avr-objcopy
SIZE    = $(BINDIR)/avr-size
#PREFIX = avr-
#CC  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)gcc -fdiagnostics-color=always
#CPP = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)g++ -fdiagnostics-color=always
#AS  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)gcc -fdiagnostics-color=always -x assembler-with-cpp
#CP  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)objcopy
#CP  = $(BINDIR)/avr-objcopy
#DP  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)objdump
#DP  = $(BINDIR)/avr-objdump
#AR  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)ar
#AR  = $(BINDIR)/avr-ar
#SZ  = $(RUN_ANSI_C) $(BINPATH)$(PREFIX)size
#SZ  = $(BINDIR)/avr-size
#HEX = $(CP) -O ihex
#BIN = $(CP) -O binary -S
HEX = $(OBJCOPY) -O ihex
BIN = $(OBJCOPY) -O binary -S
AVRDUDE = avrdude
RM  = rm -rf
USBPORT = /dev/ttyUSB0
# wykys scripts
#WTR = $(RUN_PYTHON) $(SCRIPTS_DIR)$(PREFIX)translate-mcu.py --mcu=$(CHIP)
#WSZ = $(RUN_PYTHON) $(SCRIPTS_DIR)$(PREFIX)size.py --mcu=$(CHIP) --color --size="$(SZ)"
#WFS = $(RUN_PYTHON) $(SCRIPTS_DIR)find-serial.py
# miniterm
#MINITERM = $(SCRIPTS_DIR)run-miniterm.sh $(shell $(WFS) -d $(USB_TO_UART)) $(BAUDRATE)


#######################################
# Atmel Device Family Packs (DFP) for new devices support.
# http://packs.download.atmel.com/
#######################################
DFP = /opt/Atmel.ATmega_DFP.1.7.374
DEVSPEC = -B $(DFP)/gcc/dev/$(CHIP)
AVRLIB = -I$(DFP)/include


#######################################
# build the application
#######################################
# compile gcc flags
MCU = -mmcu=$(CHIP)
AFLAGS = $(MCU) -Wall $(INC)
CFLAGS = $(MCU) -Wall -std=c99 $(OPT) $(INC) $(DEVSPEC) $(AVRLIB)
CPPFLAGS = $(MCU) -Wall -std=c++11 $(OPT) $(INC) $(DEVSPEC) $(AVRLIB)
LDFLAGS = $(MCU)  -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -Wl,--cref $(DEVSPEC) $(AVRLIB)

# generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
CPPFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

# list of objects
# add C++ to objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# add C to objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# add ASM to objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

# default action: build all
#all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/EEPROM.hex $(BUILD_DIR)/$(TARGET).lss size
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/EEPROM.hex

# create object files from C++ files
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@echo "Compiling \t$< --> $@"
	@$(CPP) -c $(CPPFLAGS) $< -o $@

# create object files from C files
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo "Compiling \t$< --> $@"
	@$(CC) -c $(CFLAGS) $< -o $@

# create object files from ASM files
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	@echo "Assembling \t$< --> $@"
	@$(AS) -c $(AFLAGS) $< -o $@

# create aplication ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo "Linking \t$^ --> $@"
	@$(CPP) $(OBJECTS) $(LDFLAGS) -o $@

# create aplication FLASH intel HEX file
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@echo "Generating Intel Hex \t$< --> $@"
	@$(HEX) -R .eeprom $< $@

# create aplication EEPROM intel HEX file
$(BUILD_DIR)/EEPROM.hex: $(BUILD_DIR)/$(TARGET).elf
	@echo "Generating EEPROM Hex \t$< --> $@"
	@$(HEX) -j .eeprom --change-section-lma .eeprom=0 $< $@ 2> /dev/null

# disassembly EFL
#$(BUILD_DIR)/$(TARGET).lss: $(BUILD_DIR)/$(TARGET).elf
#	@$(DP) -h -S $< > $@
#	@$(OBJDUMP) -h -S $< > $@

# create build directory
$(BUILD_DIR):
	@echo "Create directory: \t$@"
	@mkdir $@

## Rule for extended listing file
list : $(BUILD_DIR)/$(TARGET).lss
$(BUILD_DIR)/$(TARGET).lss : $(BUILD_DIR)/$(TARGET).elf
	@echo "Generating listing file\t$< --> $@"
	@$(OBJDUMP) -h -S $< > $@

## Rule for printing the actual program size
# Displays the sizes of sections inside binary file
#size:
#	@$(WSZ) -e $(BUILD_DIR)/$(TARGET).elf
size : $(BUILD_DIR)/$(TARGET).elf
	@$(SIZE) --format=avr --mcu=$(MCU) --radix=16 $<


#######################################
# avrdude
#######################################
## Rule for program flashing
# https://www.nongnu.org/avrdude/user-manual/avrdude_4.html

###### TODO
dump_eeprom:
	@echo "dump eeprom" | $(AVRDUDE) -t

#flash:
#	$(AVRDUDE) -U flash:w:$(BUILD_DIR)/$(TARGET).elf:e
flash :
	@echo "Flashing program memory\t$<"
	$(AVRDUDE) -p $(MCU_DUDE) -c arduino -D -V -u -q -U flash:w:$(BUILD_DIR)/$(TARGET).hex:i -P $(USBPORT)

###### TODO
flash_all :
	@$(AVRDUDE) -U flash:w:$(BUILD_DIR)/$(TARGET).elf:e -U eeprom:w:$(BUILD_DIR)/$(TARGET).elf:e

build_and_flash: all flash


#######################################
# miniterm
#######################################
#miniterm:
#	@$(MINITERM)


## Clean rule
clean :
	@echo "Cleaning project files"
	@$(RM) $(BUILD_DIR)
