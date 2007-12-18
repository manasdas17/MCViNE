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

#ifndef MCNI_PROCESS_NEUTRON_EVENTS_H
#define MCNI_PROCESS_NEUTRON_EVENTS_H


namespace mcni{

  // forward declaration
  class AbstractNeutronScatterer;

  // convenient methods
  void process(AbstractNeutronScatterer &sk, Neutron::Events &buffer);
  void processM(AbstractNeutronScatterer &sk, Neutron::Events &buffer);

} // mcni


#endif // MCNI_PROCESS_NEUTRON_EVENTS_H


// version
// $Id: process_neutron_events.h 591 2006-09-25 07:17:26Z linjiao $

// End of file 
