//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>

#include "ag.h"
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <vector>

//---------------------------------------------------------------------------
class TF_Main : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnlParam;
  TPanel *pnlGrid;
  TGroupBox *gbParam;
  TStatusBar *statusbar;
  TLabel *lbDimPlan;
  TCSpinEdit *spinGridX;
  TCSpinEdit *spinGridY;
  TLabel *Label8;
  TGroupBox *gbGaragem;
  TLabel *lbCenGar;
  TLabel *Label5;
  TEdit *eXEst;
  TLabel *Label6;
  TEdit *eYEst;
  TGroupBox *gbCarro;
  TGroupBox *gbCarPos;
  TRadioButton *rbPosMan;
  TRadioButton *rbPosAleat;
  TGroupBox *gbOrient;
  TRadioButton *rbOriMan;
  TRadioButton *rbOriAleat;
  TEdit *eOrient;
  TPaintBox *pb;
  TLabel *lbDelay;
  TEdit *eTempoEsp;
  TPanel *pnlBottom;
  TPageControl *pgcTabGraf;
  TPanel *pnlRight;
  TButton *btnExecuta;
  TButton *btnPause;
  TButton *btnNew;
  TBitBtn *btnExit;
  TTabSheet *tsTab;
  TListView *lvIndivs;
  TTabSheet *tsGraf;
  TChart *chDist;
  TLineSeries *Series1;
  TSplitter *Splitter;
  TEdit *eX;
  TEdit *eY;
  TLabel *lbRay;
  TLabel *lbUnitRay;
  TLabel *lbTolerance;
  TEdit *eToler;
  TTrackBar *tbRaio;
  TLabel *lblRaio;
  TEdit *eStep;
  TLabel *lbStep;
  TTabSheet *tsStat;
  TChart *crtStat;
  TFastLineSeries *Series2;
  TFastLineSeries *Series3;
  TCheckBox *cbRealTime;
  TButton *btnAGConf;
  TGroupBox *gbVarAng;
  TEdit *edAngRight;
  TLabel *lbAngRight;
  TLabel *lbAngLeft;
  TEdit *edAngLeft;
  TLabel *lbGarStep;
  TEdit *edGarStep;
  void __fastcall Exit(TObject *Sender);
  void __fastcall ExecutarAg(TObject *Sender);
  void __fastcall Limpar(TObject *Sender);
  void __fastcall tbRaioChange(TObject *Sender);
  void __fastcall PararAG(TObject *Sender);
  void __fastcall cbRealTimeClick(TObject *Sender);
  void __fastcall AGConfClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations

  double x, y, x_est, y_est, x_max, y_max, xaux, yaux;
  double orient;
  double dist;
  double ang_lininf, ang_linsup;
  double step;
  int gerac, raio;

  std::vector< TPoint > vec_path;

  bool terminar;

  LLS::GA* ag;

  // Rotinas de desenho
  void __fastcall ConvertCoord( double X, double Y, double &XScreen, double &YScreen );

  void __fastcall DrawPath();
  void __fastcall DrawCar( double X, double Y );
  void __fastcall DrawPark();
  void __fastcall DesenhaTri( TPoint Pt, double Orient );
  double AngComplemento( double Ang );

public:		// User declarations
  __fastcall TF_Main(TComponent* Owner);

  void __fastcall AtualizaGraf();
  
  double orientacao( LLS::CROMS* Cro );
  void   move( double &X, double &Y, double Orient );
  void   avalia_indiv( LLS::IDV *Idv, double X, double Y, double Orient);
  double distancia( double X, double Y );

  LLS::GA* Ag() { return ag; }
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Main *F_Main;
//---------------------------------------------------------------------------
#endif
