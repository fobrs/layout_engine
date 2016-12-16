#ifndef LE_RENDER_TEXT_H_
#define LE_RENDER_TEXT_H_

#include "controller/paragraph_controller.h"

namespace le {

class RenderText
{
 public:
  RenderText();
  virtual ~RenderText();

  void InsertText(const std::string& text);
  void Layout();
  
 private:
  ParagraphController controller_;

};


}  // le

#endif /* LE_RENDER_TEXT_H_ */
