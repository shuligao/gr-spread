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

using size_t = std::size_t;

/* Simple FIR filter */
template<typename T>
class fir {
public:
    fir(const std::vector<T> &init)
        : coeff(init)
    {}

    fir(std::vector<T> &&init)
        : coeff(std::move(init))
    {}

    fir(const size_t len)
        : coeff(len, T(0))
    {}

private:
    std::vector<T> coeff;
};
