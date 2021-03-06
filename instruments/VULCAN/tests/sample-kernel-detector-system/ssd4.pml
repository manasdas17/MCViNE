<?xml version="1.0"?>
<!--
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!
!                             Jiao Lin, Alex Dementsov
!                      California Institute of Technology
!                      (C) 2006-2010  All Rights Reserved
!
! {LicenseText}
!
! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-->

<!-- [SNS_source4] -> [PowderKernel] -> [DetectorSystem] -->

<!DOCTYPE inventory>

<inventory>

    <component name="ssd4">

        <property name="sequence">['source', 'sample', 'detector']</property>

        <facility name="source">sources/SNS_source4</facility>
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="detector">detectorsystem</facility>

        <property name="multiple-scattering">False</property>

        <property name="ncount">100000</property>
        <property name="buffer_size">10000</property>

        <property name="overwrite-datafiles">True</property>
        <property name="output-dir">out</property>
        <property name="dump-registry">False</property>

        <component name="source">
            
            <property name="yh">0.085</property>
            <property name="dist">10</property>
            <property name="Emin">0.01</property>
            <property name="Emax">1000</property>
            <property name="tinmin">0.0</property>
            <property name="sample_t">1</property>
            <property name="height">0.12</property>
            <property name="width">0.10</property>
            <property name="proton_T">0.600</property>
            <property name="tinmax">2000.0</property>
            <property name="sample_E">2</property>
            <property name="S_filename">a1Gw2-8-f5_fit_fit.dat</property>
            <property name="xw">0.016</property>
            
        </component>

        <component name="sample">
            <property name="xml">Al_assembly2/sampleassembly.xml</property>
        </component>

        <component name="detector">
            <property name="xwidth">0.770</property>
            <property name="yheight">0.385</property>
            <property name="tmin">0</property>
            <property name="tmax">0.02</property>
            <property name="nt">100</property>
            <property name="wmin">0</property>
            <property name="wmax">10</property>
            <property name="nw">100</property>
        </component>

        <component name="geometer">
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="sample">((0, 0, 10), (0, 0, 0))</property>
            <property name="detector">((0, 0, 10), (0, 0, 0))</property>
            <property name="dump">False</property>
        </component>

    </component>

</inventory>


