<?xml version="1.0"?>
<!--
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!
!                                   Jiao Lin
!                      California Institute of Technology
!                      (C) 2006-2010  All Rights Reserved
!
! {LicenseText}
!
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-->

<!DOCTYPE inventory>

<inventory>

    <component name="sim">
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="monitor">monitors/IQE_monitor</facility>
        <property name="sequence">['source', 'sample', 'monitor']</property>
        <property name="overwrite-datafiles">True</property>
        <property name="output-dir">out</property>
        <property name="ncount">1e6</property>
        <property name="multiple-scattering">False</property>
        <facility name="source">sources/Source_simple</facility>
        <facility name="geometer">geometer</facility>
        <property name="buffer_size">100000</property>

        <component name="sample">
            <property name="xml">sampleassembly/Al-sqekernel-analyticalsqe.xml</property>
        </component>


        <component name="source">
            <property name="yh">0.1</property>
            <property name="dist">10.0</property>
            <property name="name">source_simple</property>
            <property name="width">0.0</property>
            <property name="dE">0.1</property>
            <property name="gauss">0.0</property>
            <property name="height">0.0</property>
            <property name="flux">1.0</property>
            <property name="dLambda">0.0</property>
            <property name="radius">0.05</property>
            <property name="Lambda0">0.0</property>
            <property name="E0">60.0</property>
            <property name="xw">0.1</property>
        </component>


        <component name="monitor">
            <property name="max_angle_in_plane">120.0</property>
            <property name="Ei">60.0</property>
            <property name="name">iqe_monitor</property>
            <property name="min_angle_in_plane">0.0</property>
            <property name="Emax">45.0</property>
            <property name="Emin">-45.0</property>
            <property name="Qmax">10.0</property>
            <property name="min_angle_out_of_plane">-30.0</property>
            <property name="nE">90</property>
            <property name="Qmin">0.0</property>
            <property name="max_angle_out_of_plane">30.0</property>
            <property name="nQ">100</property>
            <property name="filename">iqe_monitor.dat</property>
        </component>


        <component name="geometer">
            <property name="sample">((0, 0, 0), (0, 0, 0))</property>
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="monitor">((0, 0, 0), (0, 0, 0))</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Sun May 23 14:00:58 2010-->

<!-- End of file -->
