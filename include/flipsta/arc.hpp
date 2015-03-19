/*
Copyright 2014, 2015 Rogier van Dalen.

This file is part of the Flipsta library.

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FLIPSTA_ARC_HPP_INCLUDED
#define FLIPSTA_ARC_HPP_INCLUDED

#include "core.hpp"

namespace flipsta {

/** \brief
An arc type for automata that stores its data explicitly.

And arc is characterised by three pieces of information, which this class holds
explicitly:
\li The state it comes from, the source state.
\li The state it goes to, the destination state.
\li The label on the arc.

\tparam State The type of the states.
\tparam Label The type of the label.
*/
template <class State_, class Label_> class ExplicitArc {
public:
    /// The type of the states.
    typedef State_ State;
    /// The type of the label.
    typedef Label_ Label;
private:
    State source_;
    State destination_;
    Label label_;

public:
    /** \brief
    Construct with the data explicitly.

    \param direction
        Indicate that the second argument is the source and the third the
        destination.
    \param source
        The source state.
    \param destination
        The destination state.
    \param label
        The label on the arc.
    */
    ExplicitArc (Forward const & direction,
        State const & source, State const & destination, Label const & label)
    : source_ (source), destination_ (destination), label_ (label) {}

    /** \brief
    Construct with the data explicitly.

    \param direction
        Indicate that the second argument is the destination and the third the
        source.
    \param destination
        The destination state.
    \param source
        The source state.
    \param label
        The label on the arc.
    */
    ExplicitArc (Backward const & direction,
        State const & destination, State const & source, Label const & label)
    : source_ (source), destination_ (destination), label_ (label) {}

    /** \brief
    Construct by copying the data from another arc.
    */
    template <class OtherArc> explicit ExplicitArc (OtherArc const & other)
    : source_ (other.state (backward)), destination_ (other.state (forward)),
        label_ (other.label()) {}

    /**
    \brief Returns the source state.
    */
    State const & state (Backward) const { return source_; }

    /**
    \brief Returns the destination state.
    */
    State const & state (Forward) const { return destination_; }

    /**
    \brief Returns the label on the arc.
    */
    Label const & label() const { return label_; }
};

} // namespace flipsta

#endif // FLIPSTA_ARC_HPP_INCLUDED
