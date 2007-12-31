#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                                   Jiao Lin
#                      California Institute of Technology
#                        (C) 2007  All Rights Reserved
#
# {LicenseText}
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#


import mccomponents.mccomponentsbp as binding


from AbstractBinding import AbstractBinding as base

class BoostPythonBinding(base):

    '''factory class of boost python computing engine of scatterers
    '''

    def composite(self, kernels):
        return binding.CompositeScatteringKernel( kernels )


    def kernelcontainer(self):
        return binding.pointer_vector_Kernel( 0 )


    pass # end of BoostPythonBinding


def register( methodname, method, override = False ):
    '''register a new handling method'''
    if hasattr(BoostPythonBinding, methodname):
        if not override:
            raise ValueError , "Cannot register handler %s. "\
                  "It was already registered." % (
                methodname )
        pass
    
    setattr( BoostPythonBinding, methodname, method )

    return


# version
__id__ = "$Id$"

# End of file 