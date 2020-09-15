#include <iostream>
#include <cassert>
#include <math.h>

#include "scala_file.hpp"
using namespace scala;

using namespace std;

int main(int, char**) {
    ifstream test_scale; 
    test_scale.open("scales/mixed.scl");
    scala::scale loaded_scale = scala::read_file(test_scale);

    /*
       Load a scale that has both cents and ratios.
    */

    assert(loaded_scale.get_scale_length() == 3);                // Note that we add the first degree explicitly.
    assert(loaded_scale.get_ratio(0) == 1);                  // Implicit. It's always 1
    assert(loaded_scale.get_ratio(1) == pow(2.0, 1.0/6.0));  // 200 cents is the sixth root of 2 
    assert(loaded_scale.get_ratio(2) == 2);                  // Defined in scale as 2/1
    test_scale.close();
    return 0;
}
