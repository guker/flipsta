/*
Copyright 2015 Rogier van Dalen.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/** \file
Test flipsta::draw.

This outputs a text file in Graphviz dot format.
This test does not actually test whether the format is correct at all, just
whether draw() runs.
If no argument is given on the command line, then the output goes into a
stringstream and then disappears.
If one argument is given on the command line, this is the name of the output
file.
This can then be run through Graphviz dot, assuming it is installed, and it can
be checked that it actually does the right thing.
*/

#define BOOST_TEST_MODULE test_flipsta_draw
#include "utility/test/boost_unit_test.hpp"

#include "flipsta/draw.hpp"

#include <fstream>
#include <sstream>

#include "math/arithmetic_magma.hpp"
#include "math/sequence.hpp"
#include "math/product.hpp"
#include "flipsta/automaton.hpp"

BOOST_AUTO_TEST_SUITE(test_suite_draw)

BOOST_AUTO_TEST_CASE (testDraw) {
    using flipsta::forward;
    using flipsta::backward;

    typedef std::string State;
    typedef math::sequence <char> Sequence;
    typedef math::product <math::over <Sequence, float>> Label;
    typedef flipsta::Automaton <State, Label> Automaton;

    Automaton automaton;

    automaton.addState ("a");
    automaton.addState ("b");
    automaton.addState ("c'");
    automaton.addState ("d");
    automaton.addState ("e\"");
    automaton.addState ("f 2");
    automaton.addState ("g");
    automaton.addState ("h");

    automaton.setTerminalLabel (forward, "a", Label (Sequence(), 1));
    automaton.setTerminalLabel (forward, "c'", Label (Sequence(), 7));
    automaton.setTerminalLabel (backward, "c'", Label (Sequence(), 14));
    automaton.setTerminalLabel (backward, "f 2", Label (Sequence(), 1));

    automaton.addArc ("a", "b", Label (Sequence (std::string ("a")), 1));
    automaton.addArc ("b", "c'", Label (Sequence (std::string ("qa")), 7));
    automaton.addArc ("a", "c'", Label (Sequence (std::string ("df")), 3));
    automaton.addArc ("a", "f 2", Label (Sequence (std::string ("\"")), 2));
    automaton.addArc ("f 2", "g", Label (
        Sequence (std::string ("\"quoted\"")), -7.7));
    automaton.addArc ("g", "a", Label (
        Sequence (std::string ("'quoted'")), 5));
    automaton.addArc ("g", "c'", Label (
        Sequence (std::string ("with spaces")), 0));

    automaton.addArc ("d", "e\"", Label (Sequence (std::string ("abc")), 21));
    automaton.addArc ("d", "a", Label (Sequence (std::string ("op")), 221));
    automaton.addArc ("d", "f 2", Label (Sequence (std::string ("k")), -0.05));
    automaton.addArc ("e\"", "f 2", Label (Sequence (std::string ("")), 3.5));

    int argc = boost::unit_test::framework::master_test_suite().argc;
    char ** argv = boost::unit_test::framework::master_test_suite().argv;
    if (argc == 2) {
        std::ofstream outputFile (argv [1]);
        flipsta::draw (outputFile, automaton);
    } else {
        assert (argc == 1);
        std::stringstream output;
        flipsta::draw (output, automaton);
    }
}

BOOST_AUTO_TEST_SUITE_END()
