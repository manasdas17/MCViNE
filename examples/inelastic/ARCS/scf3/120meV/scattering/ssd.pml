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
        <facility name="source">sources/NeutronFromStorage</facility>
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="detector">monitors/NeutronToStorage</facility>

        <property name="multiple-scattering">False</property>

        <property name="ncount">242200</property>
        <property name="buffer_size">2422</property>

        <property name="overwrite-datafiles">True</property>
        <property name="output-dir">out</property>

        <component name="sample">
            <property name="xml">scf3/sampleassembly.xml</property>
        </component>


        <component name="source">
            <property name="path">../mod2sample/out/neutrons</property>
        </component>


        <component name="detector">
            <property name="path">neutrons</property>
            <property name="append">False</property>
        </component>


        <component name="geometer">
            <property name="source">((0, 0, 13.45), (0, 0, 0))</property>
            <property name="sample">((0, 0, 13.6), (0, 0, 0))</property>
            <property name="detector">((0, 0, 13.6), (0, 0, 0))</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Sun Aug  1 15:15:18 2010-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ ssd -source=sources/NeutronFromStorage -detector=NeutronToStorage -h -dump-pml=new.pml
-->

