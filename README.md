Kicad Tools
-----------

Kicad Tools is a set of tolls which aims to extend kicad functionality.

Licensing
---------

Kicad Tools is provided under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your option) any
later version.

Wiki
----

More details  [here](https://hephaistos.lpp.polytechnique.fr/redmine/projects/kicadtools/wiki)

How to build
------------

To build it on linux you can look here https://hephaistos.lpp.polytechnique.fr/redmine/projects/kicadtools/wiki/Linux_setup

If you can't access to it, first you will need a working qt5 kit with all the development packages.
 Step 1:
  Get and install SocExplorer
```Bash
  hg clone https://hephaistos.lpp.polytechnique.fr/rhodecode/HG_REPOSITORIES/LPP/INSTRUMENTATION/kicadtools kicadtools
  cd kicadtools
  qmake-qt5
  make
  sudo make install
```


Bug repports
------------

To repport any bug you can either send a [mail](mailto:alexis.jeandet@member.fsf.org) or repport an issue [here](https://hephaistos.lpp.polytechnique.fr/redmine/projects/kicadtools/issues)

