/* -*- c++ -*- */
/*
 * Copyright 2016 Paul David.
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

#include <gnuradio/attributes.h>
#include <cppunit/TestAssert.h>
#include "scramblers.h"
#include "qa_scramblers.h"

namespace gr {
  namespace spread {

    void
    qa_scramblers::t1()
    {
        uarray_t data{1, 0, 0, 0,
                      1, 1, 1, 0,
                      1, 1, 0, 1,
                      0, 1, 0, 1,
                      1, 0, 0, 0,
                      1, 1, 1, 0};

        uarray_t poly{1, 0, 0, 1, 0, 0, 1};
        uarray_t init{1, 1, 1, 1, 1, 1, 1};

        fh_scramble scrambler(poly, init);
        fh_scramble descrambler(poly, init);

        uarray_t scrambled_data = scrambler.scramble(data);
        uarray_t descrambled_data = descrambler.descramble(scrambled_data);

        for (size_t i = 0; i < data.size(); i++)
            CPPUNIT_ASSERT_EQUAL(data[i], descrambled_data[i]);

        std::cout << "FHSS scrambler test passed..." << std::endl;
    }

    void
    qa_scramblers::t2()
    {
        uarray_t data{1, 0, 0, 0,
                      1, 1, 1, 0,
                      1, 1, 0, 1,
                      0, 1, 0, 1,
                      1, 0, 0, 0,
                      1, 1, 1, 0,
                      1, 0, 1, 0};

        uarray_t poly{1, 0, 0, 1, 0, 0, 1};
        uarray_t init{1, 1, 1, 1, 1, 1, 1};

        ds_scramble scrambler(poly, init);
        ds_scramble descrambler(poly, init);

        uarray_t scrambled_data = scrambler.scramble(data);
        uarray_t descrambled_data = descrambler.descramble(scrambled_data);

        for (size_t i = 0; i < data.size(); i++)
            CPPUNIT_ASSERT_EQUAL(data[i], descrambled_data[i]);

        std::cout << "DSSS scrambler test passed..." << std::endl;
    }

  } /* namespace spread */
} /* namespace gr */

