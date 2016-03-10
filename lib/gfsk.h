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

#pragma once

#include "fir.h"

#include <complex>

using uarray_t = std::vector<uint8_t>;
using carray_t = std::vector<std::complex<double>>;

class gfskmod {
public:
    gfskmod(const int samp_sym,
            const int delay,
            const double bw,
            const double bt);

    // modulate a single bit
    std::complex<double> modulate(uint8_t &bit);

    // modulate a block of bits
    carray_t modulate_block(uarray_t &array);

private:
    const int _samp_sym;
    const int _delay;

    const double _bw;
    const double _bt;

    carray_t coeff;
};

class gfskdemod {
public:
    gfskdemod(const int samp_sym,
              const int delay,
              const double bw,
              const double bt);

    // demodulate a set of samples
    uint8_t demodulate(carray_t &samples);

    // demodulate a block of samples
    uarray_t demodulate_block(carray_t &array);

private:
    const int _samp_sym;
    const int _delay;

    const double _bw;
    const double _bt;

    carray_t coeff;
};
