/* -*- c++ -*- */

#define SPREAD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "spread_swig_doc.i"

%{
#include "spread/fhss_framer.h"
#include "spread/fhss_deframer.h"
%}


%include "spread/fhss_framer.h"
GR_SWIG_BLOCK_MAGIC2(spread, fhss_framer);
%include "spread/fhss_deframer.h"
GR_SWIG_BLOCK_MAGIC2(spread, fhss_deframer);
