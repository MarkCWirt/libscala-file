#include <iostream>
#include <cassert>
#include <math.h>

#include "scala_file.hpp"

using namespace scala;

using namespace std;

int main(int, char**) {
  ifstream test_kbm; 
  test_kbm.open("kbm/12-tet-xs.kbm");
  scala::kbm loaded_kbm = scala::read_kbm(test_kbm);

  /*
    This test ensures that x's are honored in the KBM 
    file.
  */

  assert(loaded_kbm.map_size == 12);
  assert(loaded_kbm.first_note == 0);
  assert(loaded_kbm.last_note == 127);
  assert(loaded_kbm.middle_note == 60);
  assert(loaded_kbm.reference_note == 69);
  assert(loaded_kbm.reference_frequency == 440.0);
  assert(loaded_kbm.octave_degree == 12);

  for (size_t i = 0; i < 12; i++){
    if (i % 2 == 0){
      assert(loaded_kbm.mapping[i] == i);
    } else {
      assert(loaded_kbm.mapping[i] == KBM_NON_ENTRY);
    }
  }

  test_kbm.close();
  return 0;
}
