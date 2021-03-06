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
If two arguments are given on the command line, the first is assumed to be the
index of the automaton that should be output to a file, and the second the name
of the output file.
This can then be run through Graphviz dot, assuming it is installed, and it can
be checked that it actually does the right thing.
*/

#define BOOST_TEST_MODULE test_flipsta_draw_examples
#include "utility/test/boost_unit_test.hpp"

#include "flipsta/draw.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include "example_automata.hpp"

BOOST_AUTO_TEST_SUITE(test_suite_draw_examples)

/**
Output \a automaton to a file if \a index is equal to \a automatonIndex, and to
a stringstream if not.
*/
template <class Automaton> inline
    void testDraw (int index, std::string const & fileName,
        int automatonIndex, Automaton const & automaton)
{
    if (index == automatonIndex) {
        std::ofstream outputFile (fileName.c_str());
        flipsta::draw (outputFile, automaton);
    } else {
        std::stringstream output;
        flipsta::draw (output, automaton);
    }
}

BOOST_AUTO_TEST_CASE (testDrawExamples) {
    int argc = boost::unit_test::framework::master_test_suite().argc;
    char ** argv = boost::unit_test::framework::master_test_suite().argv;

    int index = -1;
    std::string fileName;
    if (argc == 3) {
        index = std::atoi (argv [1]);
        fileName = argv [2];
        std::cout << "Outputting automaton " << index << " to file "
            << fileName << std::endl;
    }

    testDraw (index, fileName, 1, *acyclicExample());
    testDraw (index, fileName, 2, *acyclicSequenceExample());

    testDraw (index, fileName, 3, *prefixExample());
    testDraw (index, fileName, 4, *suffixExample());

    auto alphabet = std::make_shared <math::alphabet <std::string>>();
    testDraw (index, fileName, 5, *hypothesisExample (alphabet));
    testDraw (index, fileName, 6, *referenceExample (alphabet));
}

BOOST_AUTO_TEST_SUITE_END()
