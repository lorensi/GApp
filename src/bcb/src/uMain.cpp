//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "uMain.h"
#include "uConf.h"
#include "multilang.h"
#include <Inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

using namespace LLS;

TF_Main *F_Main;
//---------------------------------------------------------------------------
__fastcall TF_Main::TF_Main(TComponent* Owner)
  : TForm(Owner)
{
  x_max = y_max = 500.;
  x_est = 50.;
  y_est = 10.;
  raio = 7;
  step = 5;
  eStep->Text = FormatFloat("0.00", step);

  ang_lininf = -30.;
  ang_linsup = 30.;

  int ini = time(NULL);
  srand(ini);

  TIniFile *inifile;
  inifile = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
  String LangFile = inifile->ReadString("Language", "File","portugues.lng" );
  delete inifile;

  //linguage
  if( !loadlangfile(LangFile.c_str()) )
  {
    MessageBox( NULL, "No language file(*.lng) found.", "Erro: Language Files", MB_OK | MB_ICONWARNING );
    Application->Terminate();
  }
}
//---------------------------------------------------------------------------

void __fastcall TF_Main::Exit(TObject *Sender)
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
void __fastcall TF_Main::ExecutarAg(TObject *Sender)
{
  if( nindv <= elite )
  {
    MessageBox(this->Handle,tr("appInvLessElite").c_str(),tr("appTip").c_str(), MB_ICONINFORMATION);
    return;
  }

  ang_lininf = edAngLeft->Text.ToDouble();
  ang_linsup = edAngRight->Text.ToDouble();

  x_max = spinGridX->Value;
  y_max = spinGridY->Value;  

  btnExecuta->Enabled = false;

  Limpar(NULL);

  raio = tbRaio->Position;

  x_est = eXEst->Text.ToInt();
  y_est = eYEst->Text.ToInt();

  dist = 1e99;

  step = eStep->Text.ToDouble();
  
  if( rbPosAleat->Checked )
  {
    x = (double)rand()/RAND_MAX * spinGridX->Value;
    y = (double)rand()/RAND_MAX * spinGridY->Value;
  }
  else if( rbPosMan->Checked )
  {
    x = eX->Text.ToDouble();
    y = eY->Text.ToDouble();
  }

  if( rbOriAleat->Checked )
    orient = (double)rand()/RAND_MAX * 360;
  else if( rbOriMan->Checked )
    orient = eOrient->Text.ToDouble();

  // instance ga  
  ag = new GA();

  // defining the genotype
  for(int i=0; i<7; ++i)
    ag->model()->cromossomo()->newGeneBin( false );

  // creating the initial population
  ag->criapopul( nindv );

  // configuration
  ag->populacao()->elitismo( elite      );
  ag->populacao()->pcross  ( pcros/100. );
  ag->populacao()->pmut    ( pmut/100.  );
  ag->populacao()->scaling ( fitsc      );

  DrawCar(x, y );

  MSG msg;
  gerac = 0;
  
  terminar = false;

  while( !terminar && dist > eToler->Text.ToDouble() )
  {
    ++gerac;

    for( int i=0; i< ag->populacao()->maxindiv(); ++i )
    {
      IDV *idv = F_Main->Ag()->populacao()->indiv( i );
      avalia_indiv( idv, x, y, orient );
    }

    double inc = orientacao( ag->populacao()->melhor()->cromossomo() );
    if( orient + inc > 360. )
      orient = (orient + inc) - 360.;
    else if( orient + inc < 0. )
      orient = 360 + (orient + inc);
    else
      orient += inc;

    move( x, y, orient );

    TListItem *item = lvIndivs->Items->Add();
    item->Caption = gerac;
    item->SubItems->Add(FormatFloat("0.000", ag->populacao()->melhor()->fitness()));
    item->SubItems->Add(FormatFloat("0.000",AngComplemento(orient)));
    item->SubItems->Add(FormatFloat("0.000",-inc));
    item->SubItems->Add("X: "+FormatFloat("0.000",x)+"  Y: "+FormatFloat("0.000",y));

    dist = distancia(x, y);
    item->SubItems->Add(FormatFloat("0.000",dist));

    ag->populacao()->statistics();


    AtualizaGraf();

    //move garagem

    // incremento de x
    double x_inc = (random()-0.5)*edGarStep->Text.ToDouble();

    x_est += x_inc;

    if( x_est + x_inc > x_max )
      x_est -= x_inc;
    else if( x_est + x_inc < 0 )
      x_est -= x_inc;

    // incremento de y
    double y_inc = (random()-0.5)*edGarStep->Text.ToDouble();

    y_est += y_inc;

    if( y_est + y_inc > y_max )
      y_est -= y_inc;
    else if( y_est + y_inc < 0 )
      y_est -= y_inc;


    ag->populacao()->geracao();

    Application->ProcessMessages();
  }

  delete ag;

  btnExecuta->Enabled = true;
}
//---------------------------------------------------------------------------

