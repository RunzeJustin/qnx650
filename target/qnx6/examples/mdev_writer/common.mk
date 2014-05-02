ifndef QCONFIG
 QCONFIG=qconfig.mk
endif
include $(QCONFIG)

# LIBS +=

NAME=mdev-writer
INSTALLDIR=usr/bin
USEFILE = $(PROJECT_ROOT)/mdev_writer.c

define PINFO
 PINFO DESCRIPTION="mdev push streamer writer"
endef


include $(MKFILES_ROOT)/qmacros.mk

include $(MKFILES_ROOT)/qtargets.mk

LIBS+=m
