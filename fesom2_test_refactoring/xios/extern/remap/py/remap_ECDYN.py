import netCDF4 as nc
import ctypes as ct
import numpy as np
import os
import sys
import math
from mpi4py import MPI

import time

remap = ct.cdll.LoadLibrary(os.path.realpath('libmapper.so'))

def from_mpas(filename):
	# construct vortex bounds from Mpas grid structure
	f = nc.Dataset(filename)
	# in this case it is must faster to first read the whole file into memory
	# before converting the data structure
	print "read"
	stime = time.time()
	lon_vert = np.array(f.variables["lonVertex"])
	lat_vert = np.array(f.variables["latVertex"])
	vert_cell = np.array(f.variables["verticesOnCell"])
	nvert_cell = np.array(f.variables["nEdgesOnCell"])
	ncell, nvert = vert_cell.shape
	assert(max(nvert_cell) <= nvert)
	lon = np.zeros(vert_cell.shape)
	lat = np.zeros(vert_cell.shape)
	etime = time.time()
	print "finished read, now convert", etime-stime
	scal = 180.0/math.pi
	for c in range(ncell):
		lat[c,:] = lat_vert[vert_cell[c,:]-1]*scal
		lon[c,:] = lon_vert[vert_cell[c,:]-1]*scal
		# signal "last vertex" by netCDF convetion
		lon[c,nvert_cell[c]] = lon[c,0]
		lat[c,nvert_cell[c]] = lat[c,0]
	print "convert end", time.time() - etime
	return lon, lat

grid_types = {
	"dynamico:mesh": {
		"lon_name": "bounds_lon_i",
		"lat_name": "bounds_lat_i",
		"pole": [0,0,0]
	},
	"dynamico:vort": {
		"lon_name": "bounds_lon_v",
		"lat_name": "bounds_lat_v",
		"pole": [0,0,0]
	},
	"dynamico:restart": {
		"lon_name": "lon_i_vertices",
		"lat_name": "lat_i_vertices",
		"pole": [0,0,0]
	},
	"test:polygon": {
		"lon_name": "bounds_lon",
		"lat_name": "bounds_lat",
		"pole": [0,0,0]
	},
	"test:latlon": {
		"lon_name": "bounds_lon",
		"lat_name": "bounds_lat",
		"pole": [0,0,1]
	},
	"mpas": {
		"reader": from_mpas,
		"pole": [0,0,0]
	}
}

interp_types = {
	"FV1": 1,
	"FV2": 2
}

usage = """
Usage: python remap.py interp srctype srcfile dsttype dstfile mode outfile

   interp: type of interpolation
       choices:
           FV1: first order conservative Finite Volume
           FV2: second order conservative Finite Volume

   srctype, dsttype: grid type of source and destination
       choices: """ + " ".join(grid_types.keys()) + """

   srcfile, dstfile: grid file names, should mostly be netCDF file

   mode: modus of operation 
       choices:
           weights: computes weight and stores them in outfile
           remap:   computes the interpolated values on destination grid and stores them in outfile

   outfile: output filename

"""

# parse command line arguments
if not len(sys.argv) == 8:
	print usage
	sys.exit(2)

interp = sys.argv[1]
try:
	srctype = grid_types[sys.argv[2]]
except KeyError:
	print "Error: srctype needs to be one of the following: " + " ".join(grid_types.keys()) + "."
	exit(2)
srcfile = sys.argv[3]
try:
	dsttype = grid_types[sys.argv[4]]
except KeyError:
	print "Error: srctype needs to be one of the following: " + " ".join(grid_types.keys()) + "."
	exit(2)
dstfile = sys.argv[5]
mode    = sys.argv[6]
outfile = sys.argv[7]

if not mode in ("weights", "remap"):
	print "Error: mode must be of of the following: weights remap."
	exit(2)

remap.mpi_init()
rank = remap.mpi_rank()
size = remap.mpi_size()

print rank, "/", size

print "Reading grids from netCDF files."

if "reader" in srctype:
	src_lon, src_lat = srctype["reader"](srcfile)
