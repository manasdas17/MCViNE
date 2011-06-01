#!/usr/bin/env python

def main():
    import os, shutil
    from pickonepixel import run

    N = 100
    
    pixelIDs = range(3)
    for pixelID in pixelIDs:
        if os.path.exists('out'):
            shutil.rmtree('out')
        n = run(
            ncount=N, 
            pixelID = pixelID,
            ei = 700,
            )
        assert (n>=0.85*N)
    return


if __name__ == '__main__': main()
    
    
