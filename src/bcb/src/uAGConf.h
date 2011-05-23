//---------------------------------------------------------------------------

#ifndef uAGConfH
#define uAGConfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>

extern double pmut;
extern double pcros;
extern int    elite;
extern int    fitsc;

//---------------------------------------------------------------------------
class TwCONF : public TForm
{
__published:	// IDE-managed Components
  TBitBtn *btnFechar;
  TGroupBox *gbParamAG;
  TLabel *lbIndiv;
  TEdit *eElite;
  TLabel *lbElitsmo;
  TEdit *ePerMut;
  TLabel *Label12;
  TLabel *lbMut;
  TEdit *ePerCruz;
  TLabel *Label11;
  TLabel *lbCrossover;
  TComboBox *cbScaling;
  TLabel *Label18;
  void __fastcall Exit(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
  __fastcall TwCONF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TwCONF *wCONF;
//---------------------------------------------------------------------------
#endif
