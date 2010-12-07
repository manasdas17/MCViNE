<?xml version="1.0"?>
<!--
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!
!
! {LicenseText}
!
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-->

<!DOCTYPE inventory>

<inventory>

    <component name="ssd">
        <property name="sequence">['source', 'sample', 'detector']</property>
        <facility name="source">sources/MonochromaticSource</facility>
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="detector">monitors/IQE_monitor</facility>
        <property name="multiple-scattering">off</property>
        <property name="ncount">1e5</property>
        <property name="buffer_size">100000</property>
        <property name="overwrite-datafiles">yes</property>
        <property name="output-dir">out</property>


        <component name="sample">
            <property name="xml">../sampleassembly.xml</property>
        </component>


        <component name="source">
            <property name="position">[0.0, 0.0, 0.0]</property>
            <property name="energy">60.0</property>
            <property name="velocity">[0.0, 0.0, 1.0]</property>
            <property name="probability">1.0</property>
            <property name="time">0.0</property>
        </component>


        <component name="detector">
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
            <property name="source">((0, 0, -1), (0, 0, 0))</property>
            <property name="detector">((0, 0, 0), (0, 0, 0))</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Sun Aug  1 12:17:26 2010-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ ssd -source=MonochromaticSource -sample=SampleAssemblyFromXml -detector=IQE_monitor -h -dump-pml=yes
-->

