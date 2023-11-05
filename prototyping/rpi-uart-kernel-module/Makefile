#################################################
#### Kernel module compilation configuration ####
#################################################

obj-m := rpi-uart.o
ccflags-y := -std=gnu99 -Wno-declaration-after-statement -Werror

# REMOVE COMMENT BELOW FOR RASPBERRY PI LINUX COMPILATION
KERNELDIR ?= ~/sources/rpi-5.4.83
KERNELDIR ?= ~/sources/linux-6.2.0
CURR_DIR := $(shell pwd)
BUILD_DIR := $(CURR_DIR)/build
# REMOVE COMMENT BELOW FOR RASPBERRY PI LINUX COMPILATION
CROSS_COMPILE := arm-poky-linux-gnueabi-
# REMOVE COMMENT BELOW FOR RASPBERRY PI LINUX COMPILATION
ARCH ?= arm
HEADERS := $(obj-m:.o=.h)
SOURCES := $(obj-m:.o=.c)

#####################################
#### Target device configuration ####
#####################################

MODULE_KO := ${obj-m:.o=.ko}
UPLOAD_TARGET := root@10.9.8.2
UPLOAD_TARGET_DIR := ~/modules

#########################
#### Other variables ####
#########################

ifdef CROSS_COMPILE
	CROSS_COMPILE_ARG := CROSS_COMPILE=$(CROSS_COMPILE)
endif

ifdef ARCH
	ARCH_ARG := ARCH=$(ARCH)
endif

MAKE_CMD := $(MAKE) $(ARCH_ARG) $(CROSS_COMPILE_ARG) -C $(KERNELDIR) M=$(BUILD_DIR)

########################
#### Target aliases ####
########################

# Make target aliases - e.g default runs module compilaton (target modules)
all default: modules
install: modules_install

########################################################
#### Build directory preperation before compilation ####
########################################################

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/$(SOURCES): $(SOURCES) $(BUILD_DIR)
	cp $< $@

$(BUILD_DIR)/$(HEADERS): $(HEADERS) $(BUILD_DIR)
	cp $< $@

$(BUILD_DIR)/Makefile: Makefile
	cp $< $@


# It is not easy to set an output directory when building a kernel module. Per default, the output will just be in the
# same directory as the source files, which is not very nice. So before building the module, we copy all the headers,
# source files and the Makefile into a build directory (created if it doesn't exist). We then run make command from here.
modules: $(BUILD_DIR) $(BUILD_DIR)/$(HEADERS) $(BUILD_DIR)/$(SOURCES) $(BUILD_DIR)/Makefile 
	@echo "\n\nReally do be buildin' tho\n\n"
	$(MAKE_CMD) $@

# Pass target onto the kernel module Makefile
modules_install help clean: 
	$(MAKE_CMD) $@

# Upload compilefd kernel module to Raspberry Pi Zero
upload: modules
	ssh $(UPLOAD_TARGET) "mkdir -p $(UPLOAD_TARGET_DIR)"
	scp -pr $(BUILD_DIR)/$(MODULE_KO) $(UPLOAD_TARGET):$(UPLOAD_TARGET_DIR)/$(MODULE_KO)



