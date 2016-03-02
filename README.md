# gr-spread
A spread spectrum out-of-tree (OOT) module for GNU Radio.
Includes frequency-hopping spread spectrum (FHSS) and
direct-sequence spread spectrum (DHSS) blocks.

Keep in mind that it is possible to make spread spectrum techniques work
in GNU Radio without creating new blocks. However, it takes a bit more effort
to figure out which blocks are better suited for this purpose.

The code provided operates in a similar fashion to FHSS and DSSS specifications described in the 802.11 standard.


Install
=======
Follows the standard procedures for a GNU Radio OOT module:

    $ git clone https://github.com/DaulPavid/gr-spread
    $ cd gr-spread
    $ mkdir build && cd build
    $ cmake -DCMAKE_INSTALL_PREFIX=/to/gnuradio/target/dirs ../
    $ make test
    $ make install

License
=======

```
Copyright 2016 Paul David

This is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this software; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street,
Boston, MA 02110-1301, USA.
```
