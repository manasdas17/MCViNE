#!/usr/bin/env python


def execute(cmd):
    import os
    print '* executing %s... ' % cmd
    if os.system(cmd):
        raise RuntimeError, "%r failed" % cmd

    
def _computeAverageEnergy():
    from histogram.hdf import load
    import os
    out = '../mod2sample/out-analyzer'
    h = load(os.path.join(out, 'ienergy.h5'), 'ienergy')
    e = (h.energy * h.I).sum()/h.I.sum()
    return e


def run(
    ncount=1e7, nodes=5, 
    Ei=700.,
    Q=10, E=100, dQ=1, dE=10, 
    mod2sample='../mod2sample',
    ):
    Ei_user = Ei
    Ei = _computeAverageEnergy()
    if abs(Ei-Ei_user)/Ei > 0.1:
        raise ValueError, "nominal energy %s is too different from average energy at sample position %s" % (Ei_user, Ei)
    import os
    incident_neutrons = 'incident-neutrons'
    if not os.path.exists(incident_neutrons):
        os.link('../mod2sample/out/neutrons', 'incident-neutrons')

    # create scattering kernel file
    createScatteringKernel(Q,E)

    # run main sim
    cmd = './sssd --ncount=%s --mpirun.nodes=%s' % (ncount, nodes)
    execute(cmd)

    # reduce events to S(Q,E)
    eventsdat = 'out/events.dat'
    Qaxis = Q-dQ, Q+dQ, dQ/50.
    Eaxis = E-dE, E+dE, dE/50.
    Ei, toffset = getEiToffset(mod2sample)
    iqe = reduceToIQE(eventsdat, Ei, toffset, Qaxis, Eaxis)
    from histogram.hdf import dump
    dump(iqe, 'iqe.h5', '/', 'c')
    global interactive
    if interactive:
        from histogram.plotter import defaultPlotter
        defaultPlotter.plot(iqe)

    # quick analysis of S(Q,E) (without detector and sample size effects)
    cmd = ['./analyze-sqe ']
    cmd.append('--mpirun.nodes=%s' % nodes)
    cmd.append('--ncount=%s --monitor.Ei=%s' % (ncount, Ei))
    cmd.append(' --monitor.Qmin=%s --monitor.Qmax=%s' % (Q-dQ, Q+dQ))
    cmd.append(' --monitor.Emin=%s --monitor.Emax=%s' % (E-dE, E+dE))
    cmd = ' '.join(cmd)
    execute(cmd)
    return


mod2sample_distance = 13.6
def getEiToffset(mod2sample):
    from histogram.hdf import load
    import os

    # I(energy)
    ie = load(os.path.join(mod2sample, 'out-analyzer/ienergy.h5'),
              'ienergy')
    # average energy
    e = (ie.I * ie.energy).sum()/ie.I.sum()
    
    # I(tof)
    itof = load(os.path.join(mod2sample, 'out-analyzer/itof.h5'),
                'itof')
    # average tof
    tof = (itof.I*itof.tof).sum()/itof.I.sum()
    
    from mcni.utils.conversion import e2v
    v = e2v(e)
    
    L = mod2sample_distance
    toffset = tof - (L/v)
    # energy: meV, toffset: microsecond
    return e, toffset * 1e6


def createScatteringKernel(Q,E):
    import os
    tf = os.path.join('sampleassembly', 'Al-scatterer.xml.template')
    t = open(tf).read()
    t = t.replace('$Q$', '%s/angstrom' % Q)
    t = t.replace('$E$', '%s*meV' % E)
    
    f = os.path.join('sampleassembly', 'Al-scatterer.xml')
    open(f, 'w').write(t)
    return 


# constants
import pyre.units.length
import pyre.units.energy
import pyre.units.time
npixels = 117760 # number of pixels for ARCS
mod2sample=13.6*pyre.units.length.meter
mod_period=0.015*pyre.units.time.s # moderator period
def reduceToIQE(eventsfile, Ei, toffset, Qaxis, Eaxis):
    from mccomponents.detector.reduction_utils import events2IQE
    from mccomponents.detector.event_utils import datatype
    import os
    nevents = os.path.getsize(eventsfile)*1. / datatype.itemsize
    assert int(nevents) - nevents == 0
    
    outfile = 'intensities.dat'
    pixelpositionsfile = 'pixelID2position.bin'
    solidanglesfile = 'solidangles.bin'
    iqe = events2IQE(
        eventsfile, nevents, 
        outfile,
        pixelpositionsfile, solidanglesfile, npixels,
        mod2sample=mod2sample,
        Ei=Ei*pyre.units.energy.meV,
        Qaxis=Qaxis, Eaxis=Eaxis,
        tofUnit=1*pyre.units.time.microsecond,
        toffset=toffset*pyre.units.time.microsecond,
        tofmax=mod_period,
        )
    return iqe



from pyre.applications.Script import Script as AppBase
class App(AppBase):

    class Inventory(AppBase.Inventory):

        import pyre.inventory
        ncount = pyre.inventory.float('ncount', default=1e7)
        nodes = pyre.inventory.int('nodes')
        Ei = pyre.inventory.float('Ei', default=700)
        Q = pyre.inventory.float('Q', default=10)
        E = pyre.inventory.float('E', default=100)
        dQ = pyre.inventory.float('dQ', default=1)
        dE = pyre.inventory.float('dE', default=10)
        mod2sample = pyre.inventory.str('mod2sample', default='../mod2sample')

        
    def main(self):
        ncount = self.inventory.ncount
        nodes = self.inventory.nodes
        Ei = self.inventory.Ei
        Q = self.inventory.Q
        E = self.inventory.E
        dQ = self.inventory.dQ
        dE = self.inventory.dE
        mod2sample = self.inventory.mod2sample
        run(
            ncount=ncount, nodes=nodes, 
            Ei=Ei, Q=Q, E=E, dQ=dQ, dE=dE,
            mod2sample = mod2sample,
            )
        return
    

def main():
    app = App('sample-scattering')
    app.run()
    return


interactive = False

if __name__ == '__main__': 
    interactive = True
    main()
