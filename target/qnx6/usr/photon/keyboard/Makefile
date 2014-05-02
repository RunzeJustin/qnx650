ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

all : $(patsubst %.kdef, %.kbd, $(wildcard *.kdef))


.PHONY : all clean hinstall install iclean

%.kbd : %.kdef
	mkkbd -h $(USE_ROOT_nto)/usr/include/ $< 
	chmod +r $@
#
#

clean :
	rm -f *.kbd

hinstall:

install : $(patsubst %.kdef, %.kbd, $(wildcard *.kdef))
	  $(CP_HOST) *.kbd $(USE_ROOT_nto)/usr/photon/keyboard/
iclean:
	rm -f *.kbd
