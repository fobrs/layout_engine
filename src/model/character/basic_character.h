#ifndef LE_BASIC_CHARACTER_H_
#define LE_BASIC_CHARACTER_H_

#include "model/character/character.h"
#include "model/run.h"

namespace le {

class BasicCharacter : public Character
{
 public:
  BasicCharacter(char c);
  virtual ~BasicCharacter();
  
  CharacterView& GetView() override { return view_; }

  Character* GetNextCharacter() override;
  Character* GetPrevCharacter() override;

  Character* GetNextParagraphCharacter() override;
  Character* GetPrevParagraphCharacter() override;

  Paragraph* GetParagraph() override { return GetRun()->GetParagraph();}

  Character* RemoveThis() override;
  void InsertThis(Character* selected) override;

 private:
  CharacterView view_;
  
};


}  // le


#endif /* LE_BASIC_CHARACTER_H_ */

