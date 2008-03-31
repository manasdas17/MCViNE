#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                                   Jiao Lin
#                      California Institute of Technology
#                        (C) 2008  All Rights Reserved
#
# {LicenseText}
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#



def _get_histogram( self ):
    from mcstas2.utils.carray import bpptr2npyarr
    core = self.core()
    n = core.nchan
    Iarr = bpptr2npyarr( core.getE_p( ), 'double', n ).copy()
    E2arr = bpptr2npyarr( core.getE_p2( ), 'double', n ).copy()
    from histogram import histogram, axis, arange
    dE = (core.Emax-core.Emin)/core.nchan
    Eaxis = axis( 'energy', arange( core.Emin, core.Emax, dE ), unit = 'meV' )
    h = histogram( 'I(E)', [Eaxis], data = Iarr, errors = E2arr )
    return h


methods = [ '_get_histogram',
            ]

# version
__id__ = "$Id$"

# End of file 
