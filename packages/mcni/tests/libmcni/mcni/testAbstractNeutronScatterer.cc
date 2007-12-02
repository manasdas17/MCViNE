// -*- C++ -*-
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//                                   Jiao Lin
//                      California Institute of Technology
//                         (C) 2005 All Rights Reserved  
//
// {LicenseText}
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//


#include <iostream>
#include "mcni/neutron.h"
#include "mcni/AbstractNeutronScatterer.h"
#include "mcni/test/assert.h"

using namespace mcni;


class Scatterer: public AbstractNeutronScatterer{
public:
  Scatterer() {}
  virtual void scatter(Neutron::Event &) 
  {
  }
};

void test1()
{
  Scatterer s;
  Neutron::Event ev;
  s.scatter( ev );
}


int main()
{
  test1();
}

// version
// $Id$

// End of file 
