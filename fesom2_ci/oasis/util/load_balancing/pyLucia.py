#!/usr/bin/env python3

##########################################################################
#
#   pyLucia.py 
#
#   Visualisation tool 
#
#   Input:  - timeline files produced by the OASIS coupler
#             ( load balancing measurement option required )
#           - json or yaml configuration file (see example below )
#
#   Output: - timeline plot of OASIS coupling events
#             (in graphical format file and visulaisation GUI)
#
#   Author : A. Piacentini (2020)
#            + E. Maisonnave (2020): Color blind friendly default palette
#
#
#   Poem lines :
#
#
#
##########################################################################
#
#  json config file example
#
###
#    {
#       "Components":[
#           {"Name":"Atmo",
#            "File":"timeline_atm.nc"},
#           {"Name":"Ocean",
#            "File":"timeline_oce.nc"},
#           {"Name":"IOserver",
#            "File":"timeline_ios.nc"}
#       ],
#       "Plots":{
#           "Kind" : true,
#           "Field": true,
#           "Component": true
#       },
#       "TimeRange":{
#           "nominFrac":0.25,
#           "nomaxFrac":0.5,
#           "nominTime":20,
#           "nomaxTime":145
#       },
#       "Rendering":{
#           "Display": true,
#           "File":"Lucia.png",
#           "EventsBounds": false,
#           "noPalette":"tab10"
#       },
#       "Fields":["Heat","Rain","Love"]
#   }
#
#
##########################################################################
#
#  yaml config file example
#
###
#    ---
#    Components:
#    - Name: Atmo
#      File: timeline_pam_.nc
#    - Name: Ocean
#      File: timeline_pim_.nc
#    - Name: Xios
#      File: timeline_poum.nc
#    Plots:
#      Kind: True
#      Field: True
#      Component: True
#    #TimeRange:
#    #  minFrac: 0.25
#    #  maxFrac: 0.5
#    #  minTime: 10
#    #  maxTime: 40
#    Rendering:
#      Display: True
#      File: Lucia.png
#      EventsBounds: False
#    Fields:
#    - Heat
#    - Rain
#    - Love
#
##########################################################################
 
import netCDF4
try:
    import json
    has_json = True
except:
    has_json = False
try:
    import yaml
    has_yaml = True
except:
    has_yaml = False
import sys, os
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.collections
from matplotlib.colors import LinearSegmentedColormap
from matplotlib.backend_bases import MouseEvent
import math

if len(sys.argv) == 1:
    print(">>> Missing configuration file name")
    exit(1)

config_ok = False
if has_json:
    try:
        jf = open(sys.argv[1])
        config = json.load(jf)
        config_ok = True
    except:
        pass
if (not config_ok) and has_yaml:
    try:
        jf = open(sys.argv[1])
        try:
            config = yaml.load(jf, Loader=yaml.FullLoader)
            config_ok = True
        except:
            try:
                config = yaml.load(jf)
                config_ok = True
            except:
                pass
    except:
        pass        
if not config_ok:    
    print(">>> Problem loading configuration file {}".format(sys.argv[1]))
    exit(1)
jf.close()

initime = time.time()

nbplots=sum([config["Plots"][i] for i in config["Plots"]])
if nbplots == 0:
    print("No plots selected")
    exit()


files = []
cnam_in = []
for cp in config["Components"]:
    files.append(cp["File"])
    cnam_in.append(cp["Name"])

if "Fields" in config:
    fieldlb = ["Oasis"]+config["Fields"]
    
dofile = "File" in config["Rendering"]
if dofile:
    outfile = config["Rendering"]["File"]
    if outfile:
        dofile = outfile.lower() != 'none' and outfile.lower() != 'no'
    else:
        dofile = False

af_in = [netCDF4.Dataset(fi,'r') for fi in files]
comp_id = [int(tf.getncattr('component_id'))-1 for tf in af_in]
cnam = [cnam_in[id] for id in comp_id]
af = [af_in[id] for id in comp_id]

udpal = "Palette" in config["Rendering"]
if udpal:
    udpalette = config["Rendering"]["Palette"]

