/*
-----------------------------------

C++ to Python plotting test

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>

namespace py = pybind11;

// Function that generates the data
std::vector<double> generate_data(int n) {
    std::vector<double> data(n);
    for (int i = 0; i < n; i++) {
        data[i] = i * i;
    }
    return data;
}

// Function that creates the Python bindings
PYBIND11_MODULE(my_module, m) {
    m.def("generate_data", &generate_data, "Generate data");
}