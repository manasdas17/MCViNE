# -*- Makefile -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                               Michael A.G. Aivazis
#                        California Institute of Technology
#                        (C) 1998-2004  All Rights Reserved
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#

PROJECT = mcvine
PACKAGE = docs/sphinx/examples

# directory structure

#--------------------------------------------------------------------------
all: export
#


TMPDIR=$(BLD_ROOT)/tmp/$(PROJECT)/$(PACKAGE)
SPHINX_OUTPUT_DIR=$(EXPORT_ROOT)/docs/mcvine/sphinx
EXAMPLE_TARBALL=$(SPHINX_OUTPUT_DIR)/examples.tgz
REPO=svn://danse.us/MCViNE/trunk/docs/sphinx/examples

export:: export-package-data

# check out this examples directory to a temporary directory 
# remove .svn and Make.mm
# create tar ball
export-package-data:: 
	mkdir -p $(TMPDIR) ; \
	cd $(TMPDIR) ; \
	svn co $(REPO) examples ; \
	find examples -name .svn -exec rm -rf {} \; ; \
	find examples -name Make.mm -exec rm -f {} \; ; \
	mkdir -p $(SPHINX_OUTPUT_DIR); \
	tar czf $(EXAMPLE_TARBALL) examples ; \


# version
# $Id$

# End of file
