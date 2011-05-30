#!/usr/bin/env python

import numpy as np, histogram as H, histogram.hdf as hh
from scipy.interpolate import interp1d


def run(Q=20, E_Q=None, dQ=0.15, dE=60, iqe=None):
    """
    Q: center of Q
    E_Q: E(Q) function
    dQ: (Q-dQ, Q+dQ) is the Q range to sum over
    dE: (-dE, dE) is the E range the result is on
    iqe: I(Q,E) histogram
    """
    Qcenter = Q
    
    Qarr = iqe.Q; Earr = iqe.E
    qstep = Qarr[1] - Qarr[0]
    estep = Earr[1] - Earr[0]
    
    # q values to sum over
    Qs = np.arange(Q-dQ, Q+dQ, qstep)

    # e values of result histogram
    Es = np.arange(-dE, dE, estep)
    # intensities
    intensities = np.zeros(len(Es))
    
    #
    for Q in Qs:
        # slice
        slice = iqe[Q, ()]

        # center E from E(Q) function
        Ecenter = E_Q(Q)
        
        # slice in the region of interest
        Emin = Ecenter - dE
        Emax = Ecenter + dE
        subslice = slice[(Emin, Emax)]
        subslice = subslice.I[:len(Es)]

        #
        intensities += subslice
        
        continue

    xaxis = H.axis('dE', Es, unit='meV')
    h = H.histogram('I(dE)', [xaxis], data=intensities)
    hh.dump(h, 'I_dE-Q=%s.h5' % Qcenter)
    return


def test():
    E_Q = lambda Q: 0.522*Q*Q
    iqe = hh.load('iqe.h5')
    run(Q=20, E_Q=E_Q, dQ=0.15, dE=60, iqe=iqe)
    return


def main():
    test()
    return


if __name__ == '__main__': main()