else:
	src = nc.Dataset(srcfile)
	# the following two lines do not perform the actual read
	# the file is read later when assigning to the ctypes array
	# -> no unnecessary array copying in memory
	src_lon = src.variables[srctype["lon_name"]]
	src_lat = src.variables[srctype["lat_name"]]

if "reader" in dsttype:
	dst_lon, dst_lat = dsttype["reader"](dstfile)
else:
	dst = nc.Dataset(dstfile)
	dst_lon = dst.variables[dsttype["lon_name"]]
	dst_lat = dst.variables[dsttype["lat_name"]]

src_ncell, src_nvert = src_lon.shape
dst_ncell, dst_nvert = dst_lon.shape

def compute_distribution(ncell):
	"Returns the local number and starting position in global array."
	if rank < ncell % size:
		return ncell//size + 1, \
		       (ncell//size + 1)*rank
	else:
		return ncell//size, \
		       (ncell//size + 1)*(ncell%size) + (ncell//size)*(rank - ncell%size)

src_ncell_loc, src_loc_start = compute_distribution(src_ncell)
dst_ncell_loc, dst_loc_start = compute_distribution(dst_ncell)

print "src", src_ncell_loc, src_loc_start 
print "dst", dst_ncell_loc, dst_loc_start 

c_src_lon = (ct.c_double * (src_ncell_loc*src_nvert))()
c_src_lat = (ct.c_double * (src_ncell_loc*src_nvert))()
c_dst_lon = (ct.c_double * (dst_ncell_loc*dst_nvert))()
c_dst_lat = (ct.c_double * (dst_ncell_loc*dst_nvert))()

c_src_lon[:] = nc.numpy.reshape(src_lon[src_loc_start:src_loc_start+src_ncell_loc,:], (len(c_src_lon),1))
c_src_lat[:] = nc.numpy.reshape(src_lat[src_loc_start:src_loc_start+src_ncell_loc,:], (len(c_src_lon),1))
c_dst_lon[:] = nc.numpy.reshape(dst_lon[dst_loc_start:dst_loc_start+dst_ncell_loc,:], (len(c_dst_lon),1))
c_dst_lat[:] = nc.numpy.reshape(dst_lat[dst_loc_start:dst_loc_start+dst_ncell_loc,:], (len(c_dst_lon),1))


print "Calling remap library to compute weights."
srcpole = (ct.c_double * (3))()
dstpole = (ct.c_double * (3))()
srcpole[:] = srctype["pole"]
dstpole[:] = dsttype["pole"]

c_src_ncell = ct.c_int(src_ncell_loc)
c_src_nvert = ct.c_int(src_nvert)
c_dst_ncell = ct.c_int(dst_ncell_loc)
c_dst_nvert = ct.c_int(dst_nvert)
order = ct.c_int(interp_types[interp])

c_nweight = ct.c_int()

print "src:", src_ncell, src_nvert
print "dst:", dst_ncell, dst_nvert

remap.remap_get_num_weights(c_src_lon, c_src_lat, c_src_nvert, c_src_ncell, srcpole,
               c_dst_lon, c_dst_lat, c_dst_nvert, c_dst_ncell, dstpole,
               order, ct.byref(c_nweight))

nwgt = c_nweight.value

c_weights = (ct.c_double * nwgt)()
c_dst_idx = (ct.c_int * nwgt)()
c_src_idx = (ct.c_int * nwgt)()

remap.remap_get_weights(c_weights, c_src_idx, c_dst_idx)

wgt_glo     = MPI.COMM_WORLD.gather(c_weights[:])
src_idx_glo = MPI.COMM_WORLD.gather(c_src_idx[:])
dst_idx_glo = MPI.COMM_WORLD.gather(c_dst_idx[:])


if rank == 0 and mode == 'weights':
	nwgt_glo = sum(len(wgt) for wgt in wgt_glo)

	print "Writing", nwgt_glo, "weights to netCDF-file '" + outfile + "'."
	f = nc.Dataset(outfile,'w')
	f.createDimension('n_src',    src_ncell)
	f.createDimension('n_dst',    dst_ncell)
	f.createDimension('n_weight', nwgt_glo)

	var = f.createVariable('src_idx', 'i', ('n_weight'))
	var[:] = np.hstack(src_idx_glo) + 1 # make indices start from 1
	var = f.createVariable('dst_idx', 'i', ('n_weight'))
	var[:] = np.hstack(dst_idx_glo) + 1 # make indices start from 1
	var = f.createVariable('weight',  'd', ('n_weight'))
	var[:] = np.hstack(wgt_glo)
	f.close()

def test_fun(x, y, z):
	return (1-x**2)*(1-y**2)*z

def test_fun_ll(lat, lon):
	#return np.cos(lat*math.pi/180)*np.cos(lon*math.pi/180)
	return 2.0 + np.cos(lat*math.pi/180.)**2 * np.cos(2*lon*math.pi/180.);

#UNUSED
#def sphe2cart(lat, lon):
#	phi   = math.pi/180*lon[:]
#	theta = math.pi/2 - math.pi/180*lat[:]
#	return np.sin(theta)*np.cos(phi), np.sin(theta)*np.sin(phi), np.cos(theta)

if mode == 'remap':
	c_centre_lon = (ct.c_double * src_ncell_loc)()
	c_centre_lat = (ct.c_double * src_ncell_loc)()
	c_areas      = (ct.c_double * src_ncell_loc)()
	remap.remap_get_barycentres_and_areas(c_src_lon, c_src_lat, c_src_nvert, c_src_ncell, srcpole,
		c_centre_lon, c_centre_lat, c_areas)
#	src_val_loc = test_fun_ll(np.array(c_centre_lat[:]), np.array(c_centre_lon[:]))
#	src_val_loc = src.variables["ps"]
#	src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[:]))
#        src_val_glo = src_val_loc

	c_centre_lon = (ct.c_double * dst_ncell_loc)()
	c_centre_lat = (ct.c_double * dst_ncell_loc)()
	c_areas      = (ct.c_double * dst_ncell_loc)()
	remap.remap_get_barycentres_and_areas(c_dst_lon, c_dst_lat, c_dst_nvert, c_dst_ncell, dstpole,
		c_centre_lon, c_centre_lat, c_areas)
#	dst_val_loc = test_fun_ll(np.array(c_centre_lat[:]), np.array(c_centre_lon[:]))

#	dst_val_glo = MPI.COMM_WORLD.gather(dst_val_loc)
	dst_areas_glo = MPI.COMM_WORLD.gather(np.array(c_areas[:]))
	dst_centre_lon_glo = MPI.COMM_WORLD.gather(np.array(c_centre_lon[:]))
	dst_centre_lat_glo = MPI.COMM_WORLD.gather(np.array(c_centre_lat[:]))


if rank == 0 and mode == 'remap':
	from scipy import sparse
	A = sparse.csr_matrix(sparse.coo_matrix((np.hstack(wgt_glo),(np.hstack(dst_idx_glo),np.hstack(src_idx_glo)))))

#	src_val = np.hstack(src_val_glo)
#	dst_ref = np.hstack(dst_val_glo)
	dst_areas = np.hstack(dst_areas_glo)
	dst_centre_lon = np.hstack(dst_centre_lon_glo)
	dst_centre_lat = np.hstack(dst_centre_lat_glo)

#	print "source:", src_val.shape
#	print "destin:", dst_ref.shape
#	dst_val = A*src_val
#	err = dst_val - dst_ref
#	print "absolute maximum error, maximum value:", np.max(np.abs(err)), np.max(np.abs(dst_ref))
#	print "relative maximum error, normalized L2 error, average target cell size (edgelength of same-area square):"
#	print np.max(np.abs(err))/np.max(np.abs(dst_ref)), np.linalg.norm(err)/np.linalg.norm(dst_ref), np.mean(np.sqrt(dst_areas))

	lev=src.dimensions['lev']
        f = nc.Dataset(outfile,'w')
	f.createDimension('nvert', dst_nvert)
	f.createDimension('cell', dst_ncell)
	f.createDimension('lev', len(lev))

	var = f.createVariable('lat', 'd', ('cell'))
	var.setncattr("long_name", "latitude")
	var.setncattr("units", "degrees_north")
	var.setncattr("bounds", "bounds_lat")
	var[:] = dst_centre_lat
	var = f.createVariable('lon', 'd', ('cell'))
	var.setncattr("long_name", "longitude")
	var.setncattr("units", "degrees_east")
	var.setncattr("bounds", "bounds_lon")
	var[:] = dst_centre_lon

	var = f.createVariable('bounds_lon', 'd', ('cell','nvert'))
	var[:] = dst_lon
	var = f.createVariable('bounds_lat', 'd', ('cell','nvert'))
	var[:] = dst_lat

	var = f.createVariable('lev', 'd', ('lev'))
	var[:] = src.variables['lev']
        var.setncattr('axis', 'Z')
        var.setncattr('units', 'Pa')
        var.setncattr('positive', 'down')
	var[:] = src.variables['lev']

        U = f.createVariable('U', 'd', ('lev','cell'))
	U.setncattr("coordinates", "lev lon lat")
 
        V = f.createVariable('V', 'd', ('lev','cell'))
	V.setncattr("coordinates", "lev lon lat")

        TEMP = f.createVariable('TEMP', 'd', ('lev','cell'))
	TEMP.setncattr("coordinates", "lev lon lat")

        R = f.createVariable('R', 'd', ('lev','cell'))
	R.setncattr("coordinates", "lev lon lat")

	Z = f.createVariable('Z', 'd', ('cell'))
	Z.setncattr("coordinates", "lon lat")

	ST = f.createVariable('ST', 'd', ('cell'))
	ST.setncattr("coordinates", "lon lat")

	CDSW = f.createVariable('CDSW', 'd', ('cell'))
	CDSW.setncattr("coordinates", "lon lat")
        
	SP = f.createVariable('SP', 'd', ('cell'))
	SP.setncattr("coordinates", "lon lat")
        


#for U
if mode == 'remap':
	src_val_loc = src.variables['U']

for l in range(0, len(lev)):
	if mode == 'remap':
		src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[l,:]))

	if rank == 0 and mode == 'remap':
      		src_val = np.hstack(src_val_glo)
		dst_val = A*src_val
		U[l,:] = dst_val

