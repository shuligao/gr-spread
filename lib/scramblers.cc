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

#include "scramblers.h"

#include <cstddef>
#include <stdexcept>
#include <numeric>

static void invert(uarray_t::iterator begin,
                   uarray_t::iterator end)
{
    for (auto it = begin; it != end; it++)
        *it = 1 - *it;
}

fh_scramble::fh_scramble(const uarray_t &poly,
                         const uarray_t &init) :
    registers(init), poly(poly), accum(0)
{
    if (poly.size() != registers.size())
        throw std::runtime_error("Polynomial and register sizes do not match");
}

uarray_t fh_scramble::scramble(const uarray_t &input)
{
    uarray_t output(input.size());

    // Push each bit into the registers
    // and store the corresponding output
    for (size_t i = 0; i < input.size(); i++)
        output[i] = push(input[i]);

    bse_encode(output);

    return output;
}

uarray_t fh_scramble::descramble(const uarray_t &input)
{
    uarray_t output(input);

    bse_decode(output);

    for (size_t i = 0; i < input.size(); i++)
        output[i] = push(input[i]);

    return output;
}

void fh_scramble::bse_encode(uarray_t &block)
{
    int bias = std::accumulate(block.begin(), block.end(), 0);

    if (accum * bias > 0) {
        invert(block.begin(), block.end());
        accum *= -1;
        accum += bias;
    }
}

void fh_scramble::bse_decode(uarray_t &block)
{
    if (block[0] == 1)
        invert(block.begin()+1, block.end());
}

uint8_t fh_scramble::push(uint8_t bit)
{
    uint8_t result = compute();
    registers.push(result);
    return (result ^ bit) & 1;
}

uint8_t fh_scramble::compute()
{
    uint8_t output = 0;
    for (size_t i = 0; i < registers.size(); i++)
        output ^= (registers.at(i) & poly[i]);

    return output & 1;
}

ds_scramble::ds_scramble(const uarray_t &poly,
                         const uarray_t &init) :
    registers(init), poly(poly)
{
    if (poly.size() != registers.size())
        throw std::runtime_error("Polynomial and register sizes do not match");
}

uarray_t ds_scramble::scramble(uarray_t &input)
{
    uarray_t output(input.size());

    for (size_t i = 0; i < input.size(); i++) {
        output[i] = (input[i] ^ compute()) & 1;
        push(output[i]);
    }

    return output;
}

uarray_t ds_scramble::descramble(uarray_t &input)
{
    uarray_t output(input.size());

    for (size_t i = 0; i < input.size(); i++) {
        output[i] = (input[i] ^ compute()) & 1;
        push(input[i]);
    }

    return output;
}

uint8_t ds_scramble::compute()
{
    uint8_t output = 0;
    for (size_t i = 0; i < registers.size(); i++)
        output ^= (registers.at(i) & poly[i]);

    return output & 1;
}

void ds_scramble::push(uint8_t bit)
{
    registers.push(bit);
}
