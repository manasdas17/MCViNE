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
PACKAGE = examples

# directory structure

#--------------------------------------------------------------------------
all: export
#


#CP_RF = cp -rf
RSYNC = rsync -a --copy-unsafe-links



EXPORT_SHAREDIR=$(EXPORT_ROOT)/share
SHARE_DEST =  $(EXPORT_SHAREDIR)/$(PROJECT)/$(PACKAGE)

export:: export-package-data

export-package-data:: 
	mkdir -p $(SHARE_DEST); \
	$(RSYNC) ./ $(SHARE_DEST)/;


# version
# $Id$

# End of file
