#include "map.h" 
#include "divide.h" 
#include <random>

int main() {
  std::random_device rd;
  std::ranlux48 gen(rd());

  Map m{2, 2, Map::BoundModeEnum::Wrap};
  m.set(0, 0, 1);
  m.set(1, 1, 1);
  float probs[2][3] = {{0,0.2,0.9}, {0.7,0.2,0}};
  for (int i = 0 ; i < 10; i++) {
    m = basic_divide(m, probs, gen);
  }
  m.save_pbm("test.pbm");
  return 0;
}
