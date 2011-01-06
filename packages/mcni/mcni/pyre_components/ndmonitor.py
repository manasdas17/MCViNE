#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                                   Jiao Lin
#                      California Institute of Technology
#                      (C) 2007-2011  All Rights Reserved
#
# {LicenseText}
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#


# quantities that are already in the neutron event record
neqs = [
    'x', 'y', 'z',
    'vx', 'vy', 'vz',
    't',
    ]

# quantity to expression translation
# required that evaluation environment has
#   x, y, z, vx, vy, vz, t  -- those quantities in the neutron event
#   mcni.utils.conversion as conversion
q2e = {
    'energy': 'conversion.VS2E * (vx*vx + vy*vy + vz*vz)',
    'divx': 'vx/vz',
    'divy': 'vy/vz',
    'tof': 't',
    }


from mcni.pyre_support.AbstractComponent import AbstractComponent

def ndmonitor(*quantities):
    '''ndmonitor("x", "vy")
    '''

    class Monitor( AbstractComponent ):

        class Inventory( AbstractComponent.Inventory ):

            import pyre.inventory

            for q in quantities:

                name = q
                code = '%smin = pyre.inventory.float("%smin")' % (name, name)
                exec code
                code = '%smax = pyre.inventory.float("%smax")' % (name, name)
                exec code
                code = 'n%s = pyre.inventory.int("n%s", default=10)' % (name, name)
                exec code
                continue
            
            filename = pyre.inventory.str('filename', default='')
    

        def process(self, neutrons):
            return self.engine.process( neutrons )
        
        
        def _fini(self):
            h = self.engine.histogram
            from histogram.hdf import dump
            dir = self.getOutputDir()
            f = self.inventory.filename or ('%s.h5' % self.name)
            import os
            f = os.path.join(dir, f)
            dump(h, f, '/', 'c')
            super(Monitor, self)._fini()
            return
        
        
        def _init(self):
            AbstractComponent._init(self)
            expressions = []
            bins = []
            ranges = []
            for q in quantities:
                if q not in neqs:
                    expr = q2e[q]
                else:
                    expr = q
                expressions.append(expr)
                n = getattr(self.inventory, 'n%s' % q)
                bins.append(n)
                range = getattr(self.inventory, '%smin' % q),\
                        getattr(self.inventory, '%smax' % q)
                ranges.append(range)
                continue

            from ..components.NDMonitor import NDMonitor
            self.engine = NDMonitor(
                self.name,
                expressions,
                bins,
                ranges,
                )
            return

        pass
    
    return Monitor



# version
__id__ = "$Id: __init__.py 601 2010-10-03 19:55:29Z linjiao $"

# End of file 
