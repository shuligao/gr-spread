/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_SPREAD_FHSS_FRAMER_H
#define INCLUDED_SPREAD_FHSS_FRAMER_H

#include <spread/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace spread {

    /*!
     * \brief <+description of block+>
     * \ingroup spread
     *
     */
    class SPREAD_API fhss_framer : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<fhss_framer> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of spread::fhss_framer.
       *
       * To avoid accidental use of raw pointers, spread::fhss_framer's
       * constructor is in a private implementation
       * class. spread::fhss_framer::make is the public interface for
       * creating new instances.
       */
      static sptr make(int test);
    };

  } // namespace spread
} // namespace gr

#endif /* INCLUDED_SPREAD_FHSS_FRAMER_H */

