#
# This is the module configuration file.
#
# It is referenced from configuration files in the target directory.
#

# Add references for filesystems and drivers
MODULE_IFACE += iofs_module_avrcpexample

# Add defines for conditional configuration compiles
MODULE_DEFINE += DRVR_avrcpexample

# Add dependent modules to required list if nessessary
MODULE_REQUIRED += 

# Add library path to find the archive
MODULE_LIBVPATH += $(PRODUCT_ROOT)/drvr/media/avrcpexample/a/$(CPUENDIAN)

# Add library name for archive
MODULE_LIB += drvr-avrcpexample

# Add extra libraries this module depends on
MODULE_EXTRA_LIBS += 
