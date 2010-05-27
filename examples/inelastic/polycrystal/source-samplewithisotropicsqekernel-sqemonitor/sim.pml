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
        <property name="ncount">1.e6</property>
        <property name="multiple-scattering">False</property>
        <facility name="source">sources/MonochromaticSource</facility>
        <facility name="geometer">geometer</facility>
        <property name="buffer_size">100000</property>

        <component name="sample">
            <property name="xml">sampleassembly/Ni-sqekernel-isotropicsqe-sampleassembly.xml</property>
        </component>


        <component name="source">
            <property name="position">[0.0, 0.0, 0.0]</property>
            <property name="energy">60.0</property>
            <property name="velocity">[0.0, 0.0, 3000.0]</property>
            <property name="probability">1.0</property>
            <property name="time">0.0</property>
        </component>


        <component name="monitor">
            <property name="max_angle_in_plane">120.0</property>
            <property name="Ei">60.0</property>
            <property name="name">iqe_monitor</property>
            <property name="min_angle_in_plane">0.0</property>
            <property name="Emax">45.0</property>
            <property name="Emin">-45.0</property>
            <property name="Qmax">11.0</property>
            <property name="min_angle_out_of_plane">-30.0</property>
            <property name="nE">90</property>
            <property name="Qmin">0.0</property>
            <property name="max_angle_out_of_plane">30.0</property>
            <property name="nQ">110</property>
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

<!-- Generated automatically by Renderer on Sun May 23 20:17:53 2010-->

<!-- End of file -->
