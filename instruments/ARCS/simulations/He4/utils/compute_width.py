#!/usr/bin/env python


"""
compute width of I(E) spectrum at a given Q point
"""

def compute(Q, E_Q=None, dQ=0.2, dE=100, iqe=None):
    #
    E_Q = E_Q or (lambda Q: 0.522*Q*Q)
    
    from getIE import getIE
    IE = getIE(Q=Q, E_Q=E_Q, dQ=dQ, dE=dE, iqe=iqe)

    # guess
    ht = max(IE.I)
    center = 0
    width = 10.
    p0 = [ht, center, width]

    # fit
    from fitg import fit
    success, p1, data = fit(IE, p0)

    if not success:
        raise RuntimeError, "failed fitting: Q=%s" % Q

    return p1, data


def run(Q, E_Q=None, dQ=0.2, dE=100, iqe=None):
    p1, data = compute(Q=Q, E_Q=E_Q, dQ=dQ, dE=dE, iqe=iqe)
    print p1
    x, expy, fittedy = data
    import pylab
    pylab.plot(x, expy, x, fittedy)
    pylab.show()
    return p1


def test():
    Q = 20.
    import histogram.hdf as hh
    iqe = hh.load('iqe.h5')

    run(Q, iqe=iqe)
    return


def main():
    import sys
    Q = eval(sys.argv[1])
    iqe = sys.argv[2]
    import histogram.hdf as hh
    iqe = hh.load(iqe)
    p1 = run(Q, iqe=iqe, dQ=0.5)
    line = '%s\t%s\n' % (Q, p1[-1])
    open('res.dat', 'a').write(line)
    return


if __name__ == '__main__': main()
