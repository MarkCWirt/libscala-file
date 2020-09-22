#include <iostream>
#include <cassert>
#include <math.h>

#include "scala_file.hpp"
using namespace scala;

using namespace std;

int main(int, char**) {
  ifstream test_kbm; 
  test_kbm.open("kbm/12-tet.kbm");
  scala::kbm loaded_kbm = scala::read_kbm(test_kbm);

  /*
    The is a test of the KBM parser.
  */

  assert(loaded_kbm.map_size == 12);
  assert(loaded_kbm.first_note == 0);
  assert(loaded_kbm.last_note == 127);
  assert(loaded_kbm.middle_note == 60);
  assert(loaded_kbm.reference_note == 69);
  assert(loaded_kbm.reference_frequency == 440.0);
  assert(loaded_kbm.octave_degree == 12);

  for (int i = 0; i < 12; i++){
    assert(loaded_kbm.mapping[i] == i);
  }
  test_kbm.close();
  return 0;
}
