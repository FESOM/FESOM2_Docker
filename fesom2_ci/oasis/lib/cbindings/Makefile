%.o: %.mod

CBINDSRC=$(COUPLE)/lib/cbindings

SRC_C = $(CBINDSRC)/c_src
SRC_F = $(CBINDSRC)/fortran_isoc

ifeq ($(MAKECMDGOALS),libshared)
  FFLAGS = $(F90FLAGS) $(DYNOPT) -I$(LIBBUILDSHARED)/mct -I$(LIBBUILDSHARED)/psmile.$(CHAN)
  CFLAGS = $(CCFLAGS) $(DYNOPT) -I$(SRC_C)
  LFLAGS = $(LDFLAGS) $(DYNOPT) $(LDDYNOPT) -L$(ARCHDIR)/lib $(NETCDF_LIBRARY)
else
  FFLAGS = $(F90FLAGS) -I$(LIBBUILD)/mct -I$(LIBBUILD)/psmile.$(CHAN)
  CFLAGS = $(CCFLAGS) -I$(SRC_C)
  LFLAGS = $(LDFLAGS) $(LDOPT) -L$(ARCHDIR)/lib $(NETCDF_LIBRARY)
endif

default: libstatic

OBJS_F = cbindings.o mod_oasis_auxiliary_routines_iso.o mod_oasis_getput_interface_iso.o mod_oasis_method_iso.o mod_oasis_part_iso.o mod_oasis_sys_iso.o mod_oasis_var_iso.o mod_oasis_grid_iso.o

OBJS_C = mod_oasis_auxiliary_routines_c.o mod_oasis_getput_interface_c.o mod_oasis_method_c.o mod_oasis_part_c.o mod_oasis_sys_c.o mod_oasis_var_c.o mod_oasis_grid_c.o

header: $(SRC_C)/oasis_c.h
	@(cp -f $(SRC_C)/oasis_c.h $(ARCHDIR)/include)

libstatic: header $(OBJS_F) $(OBJS_C)
	$(AR) $(ARFLAGS) $(ARCHDIR)/lib/liboasis.cbind.a $(OBJS_F) $(OBJS_C)

libshared: header $(OBJS_F) $(OBJS_C)
	$(F90) $(LFLAGS) $(OBJS_F) $(OBJS_C) -lpsmile.$(CHAN) -lscrip -lmct -lmpeu -o $(ARCHDIR)/lib/liboasis.cbind.so

# C

mod_oasis_part_c.o: $(SRC_C)/oasis_c.h $(SRC_C)/mod_oasis_part_c.c $(OBJS_F)
	$(CC) $(CFLAGS) -c $(SRC_C)/mod_oasis_part_c.c

mod_oasis_var_c.o: $(SRC_C)/oasis_c.h $(SRC_C)/mod_oasis_var_c.c $(OBJS_F)
	$(CC) $(CFLAGS) -c $(SRC_C)/mod_oasis_var_c.c

mod_oasis_getput_interface_c.o: $(SRC_C)/oasis_c.h $(SRC_C)/mod_oasis_getput_interface_c.c $(OBJS_F)
	$(CC) $(CFLAGS) -c $(SRC_C)/mod_oasis_getput_interface_c.c

mod_oasis_auxiliary_routines_c.o: $(SRC_C)/oasis_c.h $(SRC_C)/mod_oasis_auxiliary_routines_c.c $(OBJS_F)
	$(CC) $(CFLAGS) -c  $(SRC_C)/mod_oasis_auxiliary_routines_c.c

mod_oasis_sys_c.o: $(SRC_C)/oasis_c.h $(SRC_C)/mod_oasis_sys_c.c $(OBJS_F)
	$(CC) $(CFLAGS) -c  $(SRC_C)/mod_oasis_sys_c.c

mod_oasis_method_c.o: $(SRC_C)/oasis_c.h $(SRC_C)/mod_oasis_method_c.c $(OBJS_F)
	$(CC) $(CFLAGS) -c  $(SRC_C)/mod_oasis_method_c.c

mod_oasis_grid_c.o: $(SRC_C)/oasis_c.h $(SRC_C)/mod_oasis_grid_c.c $(OBJS_F)
	$(CC) $(CFLAGS) -c  $(SRC_C)/mod_oasis_grid_c.c


# ISO C Fortran

mod_oasis_getput_interface_iso.o: $(SRC_F)/mod_oasis_getput_interface_iso.F90 cbindings.o
	$(F90) $(FFLAGS) -c $(SRC_F)/mod_oasis_getput_interface_iso.F90

mod_oasis_var_iso.o: $(SRC_F)/mod_oasis_var_iso.F90 cbindings.o
	$(F90) $(FFLAGS) -c  $(SRC_F)/mod_oasis_var_iso.F90

mod_oasis_part_iso.o: $(SRC_F)/mod_oasis_part_iso.F90 cbindings.o
	$(F90) $(FFLAGS) -c  $(SRC_F)/mod_oasis_part_iso.F90

mod_oasis_auxiliary_routines_iso.o: $(SRC_F)/mod_oasis_auxiliary_routines_iso.F90 cbindings.o
	$(F90) $(FFLAGS) -c  $(SRC_F)/mod_oasis_auxiliary_routines_iso.F90

mod_oasis_sys_iso.o: $(SRC_F)/mod_oasis_sys_iso.F90 cbindings.o
	$(F90) $(FFLAGS) -c  $(SRC_F)/mod_oasis_sys_iso.F90

mod_oasis_method_iso.o: $(SRC_F)/mod_oasis_method_iso.F90 cbindings.o
	$(F90) $(FFLAGS) -c $(SRC_F)/mod_oasis_method_iso.F90

mod_oasis_grid_iso.o: $(SRC_F)/mod_oasis_grid_iso.F90 cbindings.o
	$(F90) $(FFLAGS) -c $(SRC_F)/mod_oasis_grid_iso.F90

cbindings.o: $(SRC_F)/cbindings.F90
	$(F90) $(FFLAGS) -c $(SRC_F)/cbindings.F90
