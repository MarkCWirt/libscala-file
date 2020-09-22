#include <iostream>
#include <cassert>
#include <math.h>

#include "scala_file.hpp"
using namespace scala;

using namespace std;

int main(int, char**) {
    ifstream test_scale; 
    test_scale.open("scales/tet-12.scl");
    scala::scale loaded_scale = scala::read_scl(test_scale);

    /*
        This test ensures the correct number of entries and that all
        of the entries are correct numerically for a cent input 
    */

    assert(loaded_scale.get_scale_length() == 13); // Note that we add the first degree explicitly.
    for (int i = 0; i < loaded_scale.get_scale_length(); i++ ){
        double desired = pow(pow(2.0, 1.0/12.0), i);
        assert(desired == loaded_scale.get_ratio(i));
    };

    test_scale.close();
    return 0;
}
