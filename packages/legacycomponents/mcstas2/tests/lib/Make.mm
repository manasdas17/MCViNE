# -*- Makefile -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                               Michael A.G. Aivazis
#                        California Institute of Technology
#                        (C) 1998-2004  All Rights Reserved
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PROJECT = mcstas2
PACKAGE = tests

PROJ_CLEAN += $(PROJ_CPPTESTS)

PROJ_PYTESTS =  
PROJ_CPPTESTS = testGravity testComponent test_detector_output_macros
PROJ_TESTS = $(PROJ_PYTESTS) $(PROJ_CPPTESTS)
PROJ_LIBRARIES = -L$(BLD_LIBDIR) -lmcstas2


#--------------------------------------------------------------------------
#

all: $(PROJ_TESTS)

test:
	for test in $(PROJ_TESTS) ; do $${test}; done

release: tidy
	cvs release .

update: clean
	cvs update .

tidy::
	BLD_ACTION="tidy" $(MM) recurse

#--------------------------------------------------------------------------
#

testGravity: testGravity.cc 
	$(CXX) $(CXXFLAGS) $(LCXXFLAGS) -o $@ testGravity.cc $(PROJ_LIBRARIES)

testComponent: testComponent.cc 
	$(CXX) $(CXXFLAGS) $(LCXXFLAGS) -o $@ testComponent.cc $(PROJ_LIBRARIES)

test_detector_output_macros: test_detector_output_macros.cc 
	$(CXX) $(CXXFLAGS) $(LCXXFLAGS) -o $@ test_detector_output_macros.cc $(PROJ_LIBRARIES)


# version
# $Id: Make.mm 114 2005-07-03 04:06:18Z linjiao $

# End of file
