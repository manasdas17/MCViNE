#!/usr/bin/env python


def execute(cmd):
    import os
    print '* executing %s... ' % cmd
    if os.system(cmd):
        raise RuntimeError, "%r failed" % cmd

    
def run(
    ncount=1e7, nodes=5, 
    Ei=700.,
    E_Q="Q*Q/3", S_Q="1", sigma_Q='Q/2.',
    Qmin=0, Qmax=10., Qstep=0.1,
    Emin=0, Emax=50., Estep=1.,
    ):
        
    # create scattering kernel file
    createScatteringKernel(
        E_Q=E_Q, S_Q=S_Q, sigma_Q=sigma_Q,
        Qmin=Qmin, Qmax=Qmax,
        )

    # run main sim
    cmd = './sssd --source.energy=%s --ncount=%s --mpirun.nodes=%s' % (
        Ei, ncount, nodes)
    execute(cmd)

    # reduce events to S(Q,E)
    eventsdat = 'out/events.dat'
    Qaxis = Qmin, Qmax, Qstep
    Eaxis = Emin, Emax, Estep
    toffset = 0
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
    cmd.append(' --monitor.Qmin=%s --monitor.Qmax=%s' % (Qmin, Qmax))
    cmd.append(' --monitor.Emin=%s --monitor.Emax=%s' % (Emin, Emax))
    cmd = ' '.join(cmd)
    # execute(cmd)
    return



mod2sample_distance = 13.6


def createScatteringKernel(E_Q,S_Q,sigma_Q, Qmin, Qmax):
    import os
    tf = os.path.join('sampleassembly', 'He4-scatterer.xml.template')
    t = open(tf).read()
    t = t.replace('$E_Q$', E_Q)
    t = t.replace('$S_Q$', S_Q)
    t = t.replace('$sigma_Q$', sigma_Q)
    t = t.replace('$Qmin$', str(Qmin))
    t = t.replace('$Qmax$', str(Qmax))
    
    f = os.path.join('sampleassembly', 'He4-scatterer.xml')
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
        tofUnit=0.1*pyre.units.time.microsecond, # must be consistent with sssd.pml.detector.tofparams
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
        E_Q = pyre.inventory.str('E_Q', default='Q*Q/3.')
        S_Q = pyre.inventory.str('S_Q', default='1.')
        sigma_Q = pyre.inventory.str('sigma_Q', default='Q/2.')
        Qmin = pyre.inventory.float('Qmin', default=0)
        Qmax = pyre.inventory.float('Qmax', default=10)
        Qstep = pyre.inventory.float('Qstep', default=0.1)
        Emin = pyre.inventory.float('Emin', default=0)
        Emax = pyre.inventory.float('Emax', default=50)
        Estep = pyre.inventory.float('Estep', default=0.5)

        
    def main(self):
        ncount = self.inventory.ncount
        nodes = self.inventory.nodes
        Ei = self.inventory.Ei
        E_Q = self.inventory.E_Q
        S_Q = self.inventory.S_Q
        sigma_Q = self.inventory.sigma_Q
        Qmin = self.inventory.Qmin
        Qmax = self.inventory.Qmax
        Qstep = self.inventory.Qstep
        Emin = self.inventory.Emin
        Emax = self.inventory.Emax
        Estep = self.inventory.Estep
        run(
            ncount=ncount, nodes=nodes, 
            Ei=Ei,
            E_Q = E_Q, S_Q = S_Q, sigma_Q = sigma_Q,
            Qmin=Qmin, Qmax=Qmax, Qstep=Qstep,
            Emin=Emin, Emax=Emax, Estep=Estep,
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
