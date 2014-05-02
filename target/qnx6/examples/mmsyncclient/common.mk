ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

DEBUG=-g -Werror

define PINFO
PINFO DESCRIPTION=Multimedia Sync Engine API Client
endef

NAME=mmsyncclient

INSTALLDIR=usr/bin

USEFILE=$(PROJECT_ROOT)/mmsyncclient.use

include $(MKFILES_ROOT)/qtargets.mk

LIBS += mmsyncclient strm

