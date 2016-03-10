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

#include "sync.h"

static carray_t get_hop_samples(double &count,
                                const double freq,
                                const double rate,
                                const uint32_t sph)
{
    carray_t samples;
    for (size_t i = 0; i < sph; i++) {
        double phase = ++count*freq/rate;
        samples.push_back(std::polar(1.0, phase));
    }

    return samples;
}

void fh_sync::generate_reference()
{
    double count = 0;
    for (size_t i = 0; i < pn_seq.size(); i++) {
        carray_t hop_samples;
        hop_samples = get_hop_samples(count,
            hops.at(i), samp_rate, samps_hop);

        reference.insert(reference.end(),
            hop_samples.begin(), hop_samples.end());
    }
}

fh_sync::fh_sync(const args_t &args)
    : buffer(args.buffer_len)
{
    hops   = args.hops;
    pn_seq = args.pn_seq;

    freq      = args.freq;
    samp_rate = args.samp_rate;
    samps_sym = args.samps_sym;
    samps_hop = args.samps_hop;

    state = sync_state_t::SEEK;

    generate_reference();
}

void fh_sync::execute(std::complex<double> &sample)
{
    // push the sample into the buffer
    buffer.push(sample);

    switch (state) {
    case sync_state_t::SEEK:
        // try to find hop alignment
        // based on PN sequence
        seekpn();
        break;
    case sync_state_t::ALIGN:
        // Receive the preamble
        // and calculate errors and offsets
        preamble();
        break;
    case sync_state_t::PAYLOAD:
        payload();
        break;
    }
}

void fh_sync::execute_block(carray_t &data)
{
    for (auto &sample : data)
        execute(sample);
}

void fh_sync::seekpn()
{
}

void fh_sync::preamble()
{
}

void fh_sync::payload()
{
}

void fh_sync::dotprod()
{
    double sum = 0.0;
    for (size_t j = 0; j < pn_seq.size(); j++)
        sum += std::real(std::conj(pn_seq[j])*buffer.at(j));
}

ds_sync::ds_sync()
{
}
