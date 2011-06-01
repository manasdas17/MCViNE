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

    <component name="sssd">
        <property name="sequence">['source', 'sample', 'storage', 'detector']</property>
        <facility name="source">sources/Source_simple</facility>
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="storage">monitors/NeutronToStorage</facility>
        <facility name="detector">detectors/DetectorSystemFromXml</facility>
	
        <property name="multiple-scattering">False</property>
	
        <property name="ncount">10000.0</property>

        <property name="overwrite-datafiles">False</property>
        <property name="output-dir">out</property>
	

        <component name="source">
            <property name="radius">0.05</property>
            <property name="width">0.0</property>
            <property name="height">0.0</property>
            <property name="dist">13.45</property>
            <property name="E0">687.0</property>
            <property name="dE">2.55</property>
            <property name="gauss">1</property>
            <property name="flux">1.0</property>
            <property name="Lambda0">0.0</property>
            <property name="dLambda">0.0</property>
            <property name="xw">0.05</property>
            <property name="yh">0.05</property>
        </component>


        <component name="sample">
            <property name="xml">sampleassembly/sampleassembly.xml</property>
        </component>


        <component name="storage">
            <property name="path">scattered-neutrons</property>
        </component>


        <component name="detector">
            <property name="tofparams">0,0.02,1e-6</property>
            <property name="instrumentxml">ARCS.xml</property>
            <property name="eventsdat">events.dat</property>
        </component>


        <component name="geometer">
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="sample">((0, 0, 13.6), (0, 0, 0))</property>
            <property name="storage">((0, 0, 13.6), (0, 0, 0))</property>
            <property name="detector">((0, 0, 13.6), (0, 0, 0))</property>
        </component>


    </component>

</inventory>

<!-- version-->
<!-- $Id$-->
<!-- End of file -->

