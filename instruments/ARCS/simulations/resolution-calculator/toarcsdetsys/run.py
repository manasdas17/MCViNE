#!/usr/bin/env python


def execute(cmd):
    import os
    print '* executing %s... ' % cmd
    if os.system(cmd):
        raise RuntimeError, "%r failed" % cmd


def run(scattering_rundir, nodes, ncount=None):
    sendneutronstodetsys(scattering_rundir, nodes, ncount=ncount)
    return


def sendneutronstodetsys(scattering_rundir, nodes, ncount=None):
    import os
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

