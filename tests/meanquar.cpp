#include <iostream>
#include <cassert>
#include <math.h>

#include "scala_file.hpp"
using namespace scala;

using namespace std;

static double calculate_cents(double cents){
    /*
      Just a helper function to calculate ratios based on cent values
    */
    return pow(pow(2.0, 1.0/12.0), cents/100.0);
}

int main(int, char**) {
    ifstream test_scale; 
    test_scale.open("scales/meanquar.scl");
    scala::scale loaded_scale = scala::read_scl(test_scale);

    /*
        This scale is taken from the Scala site and is given as an example of a
        valid file. We should be able to read it.
    */

    assert(loaded_scale.get_scale_length() == 13); // Note that we add the first degree explicitly.
   
    // We're just going to do this one by hand
    assert(loaded_scale.get_ratio(0) == 1.0);
    assert(loaded_scale.get_ratio(1) == calculate_cents(76.04900));
    assert(loaded_scale.get_ratio(2) == calculate_cents(193.15686));
    assert(loaded_scale.get_ratio(3) == calculate_cents(310.26471));
    assert(loaded_scale.get_ratio(4) == 5.0/4.0);
    assert(loaded_scale.get_ratio(5) == calculate_cents(503.42157));
    assert(loaded_scale.get_ratio(6) == calculate_cents(579.47057));
    assert(loaded_scale.get_ratio(7) == calculate_cents(696.57843));
    assert(loaded_scale.get_ratio(8) == 25.0/16.0);
    assert(loaded_scale.get_ratio(9) == calculate_cents(889.73529));
    assert(loaded_scale.get_ratio(10) == calculate_cents(1006.84314));
    assert(loaded_scale.get_ratio(11) == calculate_cents(1082.892));
    assert(loaded_scale.get_ratio(12) == 2.0/1.0);

    test_scale.close();
    return 0;
}
