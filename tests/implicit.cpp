#include <iostream>
#include <cassert>
#include <math.h>

#include "scala_file.hpp"
using namespace scala;

using namespace std;

int main(int, char**) {
    ifstream test_scale; 
    test_scale.open("scales/implicit.scl");
    scala::scale loaded_scale = scala::read_file(test_scale);

    /*
        Ensure that ratios denominators are implicit
    */

    assert(loaded_scale.get_scale_length() == 6); //
    for (int i = 0; i < loaded_scale.get_scale_length(); i++ ){
        double desired = static_cast<double>(i) + 1;
        assert(desired == loaded_scale.get_ratio(i));
    };

    test_scale.close();
    return 0;
}
