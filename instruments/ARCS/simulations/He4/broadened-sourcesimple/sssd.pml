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
        <facility name="source">sources/MonochromaticSource</facility>
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="storage">monitors/NeutronToStorage</facility>
        <facility name="detector">detectors/DetectorSystemFromXml</facility>
	
        <property name="multiple-scattering">False</property>
	
        <property name="ncount">10000.0</property>

        <property name="overwrite-datafiles">False</property>
        <property name="output-dir">out</property>
	

        <component name="source">
            <property name="probability">1.0</property>
            <property name="energy">687</property>
            <property name="height">0.05</property>
            <property name="width">0.05</property>
            <property name="time">0.0</property>
            <property name="position">[0.0, 0.0, 0.0]</property>
            <property name="velocity">[0.0, 0.0, 1.0]</property>
        </component>


        <component name="sample">
            <property name="xml">sampleassembly/sampleassembly.xml</property>
        </component>


        <component name="storage">
            <property name="path">scattered-neutrons</property>
        </component>


        <component name="detector">
            <property name="tofparams">0,0.02,1e-7</property>
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

<!-- Generated automatically by Renderer on Wed Mar 30 17:23:25 2011-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ sssd -source=NeutronFromStorage -sample=SampleAssemblyFromXml -storage=NeutronToStorage -detector=DetectorSystemFromXml -dump-pml
-->

