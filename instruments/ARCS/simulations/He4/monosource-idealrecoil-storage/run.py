#!/usr/bin/env python


r = 0.01; h = 0.02



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
    from numpy import arange
    for x in arange(-r*0.95, r*0.95, r/3.):
        for y in arange(-h/2*0.95, h/2*0.95, h/3):
            checkHit(x,y)
            continue
        continue

    epsilon = 1e-3
    x = r * (1+epsilon)
    for y in arange(-h/2*0.95, h/2*0.95, h/5):
        checkMiss(x,y)
        continue
    x = r * (-1-epsilon)
    for y in arange(-h/2*0.95, h/2*0.95, h/5):
        checkMiss(x,y)
        continue
    y = h/2 * (1+epsilon)
    for x in arange(-r*0.95, r*0.95, r/5):
        checkMiss(x,y)
        continue
    y = -h/2 * (1+epsilon)
    for x in arange(-r*0.95, r*0.95, r/5):
        checkMiss(x,y)
        continue

    return


def checkMiss(x,y):
    print '*'*3, "checkMiss:", x,y; 
    epsilon = 1e-4
    def eq(x,y): return abs(x-y)<epsilon
    N = 10
    for i in range(N):
        runsim(x,y)
        neutron = readNeutron()
        
        position = tuple(neutron.state.position)
        x1,y1,z = position
        print position
        assert eq(x1,x) and eq(y1,y) and eq(z,-13.6), str(position)
        
        continue
    return


def checkHit(x,y):
    print '*'*3, "checkHit:", x,y; 
    #
    N = 10
    epsilon = 1e-4
    for i in range(N):
        runsim(x,y)
        neutron = readNeutron()
        
        velocity = tuple(neutron.state.velocity)
        vx, vy, vz = velocity
        
        position = tuple(neutron.state.position)
        x1,y1,z1 = position

        assert x1!=0 or y1!=0 or z1!=r

        assert abs(x1*x1+z1*z1) <= r*r*(1+epsilon), "position=%s, x^2=%s, z^2=%s, x^2+z^2=%s, r^2=%s" % (
            position, x1*x1, z*z, x1*x1+z1*z1, r*r)
        assert abs(y1) <= h/2 * (1+epsilon)
        continue
    
    return


def readNeutron():
    neutrons = 'out/scattered-neutrons'
    from mcni.neutron_storage import load
    neutrons = load(neutrons)
    assert len(neutrons) == 1
    return neutrons[0]

    
def runsim(
    x,y
    ):
    """source neutrons come from (x,y) going to direction z
    """
    import os, shutil
    if os.path.exists('out'):
        shutil.rmtree('out')
    # run main sim
    cmd = './sss --source.position="%s,%s,0"' % (x,y,)
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
