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

PROJECT = simulation
PACKAGE = tests

PROJ_CLEAN += $(PROJ_CPPTESTS)

PROJ_PYTESTS =  alltests.py
PROJ_CPPTESTS = testEvent testCeventbuffer testcoords_transform
PROJ_TESTS = $(PROJ_PYTESTS) $(PROJ_CPPTESTS)
PROJ_LIBRARIES = -L$(BLD_LIBDIR) -ljournal -lmcni


#--------------------------------------------------------------------------
#

all: $(PROJ_TESTS)

test:
	for test in $(PROJ_TESTS) ; do $${test}; done

release: tidy
	cvs release .

update: clean
	cvs update .

#--------------------------------------------------------------------------
#

testCeventbuffer: testCeventbuffer.cc 
	$(CXX) $(CXXFLAGS) $(LCXXFLAGS) -o $@ testCeventbuffer.cc $(PROJ_LIBRARIES)

testEvent: testEvent.cc 
	$(CXX) $(CXXFLAGS) $(LCXXFLAGS) -o $@ testEvent.cc $(PROJ_LIBRARIES)

testcoords_transform: testcoords_transform.cc 
	$(CXX) $(CXXFLAGS) $(LCXXFLAGS) -o $@ testcoords_transform.cc $(PROJ_LIBRARIES)


# version
# $Id: Make.mm 620 2007-07-11 23:24:50Z linjiao $

# End of file