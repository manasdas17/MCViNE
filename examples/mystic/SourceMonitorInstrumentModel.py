#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                                   Jiao Lin
#                      California Institute of Technology
#                        (C) 2007 All Rights Reserved  
#
# {LicenseText}
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#



def simulate(
    source_E0=60, source_dE=5, 
    monitor_Emin=50, monitor_Emax=70, monitor_N=20):
    
    out = {}
    
    from mcni.pyre_support.Instrument import Instrument as base
    class Instrument(base):

        class Inventory( base.Inventory ):

            from mcstas2.pyre_support import facility
            source = facility( 'sources', 'Source_simple', 'source' )
            monitor = facility( 'monitors', 'E_monitor', 'monitor' ) 
            pass # end of Inventory


        def __init__(self, name = 'source-monitor'):
            base.__init__(self, name)
            return


        def _defaults(self):
            base._defaults(self)
            self.inventory.sequence = ['source', 'monitor']
            geometer = self.inventory.geometer
            geometer.inventory.monitor = (0,0,1), (0,0,0)

            source = self.inventory.source
            # dimension of source
            source.inventory.radius= 0.1
            # distance from source to target
            source.inventory.dist = 1. # should match monitor position
            # target dimension
            source.inventory.xw = 0.1 
            source.inventory.yh = 0.1
            # energy distibution
            # gaussian distibution
            source.inventory.gauss = 1
            source.inventory.E0 = source_E0
            source.inventory.dE = source_dE
            
            monitor = self.inventory.monitor
            # dimension
            monitor.inventory.xwidth = -0.1
            monitor.inventory.yheight = 0.1
            # 
            monitor.inventory.Emin = monitor_Emin
            monitor.inventory.Emax = monitor_Emax
            monitor.inventory.nchan = monitor_N
            
            return


        def fini(self):
            super(Instrument, self).fini()
            monitor = self.inventory.monitor
            out['hist'] = monitor.getFinalHistogram()
            return

        pass # end of Instrument
    
    instr = Instrument()
    instr.run()

    histogram = out['hist']
    return histogram.I


def test():
    print simulate()
    return


def main():
    test()
    return    
    
if __name__ == "__main__":
    main()
    
# version
__id__ = "$Id$"

# End of file 
