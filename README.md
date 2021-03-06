# keyvi

A key value index based on finite state technology.

## Install

### Quick

Precompiled binaries for Ubuntu 14.04LTS are available at the [keyvi PPA](https://launchpad.net/~hendrik-muhs/+archive/ubuntu/keyvi). To install use: 

    sudo add-apt-repository ppa:hendrik-muhs/keyvi
    sudo apt-get update
    sudo apt-get install keyvi python-keyvi

### From Source

The core part is a C++ header-only library, but the TPIE 3rdparty library needs to be compiled once. The commandline
tools are also part of the C++ code. For instructions check the [Readme](/keyvi/README.md) file.

For the python extension pykeyvi check the [Readme](/pykeyvi/README.md) file in the pykeyvi subfolder.

## Usage

  * Howtos
    * [Compiling Dictionaries/Indexes](/doc/usage/Building keyvi dictionaries.md)
    * Pykeyvi
      * [Compiling](/doc/usage/Building keyvi dictionaries with python.md)
  * [Crashcourse](/doc/usage/Crashcourse.md)
  
## Development
 
  * [Build/Packaging](/doc/development/Packaging keyvi.md)
  
## Internals
  
  * [Construction Basics](/doc/algorithm/Construction-Basics.md)
  * [Persistence Basics](/doc/algorithm/Persistence-Basics.md)
  * [Minimization](/doc/algorithm/Minimization.md)
  * [Scaling](/doc/algorithm/Scaling.md)
  * [Extensibility](/doc/algorithm/Extensibility.md)

If you like to go deep down in the basics, keyvi is inspired by the following 2 papers:

  * Sparse Array (See Storing a Sparse Table, Robert E. Tarjan et al. http://infolab.stanford.edu/pub/cstr/reports/cs/tr/78/683/CS-TR-78-683.pdf)
  * Incremental, which means minimization is done on the fly (See Incremental Construction of Minimal Acyclic Finite-State Automata, J. Daciuk et al.: http://www.mitpressjournals.org/doi/pdf/10.1162/089120100561601)
  
## Licence and 3rdparty dependencies

keyvi is licenced under apache license 2.0, see [licence](LICENSE) for details.

In addition keyvi uses 3rdparty libraries which define their own licence. Please check their respective licence. 
The 3rdparty libraries can be found at [keyvi/3rdparty](/keyvi/3rdparty).
