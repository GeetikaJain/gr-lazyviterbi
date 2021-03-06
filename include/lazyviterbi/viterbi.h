/* -*- c++ -*- */
/*
 * Copyright 2018 Free Software Foundation, Inc.
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


#ifndef INCLUDED_LAZYVITERBI_VITERBI_H
#define INCLUDED_LAZYVITERBI_VITERBI_H

#include <limits>
#include <lazyviterbi/api.h>
#include <gnuradio/block.h>
#include <gnuradio/trellis/fsm.h>

namespace gr {
  namespace lazyviterbi {

    /*!
     * \brief A maximum likelihood decoder.
     *
     * This block implements the Viterbi algorithm in its classical form,
     * as way described e.g., in \cite Forney1973.
     *
     * It takes euclidean metrics as an input and produces decoded sequences.
     */
    class LAZYVITERBI_API viterbi : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<viterbi> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of lazyviterbi::viterbi.
       *
       * To avoid accidental use of raw pointers, lazyviterbi::viterbi's
       * constructor is in a private implementation
       * class. lazyviterbi::viterbi::make is the public interface for
       * creating new instances.
       *
       * \param FSM Trellis of the code.
       * \param K Length of a block of data.
       * \param S0 Initial state of the encoder (set to -1 if unknown).
       * \param SK Final state of the encoder (set to -1 if unknown).
       */
      static sptr make(const gr::trellis::fsm &FSM, int K, int S0, int SK);

      /*!
       * \return The trellis used by the decoder.
       */
      virtual gr::trellis::fsm FSM() const  = 0;
      /*!
       * \return The data blocks length considered by the decoder.
       */
      virtual int K()  const = 0;
      /*!
       * \return The initial state of the encoder (as given by the decoder, -1
       * if unspecified).
       */
      virtual int S0()  const = 0;
      /*!
       * \return The final state of the encoder (as given by the decoder, -1 if
       * unspecified).
       */
      virtual int SK()  const = 0;

      /*!
       * Set the trellis to be used.
       */
      virtual void set_FSM(const gr::trellis::fsm &FSM) = 0;
      /*!
       * Set the data blocks length to be used.
       */
      virtual void set_K(int K) = 0;
      /*!
       * Gives the initial state of the encoder to the decoder (set to -1 if unknown).
       */
      virtual void set_S0(int S0) = 0;
      /*!
       * Gives the final state of the encoder to the decoder (set to -1 if unknown).
       */
      virtual void set_SK(int SK) = 0;

      /*!
       * \brief Actual Viterbi algorithm implementation
       *
       * \param I The number of input sequences (e.g. 2 for binary codes).
       * \param S The number of states in the trellis.
       * \param O The number of output sequences (e.g. 4 for a binary code with a coding efficiency of 1/2).
       * \param NS Gives the next state ns of a branch defined by its initial state s
       * and its input symbol i : NS[s*I+i]=ns.
       * \param OS Gives the output symbol os of a branch defined by its initial state s
       * and its input symbol i : OS[s*I+i]=os.
       * \param PS Such that PS[s] contains all the previous states having a branch with state s.
       * \param PI Such that PI[s] contains all the inputs yielding to state s.
       * \param K Length of a block of data.
       * \param S0 Initial state of the encoder (set to -1 if unknown).
       * \param SK Final state of the encoder (set to -1 if unknown).
       * \param in Input euclidean metrics for the algorithm.
       * \param out Output decoded sequence.
       *
       */
      virtual void viterbi_algorithm(int I, int S, int O,
          const std::vector<int> &NS, const std::vector<int> &OS,
          const std::vector< std::vector<int> > &PS,
          const std::vector< std::vector<int> > &PI, int K, int S0, int SK,
          const float *in, unsigned char *out) = 0;
    };

  } // namespace lazyviterbi
} // namespace gr

#endif /* INCLUDED_LAZYVITERBI_VITERBI_H */

