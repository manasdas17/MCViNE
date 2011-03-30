#!/usr/bin/env python


def execute(cmd):
    import os
    print '* executing %s... ' % cmd
    if os.system(cmd):
        raise RuntimeError, "%r failed" % cmd


def run(scattering_rundir, nodes, ncount=None):
    sendneutronstodetsys(scattering_rundir, nodes, ncount=ncount)
    eventsdat = 'out/events.dat'
    iqe = reduceToIQE(eventsdat)
    from histogram.hdf import dump
    dump(iqe, 'iqe.h5', '/', 'c')
    from histogram.plotter import defaultPlotter
    defaultPlotter.plot(iqe)
    return


def reduceToIQE(eventsfile):
    from mccomponents.detector.reduction_utils import events2IQE
    import os
    nevents = os.path.getsize(eventsfile) / 16.
    assert int(nevents) - nevents == 0
    
    outfile = 'intensities.dat'
    pixelpositionsfile = 'pixelID2position.bin'
    npixels = 117760
    import pyre.units.length
    import pyre.units.energy
    import pyre.units.time
    iqe = events2IQE(
        eventsfile, nevents, 
        outfile,
        pixelpositionsfile, npixels,
        mod2sample=13.6*pyre.units.length.meter,
        Ei=700*pyre.units.energy.meV,
        Qaxis=(9.5,10.5,0.02), Eaxis=(30,120,1.),
        tofUnit=1*pyre.units.time.microsecond,
        toffset=0*pyre.units.time.s,
        tofmax=0.015*pyre.units.time.s,
        )
    return iqe


def sendneutronstodetsys(scattering_rundir, nodes, ncount=None):
    import os
    if os.path.exists('out'):
        raise IOError, "output directory 'out' already exists. Rename or remove it"
    # number of neutrons scattered
    neutronfile = os.path.join(scattering_rundir, 'out', 'scattered-neutrons')
    if not ncount:
        from mcni.neutron_storage.idf_usenumpy import count
        ncount = count(neutronfile)

    # build command
    cmd = ['./sd']
    args = {
        'ncount': ncount,
        'mpirun.nodes': nodes,
        'source.path': neutronfile,
        }
    cmd += ['--%s=%s' % (k,v) for k,v in args.iteritems()]
    cmd = ' '.join(cmd)
    execute(cmd)
    return


def main():
    import sys
    scattering_rundir = sys.argv[1]
    nodes = int(sys.argv[2])
    if len(sys.argv) >= 4:
        ncount = float(sys.argv[3])
    else:
        ncount = None
    run(scattering_rundir, nodes, ncount=ncount)
    return


if __name__ == '__main__': main()

