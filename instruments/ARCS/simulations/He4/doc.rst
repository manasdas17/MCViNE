Quick Overview
""""""""""""""

This example can be found in ::

 $MCVINE_DIR/share/mcvine/instruments/ARCS/simulations/He4

To start, make a copy of that directory::

 $ cp -r $MCVINE_DIR/share/mcvine/instruments/ARCS/simulations/He4 <workdir>

Now cd into it::

 $ cd <workdir>

To run a moderator...sample simulation, cd into mod2sample::

 $ cd mod2sample

Take a look at the "run" script and modify it according to your needs,
and run it::

 $ ./run

After the simulation, you can find results in directories "out" and 
"out-analyzer". For example::

 $ PlotHist.py out-analyzer/ienergy.h5

.. figure:: images/ARCS/I_E.png
   :width: 50%

Next, go to the "ideal" directory::

 $ cd ../ideal

In this directory you can calculate simulation
from a sample with idea recoil function.
To run the simulation, take a look
at the "run" script and modify it to your needs, and run it::

 $ ./run

You should see a I(Q,E) plot after the simulation is done.

.. figure:: images/ARCS/He4-ideal-recoil-IQE.png
   :width: 50%


More details
""""""""""""

mod2sample
''''''''''
This directory runs the simulation of neutrons 
emitting from the moderator, going down the stream through
guides and choppers, until they arrive just before the
sample position.

The run script reads::

  python run.py  \
    -Ei=700 \
    -ncount=1e7 \
    -nodes=5 \
    -moderator_erange=660,770 \
    -fermichopper=700-0.5-AST \
    -fermi_nu=600 \
    -T0_nu=120 \
    -emission_time=-1 \
    -dry_run=off


where

- Ei: nominal incident neutron energy
- ncount: # of Monte Carlo samples
- nodes: # of nodes
- fermichopper: choice of Fermi chopper


ideal
'''''

In this directory, the neutrons simulated at sample position
in mod2sample are sent to a sample with ideal recoil function like
scattering kernel.
The scattered neutrons are intercepted by virtual ARCS 
detector system and that generates events to be stored
in an event-mode data file.
The event data file is then reduced to I(Q,E).

The run script reads::

  python run.py \
    -ncount=1e6 \
    -nodes=2 \
    -Ei=700 \
    -E_Q=Q*Q/1.8 \
    -S_Q=1. \
    -Qmin=0. \
    -Qmax=28. \
    -Qstep=0.1 \
    -Emin=-50. \
    -Emax=500. \
    -Estep=1. \
    -mod2sample=../mod2sample \


where

- ncount: # of Monte Carlo samples
- nodes: # of nodes
- Ei: nominal incident energy
- E_Q: E(Q) recoil function form
- S_Q: S(Q) function form
- Qmin, Qmax, Qstep: define the Q axis
- Emin, Emax, Estep: define the E axis
- mod2sample: the path to the directory where mod2sample simulation
  were run
