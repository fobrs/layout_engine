#include "word_view.h"

#include <iostream>

#include "model/word.h"
#include "model/character/character.h"

#include "graphic/canvas.h"
#include "view/line_view.h"

namespace le {

WordView::WordView(Word& word)
    : word_(word)
{}

WordView::~WordView()
{}

void WordView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());

  
  int baseline = static_cast<LineView*>(GetParent())->GetBaseline();

  auto x = 0;
  for( auto ch = word_.GetFirstCharacter() ; ch ; ch = ch->GetNextWordCharacter() ) {
    auto glyph = ch->GetGlyph();
    //canvas.DrawGlyph(Point(x + glyph.GetLeft(), baseline - glyph.GetTop()), glyph);
    canvas.DrawGlyph(Point(x, baseline), glyph);
    x += glyph.GetAdvanceX();
  }

  canvas.Restore();
}

void WordView::Layout()
{
  SetY(0);
  SetWidth(word_.GetWordWidth());
  SetHeight(word_.GetWordHeight());

  auto word_index = GetIndex();
  auto word_width = word_.GetWordWidth();
  auto space_width = word_.GetSpaceWidth();

  if( word_index == 0 ) {
    SetX(0);
    if( GetParent()->GetWidth() < word_width ) {
      
    }
  }
  else {
    auto prev = GetParent()->GetChildAt(word_index - 1);
    auto x = prev->GetX() + prev->GetWidth();
    if( x + word_width - space_width < GetParent()->GetWidth() ) {
      SetX(x);
    }
    else {
      //next line
      auto nextline = GetParent()->GetNextParent();

      auto index = 0;
      for( ; index < GetParent()->GetChildCount() ; ++index )
        if( GetParent()->GetChildAt(index) == this )
          break;

      for( int i = GetParent()->GetChildCount() - 1 ; i >= index ; --i ) {
        auto word = GetParent()->GetChildAt(i);
        GetParent()->RemoveChildAt(i);
        nextline->AddChildAt(0, word);
      }
      
      return;
    }
  }

  for( auto index = 0; index < GetChildCount() ; ++index )
    GetChildAt(index)->Layout();
}

}  // le
