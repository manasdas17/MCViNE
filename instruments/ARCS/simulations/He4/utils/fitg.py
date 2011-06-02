#!/usr/bin/env python

"""
 $ fitg.py <histogram> <guess>

where guess = height,center,sigma

Example:
 $ fitg.py IE.h5  10,0.01,5
"""


def fit(h, p0):
    from scipy import optimize
    from numpy import exp
    g = lambda p, x: p[0]*exp(-((x-p[1])/p[2])**2/2)
    r = lambda p, x, y: g(p,x) -y
    p1, success = optimize.leastsq(r, p0, args=(h.axes()[0].binCenters(),h.I)) 
    return p1, success


def run(hfile, p0):
    import histogram.hdf as hh
    h = hh.load(hfile)
    p1, success =  fit(h, p0)
    print p1
    print success
    return


def main():
    import sys
    hfile = sys.argv[1]
    p0 = eval(sys.argv[2])
    run(hfile, p0)
    return


if __name__ == "__main__": main()