totprocs = -1
cprocs = []
fprocs = []
for i,tf in enumerate(af):
    timeini = time.time()
    nevents = len(tf.dimensions['nx'])
    nprocs  = len(tf.dimensions['ny'])
    tstrt   = tf.variables['timer_strt'][:,:].flatten()
    tstop   = tf.variables['timer_stop'][:,:].flatten()
    if config["Plots"]["Kind"]:
        kind    = tf.variables['kind'][:]
        kindlb  = tf.variables['kind'].getncattr('flag_meanings').split()
    if config["Plots"]["Field"]:
        field   = tf.variables['field'][:]
    if config["Plots"]["Component"]:
        compo   = tf.variables['component'][:]
    tf.close()

    if config["Plots"]["Kind"]:
        lpkind  = np.tile(kind,nprocs)
    if config["Plots"]["Field"]:
        lpfield = np.tile(field,nprocs)
    if config["Plots"]["Component"]:
        lpcompo = np.tile(compo,nprocs)

    procs = np.arange(nprocs)+totprocs+1
    procs = np.repeat(procs,nevents)
    totprocs += nprocs
    cprocs.append(totprocs+1)
    fprocs.append(totprocs+1.5)

    polyx = np.array([tstrt,tstop,tstop,tstrt]).T
    polyy = np.array([procs+0.5,procs+0.5,procs+1.5,procs+1.5]).T
    lpolyxy = np.dstack((polyx[...,np.newaxis],polyy[...,np.newaxis]))

    if i == 0:
        if config["Plots"]["Kind"]:
            pkind = np.copy(lpkind)
        if config["Plots"]["Field"]:
            pfield = np.copy(lpfield)
        if config["Plots"]["Component"]:
            pcompo = np.copy(lpcompo)
        polyxy = np.copy(lpolyxy)
    else:
        if config["Plots"]["Kind"]:
            pkind = np.hstack((pkind,lpkind))
        if config["Plots"]["Field"]:
            pfield = np.hstack((pfield,lpfield))
        if config["Plots"]["Component"]:
            pcompo = np.hstack((pcompo,lpcompo))
        polyxy = np.concatenate((polyxy,lpolyxy))
    print('Loaded {} in {} sec.'.format(cnam[i],time.time()-timeini))

# Time range selection

timeini = time.time()

if config["Plots"]["Kind"]:
    minpkind = np.min(pkind)
    maxpkind = np.max(pkind)
if config["Plots"]["Field"]:
    minpfield = np.min(pfield)
    maxpfield = np.max(pfield)
if config["Plots"]["Component"]:
    minpcompo = np.min(pcompo)
    maxpcompo = np.max(pcompo)

trange = np.max(polyxy[:,1,0])-np.min(polyxy[:,0,0])
print("The full trace spans {} sec. and contains {} events".format(trange,polyxy.shape[0]))

uselimits = "TimeRange" in config
if uselimits:
    if "minFrac" in config["TimeRange"]:
        tmin = np.min(polyxy[:,0,0]) + config["TimeRange"]["minFrac"] * trange
    else:
        if "minTime" in config["TimeRange"]:
            tmin = config["TimeRange"]["minTime"]
        else:
            tmin = np.min(polyxy[:,0,0])
    if "maxFrac" in config["TimeRange"]:
        tmax = np.min(polyxy[:,0,0]) + config["TimeRange"]["maxFrac"] * trange
    else:
        if "maxTime" in config["TimeRange"]:
            tmax = config["TimeRange"]["maxTime"]
        else:
            tmax = np.max(polyxy[:,1,0])
else:
    tmin = np.min(polyxy[:,0,0])
    tmax = np.max(polyxy[:,1,0])
tmin = float(math.floor(tmin))
tmax = float(math.ceil(tmax))
if uselimits:
    ti_msk = np.less_equal(polyxy[:,1,0],tmin)
    ti_msk = np.logical_or(ti_msk,np.greater_equal(polyxy[:,0,0],tmax))
    
    if config["Plots"]["Kind"]:
        pkind = np.delete(pkind,ti_msk)
    if config["Plots"]["Field"]:
        pfield = np.delete(pfield,ti_msk)
    if config["Plots"]["Component"]:
        pcompo = np.delete(pcompo,ti_msk)
    polyxy = np.delete(polyxy,ti_msk,axis=0)
    print("The selection spans {} sec. between {} and {} and contains {} events".format(tmax-tmin,tmin,tmax,polyxy.shape[0]))
    print('Time range selection took {} sec'.format(str(time.time()-timeini)))


# Plotting

