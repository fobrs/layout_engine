#ifndef LE_CHARACTER_H_
#define LE_CHARACTER_H_

#include "type/container.h"

namespace le {

class CharacterView;
class Word;
class Run;
class Glyph;

class Character
{
 public:
  Character(char c);
  virtual ~Character();

  char GetChar() { return c_; }

  void SetRun(Run* run) { run_node_.SetContainer(run); }
  Run* GetRun() { return run_node_.GetContainer(); }

  void SetWord(Word* word) { word_node_.SetContainer(word); }
  Word* GetWord() { return word_node_.GetContainer(); }

  virtual void InsertChar(Character* character);

  void SetGlyph(Glyph* glyph){ glyph_ = glyph; }
  Glyph* GetGlyph(){ return glyph_; }

  Character* GetPrevWordCharacter();
  Character* GetNextWordCharacter();
  std::list<Character*>::iterator GetWordIterator() { return word_node_.GetIterator(); }
  void SetWordIterator(std::list<Character*>::iterator iter) { word_node_.SetIterator(iter); }

  Character* GetPrevRunCharacter();
  Character* GetNextRunCharacter();
  std::list<Character*>::iterator GetRunIterator() { return run_node_.GetIterator(); }
  void SetRunIterator(std::list<Character*>::iterator iter) { run_node_.SetIterator(iter); }

 private:
  CharacterView* view_;
  Glyph* glyph_;
  char c_;

  Node<Word, Character> word_node_;
  Node<Run, Character> run_node_;
};




}  // le

#endif /* LE_CHARACTER_H_ */
