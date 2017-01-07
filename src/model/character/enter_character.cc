#include "enter_character.h"

#include "model/word.h"
#include "space_character.h"
#include "basic_character.h"
#include "model/text_run.h"
#include "model/paragraph.h"
#include "controller/enter_char_controller.h"
#include <typeinfo>

namespace le {

namespace {

void InsertWordInternal(Paragraph* paragraph, Character* character)
{
  auto last_word = paragraph->GetLastWord();
  
  if( last_word == nullptr ) {
    last_word = new Word();
    paragraph->InsertWord(last_word, nullptr);
    last_word->InsertCharacter(character, nullptr);
  } else {
    
    auto prev_char = last_word->GetLastCharacter();
    if( typeid(*character) == typeid(BasicCharacter) ) {
      if( typeid(*prev_char) == typeid(BasicCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if ( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
    } else if (typeid(*character) == typeid(SpaceCharacter) ) {
      if( typeid(*prev_char) == typeid(BasicCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
      } else if( typeid(*prev_char) == typeid(SpaceCharacter) ) {
        last_word->InsertCharacter(character, nullptr);
        last_word->Split(character);
      } else {

      }
      
    } else {

    }
  }

}

void InsertRunInternal(Paragraph* paragraph, Character* character)
{
  auto cached = Run::GetCachedRun();
  if( cached ) {
    paragraph->InsertRun(cached, nullptr);
  }
  
  auto last_run =  paragraph->GetLastRun();

  if(last_run == nullptr) {
    last_run = new TextRun();
    paragraph->InsertRun(last_run, nullptr);
  }
  
  last_run->InsertCharacter(character, nullptr);

  Run::SetCachedRun(nullptr);
}

}

EnterCharacter::EnterCharacter(EnterRun* enter_run_)
    : Character('\n')
{
  SetRun(enter_run_);
}

EnterCharacter::~EnterCharacter()
{}

void EnterCharacter::InsertChar(Character* character)
{
  auto paragraph = GetRun()->GetParagraph();

  InsertWordInternal(paragraph, character);
  InsertRunInternal(paragraph, character);

  
}

void EnterCharacter::SetBold(bool bold)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetBold(bold);
}

void EnterCharacter::SetItalic(bool italic)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetItalic(italic);
}

void EnterCharacter::SetSize(int size)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetSize(size);
}

std::unique_ptr<Controller> EnterCharacter::GetController()
{
  return std::unique_ptr<EnterCharController>(new EnterCharController(*this));
}


}  // le
