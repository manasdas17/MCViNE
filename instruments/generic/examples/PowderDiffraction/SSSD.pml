<?xml version="1.0"?>
<!--
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!
!                                   Jiao Lin
!                      California Institute of Technology
!                        (C) 2008  All Rights Reserved
!
! {LicenseText}
!
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-->


<!DOCTYPE inventory>

<inventory>

  <component name="SSSD">

    <property name="ncount">1e6</property>
    <property name="buffer_size">10000</property>
<!--
    <property name='overwrite-datafiles'>yes</property>
-->

    <component name="geometer">
      <property name="source">(0,0,0), (0,0,0)</property>
      <property name="sample">(0,0,10), (0,0,0)</property>
      <property name="neutron_storage">(0,0,10), (0,0,0)</property>
      <property name="detector">(0,0,10), (0,0,0)</property>
    </component>

    <facility name='source'>pseudo_monochromatic</facility>
    <component name="pseudo_monochromatic">
      <property name="radius">0.05</property>
      <property name="height">0</property>
      <property name="width">0</property>
      <property name="dist">10</property>
      <property name="xw">0.01</property>
      <property name="yh">0.01</property>
      <property name="E0">50</property>
      <property name="dE">40</property>
      <property name="Lambda0">0</property>
      <property name="dLambda">0</property>
      <property name="flux">1</property>
      <property name="gauss">0</property>
    </component>

    <facility name="sample">powder_sample</facility>
    <component name="powder_sample">
      <property name="d_phi">0</property>
      <property name="radius">0.015</property>
      <property name="radius_i">0</property>
      <property name="yheight">0.05</property>
      <property name="Vc">0</property>
      <property name="sigma_abs">0</property>
      <property name="sigma_inc">0</property>
      <property name="reflections">Al.laz</property>
      <property name="format">3</property>
    </component>

    <component name="neutron_storage">
      <property name="path">neutrons</property>
      <property name="packetsize">10000</property>
    </component>

    <facility name="detector">psd_4pi</facility>
    <component name="psd_4pi">
      <property name="radius">3</property>
      <property name="nx">180</property>
      <property name="ny">90</property>
      <property name="filename">psd_4pi.dat</property>
    </component>

  </component>

</inventory>


<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by XMLMill on Mon Jul 14 13:47:59 2008-->

<!-- End of file -->