double TF_Main::AngComplemento( double Ang )
{
  Ang = 360 - Ang;
  if( Ang > 360. )
    Ang = Ang - 360.;
  else if( Ang < 0. )
    Ang = 360 + Ang;

  return Ang;
}

double TF_Main::distancia( double X, double Y )
{
  return sqrt( pow((X-x_est),2) + pow((Y-y_est),2) );
}

void TF_Main::avalia_indiv( IDV *Idv, double X, double Y, double Orient)
{
  double deg = orientacao( Idv->cromossomo() );

  if( deg < ang_linsup && deg > ang_lininf )
  {
    if( Orient + deg > 360. )
      Orient = (Orient + deg) - 360.;
    else if( Orient + deg < 0. )
      Orient = 360. + (Orient + deg);
    else
      Orient += deg;

    move(X, Y, Orient );

    double dist = distancia( X, Y );
    Idv->fitness( 1/dist );
  }
  else
    Idv->fitness( 0.0 );
}

double TF_Main::orientacao( CROMS* Cro )
{
  double und = 0.0, des = 0.0, sig;

  for( int i=3; i< 7; ++i)
  {
    bool val = Cro->gene(i)->dado();
    if( val )
      und += pow(2,i-3);
  }

  for( int i=0; i< 2; ++i)
  {
    bool val = Cro->gene(i)->dado();
    if( val )
      des += pow(2,i);
  }

  if( und > 9.0 )
    und = 9.0;

  des *= 10.0;
  double deg = des + und;
  sig = Cro->gene(6)->dado() ? 1 : -1;
  deg *= sig;

  return deg;
}

void __fastcall TF_Main::AtualizaGraf()
{
  pb->Repaint();
  DrawPark();
  DrawPath();
  DrawCar(x, y);

  statusbar->Panels->Items[0]->Text = tr("agCurrGen",IntToStr(gerac)).c_str();
  statusbar->Panels->Items[1]->Text = tr("agDistGen",FormatFloat("0.000", dist )).c_str();
  statusbar->Panels->Items[2]->Text = tr("agCurrPos",FormatFloat("0.000",x),FormatFloat("0.000",y)).c_str();
  statusbar->Panels->Items[3]->Text = tr("agCurrOri",FormatFloat("0.000",AngComplemento(orient)) ).c_str();

  Series1->AddXY( gerac, dist,"" , clGreen );

  Series2->AddXY( gerac, ag->populacao()->ftnmax(), "" , clRed );
  Series3->AddXY( gerac, ag->populacao()->ftnavg(), "" , clRed );  
}

void TF_Main::move( double &X, double &Y, double Orient )
{
  X += step*cos(Orient*M_PI/180.);
  Y += step*sin(Orient*M_PI/180.);
}

void __fastcall TF_Main::ConvertCoord( double X, double Y, double &XScreen, double &YScreen )
{
  XScreen = ((double)pb->Width *X)/((double)x_max);
  YScreen = ((double)pb->Height*Y)/((double)y_max);
}

void __fastcall TF_Main::DesenhaTri( TPoint Pt, double Orient )
{
  double rad = Orient*M_PI/180.;

  float Bx = Pt.x+(raio-1)*cos(rad);
  float By = Pt.y+(raio-1)*sin(rad);

  float Ax = Pt.x-(raio/2)*sin(-rad);
  float Ay = Pt.y-(raio/2)*cos(-rad);

  float Cx = Pt.x+(raio/2)*sin(-rad);
  float Cy = Pt.y+(raio/2)*cos(-rad);

  pb->Canvas->MoveTo(Pt.x,Pt.y);
  pb->Canvas->LineTo(Ax,Ay);
  pb->Canvas->MoveTo(Pt.x,Pt.y);
  pb->Canvas->LineTo(Cx,Cy);
  pb->Canvas->LineTo(Bx,By);
  pb->Canvas->LineTo(Ax,Ay);
}

void __fastcall TF_Main::DrawPath()
{
  if( vec_path.size() >= 1)
  {
    pb->Canvas->MoveTo( vec_path[0].x, vec_path[0].y );

    for( size_t i=1; i < vec_path.size(); ++i )
    {
      pb->Canvas->LineTo( vec_path[i].x, vec_path[i].y );
    }
  }
}

void __fastcall TF_Main::DrawCar( double X, double Y )
{
  ConvertCoord( X, Y, X, Y );

  vec_path.push_back( TPoint( X, Y ) );

  pb->Canvas->Pen->Style = psSolid;

  int x1 = X - (double)raio;
  int x2 = X + (double)raio;
  int y1 = Y - (double)raio;
  int y2 = Y + (double)raio;

  pb->Canvas->Pen->Color = clBlack;
  pb->Canvas->Brush->Color = clWhite;

  pb->Canvas->Ellipse( x1, y1, x2, y2);
  DesenhaTri( TPoint(X,Y), orient );

  double rad = orient*M_PI/180. + M_PI;
  float Ax = X+(raio+1)*cos(rad);
  float Ay = Y+(raio+1)*sin(rad);
  pb->Canvas->Brush->Color = clBlack;
  pb->Canvas->Ellipse( Ax-1, Ay-1, Ax+1, Ay+1);

  Sleep( eTempoEsp->Text.ToInt() );
}

