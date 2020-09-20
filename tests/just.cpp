#include <iostream>
#include <cassert>
#include <math.h>

#include "scala_file.hpp"
using namespace scala;

using namespace std;

int main(int, char**) {
    ifstream test_scale; 
    test_scale.open("scales/just.scl");
    scala::scale loaded_scale = scala::read_scl(test_scale);

    /*
        Ensure that ratios are loaded correctly in a just-intonation files
    */

    assert(loaded_scale.get_scale_length() == 7); // Note that we add the first degree explicitly.
    for (int i = 0; i < loaded_scale.get_scale_length(); i++ ){
        double desired = 1.0 / (static_cast<double>(i) +1);
        assert(desired == loaded_scale.get_ratio(i));
    };

    test_scale.close();
    return 0;
}
