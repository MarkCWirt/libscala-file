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
    test_scale.open("scales/valid.scl");
    scala::scale loaded_scale = scala::read_scl(test_scale);

    /*
        Intervals from the scala site
    */

    assert(loaded_scale.get_scale_length() == 10); // Note that we add the first degree explicitly.

    // The only interesting interval in this set -- something that we haven't seen in the
    // other tests -- if the entry for negative five cents.
   
    assert(loaded_scale.get_ratio(5) == calculate_cents(-5.0));

    test_scale.close();
    return 0;
}
