#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <bitset>

using map_int = unsigned char;

class Map {
public:
  enum BoundModeEnum {
    Wrap,
    Clamp,
    Value
  };

  Map(int width, int height, BoundModeEnum mode, map_int value = 0)
      : width_(width), height_(height), mode_(mode), value_(value) {
        array_ = std::vector<map_int>(width_ * height_, 0);
      }

  Map divide() {
    return Map(width_ * 2, height_ * 2, mode_, value_);
  }

  int width() {
    return width_;
  }

  int height() {
    return height_;
  }

  void save_pgm(std::string file_name) {
    std::ofstream file;
    file.open(file_name);
    file << "P5\n" + std::to_string(width_) + " " + std::to_string(height_) + "\n255\n";
    file.close();
    file.open(file_name, std::ios::binary | std::ios::app);
    file.write((char*)&array_[0], width_ * height_ * sizeof(map_int));
    file.close();
  }

  void save_pbm(std::string file_name, map_int threshold = 0) {
    int size = width_ * height_;

    std::ofstream file;
    file.open(file_name);
    file << "P4\n" + std::to_string(width_) + " " + std::to_string(height_) + "\n";
    file.close();
    file.open(file_name, std::ios::binary | std::ios::app);

    int i = 0;
    char byte = 0;
    for (int y = 0; y < height_; y++) {
      for (int x = 0; x < width_; x+=8) {
        byte = 0;
        for (int i = 0; i < 8 && x + i < width_; i++) {
          byte |= (get(x+i, y) > threshold) << (7-i);
        }
        file.write(&byte, 1);
      }
    }
    file.close();
  }

  void set(int x, int y, map_int val) {
    array_[x + y * width_] = val;
  }

  map_int get(int x, int y) {
    return array_[x + y * width_];
  }

  map_int at(int x, int y) {
    switch (mode_) {
      case Value:
        if (x < 0 || x >= width_) return value_;
        if (y < 0 || y >= height_) return value_;
        break;
      case Clamp:
        if (x < 0) x = 0;
        if (x >= width_) x = width_-1;
        if (y < 0) y = 0;
        if (y >= height_) y = height_-1;
        break;
      case Wrap:
        if (x < 0) x += width_;
        if (x >= width_) x -= width_;
        if (y < 0) y += height_;
        if (y >= height_) y -= height_;
        break;
    }

    return get(x, y);
  }

  template<bool bounds_check = false>
  std::vector<map_int> get_quarter_neighbors(int qx, int qy) {
    // quarter cell (qx, qy) is inside cell (x, y)
    int x = qx/2;
    int y = qy/2;

    // cells (nx, y) and (x, ny) border quarter cells (qx, qy)
    int nx = x + 2 * (qx % 2) - 1;
    int ny = y + 2 * (qy % 2) - 1;

    if (bounds_check) {
      return {at(nx, y), at(x, ny)};
    }
    return {get(nx, y), get(x, ny)};
  }

private:
  std::vector<map_int> array_;
  int width_;
  int height_;
  BoundModeEnum mode_;
  map_int value_;
};

#endif
