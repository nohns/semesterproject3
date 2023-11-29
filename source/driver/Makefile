#################################################
#### Kernel module compilation configuration ####
#################################################

dmc_driver-objs := dmc_driver_main.o dmc/event.o dmc/ctrl/event_handler.o dmc/ctrl/packet_handler.o dmc/netlink/handler.o dmc/netlink/message.o dmc/uart/handler.o
obj-m += dmc_driver.o
overlay := dmc_overlay.dts
ccflags-y := -std=gnu99 -DDEBUG -Wno-declaration-after-statement -Wno-unused-function -Werror -I$(src)/../common/hw/include

ENV ?= "native-pi"
ifeq ($(ENV), "vm")
	KERNELDIR := /lib/modules/6.2.0-36-generic/build
else ifeq ($(ENV), "pi")
	KERNELDIR := ~/sources/linux
	ARCH := arm64
	CROSS_COMPILE := aarch64-linux-gnu-
	UPLOAD_TARGET := pi@172.20.10.5
	UPLOAD_TARGET_DIR := ~/modules
else ifeq ($(ENV), "native-pi")
	KERNELDIR := /lib/modules/6.1.0-rpi6-rpi-2712/build
endif

CURR_DIR := $(shell pwd)
SOURCES := $(obj-m:.o=.c)
SOURCES += $(dmc_driver-objs:.o=.c)
MODULE_KO := ${obj-m:.o=.ko}
OVERLAY_OUT := ${overlay:.dts=.dtbo}

#########################
#### Other variables ####
#########################

ifdef CROSS_COMPILE
	CROSS_COMPILE_ARG := CROSS_COMPILE=$(CROSS_COMPILE)
endif

ifdef ARCH
	ARCH_ARG := ARCH=$(ARCH)
endif

MAKE_CMD := $(MAKE) $(ARCH_ARG) $(CROSS_COMPILE_ARG) -C $(KERNELDIR) M=$(shell pwd)

########################
#### Target aliases ####
########################

# Make target aliases - e.g default runs module compilaton (target modules)
all default: modules
install: modules_install

$(OVERLAY_OUT): $(overlay)
	dtc -@ -I dts -O dtb -o $@ $<

modules:
	@echo "Making for environment: $(ENV)"
	$(MAKE_CMD) $@

# Pass target onto the kernel module Makefile
modules_install help clean: 
	$(MAKE_CMD) $@

# Upload compiled kernel module to Raspberry Pi Zero
upload: modules $(OVERLAY_OUT)
	ssh $(UPLOAD_TARGET) "mkdir -p $(UPLOAD_TARGET_DIR)"
	scp -pr $(MODULE_KO) $(UPLOAD_TARGET):$(UPLOAD_TARGET_DIR)/$(MODULE_KO)
	scp -pr $(OVERLAY_OUT) $(UPLOAD_TARGET):$(UPLOAD_TARGET_DIR)/$(OVERLAY_OUT)
	@echo "Uploaded $(MODULE_KO) and $(OVERLAY_OUT) to $(UPLOAD_TARGET):$(UPLOAD_TARGET_DIR)"
	@echo "Don't forget to install the overlay to /boot/overlays and add it to /boot/config.txt"



