#!/usr/bin/env python

import histogram.hdf as hh
import histogram
import pylab

def main():
    # load data and apply efficiency
    itof = hh.load('out/mon1-tof.h5', 'I(tof)')
    eff = hh.load('eff.h5')
    i = itof.I * eff.I
    itof.I[:] = i

    # clean up
    itof[(0.019,None)].I = 0

    #
    x = itof.tof
    y = itof.I

    # convert to counts/10 mus
    from smooth import smooth
    y = smooth(y, window_len=10)
    y = y[:len(x)]
    y *= 10.

    # convert to arcs run #5
    y *= 800*110e3/(2e6/60)

    # plot
    from matplotlib import pyplot
    fig = pyplot.figure()
    ax = fig.add_subplot(1,1,1)
    line = ax.plot(x, y)
    ax.set_xscale('log')
    ax.set_xlim(1e-4, 0.019)
    pylab.show()
    return

if __name__ == '__main__': main()
