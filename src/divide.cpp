#include "divide.h"
#include <random>
#include <functional>
Map basic_divide(Map& map, float probabilites[][3], std::ranlux48 gen) {
  Map dmap = map.divide();
  for (int y = 0; y < dmap.height(); y++) {
    for (int x = 0; x < dmap.width(); x++) {
      int val = map.get(x/2, y/2) != 0;
      auto neighbors = map.get_quarter_neighbors<true>(x, y);
      int sum = (neighbors[0] != 0) + (neighbors[1] != 0);
      float prob = probabilites[val][sum];
      float rand = std::generate_canonical<double, 10>(gen);
      if (rand < prob) val = !val;
      dmap.set(x, y, val);
    }
  }

  return dmap;
};
