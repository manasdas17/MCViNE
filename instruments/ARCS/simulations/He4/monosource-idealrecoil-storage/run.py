#!/usr/bin/env python


def execute(cmd):
    import os
    print '* executing %s... ' % cmd
    if os.system(cmd):
        raise RuntimeError, "%r failed" % cmd



def run():
    # create scattering kernel file
    createScatteringKernel(
        E_Q="Q*Q*0.5", S_Q="1", 
        Qmin=0, Qmax=28,
        )

    #
    import os, shutil
    if os.path.exists('out'):
        shutil.rmtree('out')
    runsim(0,0)
    return

    
def runsim(
    x,y
    ):
    """source neutrons come from (x,y) going to direction z
    """
    # run main sim
    cmd = './sssd --source.position="%s,%s,0"' % (x,y,)
    execute(cmd)
    return


mod2sample_distance = 13.6


def createScatteringKernel(E_Q,S_Q, Qmin, Qmax):
    import os
    tf = os.path.join('sampleassembly', 'He4-scatterer.xml.template')
    t = open(tf).read()
    t = t.replace('$E_Q$', E_Q)
    t = t.replace('$S_Q$', S_Q)
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



def main():
    run()
    return


interactive = False

if __name__ == '__main__': 
    interactive = True
    main()
