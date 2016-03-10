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

#include "buffers.h"

#include <complex>
#include <vector>
#include <map>

using carray_t = std::vector<std::complex<double>>;

/*
 * Frequency hopping synchronizer
 */
class fh_sync {
public:
    // arguments for the synchronizer
    struct args_t {
        std::map<size_t, double> &hops;
        carray_t &pn_seq;

        double freq;

        size_t buffer_len;

        uint32_t samp_rate;
        uint32_t samps_hop;
        uint32_t samps_sym;
    };

    fh_sync(const args_t &args);

    // generate a referenced hop signal
    void generate_reference();

    // execute synchronizer on a single sample
    void execute(std::complex<double> &sample);

    // execute the timing synchronization
    // on a block of samples
    void execute_block(carray_t &data);

    // try to detect the signal preamble
    void seekpn();

    // use the preamble to correct for
    // carrier offset
    void preamble();

    // try to recover the payload
    void payload();

    // calculate the dot products
    void dotprod();

private:
    std::map<size_t, double> hops;
    circ<std::complex<double>> buffer;

    double freq;
    size_t buffer_len;

    uint32_t samp_rate;
    uint32_t samps_hop;
    uint32_t samps_sym;

    carray_t pn_seq, reference;

    enum class sync_state_t {
        SEEK, ALIGN, PAYLOAD
    } state;
};

/*
 * Direct-sequence synchronizer
 */
class ds_sync {
public:
    ds_sync();
private:
};
