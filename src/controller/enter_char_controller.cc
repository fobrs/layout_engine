#include "enter_char_controller.h"

#include "model/paragraph.h"
#include "model/character/basic_character.h"
#include "model/character/space_character.h"
#include "model/text_run.h"

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


EnterCharController::EnterCharController(EnterCharacter& enter_char)
    : enter_char_(enter_char)
{}
EnterCharController::~EnterCharController()
{}

void EnterCharController::InsertText(std::string text)
{

}

void EnterCharController::InsertChar(Character* character)
{
  auto paragraph = enter_char_.GetRun()->GetParagraph();

  InsertWordInternal(paragraph, character);
  InsertRunInternal(paragraph, character);
}

void EnterCharController::SetBold(bool bold)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetBold(bold);
}

void EnterCharController::SetItalic(bool italic)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetItalic(italic);
}

void EnterCharController::SetSize(int size)
{
  auto cached = Run::GetCachedRun();
  if( cached == nullptr ) {
    Run::SetCachedRun(new TextRun());
    cached = Run::GetCachedRun();
  }

  cached->GetRunProp().SetSize(size);
}

void EnterCharController::SetPageSize(int width, int height)
{
  auto paragraph = enter_char_.GetRun()->GetParagraph();
  auto& sectionprop = paragraph->GetParent()->GetSectionProp();
  sectionprop.GetPageSize().SetWidth(width);
  sectionprop.GetPageSize().SetHeight(height);
}

}  // le
