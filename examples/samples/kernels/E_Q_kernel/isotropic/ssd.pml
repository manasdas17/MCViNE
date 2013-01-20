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
        <facility name="source">sources/Source_simple</facility>
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="detector">monitors/IQE_monitor</facility>

        <property name="multiple-scattering">False</property>

        <property name="ncount">10000.0</property>

        <property name="output-dir">out</property>
        <property name="overwrite-datafiles">False</property>

        <property name="tracer">no-neutron-tracer</property>
        <property name="launcher">mpirun</property>
        <property name="dump-registry">False</property>
        <property name="dump-instrument">False</property>


        <component name="geometer">
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="sample">((0, 0, 10), (0, 0, 0))</property>
            <property name="detector">((0, 0, 10), (0, 0, 0))</property>
        </component>


        <component name="source">
            <property name="name">source_simple</property>
            <property name="radius">0.0001</property>
            <property name="height">0.0</property>
            <property name="width">0.0</property>
            <property name="xw">0.0001</property>
            <property name="yh">0.0001</property>
            <property name="dist">10.0</property>
            <property name="flux">1.0</property>
            <property name="E0">500.0</property>
            <property name="dE">5.0</property>
            <property name="gauss">0.0</property>
            <property name="dLambda">0.0</property>
            <property name="Lambda0">0.0</property>
        </component>


        <component name="sample">
            <property name="xml">sample/sampleassembly.xml</property>
        </component>


        <component name="detector">
            <property name="name">iqe_monitor</property>
            <property name="Ei">500.0</property>
            <property name="Qmin">0.0</property>
            <property name="Qmax">30.0</property>
            <property name="nQ">100</property>
            <property name="Emax">500.0</property>
            <property name="Emin">-100.0</property>
            <property name="nE">120</property>
            <property name="min_angle_in_plane">0.0</property>
            <property name="max_angle_in_plane">120.0</property>
            <property name="min_angle_out_of_plane">-30.0</property>
            <property name="max_angle_out_of_plane">30.0</property>
            <property name="filename">iqe.dat</property>
            <property name="restore_neutron">False</property>
        </component>


        <component name="mpirun">
            <property name="nodes">0</property>
        </component>


    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- End of file -->

