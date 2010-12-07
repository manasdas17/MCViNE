#!/usr/bin/env python


import os

header = """<?xml version="1.0"?>

<!DOCTYPE scatterer>

<!-- weights: absorption, scattering, transmission -->
<homogeneous_scatterer mcweights="0, 1, 0">

  <KernelContainer>

"""


footer = """
  </KernelContainer>
  
</homogeneous_scatterer>

"""


kernel_template = """
    <ConstantEnergyTransferKernel energy-transfer="%s*meV">
    </ConstantEnergyTransferKernel>
"""

def render(energies):
    kernels = [kernel_template % e for e in energies]
    items = [header] + kernels + [footer]
    return '\n'.join(items)



from pyre.applications.Script import Script
class App(Script):

    class Inventory(Script.Inventory):

        import pyre.inventory
        out = pyre.inventory.str('out')

        energies = pyre.inventory.array('energies')

        max_energy = pyre.inventory.float('max', default=100)


    def main(self):
        filename = self.inventory.out
        energies = self.inventory.energies
        max = self.inventory.max_energy
        energies = [e for e in energies if e < max]
        
        if os.path.exists(filename):
            raise RuntimeError, "%s already exists" % filename

        print filename
        s = open(filename, 'w')
        s.write(render(energies))

        return


def main():
    app = App('create-scatterer-xml')
    app.run()
    return


if __name__=='__main__': main()
