ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION=Android Open Accessory Swap-only Client
endef

INSTALLDIR=usr/bin
USEFILE=

include $(MKFILES_ROOT)/qtargets.mk

LIBS += m aoa
