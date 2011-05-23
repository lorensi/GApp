/*
**  Multi-Language
**  Lucas Lorensi dos Santos
**  13/10/2004
**
**  Updated: 14/07/2006
*/

#include "multilang.h"

#include <utility>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <stdarg.h>
#include <map.h>
#define MAXSTR 255

typedef char* pchar;
map<string,string> mapNameVals;
map<string,string>::iterator itNameVals;

bool loadlangfile( char* Filename)
{
  if( strlen(Filename) == 0 )
    return false;
    
  ifstream iflang(Filename);

  if( iflang )
  {
    char buf[MAXSTR];
    string line, name, value;
    int pos;

    mapNameVals.clear();

    while( !iflang.eof() )
    {
      iflang.getline(buf,MAXSTR);

      if( buf[0] == '[' || buf[0] == ';') continue;

      line = buf;
      pos = line.find("=");

      name = line.substr(0,pos);
      value = line.substr(pos+1,MAXSTR);

      itNameVals = mapNameVals.find(name);
      if( itNameVals == mapNameVals.end() )
      {
        mapNameVals.insert( make_pair(name,value) );
      }
    }

    iflang.close();
    return true;
  }

  return false;
}

std::string tr( char* Name, ... )
{
  itNameVals = mapNameVals.find(Name);
  if( itNameVals == mapNameVals.end() )
    return std::string(Name);

  string value = itNameVals->second;

  int pos = value.find("%");
  if( pos == -1 )
  {
    return value;
  }
  else
  {
    pchar arg;
    va_list ap;
    va_start(ap, Name);

    char param = '0';

    string argn = string("%")+ ++param;
    pos = value.find( argn );

    while( pos != -1 )
    {
      arg = va_arg(ap,pchar);

      value.replace(pos,argn.length(),arg);

      argn = string("%")+ ++param;
      pos = value.find( argn );
    }

    va_end(ap);
    value.reserve(MAXSTR);
    return value;
  }
}


