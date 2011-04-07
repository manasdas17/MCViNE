#!/usr/bin/env python


def execute(cmd):
    import os
    print '* executing %s... ' % cmd
    if os.system(cmd):
        raise RuntimeError, "%r failed" % cmd


def run(Ei, ncount, nodes,
        moderator_erange = None,
        fermichopper=None, fermi_nu=None, 
        T0_nu = None,
        emission_time = None,
        dry_run=False):
    fermichopper = fermichopper or "100-1.5-SMI"
    emission_time = emission_time or -1
    fermi_nu = fermi_nu or 600
    T0_nu = T0_nu or 120
    # generate configration
    cmd = """
    arcs-m2s \
        --fermi_nu=%(fermi_nu)s \
        --T0_nu=%(T0_nu)s \
        --E=%(Ei)s \
        --emission_time=%(emission_time)s \
        --fermi_chopper=%(fermichopper)s \
        --- \
        -dump-pml
    """ % locals()
    execute(cmd)


    # fine tune configuraiton
    cmd = ["arcs_moderator2sample --overwrite-datafiles"]
    Emin, Emax = moderator_erange
    cmd.append('--moderator.Emin=%s' % Emin)
    cmd.append('--moderator.Emax=%s' % Emax)
    cmd.append("--dump-pml")
    cmd = ' '.join(cmd)
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
    if dry_run:
        print cmd
    else:
        execute(cmd)


    # analyze output
    # ... number of neutrons left
    neutronfile = os.path.join('out', 'neutrons')
    from mcni.neutron_storage.idf_usenumpy import count
    if dry_run:
        ncountatsample = 1000
    else:
        ncountatsample = count(neutronfile)

    if ncountatsample == 0:
        raise RuntimeError, "no neutrons at sample. need to increase mc samples at mod2sample simulation"
    
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
    if dry_run:
        print cmd
    else:
        execute(cmd)
    return


from pyre.applications.Script import Script as AppBase
class App(AppBase):

    class Inventory(AppBase.Inventory):

        import pyre.inventory
        Ei = pyre.inventory.float('Ei')
        ncount = pyre.inventory.float('ncount', default=1e7)
        nodes = pyre.inventory.int('nodes', default=5)
        moderator_erange = pyre.inventory.str('moderator_erange')
        fermichopper = pyre.inventory.str('fermichopper')
        fermi_nu= pyre.inventory.float('fermi_nu', default=600)
        T0_nu = pyre.inventory.float('T0_nu', default=120)
        emission_time = pyre.inventory.float('emission_time', default=-1)
        dry_run = pyre.inventory.bool('dry_run', default=False)

    def main(self):
        Ei = self.inventory.Ei
        ncount = self.inventory.ncount
        nodes = self.inventory.nodes
        moderator_erange = self.inventory.moderator_erange or None
        if moderator_erange:
            moderator_erange = eval(moderator_erange)
        fermichopper = self.inventory.fermichopper
        fermi_nu = self.inventory.fermi_nu
        T0_nu = self.inventory.T0_nu
        emission_time = self.inventory.emission_time
        dry_run = self.inventory.dry_run
        run(Ei, ncount, nodes,
            moderator_erange = moderator_erange,
            fermichopper=fermichopper, 
            fermi_nu = fermi_nu,
            T0_nu = T0_nu,
            emission_time = emission_time,
            dry_run = dry_run)
        return


def main():
    App('mod2sample').run()
    return

if __name__ == '__main__': main()

