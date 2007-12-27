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

#include <cassert>
#include <iostream>
#include "mcni/neutron.h"
#include "mccomposite/AbstractNeutronScatterer.h"
#include "mccomposite/neutron_propagation.h"
#include "mccomposite/geometry/AbstractShape.h"
#include "mccomposite/geometry/shapes.h"
#include "mcni/test/assert.h"



class None: public mccomposite::AbstractNeutronScatterer{
public:
  None(const mccomposite::geometry::AbstractShape & shape) 
    : AbstractNeutronScatterer( shape ) 
  {}
  InteractionType interact_path1(mcni::Neutron::Event &) 
  {
    return none;
  }
};

class ToX: public mccomposite::AbstractNeutronScatterer{
public:
  ToX(const mccomposite::geometry::AbstractShape & shape) 
    : AbstractNeutronScatterer( shape ) 
  {}
  InteractionType interact_path1(mcni::Neutron::Event &ev) 
  {
    using namespace mccomposite;

    double t;
    if (locate(ev, shape()) != geometry::Locator::inside )
      propagate_to_next_incident_surface(ev, shape());
    tofs_t tofs = intersect( ev, shape() );
    if (tofs.size()==0) {
      return none;
    }
    else if (tofs.size()==1) {
      t = tofs[0]/2;
    } else {
      t = (tofs[1] - tofs[0])/2;
    }

    propagate(ev, t);
    
    ev.state.velocity = geometry::Direction(1,0,0);

    propagate_to_next_exiting_surface(ev, shape());

    return scattering;
  }
};

void test1()
{
  using namespace mccomposite;

  geometry::Box box(1,1,1);
  None s(box);
  mcni::Neutron::Event ev;
  assert (s.interact_path1( ev )==AbstractNeutronScatterer::none);
}


void test2()
{
  using namespace mccomposite;

  geometry::Box box(1,1,1);
  ToX s(box);
  mcni::Neutron::Event ev;
  ev.state.position = geometry::Position(0,0,-5);
  ev.state.velocity = geometry::Position(0,0,1);
  
  s.scatter(ev);
  
  assert( ev.state.position.x == 0.5 );
  assert( ev.state.position.y == 0 );
  assert( ev.state.position.z == 0 );

  assert( ev.state.velocity.x == 1 );
  assert( ev.state.velocity.y == 0 );
  assert( ev.state.velocity.z == 0 );
}


int main()
{
  test1();
  test2();
}

// version
// $Id$

// End of file 
