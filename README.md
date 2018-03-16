NEXTSim
========

NEXTSim is a [Geant4](https://geant4.web.cern.ch/geant4/)/[ROOT](https://root.cern.ch/) based software devoted to simulate and optimize the performance of the NEXT neutron detector


Authors
-------

- Xiadong Zhang
- Kyle Schmitt
- David Perez Loureiro 

Features
--------

- Realistic simulation of scintillation detectors
- Diferent geometries available
- SiPM readout

Installation
------------

### Getting the source

    $git clone https://github.com/alourei/NEXTSim
    
will clone the GitHub repository to your computer and will create the  NEXTSim folder

### Compiling
 Create the build directory and change to it
    
    $mkdir NEXTSim-build
    $cd NEXTSim-build
   
Generate the Makefile using cMake

    $cmake -DGeant4_DIR </pathToGeant4Instalation/lib/Geant<version>> </pathToNEXTsimSource>

Compile the code

    $make

Contribute
----------

- Issue Tracker: https://github.com/alourei/NEXTSim/issues
- Source Code: https://github.com/alourei/NEXTSim

Support
-------

If you are having issues, please let us know.

License
-------

NEXTSim is distributed under the terms of the GNU Lesser General Public Licence version 3 (LGPL)