timeini = time.time()

if nbplots == 1:
    figsz=(11.75,8.25)
else:
    figsz=(8.25,11.75)

fig=plt.figure(figsize=figsz, frameon=True)

# Define default color blind friendly palette
okabe_ito = ['#E69F00', '#56B4E9', '#009E73', '#F0E442', '#0072B2', '#D55E00', '#CC79A7', '#000000']
cmap_name = "mycolor"

compolb = ['Oasis']+cnam
compopc = [0]+cprocs
plotnb = 0

if config["Plots"]["Kind"]:
    cm = LinearSegmentedColormap.from_list(cmap_name, okabe_ito, N=10)
    if udpal:
        palette = udpalette # 'tab10' # or 'Paired'
    else :
        palette = cm 
    plotnb += 1
    kind_ax = plt.subplot(nbplots*100+10+plotnb)
    kind_ax.set_ylim([0.5,totprocs+1.5])
    kind_ax.set_xlim([tmin,tmax])
    kind_pc = matplotlib.collections.PolyCollection(polyxy,pickradius=0.0)
    kind_pc.set_array(pkind)
    kind_pc.set_clim([minpkind-.5,maxpkind+.5])
    cmap = plt.get_cmap(palette, maxpkind-minpkind+1)
    cbar = plt.colorbar(kind_pc, ticks=np.arange(minpkind,maxpkind+1))
    kind_pc.set_cmap(cmap)
    
    plt.hlines(fprocs[:-1],tmin,tmax,colors='black',linestyles='dashed', linewidth=0.8)
    kind_ax.add_collection(kind_pc)
    kind_ax.set_title('KIND')
    cbar.ax.set_yticklabels(kindlb[minpkind:maxpkind+1])
    for i,label in enumerate(compolb[1:],start=1):
        kind_ax.text(tmax*1.005,
                     compopc[i-1]+(compopc[i]-compopc[i-1])/2,
                     compolb[i],{'ha': 'left', 'va': 'center'},
                     rotation = 60)

if config["Plots"]["Field"]:
    cm = LinearSegmentedColormap.from_list(cmap_name, okabe_ito, N=len(fieldlb))
    if udpal:
        palette = udpalette # 'tab10' # or 'Paired'
    else :
        palette = cm 
    plotnb += 1
    field_ax = plt.subplot(nbplots*100+10+plotnb)
    field_ax.set_ylim([0.5,totprocs+1.5])
    field_ax.set_xlim([tmin,tmax])
    field_pc = matplotlib.collections.PolyCollection(polyxy,pickradius=0.0)
    field_pc.set_array(pfield)
    field_pc.set_clim([minpfield-.5,maxpfield+.5])
    cmap = plt.get_cmap(palette, len(fieldlb))
    cbar = plt.colorbar(field_pc, ticks=np.arange(len(fieldlb)))
    field_pc.set_cmap(cmap)
    
    plt.hlines(fprocs[:-1],tmin,tmax,colors='black',linestyles='dashed', linewidth=0.8)
    field_ax.add_collection(field_pc)
    field_ax.set_title('FIELD')
    if "Fields" in config:
        cbar.ax.set_yticklabels(fieldlb)
    for i,label in enumerate(compolb[1:],start=1):
        field_ax.text(tmax*1.005,
                      compopc[i-1]+(compopc[i]-compopc[i-1])/2,
                      compolb[i],{'ha': 'left', 'va': 'center'},
                      rotation = 60)

if config["Plots"]["Component"]:
    cm = LinearSegmentedColormap.from_list(cmap_name, okabe_ito, N=len(compolb))
    if udpal:
        palette = udpalette # 'tab10' # or 'Paired'
    else :
        palette = cm 
    plotnb += 1
    compo_ax = plt.subplot(nbplots*100+10+plotnb)
    compo_ax.set_ylim([0.5,totprocs+1.5])
    compo_ax.set_xlim([tmin,tmax])
    compo_pc = matplotlib.collections.PolyCollection(polyxy,pickradius=0.0)
    compo_pc.set_array(pcompo)
    compo_pc.set_clim([-.5,len(compolb)-.5])
    cmap = plt.get_cmap(palette, len(compolb))
    cbar = plt.colorbar(compo_pc, ticks=np.arange(len(compolb)))
    compo_pc.set_cmap(cmap)
    
    plt.hlines(fprocs[:-1],tmin,tmax,colors='black',linestyles='dashed', linewidth=0.8)
    compo_ax.add_collection(compo_pc)
    compo_ax.set_title('COMPONENT')
    cbar.ax.set_yticklabels(compolb)
    for i,label in enumerate(compolb[1:],start=1):
        compo_ax.text(tmax*1.005,
                      compopc[i-1]+(compopc[i]-compopc[i-1])/2,
                      compolb[i],{'ha': 'left', 'va': 'center'},
                      rotation = 60)

