#!/usr/bin/env python

import histogram.hdf as hh
import histogram
import pylab


def loadsimdata(filename):
    # load data and apply efficiency
    itof = hh.load(filename, 'I(tof)')
    eff = hh.load('mon1-eff.h5')
    i = itof.I * eff.I
    itof.I[:] = i

    # clean up
    itof[(0.019,None)].I = 0
    
    #
    x = itof.tof
    y = itof.I

    # convert to counts/10 mus
    #  counts * 10, bins / 10
    from smooth import smooth
    y = smooth(y, window_len=10, window='flat')
    # y = y[:len(x)]
    # y *= 10.
    indexes = range(5, len(x), 10)
    x = x[indexes]
    y = y[indexes] * 10

    # convert to arcs run #5
    # according to ARCS_runinfo.xml of run #5
    # beam power 110kW
    # total run time is 22590/30 seconds
    # the mc simulated was 2MW, 60Hz
    y *= 22590/30*110e3/(2e6/60)

    # extra scaling factor, why?
    y *= 0.83
    return x,y


def loadexpdata(filename, n, binsize=10):
    # load data and apply efficiency
    itof = hh.load(filename)
    x = itof.tof
    y = itof.I

    # convert to counts/10 mus
    #  counts * 10, bins / 10
    from smooth import smooth
    y = smooth(y, window_len=binsize, window='flat')
    indexes = range(binsize/2, binsize/2+binsize*n, binsize)
    x = x[indexes]
    y = y[indexes] * binsize

    return x,y


def plot(sim1, sim2, exp):
    x1,y1 = loadsimdata(sim1)
    x2,y2 = loadsimdata(sim2)
    x3, y3 = loadexpdata(exp, len(x2))

    # plot
    from matplotlib import pyplot
    fig = pyplot.figure()
    ax = fig.add_subplot(1,1,1)
    
    line1 = ax.plot(x3, y1)
    line2 = ax.plot(x3, y2)
    line3 = ax.plot(x3, y3)

    loc = 2 # upper left
    lines = [line1, line2, line3]
    labels = [
        'sim. new moderator',
        'sim. old moderator',
        'experiment',
        ]
    pylab.legend(lines, labels, loc=loc)
    
    ax.set_xscale('log')
    ax.set_xlim(1e-4 * 1e6, 0.019 * 1e6)
    ax.set_xlabel("Time-of-flight(microseconds)")
    ax.set_ylabel("Counts/10microseconds")
    pylab.show()

    return


def main():
    import sys
    sim1 = sys.argv[1]
    sim2 = sys.argv[2]
    exp = sys.argv[3]
    plot(sim1, sim2, exp)
    return


if __name__ == '__main__': main()
