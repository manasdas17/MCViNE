#!/usr/bin/env python

"""
 $ fitg.py <histogram> <guess>

where guess = height,center,sigma

Example:
 $ fitg.py IE.h5  10,0.01,5
"""


def fit(h, p0):
    from scipy import optimize
    from numpy import exp, array, sqrt
    g = lambda p, x: p[0]*exp(-((x-p[1])/p[2])**2/2)
    x = array(h.axes()[0].binCenters())
    expy = h.I
    # yerr = sqrt(expy)/1e5
    r = lambda p, x, y: g(p,x) -y
    # r = lambda p, x, y, yerr: (g(p,x) -y)/yerr
    p1, success = optimize.leastsq(r, p0, args=(x,expy))
    # p1, success = optimize.leastsq(r, p0, args=(x,expy, yerr))
    fitted_y = g(p1, x)
    return success, p1, (x, expy, fitted_y)


def run(hfile, p0):
    import histogram.hdf as hh
    h = hh.load(hfile)
    success, p1, data =  fit(h, p0)
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
