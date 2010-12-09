# -*- Makefile -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                                Jiao Lin
#                        (C) 2008 All Rights Reserved
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PROJECT = mcni
PACKAGE = components


BUILD_DIRS = \


RECURSE_DIRS = $(BUILD_DIRS)


#--------------------------------------------------------------------------
#

all: export

release: tidy
	cvs release .

update: clean
	cvs update .

#--------------------------------------------------------------------------
#
# export

EXPORT_PYTHON_MODULES = \
	ComponentGroup.py \
	Dummy.py \
	MonochromaticSource.py \
	NDMonitor.py \
	NeutronFromStorage.py \
	NeutronPrinter.py \
	NeutronToStorage.py \
	NeutronsOnCone_FixedQE.py \
	Registry.py \
	__init__.py \
	repositories.py \


export:: export-package-python-modules
	BLD_ACTION="export" $(MM) recurse


# version
# $Id$

# End of file
