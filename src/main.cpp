#include <map.h>
#include <iostream>
#include <fstream>

int main() {
  Map m{2, 2, Map::BoundModeEnum::Clamp};
  m.set(0, 0, 1);
  m.set(1, 0, 2);
  m.set(0, 1, 4);
  m.set(1, 1, 5);
  m.save_pbm("test.pbm", 3);
  return 0;
}
