#!/usr/bin/env bash

mcvine-simulate \
    --components=source,sample,detector_90tc,detector_90wc,detector_90tt,detector_90wt,detector_90tb,detector_90wb \
    --ncount=1000 \
    --buffer_size=100 \
    --source=SNS_source4 \
    --sample=V_sample \
    --detector_90tc=PSD_TEW_monitor \
    --detector_90wc=PSD_TEW_monitor \
    --detector_90tt=PSD_TEW_monitor \
    --detector_90wt=PSD_TEW_monitor \
    --detector_90tb=PSD_TEW_monitor \
    --detector_90wb=PSD_TEW_monitor \
    --source.yh='0.085' \
    --source.dist='4.3' \
    --source.Emin='0.01' \
    --source.Emax='1000' \
    --source.tinmin='0.0' \
    --source.sample_t='1' \
    --source.height='0.12' \
    --source.width='0.10' \
    --source.proton_T='0.600' \
    --source.tinmax='2000.0' \
    --source.sample_E='2' \
    --source.S_filename='a1Gw2-8-f5_fit_fit.dat' \
    --source.xw='0.016' \
    --geometer.source='(0.00000, 0.00000, 0.00000),(0.00000, 0.00000, 0.00000)' \
    --sample.target_index='0' \
    --sample.radius_i='0.015' \
    --sample.radius_o='0.02' \
    --sample.focus_aw='0' \
    --sample.focus_yh='1.30' \
    --sample.V0='13.827' \
    --sample.zthick='0' \
    --sample.focus_ah='0' \
    --sample.sig_i='4.935' \
    --sample.f_QE='0' \
    --sample.frac='1' \
    --sample.sig_a='5.08' \
    --sample.target_z='0' \
    --sample.target_x='-2' \
    --sample.target_y='0' \
    --sample.focus_r='0' \
    --sample.h='0.05' \
    --sample.yheight='0' \
    --sample.focus_xw='0.780' \
    --sample.xwidth='0' \
    --sample.gamma='0' \
    --sample.pack='1' \
    --geometer.sample='relative((0.00000, 0.00000, 2.00000), to="previous"),relative((0.00000, 0.00000, 0.00000), to="previous")' \
    --detector_90tc.nxchan='1' \
    --detector_90tc.format='table' \
    --detector_90tc.bmax='100' \
    --detector_90tc.yheight='0.385' \
    --detector_90tc.restore_neutron='1' \
    --detector_90tc.filename='detector_l90tc.txt' \
    --detector_90tc.nychan='1' \
    --detector_90tc.bmin='0' \
    --detector_90tc.deltab='0' \
    --detector_90tc.nbchan='100' \
    --detector_90tc.xwidth='0.770' \
    --detector_90tc.type='time' \
    --geometer.detector_90tc='relative((-2, 0.00000, 0.00000), to="sample"),relative((0.00000, 90, 0.00000), to="sample")' \
    --detector_90wc.nxchan='1' \
    --detector_90wc.format='table' \
    --detector_90wc.bmax='10' \
    --detector_90wc.yheight='0.385' \
    --detector_90wc.restore_neutron='1' \
    --detector_90wc.filename='detector_l90wc.txt' \
    --detector_90wc.nychan='1' \
    --detector_90wc.bmin='0' \
    --detector_90wc.deltab='0' \
    --detector_90wc.nbchan='100' \
    --detector_90wc.xwidth='0.770' \
    --detector_90wc.type='wavelength' \
    --geometer.detector_90wc='relative((-2, 0.00000, 0.00000), to="sample"),relative((0.00000, 90, 0.00000), to="sample")' \
    --detector_90tt.nxchan='1' \
    --detector_90tt.format='table' \
    --detector_90tt.bmax='100' \
    --detector_90tt.yheight='0.385' \
    --detector_90tt.restore_neutron='1' \
    --detector_90tt.filename='detector_l90tt.txt' \
    --detector_90tt.nychan='1' \
    --detector_90tt.bmin='0' \
    --detector_90tt.deltab='0' \
    --detector_90tt.nbchan='100' \
    --detector_90tt.xwidth='0.770' \
    --detector_90tt.type='time' \
    --geometer.detector_90tt='relative((-1.959, 0.403, 0.00000), to="sample"),relative((0.00000, 90, 0.00000), to="sample")' \
    --detector_90wt.nxchan='1' \
    --detector_90wt.format='table' \
    --detector_90wt.bmax='10' \
    --detector_90wt.yheight='0.385' \
    --detector_90wt.restore_neutron='1' \
    --detector_90wt.filename='detector_l90wt.txt' \
    --detector_90wt.nychan='1' \
    --detector_90wt.bmin='0' \
    --detector_90wt.deltab='0' \
    --detector_90wt.nbchan='100' \
    --detector_90wt.xwidth='0.770' \
    --detector_90wt.type='wavelength' \
    --geometer.detector_90wt='relative((-1.959, 0.403, 0.00000), to="sample"),relative((0.00000, 90, 0.00000), to="sample")' \
    --detector_90tb.nxchan='1' \
    --detector_90tb.format='table' \
    --detector_90tb.bmax='100' \
    --detector_90tb.yheight='0.385' \
    --detector_90tb.restore_neutron='1' \
    --detector_90tb.filename='detector_l90tb.txt' \
    --detector_90tb.nychan='1' \
    --detector_90tb.bmin='0' \
    --detector_90tb.deltab='0' \
    --detector_90tb.nbchan='100' \
    --detector_90tb.xwidth='0.770' \
    --detector_90tb.type='time' \
    --geometer.detector_90tb='relative((-1.959, -0.403, 0.00000), to="sample"),relative((0.00000, 90, 0.00000), to="sample")' \
    --detector_90wb.nxchan='1' \
    --detector_90wb.format='table' \
    --detector_90wb.bmax='10' \
    --detector_90wb.yheight='0.385' \
    --detector_90wb.restore_neutron='1' \
    --detector_90wb.filename='detector_l90wb.txt' \
    --detector_90wb.nychan='1' \
    --detector_90wb.bmin='0' \
    --detector_90wb.deltab='0' \
    --detector_90wb.nbchan='100' \
    --detector_90wb.xwidth='0.770' \
    --detector_90wb.type='wavelength' \
    --geometer.detector_90wb='relative((-1.959, -0.403, 0.00000), to="sample"),relative((0.00000, 90, 0.00000), to="sample")' \

