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
 	    <property name="xml">Al/sampleassembly.xml</property>
        </component>

	<component name="detector">
<!-- if use PSD_monitor_4PI
	  <property name="radius">3</property>
	  <property name="nx">180</property>
	  <property name="ny">90</property>
	  <property name="filename">psd_4pi.dat</property>
-->
	  <property name="Ei">120</property>
	  <property name="Emin">-50</property>
	  <property name="Emax">50</property>
	  <property name="nE">100</property>
	  <property name="Qmin">0</property>
	  <property name="Qmax">13</property>
	  <property name="nQ">130</property>
	  <property name="filename">iqe.dat</property>
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

