#include "run_view.h"

#include "graphic/canvas.h"
#include "model/run.h"
#include "model/face/face_manager.h"

namespace le {

RunView::RunView(Run& run)
    : run_(run)
{}

RunView::~RunView()
{}

void RunView::Layout()
{
  view_util::SetHorizontalBlockPosition(this);
  for(int i=0 ; i<GetChildCount() ; i++ )
    GetChildAt(i)->Layout();

  SetWidth(GetLastChild()->GetX() + GetLastChild()->GetWidth());

  auto& prop = run_.GetRunProp();
  auto face = FaceManager::GetInstance()->GetFace(prop);
  auto height = face.GetHeight();

  for(int i=0 ; i<GetChildCount() ; i++ )
    GetChildAt(i)->SetHeight(height);
  
}

void RunView::Paint(Canvas& canvas)
{
  canvas.Save();
  canvas.GetMatrix().Translate(GetX(), GetY());

  auto& runprop = GetRun().GetRunProp();
  runprop.GetUnderline()->DrawUnderline(*this,canvas);
  
  for(int i=0 ; i<GetChildCount() ; i++ )
    GetChildAt(i)->Paint(canvas);
  

  canvas.Restore();  
}

View* RunView::GetNextParent() const
{
  auto nextparent = GetParent()->GetNextParent();
  auto newview = new RunView(GetRun());
  nextparent->AddChildAt(0, newview);
  return newview;
}


}  // le
