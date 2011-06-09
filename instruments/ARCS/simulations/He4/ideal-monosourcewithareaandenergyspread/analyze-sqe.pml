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

    <component name="analyze-sqe">
        <property name="dump-instrument">False</property>
        <facility name="monitor">monitors/IQE_monitor</facility>
        <property name="sequence">['source', 'monitor']</property>
        <property name="launcher">mpirun</property>
        <property name="overwrite-datafiles">True</property>
        <property name="output-dir">out-analyze-sqe</property>
        <property name="ncount">10000.0</property>
        <property name="multiple-scattering">False</property>
        <facility name="source">sources/NeutronFromStorage</facility>
        <facility name="geometer">geometer</facility>
        <property name="dump-registry">False</property>
        <property name="tracer">no-neutron-tracer</property>

        <component name="source">
            <property name="path">out/scattered-neutrons</property>
        </component>


        <component name="monitor">
            <property name="min_angle_in_plane">-180.0</property>
            <property name="max_angle_in_plane">180.0</property>
            <property name="min_angle_out_of_plane">-90.0</property>
            <property name="max_angle_out_of_plane">90.0</property>
            <property name="Ei">60.0</property>
            <property name="Qmin">0.0</property>
            <property name="Qmax">10.0</property>
            <property name="nQ">500</property>
            <property name="Emin">-45.0</property>
            <property name="Emax">45.0</property>
            <property name="nE">500</property>
            <property name="filename">iqe.dat</property>
        </component>


        <component name="geometer">
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="monitor">((0, 0, 0), (0, 0, 0))</property>
        </component>


    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Sat Mar 26 00:29:22 2011-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ analyze-sqe -source=NeutronFromStorage -monitor=IQE_monitor -dump-pml
-->

