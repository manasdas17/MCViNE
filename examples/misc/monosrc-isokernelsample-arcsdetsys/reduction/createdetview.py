#!/usr/bin/env python

'''
create detector view from I(pix) histogram in ipix.pkl
'''

import arcseventdata, histogram

import pickle
ipix = pickle.load(open('ipix.pkl'))

packaxis = histogram.axis('detectorpackID', range(1,116))
detaxis = histogram.axis('detectorID', range(8))
pixaxis = histogram.axis('pixelID', range(128))

axes = [packaxis, detaxis, pixaxis]

ipdp = histogram.histogram('Ipdp', axes)
ipix.shape = 115, 8, 128
ipdp.I = ipix

v = arcseventdata.detectorview(ipdp)

import histogram.hdf as hh
hh.dump(v, 'view.h5', '/', 'c')
