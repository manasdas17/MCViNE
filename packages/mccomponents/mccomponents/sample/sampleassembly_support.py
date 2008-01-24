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


def sampleassembly2compositescatterer( sampleassembly ):
    return SampleAssembly2CompositeScatterer().render( sampleassembly )



def findkernelsfromxmls( compositescatterer ):
    return FindKernelsFromXMLs().render( compositescatterer )



class SampleAssembly2CompositeScatterer:

    '''render a composite scatterer reperesentation
    (svn://danse.us/MCViNE/.../mccomposite)
    from
    a sample assembly representation
    (svn://danse.us/inelastic/sample/.../sampleassembly)
    '''

    def render(self, sampleassembly):
        return sampleassembly.identify(self)


    def onSampleAssembly(self, sampleassembly ):
        #
        lg = sampleassembly.local_geometer

        # the container
        import mccomposite
        compositeScatterer = mccomposite.composite( )

        for scatterer in sampleassembly.elements():
            s = scatterer.identify(self)
            p = lg.position( scatterer )
            o = lg.orientation( scatterer )
            compositeScatterer.addElement( s, p, o )
            continue

        return compositeScatterer


    def onHomogeneousScatterer(self, scatterer ):
        import mccomponents.homogeneous_scatterer as hs
        s = hs.homogeneousScatterer( scatterer.shape(), kernel = None )
        s.origin = scatterer
        return s


    onPowderSample = onHomogeneousScatterer

    pass # end of SampleAssembly2CompositeScatterer



#go thru the scatterer composite tree and
#find scatterer xmls and load them.
#Those scatterer xmls specify the mc simulation details.
#each scatterer in the input composite has an "origin" attached, and that "origin"
#is a node of "sampleassembly" package (svn://danse.us/inelastic/sample/.../sampleassembly).
#Basisically, the input, a scatterer composite tree,
#is result of SampleAssembly2CompositeScatterer rendering.
class FindKernelsFromXMLs:
    
    def render(self, compositescatterer):
        return compositescatterer.identify(self)


    def onCompositeScatterer(self, compositescatterer):
        for scatterer in compositescatterer.elements():
            scatterer.identify(self)
            continue
        return compositescatterer


    def onHomogeneousScatterer(self, scatterer):
        origin = scatterer.origin
        name = origin.name
        xmlfilename = '%s-scatterer.xml' % name
        from kernelxml import parse_file
        mcscatterer = parse_file( xmlfilename )

        # transfer weights
        scatterer.mcweights_absorption_scattering_transmission = mcscatterer.mcweights_absorption_scattering_transmission
                                                               
        # transfer shape if necessary
        shape = mcscatterer.shape()
        if shape: scatterer.setShape( shape )
        
        # transfer kernel
        kernel = mcscatterer.kernel()
        scatterer.setKernel( kernel )

        # remember origin
        kernel.scatterer_origin = origin
        return


    onPowderSample = onHomogeneousScatterer

    pass # end of FindKernelsFromXMLs


# version
__id__ = "$Id$"

# End of file 