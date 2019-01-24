//
//  module.cpp
//  tictactoe
//
//  Created by Semin Park on 23/01/2019.
//  Copyright © 2019 Semin Park. All rights reserved.
//

#include "pybind11/pybind11.h"            // Pybind11 import to define Python bindings
#include "pybind11/stl.h"                 // map, vector, etc
#define FORCE_IMPORT_ARRAY                // numpy C api loading
#include "xtensor-python/pytensor.hpp"    // Numpy bindings

#include "tictactoe.hpp"

PYBIND11_MODULE(TicTacToe, m)
{
    xt::import_numpy();
    m.doc() = "TicTacToe game environment";
    
    pybind11::class_<TicTacToe>(m, "TicTacToe")
    .def(pybind11::init<>())
    .def("reset", &TicTacToe::pyreset)
    .def("step", &TicTacToe::pystep, pybind11::arg("state"), pybind11::arg("action"))
    .def("place_possible", &TicTacToe::pyplace_possible, pybind11::arg("board"), pybind11::arg("player"), pybind11::arg("action"))
    .def("print", &TicTacToe::print, pybind11::arg("state"))
    .def_readonly("SIZE", &TicTacToe::size)
    ;
}
