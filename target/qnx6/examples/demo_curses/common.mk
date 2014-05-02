ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

define PINFO
PINFO DESCRIPTION=Android Open Accessory Curses Client
endef

NAME=aoa_curses
INSTALLDIR=usr/bin
USEFILE=

include $(MKFILES_ROOT)/qtargets.mk

LIBS += ncurses m aoa
