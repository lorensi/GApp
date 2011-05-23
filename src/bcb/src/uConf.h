//---------------------------------------------------------------------------

#ifndef uConfH
#define uConfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>

extern double pmut;
extern double pcros;
extern int    elite;
extern int    fitsc;
extern int    nindv;

//---------------------------------------------------------------------------
class TwCONF : public TForm
{
__published:	// IDE-managed Components
  TBitBtn *btnFechar;
  TGroupBox *gbIntelligence;
  TGroupBox *bgLanguage;
  TComboBox *cbLanguage;
  TGroupBox *gbAdvanced;
  TLabel *lbCrossover;
  TEdit *ePerCruz;
  TLabel *Label11;
  TEdit *eElite;
  TLabel *lbElitsmo;
  TLabel *lbIndiv;
  TCSpinEdit *spinNumIdv;
  TLabel *lbNumIndiv;
  TEdit *ePerMut;
  TLabel *Label12;
  TLabel *lbMut;
  TRadioButton *rbSimple;
  TRadioButton *rbAdvanced;
  TGroupBox *gbSimple;
  TTrackBar *tbIntlg;
  TLabel *lbIntlg;
  void __fastcall Exit(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall cbLanguageChange(TObject *Sender);
  void __fastcall spinNumIdvChange(TObject *Sender);
  void __fastcall rbAdvancedClick(TObject *Sender);
  void __fastcall rbSimpleClick(TObject *Sender);
  void __fastcall tbIntlgChange(TObject *Sender);
private:	// User declarations
  void __fastcall DisEnabledChildren(TWinControl *Comp, bool Value);
public:		// User declarations
  __fastcall TwCONF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TwCONF *wCONF;
//---------------------------------------------------------------------------
#endif
