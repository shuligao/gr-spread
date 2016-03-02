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

#include <vector>
#include <cstdint>

using uarray_t = std::vector<uint8_t>;
using size_t = std::size_t;

/* Circular buffer */
template<typename T>
class circ {
public:
    circ(const uarray_t &init)
        : array(init), head(0), tail(0)
    {
    }

    void push(T val)
    {
        tail = ++tail % array.size();

        if (full())
            head = ++head % array.size();

        array[tail++ % array.size()] = val;
    }

    T pop()
    {
        if (head == tail)
            return nullptr;

        head = ++head % array.size();
        return array[head];
    }

    const T& front()
    {
        return array[head];
    }

    const T& at(size_t i)
    {
        return array[(head + i) % array.size()];
    }

    bool empty()
    {
        return head == tail;
    }

    bool full()
    {
        return (tail + 1) % array.size() == head;
    }

    size_t size()
    {
        return array.size();
    }

    void clear()
    {
        head = 0;
        tail = 0;
    }

private:
    size_t head, tail;

    std::vector<T> array;
};

/*
 *  Data scramblers/descramblers for synchronization
 *  Assumes that synchronization was already performed
 */
class fh_scramble
{
public:
    fh_scramble(const uarray_t &poly,
                const uarray_t &init);

    uarray_t scramble(const uarray_t &input);
    uarray_t descramble(const uarray_t &input);

private:
    uarray_t poly;
    circ<uint8_t> registers;

    int accum;

    // Push a value onto the LFSR
    uint8_t push(uint8_t bit);

    // Bias-suppression encoding (BSE) meant to remove
    // DC bias introduced by the data
    void bse_encode(uarray_t &block);
    void bse_decode(uarray_t &block);

    // compute scrambler output
    uint8_t compute();
};

/*
 *  Data scrambler/descrambler
 *  This pair is self-synchronizing
 */
class ds_scramble
{
public:
    ds_scramble(const uarray_t &poly,
                const uarray_t &init);

    uarray_t scramble(uarray_t &input);
    uarray_t descramble(uarray_t &input);


private:
    uarray_t poly;
    circ<uint8_t> registers;

    // Push a value onto the LFSR
    void push(uint8_t bit);

    // compute scrambler output
    uint8_t compute();
};
