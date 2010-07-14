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
        <facility name="source">sources/MonochromaticSource</facility>
        <facility name="sample">samples/SampleAssemblyFromXml</facility>
        <facility name="monitor">monitors/NeutronToStorage</facility>
        <property name="overwrite-datafiles">True</property>
        <property name="output-dir">out</property>
        <property name="sequence">['source', 'sample', 'monitor']</property>
        <property name="ncount">1e7</property>
        <property name="multiple-scattering">False</property>
        <property name="buffer_size">1000000</property>

        <component name="sample">
            <property name="xml">Al/Al-isotropickernel.xml</property>
        </component>


        <component name="source">
            <property name="position">[0.0, 0.0, 0.0]</property>
            <property name="energy">0.0</property>
            <property name="velocity">[0.0, 0.0, 3000.0]</property>
            <property name="probability">1.0</property>
            <property name="time">0.0</property>
        </component>


        <component name="monitor">
            <property name="path">scattered-neutrons</property>
            <property name="append">False</property>
        </component>


        <component name="geometer">
            <property name="sample">((0, 0, 13.6), (0, 0, 0))</property>
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="monitor">((0, 0, 13.6), (0, 0, 0))</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Tue Jul 13 14:12:45 2010-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ ssd -source=MonochromaticSource -sample=SampleAssemblyFromXml -h -dump-pml=new.pml
-->

