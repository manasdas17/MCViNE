#!/usr/bin/env python


def execute(cmd):
    import os
    print '* executing %s... ' % cmd
    if os.system(cmd):
        raise RuntimeError, "%r failed" % cmd


def run(Ei, ncount, nodes):
    # generate configration
    cmd = """
    arcs-m2s \
        --fermi_nu=600 \
        --fermi_bladeradius=0.5801 \
        --T0_nu=120 \
        --E=%(Ei)s \
        --emission_time=0 \
        --- \
        -dump-pml
    """ % locals()
    execute(cmd)


    # fine tune configuraiton
    cmd = "arcs_moderator2sample --overwrite-datafiles --dump-pml"
    execute(cmd)


    # run simulation
    import os, shutil
    if os.path.exists('out'):
        shutil.rmtree('out')
    cmd = "arcs_moderator2sample -ncount=%(ncount)s " % locals()
    # ... moderator data file
    moddat = os.path.join(
        os.environ['MCVINE_DIR'], 'share', 'mcvine',
        'instruments', 'ARCS', 'source_sct521_bu_17_1.dat',
        )
    cmd += ' -moderator.S_filename=%s ' % moddat
    cmd += ' -mpirun.nodes=%s' % nodes
    cmd += '> m2s.log 2> m2s.err'
    execute(cmd)


    # analyze output
    # ... number of neutrons left
    neutronfile = os.path.join('out', 'neutrons')
    from mcni.neutron_storage.idf_usenumpy import count
    ncountatsample = count(neutronfile)
    
    cmd = [
        'arcs_analyze_beam',
        '-source.path=%(neutronfile)s' % locals(),
        '-ncount=%(ncountatsample)s' % locals(),
        '--output-dir=out-analyzer',
        ]
    # ... compute enegy range
    from mcni.utils.conversion import e2v
    v = e2v(Ei)
    from pyre.units.time import second
    L = 13.6
    t = L/v
    # ... build command line with monitor parameters
    cmd += ['--monitor.mtof.tofmin=%s' % (t*0.9)]
    cmd += ['--monitor.mtof.tofmax=%s' % (t*1.1)]
    cmd += ['--monitor.mtof.ntof=%s' % (1000)]
    cmd += ['--monitor.menergy.energymin=%s' % (Ei*0.9)]
    cmd += ['--monitor.menergy.energymax=%s' % (Ei*1.1)]
    cmd += ['--monitor.menergy.nenergy=%s' % (1000)]
    # ... run
    cmd = ' '.join(cmd)
    execute(cmd)
    return


def main():
    import sys
    Ei = float(sys.argv[1])
    ncount = float(sys.argv[2])
    nodes = int(sys.argv[3])
    run(Ei, ncount, nodes)
    return


if __name__ == '__main__': main()

