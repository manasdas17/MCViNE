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



from mccomponents.homogeneous_scatterer.bindings.BoostPythonBinding \
     import BoostPythonBinding, extend

import mccomponents.mccomponentsbp as b
import mccomposite.mccompositebp as b1


class New:

    def gridsqe(self, qbegin, qend, qstep,
                ebegin, eend, estep,
                s ):
        '''gridsqe: S(Q,E) on grid

        qbegin, qend, qstep: Q axis
        ebegin, eend, estep: E axis
        s: numpy array of S
        '''
        shape = s.shape
        assert len(shape) == 2
        assert shape[0] == int( (qend-qbegin)/qstep +0.5 ), (
            'qend: %s, qbegin: %s, qstep: %s, shape0: %s' % (
            qend, qbegin, qstep, shape[0]) )
        assert shape[1] == int( (eend-ebegin)/estep +0.5 )
        size = shape[0] * shape[1]
        
        svector = b.vector_double( size )
        saveshape = s.shape
        s.shape = -1,
        svector[:] = s
        s.shape = saveshape
        
        fxy = b.new_fxy(
            qbegin, qend, qstep,
            ebegin, eend, estep,
            svector)
        
        return b.GridSQE( fxy )

    
    def sqeFromExpression(self, expr):
        '''sqeFromExpression: S(Q,E) from analystic expreession
        '''
        expr = str(expr)
        return b.SQE_fromexpression(expr)

    
    def sqekernel(self, absorption_cross_section, scattering_cross_section,
                  unitcell_vol,
                  sqe, Qrange, Erange):
        '''sqekernel: a kernel takes S(Q,E) a functor

        absorption_cross_section: absorption cross section
        scattering_cross_section: scattering cross section
        sqe: S(Q,E) functor
        Qrange, Erange: range of Q and E
        '''
        Emin, Emax = Erange
        Qmin, Qmax = Qrange
        return b.SQEkernel(
            absorption_cross_section, scattering_cross_section,
            unitcell_vol,
            sqe, Qmin, Qmax, Emin, Emax )
    

    def isotropickernel(self, absorption_cross_section, scattering_cross_section):
        '''isotropickernel: a kernel scatters isotropically and elastically

        absorption_cross_section: absorption cross section
        scattering_cross_section: scattering cross section
        '''
        return b.IsotropicKernel(absorption_cross_section, scattering_cross_section)


    def constantEnergyTransferKernel(self, E, absorption_cross_section, scattering_cross_section):
        '''constantenergytransferkernel: a kernel scatters isotropically with fixed energy transfer

        E: energy transfer
        absorption_cross_section: absorption cross section
        scattering_cross_section: scattering cross section
        '''
        return b.ConstantEnergyTransferKernel(E, absorption_cross_section, scattering_cross_section)


    def constantQEKernel(self, Q, E, absorption_cross_section, scattering_cross_section):
        '''constantqekernel: a kernel scatters isotropically with fixed momentum and energy transfer

        Q: momentum transfer
        E: energy transfer
        absorption_cross_section: absorption cross section
        scattering_cross_section: scattering cross section
        '''
        return b.ConstantQEKernel(Q, E, absorption_cross_section, scattering_cross_section)

    
    pass # end of BoostPythonBinding


extend( New )



# version
__id__ = "$Id$"

# End of file 
