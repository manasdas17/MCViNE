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

    <component name="sd">
        <property name="output-dir">out</property>
        <property name="sequence">['source', 'detsys']</property>
        <facility name="source">sources/NeutronFromStorage</facility>
        <facility name="detsys">detectors/DetectorSystemFromXml</facility>
        <property name="ncount">26606000</property>
        <property name="multiple-scattering">False</property>
        <property name="buffer_size">266060</property>
        <property name="overwrite-datafiles">1</property>

        <component name="source">
            <property name="path">scattered-neutrons</property>
        </component>


        <component name="detsys">
            <property name="tofparams">0,0.017,1e-6</property>
            <property name="instrumentxml">ARCS.xml</property>
            <property name="eventsdat">events.dat</property>
        </component>


        <component name="geometer">
            <property name="source">((0, 0, 0), (0, 0, 0))</property>
            <property name="detsys">((0, 0, 0), (0, 0, 0))</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Thu Jun 17 21:02:19 2010-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ sd -h -source=NeutronFromStorage -detsys=DetectorSystemFromXml -dump-pml=yes
-->