void __fastcall TF_Main::DrawPark()
{
  double x, y;
  ConvertCoord( x_est, y_est, x, y );

  double tolx = pb->Width*(eToler->Text.ToDouble()/x_max);
  double toly = pb->Height*(eToler->Text.ToDouble()/y_max);

  int x1 = x - ((double)raio+tolx);
  int x2 = x + ((double)raio+tolx);
  int y1 = y - ((double)raio+toly);
  int y2 = y + ((double)raio+toly);

  pb->Canvas->Pen->Style = psSolid;
  pb->Canvas->Pen->Color = clBlack;
  pb->Canvas->Rectangle( x1, y1, x2, y2);
}

//---------------------------------------------------------------------------

void __fastcall TF_Main::Limpar(TObject *Sender)
{
  pb->Repaint();
  lvIndivs->Items->Clear();
  Series1->Clear();
  chDist->UndoZoom();
  Series2->Clear();
  Series3->Clear();
  crtStat->UndoZoom();
  vec_path.clear();
}
//---------------------------------------------------------------------------

void __fastcall TF_Main::tbRaioChange(TObject *Sender)
{
  raio = tbRaio->Position;
  lblRaio->Caption = tbRaio->Position;
  pb->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TF_Main::PararAG(TObject *Sender)
{
  terminar = true;
}
//---------------------------------------------------------------------------
void __fastcall TF_Main::cbRealTimeClick(TObject *Sender)
{
  if( cbRealTime->Checked )
  {
    lvIndivs->Items->EndUpdate();
    chDist->AddSeries( Series1 );
    crtStat->AddSeries( Series2 );
    crtStat->AddSeries( Series3 );
  }
  else
  {
    lvIndivs->Items->BeginUpdate();
    chDist->RemoveAllSeries();
    crtStat->RemoveAllSeries();
  }
}
//---------------------------------------------------------------------------

void __fastcall TF_Main::AGConfClick(TObject *Sender)
{
  wCONF->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TF_Main::FormCreate(TObject *Sender)
{
  F_Main->Caption = tr("appTitle").c_str();
  gbParam->Caption = tr("appConfigArea").c_str();
  lbDimPlan->Caption = tr("appDimPlan").c_str();
  lbDelay->Caption = tr("appDelay").c_str();
  lbStep->Caption = tr("appStep").c_str();
  gbGaragem->Caption = tr("agGarage").c_str();
  lbCenGar->Caption = tr("agCenterGarage").c_str();
  lbTolerance->Caption = tr("agTolerance").c_str();
  gbCarro->Caption = tr("agCar").c_str();
  lbRay->Caption = tr("agRay").c_str();
  gbCarPos->Caption = tr("agCarPos").c_str();
  rbPosAleat->Caption = tr("agRandPos").c_str();
  rbPosMan->Caption = tr("agPosMan").c_str();
  gbOrient->Caption = tr("agOrient").c_str();
  rbOriAleat->Caption = tr("agRandPos").c_str();
  rbOriMan->Caption = tr("agAngMan").c_str();
  gbVarAng->Caption = tr("agAngLim").c_str();
  lbAngRight->Caption = tr("agAngLinRight").c_str();
  lbAngLeft->Caption = tr("agAngLinLeft").c_str();
  lbGarStep->Caption = tr("appStep").c_str();

  btnAGConf->Caption = tr("appParam").c_str();
  tsTab->Caption = tr("appGeneral").c_str();
  tsGraf->Caption = tr("appDist").c_str();
  tsStat->Caption = tr("appStatistic").c_str();
  cbRealTime->Caption = tr("appShow").c_str();

  lvIndivs->Columns->Items[0]->Caption = tr("appColumn0").c_str();
  lvIndivs->Columns->Items[1]->Caption = tr("appColumn1").c_str();
  lvIndivs->Columns->Items[2]->Caption = tr("appColumn2").c_str();
  lvIndivs->Columns->Items[3]->Caption = tr("appColumn3").c_str();
  lvIndivs->Columns->Items[4]->Caption = tr("appColumn4").c_str();
  lvIndivs->Columns->Items[5]->Caption = tr("appColumn5").c_str();
  btnExecuta->Caption = tr("appRun").c_str();
  btnPause->Caption = tr("appPause").c_str();
  btnNew->Caption = tr("appClear").c_str();
  btnExit->Caption = tr("appExit").c_str();

  for(int i=0; i<statusbar->Panels->Count; ++i)
    statusbar->Panels->Items[i]->Text="";
}
//---------------------------------------------------------------------------

