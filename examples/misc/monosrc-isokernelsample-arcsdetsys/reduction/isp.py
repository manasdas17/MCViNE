#!/usr/bin/env python

"""
Get I(super pixel ID) histogram from a detector view.
"""

def createIsp(view):
    subv = view[(0,200), ()]
    Isp = subv.sum('super-detectorID')
    Isp /= (201., 0)
    return Isp
