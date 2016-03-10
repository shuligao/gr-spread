/* -*- c++ -*- */
/*
 * Copyright 2016 Paul David
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "gfsk.h"

gfskmod::gfskmod(const int samp_sym,
                 const int delay,
                 const double bw,
                 const double bt)
    : _samp_sym(samp_sym), _delay(delay),
      _bw(bw), _bt(bt)
{
}

std::complex<double> gfskmod::modulate(uint8_t &bit)
{
}

carray_t gfskmod::modulate_block(uarray_t &array)
{
}

gfskdemod::gfskdemod(const int samp_sym,
                     const int delay,
                     const double bw,
                     const double bt)
    : _samp_sym(samp_sym), _delay(delay),
      _bw(bw), _bt(bt)
{
}

uint8_t gfskdemod::demodulate(carray_t &samples)
{
}

uarray_t gfskdemod::demodulate_block(carray_t &array)
{
}
