//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAGConf.h"
#include "multilang.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

double pmut  = 10;
double pcros = 95;
int    elite = 2;
int    fitsc = 0;

TwCONF *wCONF;
//---------------------------------------------------------------------------
__fastcall TwCONF::TwCONF(TComponent* Owner)
  : TForm(Owner)
{
  cbScaling->ItemIndex = 0;

  gbParamAG->Caption = text("appConfigArea");
  lbCrossover->Caption = text("agCrossOver");
  lbMut->Caption = text("agMutation");
  lbElitsmo->Caption = text("agElite");
  lbIndiv->Caption = text("agIndiv");
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::Exit(TObject *Sender)
{
  TEdit *ed = dynamic_cast<TEdit*>( Sender );
  try
  {
    ed->Text.ToDouble();
  }
  catch(...)
  {
    MessageBox(this->Handle,text("appInvalidNum",ed->Text),text("appError"),MB_ICONERROR);
    ed->SelectAll();
    ed->SetFocus();
  }  
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  pmut  = ePerMut->Text.ToDouble();
  pcros = ePerCruz->Text.ToDouble();
  elite = eElite->Text.ToInt();
  fitsc = cbScaling->ItemIndex;
}
//---------------------------------------------------------------------------