plt.subplots_adjust(left=0.07,right=1.05,bottom=0.03,top=0.95,wspace=0.0,hspace=0.2)

print('Plot preparation took {} sec'.format(str(time.time()-timeini)))

if dofile:
    timeini = time.time()
    plt.savefig(outfile,bbox_inches='tight')
    print('File output took {} sec'.format(str(time.time()-timeini)))
print('Overall time {} sec'.format(str(time.time()-initime)))

if config["Rendering"]["Display"]:
    if "EventsBounds" not in config["Rendering"]:
        config["Rendering"]["EventsBounds"] = False
    if config["Rendering"]["EventsBounds"]:
        if config["Plots"]["Kind"]:
            kind_pc.set_edgecolor('black')
            kind_pc.set_linewidth(0.3)
        if config["Plots"]["Field"]:
            field_pc.set_edgecolor('black')
            field_pc.set_linewidth(0.3)
        if config["Plots"]["Component"]:
            compo_pc.set_edgecolor('black')
            compo_pc.set_linewidth(0.3)
        
    class pseudo_mouse:
        def __init__(self,x,y):
            self.x = x
            self.y = y

    if config["Plots"]["Kind"]:
        def format_coord_kind(x, y):
            comp = compolb[min(np.searchsorted(fprocs,y)+1,len(compolb)-1)]
            ip = min(max(1,int(round(y))),compopc[-1])
            proc = ip-1 - compopc[np.searchsorted(fprocs,y)]
            px, py = kind_pc.get_transform().transform((x,y))
            cont, ind = kind_pc.contains(pseudo_mouse(px,py))
            if cont:
                return 'Time: {:.3f}, Resource: {:.0f}, Component: {}, Rank: {:.0f}, Kind: {}'.format(x, ip, comp, proc, kindlb[pkind[ind['ind'][0]]])
            else:
                return 'Time: {:.3f}, Resource: {:.0f}, Component: {}, Rank: {:.0f}'.format(x, ip, comp, proc)

        kind_ax.format_coord = format_coord_kind
    if config["Plots"]["Field"]:
        def format_coord_field(x, y):
            comp = compolb[min(np.searchsorted(fprocs,y)+1,len(compolb)-1)]
            ip = min(max(1,int(round(y))),compopc[-1])
            proc = ip-1 - compopc[np.searchsorted(fprocs,y)]
            px, py = field_pc.get_transform().transform((x,y))
            cont, ind = field_pc.contains(pseudo_mouse(px,py))
            if cont:
                return 'Time: {:.3f}, Resource: {:.0f}, Component: {}, Rank: {:.0f}, Field: {}'.format(x, ip, comp, proc, fieldlb[pfield[ind['ind'][0]]])
            else:
                return 'Time: {:.3f}, Resource: {:.0f}, Component: {}, Rank: {:.0f}'.format(x, ip, comp, proc)

        field_ax.format_coord = format_coord_field
    if config["Plots"]["Component"]:
        def format_coord_compo(x, y):
            comp = compolb[min(np.searchsorted(fprocs,y)+1,len(compolb)-1)]
            ip = min(max(1,int(round(y))),compopc[-1])
            proc = ip-1 - compopc[np.searchsorted(fprocs,y)]
            px, py = compo_pc.get_transform().transform((x,y))
            cont, ind = compo_pc.contains(pseudo_mouse(px,py))
            if cont:
                return 'Time: {:.3f}, Resource: {:.0f}, Component: {}, Rank: {:.0f}, Comp: {}'.format(x, ip, comp, proc, compolb[pcompo[ind['ind'][0]]])
            else:
                return 'Time: {:.3f}, Resource: {:.0f}, Component: {}, Rank: {:.0f}'.format(x, ip, comp, proc)

        compo_ax.format_coord = format_coord_compo
    plt.show()
