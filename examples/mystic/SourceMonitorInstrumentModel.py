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

            self.inventory.overwrite_datafiles = True
            
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


from mystic.models.abstract_model import AbstractModel

class Model(AbstractModel):

    
    def __init__(self, name = 'mcvine:source-monitor'):
        super(Model, self).__init__(name)
        return


    def evaluate(self, coeffs, x):
        # at this moment, x must be an array and must be
        # evenly spaced
        x = self._assertIsEventlySpacedEnergyBins(x)

        source_E0, source_dE = coeffs
        
        monitor_Emin=x[0]
        monitor_Emax=x[-1]
        monitor_N=len(x) 

        return simulate(
            source_E0, source_dE, 
            monitor_Emin, monitor_Emax, monitor_N)


    def _assertIsEventlySpacedEnergyBins(self, x):
        import numpy as np
        x = np.array(x)
        x.shape = -1,
        size = x.shape[0]
        assert size > 2
        Emin = x[0]
        dE = x[1]-x[0]
        assert dE > 0
        
        # evenly spaced
        assert (np.abs( (x[2:] - x[1:-1])-dE )/dE < 1.e-6).all()
        
        return x


def test1():
    print simulate()
    return


def test2():
    model = Model()
    import numpy
    print model.evaluate((75, 5), numpy.arange(50,100, 1.))
    return


def main():
    test1()
    test2()
    return    
    

if __name__ == "__main__": main()

    
# version
__id__ = "$Id$"

# End of file 
