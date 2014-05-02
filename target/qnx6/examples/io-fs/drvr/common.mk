ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

INSTALLDIR=lib/dll

USEFILE=

include $(MKFILES_ROOT)/qmacros.mk
-include $(PRODUCT_ROOT)/testing.mk

# Adjust SECTION and PROJECT because we have one extra level of directory
DRVR_TYPE := $(SECTION)
PROJECT_ROOT := $(SECTION_ROOT)
SECTION := $(firstword $(filter-out $(SECTION), $(foreach level, 9 8 7 6 5 4 3 2 1, $(VARIANT$(level)))))
SECTION_ROOT := $(SECTION_ROOT)/$(SECTION)

include $(SECTION_ROOT)/pinfo.mk

EXTRA_INCVPATH = $(SECTION_ROOT)/public $(PROJECT_ROOT)/public $(PRODUCT_ROOT) $(PRODUCT_ROOT)/lib/public $(PRODUCT_ROOT)/../../lib/cipher/public

#CCFLAGS += -D_FILE_OFFSET_BITS=64
CCFLAGS += -DMODULE_NAME="$(SECTION)"

# The following is used optionally do bounds checking
-include $(PRODUCT_ROOT)/bounds.mk

EXTRA_SILENT_VARIANTS = $(if $(filter lib,$(SECTION)),lib,$(DRVR_TYPE))

-include $(SECTION_ROOT)/extra.mk
-include $(PROJECT_ROOT)/extra.mk

ifeq ($(filter dll, $(VARIANTS)),)

INSTALLDIR=/dev/null

else

NAME=iofs
LDVFLAG_dll = -Wl,"--version-script export.ver"
include $(SECTION_ROOT)/module.mk
MODULE_LIB=
ifeq ($(filter lib, $(SECTION)),)
ENDIAN := $(filter le be, $(VARIANT_LIST))
CPUENDIAN := $(CPU)$(if $(ENDIAN),-)$(ENDIAN)
SHARED_DIR = -shared
SHARED_LIB = S
-include $(PROJECT_ROOT)/lib/module.mk
LIBS = $(MODULE_LIB) $(MODULE_EXTRA_LIBS)
EXTRA_LIBVPATH = $(MODULE_LIBVPATH)
EXTRA_DEPS += export.ver
EXTRA_CLEAN = export.ver
endif

endif

EXPORT_SYMS += iofs_module

include $(MKFILES_ROOT)/qtargets.mk

export.ver:
	@$(RM_HOST) export.ver
	@$(ECHO_HOST) "{ global: $(foreach symbol,$(sort $(EXPORT_SYMS)),$(symbol); ) local: *; };" >export.ver
