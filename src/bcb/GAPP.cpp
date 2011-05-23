//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("GAPP.res");
USEFORM("src\uMain.cpp", F_Main);
USEFORM("src\uConf.cpp", wCONF);
USEUNIT("..\multilang\multilang.cpp");
USEUNIT("..\ag\ag.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->Title = "GAPP";
     Application->CreateForm(__classid(TF_Main), &F_Main);
     Application->CreateForm(__classid(TwCONF), &wCONF);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