#for V
if mode == 'remap':
	src_val_loc = src.variables['V']

for l in range(0, len(lev)):
	if mode == 'remap':
		src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[l,:]))

	if rank == 0 and mode == 'remap':
      		src_val = np.hstack(src_val_glo)
		dst_val = A*src_val
		V[l,:] = dst_val


#for TEMP
if mode == 'remap':
	src_val_loc = src.variables['TEMP']

for l in range(0, len(lev)):
	if mode == 'remap':
		src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[l,:]))

	if rank == 0 and mode == 'remap':
      		src_val = np.hstack(src_val_glo)
		dst_val = A*src_val
		TEMP[l,:] = dst_val

#for R
if mode == 'remap':
	src_val_loc = src.variables['R']

for l in range(0, len(lev)):
	if mode == 'remap':
		src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[l,:]))

	if rank == 0 and mode == 'remap':
      		src_val = np.hstack(src_val_glo)
		dst_val = A*src_val
		R[l,:] = dst_val


#for Z
if mode == 'remap':
	src_val_loc = src.variables['Z']
	src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[:]))

if rank == 0 and mode == 'remap':
      	src_val = np.hstack(src_val_glo)
	dst_val = A*src_val
	Z[:] = dst_val

#for ST
if mode == 'remap':
	src_val_loc = src.variables['ST']
	src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[:]))

if rank == 0 and mode == 'remap':
      	src_val = np.hstack(src_val_glo)
	dst_val = A*src_val
	ST[:] = dst_val


#for CDSW
if mode == 'remap':
	src_val_loc = src.variables['CDSW']
	src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[:]))

if rank == 0 and mode == 'remap':
      	src_val = np.hstack(src_val_glo)
	dst_val = A*src_val
	CDSW[:] = dst_val

#for SP
if mode == 'remap':
	src_val_loc = src.variables['SP']
	src_val_glo = MPI.COMM_WORLD.gather(np.array(src_val_loc[:]))

if rank == 0 and mode == 'remap':
      	src_val = np.hstack(src_val_glo)
	dst_val = A*src_val
	SP[:] = dst_val



if mode == 'remap':
	f.close()
        

if not "reader" in srctype:
	src.close()
if not "reader" in dsttype:
	dst.close()

