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

    <component name="checkbysqemon">

        <property name="sequence">['source', 'monitor']</property>
        <facility name="source">sources/NeutronFromStorage</facility>
        <facility name="monitor">monitors/IQE_monitor</facility>

        <property name="multiple-scattering">False</property>

        <property name="ncount">100000.0</property>
        <property name="buffer_size">1000</property>

        <property name="output-dir">out</property>
        <property name="overwrite-datafiles">False</property>

        <component name="source">
            <property name="path">out/neutrons</property>
        </component>

        <component name="monitor">
            <property name="Ei">120</property>
            <property name="Emin">-115</property>
            <property name="Emax">115</property>
            <property name="Qmin">0</property>
            <property name="Qmax">14</property>
            <property name="nE">230</property>
            <property name="nQ">140</property>
        </component>

        <component name="geometer">
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="monitor">((0, 0, 0), (0, 0, 0))</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Wed Aug 25 09:19:55 2010-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ checkbysqemon -dump-pml=yes -h
-->

