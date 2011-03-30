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


def run(ncount=1e7, nodes=5, Ei=700., Q=10, E=100, dQ=1, dE=10):
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
    cmd = './ssd --ncount=%s --mpirun.nodes=%s' % (ncount, nodes)
    execute(cmd)

    # analyze S(Q,E) quickly
    cmd = ['./analyze-sqe ']
    cmd.append('--mpirun.nodes=%s' % nodes)
    cmd.append('--ncount=%s --monitor.Ei=%s' % (ncount, Ei))
    cmd.append(' --monitor.Qmin=%s --monitor.Qmax=%s' % (Q-dQ, Q+dQ))
    cmd.append(' --monitor.Emin=%s --monitor.Emax=%s' % (E-dE, E+dE))
    cmd = ' '.join(cmd)
    execute(cmd)
    return


def createScatteringKernel(Q,E):
    import os
    tf = os.path.join('sampleassembly', 'Al-scatterer.xml.template')
    t = open(tf).read()
    t = t.replace('$Q$', '%s/angstrom' % Q)
    t = t.replace('$E$', '%s*meV' % E)
    
    f = os.path.join('sampleassembly', 'Al-scatterer.xml')
    open(f, 'w').write(t)
    return 



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

        
    def main(self):
        ncount = self.inventory.ncount
        nodes = self.inventory.nodes
        Ei = self.inventory.Ei
        Q = self.inventory.Q
        E = self.inventory.E
        dQ = self.inventory.dQ
        dE = self.inventory.dE
        run(ncount=ncount, nodes=nodes, Ei=Ei, Q=Q, E=E, dQ=dQ, dE=dE)
        return
    

def main():
    app = App('sample-scattering')
    app.run()
    return


if __name__ == '__main__': main()
