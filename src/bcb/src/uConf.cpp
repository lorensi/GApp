//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uConf.h"
#include "multilang.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

double pmut  = 10;
double pcros = 95;
int    elite = 2;
int    fitsc = 0;
int    nindv = 10;

TwCONF *wCONF;
//---------------------------------------------------------------------------
__fastcall TwCONF::TwCONF(TComponent* Owner)
  : TForm(Owner)
{
  rbSimple->OnClick(NULL);
  cbLanguage->ItemIndex = 0;  
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
    MessageBox(this->Handle,tr("appInvalidNum",ed->Text).c_str(),tr("appError").c_str(),MB_ICONERROR);
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
//  fitsc = cbScaling->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::FormCreate(TObject *Sender)
{
  wCONF->Caption = tr("appWConf").c_str();
  gbIntelligence->Caption = tr("appIntelligence").c_str();
  lbCrossover->Caption = tr("agCrossOver").c_str();
  lbMut->Caption = tr("agMutation").c_str();
  lbElitsmo->Caption = tr("agElite").c_str();
  lbIndiv->Caption = tr("agIndiv").c_str();
  bgLanguage->Caption = tr("cfgLanguage").c_str();
  rbAdvanced->Caption = tr("cfgAdvanced").c_str();
  rbSimple->Caption = tr("cfgSimple").c_str();
  lbNumIndiv->Caption = tr("agNumIndiv").c_str();
  lbIntlg->Caption = tr("lbIntlg").c_str();
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::cbLanguageChange(TObject *Sender)
{
  loadlangfile( (ExtractFilePath(Application->ExeName)+cbLanguage->Text+".lng").c_str());
  for( int i=0; i < Application->ComponentCount; ++i)
  {
    TComponent *comp = Application->Components[i];
    if( comp->InheritsFrom(__classid(TForm)) )
      ((TForm*)comp)->AfterConstruction();
  }
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::spinNumIdvChange(TObject *Sender)
{
  nindv = spinNumIdv->Value;
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::rbAdvancedClick(TObject *Sender)
{
  DisEnabledChildren( gbSimple, false );
  DisEnabledChildren( gbAdvanced, true );
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::DisEnabledChildren(TWinControl *Comp, bool Value)
{
  for( int i=0; i < Comp->ControlCount; ++i)
  {
    TControl *comp = Comp->Controls[i];
    comp->Enabled = Value;
  }
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::rbSimpleClick(TObject *Sender)
{
  DisEnabledChildren( gbSimple, true );
  DisEnabledChildren( gbAdvanced, false );
  tbIntlg->OnChange(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TwCONF::tbIntlgChange(TObject *Sender)
{
  spinNumIdv->Value = tbIntlg->Position % 2 ? tbIntlg->Position + 1 : tbIntlg->Position;
  int elite = (int)spinNumIdv->Value/4;
  elite = elite % 2 ? elite +1 : elite;
  eElite->Text = elite;
}
//---------------------------------------------------------------------------

