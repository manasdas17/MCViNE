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
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <property name="dump-instrument">False</property>
        <property name="overwrite-datafiles">1</property>
        <property name="sequence">['source', 'sample', 'detector']</property>
        <property name="launcher">mpirun</property>
        <property name="output-dir">out</property>
        <property name="ncount">10000.0</property>
        <property name="multiple-scattering">False</property>
        <facility name="source">sources/NeutronFromStorage</facility>
        <facility name="geometer">geometer</facility>
        <facility name="detector">monitors/NeutronToStorage</facility>
        <property name="dump-registry">False</property>
        <property name="tracer">no-neutron-tracer</property>

        <component name="mpirun">
            <property name="dry">False</property>
            <property name="nodelist">[]</property>
            <property name="extra"></property>
            <property name="python-mpi">`which python`</property>
            <property name="command">mpirun</property>
            <property name="debug">False</property>
            <property name="nodes">0</property>
        </component>


        <component name="sample">
            <property name="xml">sampleassembly/sampleassembly.xml</property>
        </component>


        <component name="source">
            <property name="path">incident-neutrons</property>
        </component>


        <component name="geometer">
            <property name="sample">((0, 0, 13.6), (0, 0, 0))</property>
            <property name="source">((0, 0, 13.45), (0, 0, 0))</property>
            <property name="detector">((0, 0, 13.6), (0, 0, 0))</property>
        </component>


        <component name="detector">
            <property name="path">scattered-neutrons</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Fri Mar 25 11:38:51 2011-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ ssd -source.path=incident-neutrons -sample.xml=sampleassembly/sampleassembly.xml -detector.path=scattered-neutrons -dump-pml
-->

