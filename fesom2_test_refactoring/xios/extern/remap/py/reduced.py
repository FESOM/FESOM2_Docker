import netCDF4 as nc
import sys
import math
import numpy as np

def from_reduced(N,M):
	"N elements from south to north and N elements around equator "
	hmax = 2*math.pi/N
	hmin = hmax/2
	nlon = N
	cells_lon = []
	cells_lat = []
	for i in range(M/2):
		lat1 = 180.0/M*i
		lat2 = 180.0/M*(i+1)
		y = math.sin(lat1*math.pi/180)
		r = math.cos(lat1*math.pi/180)
		h = 2.0*r/nlon
		reduce_nlon = (h < hmin) and (i > 0) and (nlon > 4)
		if reduce_nlon:
			nlon = nlon/2
		for j in range(nlon):
			lon1 = 360.0*j/nlon
			lon2 = 360.0*(j+1)/nlon
			bounds_lon = [lon1, lon1, lon2, lon2]
			bounds_lat = [lat1, lat2, lat2, lat1]
			if reduce_nlon:
				bounds_lon.append((lon1+lon2)/2)
				bounds_lat.append(lat1)
			else: # close by netCDF convention
				bounds_lon.append(bounds_lon[0])
				bounds_lat.append(bounds_lat[0])
			# northern hemisphere
			cells_lon.append(bounds_lon) 
			cells_lat.append(bounds_lat)
			# southern hemisphere
			cells_lon.append(bounds_lon)
			cells_lat.append(list(-np.array(bounds_lat))) # convert to array to negate elementwise
	return np.array(cells_lon), np.array(cells_lat)

for N in [64, 128, 256, 512]:
	filename = "reduced" + str(N) + ".nc"

	print "Generating: N =", N 
	lon, lat = from_reduced(N*2,N)

	print lon.shape[0], "cells -> writing as ", filename

	f = nc.Dataset(filename,'w')
	f.createDimension('n_vert', 5)
	f.createDimension('n_cell', lon.shape[0])

	var = f.createVariable('lat', 'd', ('n_cell'))
	var.setncattr("long_name", "latitude")
	var.setncattr("units", "degrees_north")
	var.setncattr("bounds", "bounds_lat")
	var[:] = np.zeros(lon.shape[0])
	var = f.createVariable('lon', 'd', ('n_cell'))
	var.setncattr("long_name", "longitude")
	var.setncattr("units", "degrees_east")
	var.setncattr("bounds", "bounds_lon")
	var[:] = np.zeros(lon.shape[0])

	var = f.createVariable('bounds_lon', 'd', ('n_cell','n_vert'))
	var[:] = lon
	var = f.createVariable('bounds_lat', 'd', ('n_cell','n_vert'))
	var[:] = lat
	var = f.createVariable('val', 'd', ('n_cell'))
	var.setncattr("coordinates", "lon lat")
	var[:] = np.arange(lon.shape[0])
	f.close()
