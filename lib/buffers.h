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

/* Circular buffer */
template<typename T>
class circ {
public:
    circ(const std::vector<T> &init)
        : array(init), head(0), tail(0)
    {}

    circ(std::vector<T> &&init)
        : array(std::move(init))
    {}

    circ(const size_t len)
        : array(len, T(0)), head(0), tail(0)
    {}

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

    void read(T& buffer)
    {
        for (size_t i = 0; i < array.size(); i++)
            buffer[i] = at(i);
    }

private:
    size_t head, tail;

    std::vector<T> array;
};
