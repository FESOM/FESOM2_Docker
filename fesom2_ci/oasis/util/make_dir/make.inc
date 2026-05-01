# ============================================================================
# *** Set build ARCHITECTURE here
# ============================================================================

# NOTE: This setting is supposedly overwritten by a command line argument
BUILD_ARCH := NO_ARCH_DEFINED

$(info --> Using BUILD_ARCH=$(BUILD_ARCH))

# ============================================================================
# *** Build ARCHITECTURE configuration
# ============================================================================

makefile_path        := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))Makefile.d
MAKEFILE_CONFIG_ARCH := $(makefile_path)/Makefile.config.$(BUILD_ARCH)

ifneq ($(wildcard $(MAKEFILE_CONFIG_ARCH)),)
    include $(MAKEFILE_CONFIG_ARCH)
else
    $(info .   ======================================================================)
    $(info .   *** Unknown build architecture: '$(BUILD_ARCH)')
    $(info .   *** ------------------------------------------------------------------)
    $(info .   *** Please make sure that you specify the correct)
    $(info .   *** BUILD_ARCH=<ARCHITECTURE> on the make command line and )
    $(info .   *** that a file '$(notdir $(MAKEFILE_CONFIG_ARCH))' exists  )
    $(info .   *** in the following directory: )
    $(info .   *** $(MAKEFILE_CONFIG).d )
    $(info .   ======================================================================)
    $(error Unknown architecture BUILD_ARCH=$(BUILD_ARCH))
endif

# ============================================================================
# *** Architecture independent configuration
# ============================================================================

#  External libraies for linking
FLIBS = $(NETCDF_LIBRARY) $(NETCDFF_LIBRARY) $(MPILIB)

# ARCHDIR : directory created when compiling
ARCHDIR   := $(COUPLE)/$(BUILD_ARCH)

# LIBPSMILE : list of oasis3 libraries
LIBPSMILE   := $(ARCHDIR)/lib/libanaisg.a \
               $(ARCHDIR)/lib/libanaism.a \
               $(ARCHDIR)/lib/libclim.$(CHAN).a \
               $(ARCHDIR)/lib/libpsmile.$(CHAN).a \
               $(ARCHDIR)/lib/libfscint.a \
               $(ARCHDIR)/lib/libmpp_io.a \
               $(ARCHDIR)/lib/libscrip.a

# BINDIR : directory for executables
BINDIR   := $(ARCHDIR)/bin

# LIBBUILD : contains a directory for each library
LIBBUILD   := $(ARCHDIR)/build/lib

# PSMILE_INCDIR : includes all *o and *mod for each library
PSMILE_INCDIR   := -I$(LIBBUILD)/psmile.$(CHAN) \
                   -I$(LIBBUILD)/clim.$(CHAN) \
                   -I$(LIBBUILD)/mpp_io

F90FLAGS += $(PSMILE_INCDIR)
CCFLAGS  += $(PSMILE_INCDIR)

# Needed to work with SCE Makefile
I4mods := I
