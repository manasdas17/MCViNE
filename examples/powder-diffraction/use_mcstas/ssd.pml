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
        <facility name="sample">samples/PowderN</facility>
        <facility name="detector">monitors/PSD_monitor_4PI</facility>

        <property name="multiple-scattering">False</property>
        <property name="ncount">10000.0</property>
        <property name="output-dir">out</property>
        <property name="overwrite-datafiles">False</property>

        <property name="launcher">mpirun</property>
        <property name="tracer">no-neutron-tracer</property>

	<component name="geometer">
	  <property name="source">(0,0,0), (0,0,0)</property>
	  <property name="sample">(0,0,10), (0,0,0)</property>
	  <property name="detector">(0,0,10), (0,0,0)</property>
	</component>
	
	<component name="source">
	  <property name="radius">0.05</property>
	  <property name="height">0</property>
	  <property name="width">0</property>
	  <property name="dist">10</property>
	  <property name="xw">0.01</property>
	  <property name="yh">0.01</property>
	  <property name="E0">120</property>
	  <property name="dE">1</property>
	  <property name="Lambda0">0</property>
	  <property name="dLambda">0</property>
	  <property name="flux">1</property>
	  <property name="gauss">0</property>
	</component>

	<component name="sample">
	  <property name="d_phi">0</property>
	  <property name="radius">0.015</property>
	  <property name="radius_i">0</property>
	  <property name="yheight">0.05</property>
	  <property name="Vc">0</property>
	  <property name="sigma_abs">0</property>
	  <property name="sigma_inc">0</property>
	  <property name="reflections">Al.laz</property>
	  <property name="format">3</property>
	</component>

	<component name="detector">
	  <property name="radius">3</property>
	  <property name="nx">180</property>
	  <property name="ny">90</property>
	  <property name="filename">psd_4pi.dat</property>
	</component>

        <component name="mpirun">
            <property name="dry">False</property>
            <property name="nodelist">[]</property>
            <property name="extra"></property>
            <property name="python-mpi">`which python`</property>
            <property name="command">mpirun</property>
            <property name="debug">False</property>
            <property name="nodes">0</property>
        </component>

    </component>

</inventory>

<!-- version-->
<!-- $Id$-->

<!-- Generated automatically by Renderer on Mon Dec 17 13:10:58 2012-->

<!-- End of file -->
<!-- 
 automatically created by the following command:
 $ ssd -source=Source_simple -sample=PowderN -detector=PSD_monitor_4PI -dump-pml
-->

