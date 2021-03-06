#ifndef LE_BITMAP_H_
#define LE_BITMAP_H_

#include <string>
#include "graphic/color.h"

namespace le {

class Bitmap
{
 public:
  Bitmap(int width, int height, int depth);
  virtual ~Bitmap();

 public:
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  int GetDepth() const { return depth_; }
  const unsigned char* GetData() const { return data_; }

  void SetPixel(int x, int y, Color color);
  void WriteBitmapFile(const std::string& filename);

 private:
  unsigned char* data_;
  
  int width_;
  int height_;
  int depth_;
  
};


}  // le

#endif /* LE_BITMAP_H_ */
