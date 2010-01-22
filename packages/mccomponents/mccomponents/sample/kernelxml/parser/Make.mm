# -*- Makefile -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                               Michael A.G. Aivazis
#                        California Institute of Technology
#                        (C) 1998-2004  All Rights Reserved
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PROJECT = mccomponents
PACKAGE = sample/kernelxml/parser

#--------------------------------------------------------------------------
#

all: export


#--------------------------------------------------------------------------
#
# export

EXPORT_PYTHON_MODULES = \
	AbstractNode.py \
	Document.py \
	GridSQE.py \
	HomogeneousScatterer.py \
	KernelContainer.py \
	ScatteringKernel.py \
	SQEkernel.py \
	__init__.py \


#include doxygen/default.def

export:: export-package-python-modules 

# version
# $Id: Make.mm 1205 2006-11-15 16:23:10Z linjiao $

# End of file
