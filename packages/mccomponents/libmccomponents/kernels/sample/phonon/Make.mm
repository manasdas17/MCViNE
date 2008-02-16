# -*- Makefile -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                               Michael A.G. Aivazis
#                        California Institute of Technology
#                        (C) 1998-2005  All Rights Reserved
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#

include local.def

PROJECT = mccomponents
PACKAGE = kernels/sample/phonon


PROJ_TMPDIR = $(BLD_TMPDIR)/$(PROJECT)/$(PACKAGE)


# directory structure

BUILD_DIRS = \

OTHER_DIRS = \

RECURSE_DIRS = $(BUILD_DIRS) $(OTHER_DIRS)



all: export
	BLD_ACTION="all" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
export:: export-package-headers

EXPORT_HEADERS = \
	AbstractDispersion_3D.h \
	LinearlyInterpolatedGridData_3D.h \
	LinearlyInterpolatedGridData_3D.icc \
	LinearlyInterpolatedDispersionOnGrid_3D.h \
	LinearlyInterpolatedDispersionOnGrid_3D.icc \
	LinearlyInterpolatedPolarizationOnGrid_3D.h \
	LinearlyInterpolatedPolarizationOnGrid_3D.icc \
	exception.h \
	interpolate.h \


# version
# $Id: Make.mm,v 1.1.1.1 2005/03/08 16:13:51 aivazis Exp $

#
# End of file
