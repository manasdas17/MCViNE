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



import unittestX as unittest
import journal

debug = journal.debug( "Dispersion_TestCase" )
warning = journal.warning( "Dispersion_TestCase" )


datapath = 'dispersion-example'

class TestCase(unittest.TestCase):

    def test0(self):
        from mccomponents.sample.idf import readDispersion
        nAtoms, dimension, Qaxes, polarizations, energies, dos \
                = readDispersion( datapath )
        print nAtoms, dimension, Qaxes
        print energies
        import pylab
        pylab.plot( dos[0], dos[1] )
        pylab.show()
        raw_input('Press ENTER to continue...')
        return

    pass  # end of TestCase



def pysuite():
    suite1 = unittest.makeSuite(TestCase)
    return unittest.TestSuite( (suite1,) )


def main():
    #debug.activate()
    pytests = pysuite()
    alltests = unittest.TestSuite( (pytests, ) )
    unittest.TextTestRunner(verbosity=2).run(alltests)
    
    
if __name__ == "__main__":
    main()
    
# version
__id__ = "$Id$"

# End of file 