/*
**  Genetic Algorithm
**  Lucas Lorensi dos Santos
**  13/10/2004
*/

#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <time.h>
                       
#include "ag.h"

namespace LLS
{

using namespace std;

//------------------------------------------------------------------------------
//--------------------------- IMPLEMENTATION -----------------------------------
//------------------------------------------------------------------------------

//===
//==  Ramdom Methods
//===

// Sets randomly the seed of the random number generator  
void initrnd ( void )
{
  time_t t = time(NULL);
  srand(t);
}

// Return a double between [0..1]
double random(void)
{
  return ((double)rand() / (double)RAND_MAX);
}

// Return true as if Probability[0..1] is greatter them a rondom number[0..1]
bool flip( double Probability )
{
  return (Probability > random() );
}

// Return a random integer number between [LowLim..HighLim] 
int rnd( int LowLim, int HighLim )
{
  int res;

  do
  {
    res = random() * (HighLim - LowLim + 1 ) + LowLim;
  }
  while(res < LowLim || res > HighLim);

  return res;
}

// Return a random double number between [LowLim..HighLim]
double rnd( double LowLim, double HighLim )
{
  return ( random() * (HighLim - LowLim) + LowLim );
}


//===
//==  Chromosome
//===

CROMS::CROMS()
{
  _genes.resize(0);
}

GENb* CROMS::newGeneBin(bool Data)
{
  GENb* gene = new GENb(this);
  _genes.push_back( (GENb*)gene );
  gene->dado( Data );
  return gene;
}

void CROMS::crossover( CROMS* Cro1, CROMS* Cro2, int Pos)
{
  if ( Pos < maxgene())
  {
    //--- copy low segment from CROMS1 and high segment from CROMS2 ---
    for( int i=0; i< maxgene(); ++i)
    {
      CROMS* cro = (i < Pos-1 ? Cro1: Cro2);
      gene(i)->dado( cro->gene(i)->dado() );
    }
  }
}

void CROMS::clear(void)
{
  while( !_genes.empty() )
  {
    delete _genes[_genes.size()-1];
    _genes.pop_back();
  }
}

void CROMS::mutation( double PMut )
{
  for( int i=0 ; i < maxgene(); ++i)
  {
    if( flip( PMut ) )
      gene(i)->mutation();
  }
}

void CROMS::clone(CROMS* Cro)
{
  if( Cro )
    for( int i=0; i< Cro->maxgene(); ++i)
    {
      GENb* g = Cro->gene(i);
      gene(i)->dado( g->dado() );
    }
}

//===
//==  Individual
//===

IDV::IDV(IDV* Mdl)
{
  _cro = new CROMS();

  for( int i=0; i< Mdl->cromossomo()->maxgene(); ++i)
  {
     _cro->newGeneBin( Mdl->cromossomo()->gene(i)->dado() );
  }
}

IDV::IDV(int MaxGene)
{
  _cro = new CROMS();

  for( int i=0; i< MaxGene; ++i)
  {
    bool val = flip( 0.5 );
    _cro->newGeneBin( val );
  }
}

IDV::~IDV()
{
  delete _cro;
}

void IDV::mutation( double PMut )
{
  _cro->mutation( PMut );
}

//===
//==  Population
//===

PPL::PPL(IDV* Mdl,int MaxIdv)
{
  for( int i=0; i<MaxIdv; ++i)
  {
    _indvs.push_back( new IDV(Mdl->cromossomo()->maxgene()) );
  }
}

PPL::~PPL()
{
  while( !_indvs.empty() )
  {
    delete _indvs[_indvs.size()-1];
    _indvs.pop_back();
  }
}

IDV* PPL::melhor()
{
  IDV* better = indiv(0);

  for( int i=1; i< maxindiv(); ++i)
  {
    if( indiv(i)->fitness() > better->fitness() )
      better = indiv(i);
  }
  return better;
}

IDV* PPL::roleta( double Sum )
{
  double sumbrk = Sum * random();
  double sumloc = 0.;

  for( int i=0; i< maxindiv(); ++i)
  {
     sumloc += indiv(i)->fitness();
     if( sumloc >= sumbrk)
      return indiv(i);
  }

  return NULL;
}

void PPL::crossover (IDV* P1, IDV* P2, IDV* F1, IDV* F2)
{
  int ponto = random()*(P1->cromossomo()->maxgene()-1);

  F1->cromossomo()->crossover( P1->cromossomo(), P2->cromossomo(), ponto);
  F2->cromossomo()->crossover( P2->cromossomo(), P1->cromossomo(), ponto);
}

void PPL::lin_coeff( double &A, double &B ) // From the book of David Goldberg
{
  double fmultiple = 2.0, delta;

  if( _ftnmin > (fmultiple * _ftnavg - _ftnmax)/(fmultiple - 1.0) ) //Normal scaling
  {
    delta = _ftnmax - _ftnavg;
    A = (fmultiple - 1.0) * _ftnavg / delta;
    B = _ftnavg * (_ftnmax - fmultiple * _ftnavg) / delta;
  }
  else // Scale as much as possible
  {
    delta = _ftnavg - _ftnmin;
    if( delta )
    {
      A = _ftnavg / delta;
      B = -_ftnmin * _ftnavg / delta;
    }
    else
    {
      A = 1;
      B = 0;
    }
  }
}

double PPL::scale( double Fitness, double A, double B)
{
  return (A * Fitness + B);
}

void PPL::scalepop(void)
{
  if( _scaling == LIN_SCALE )
  {
    double a, b;

    lin_coeff(a, b);

    _ftnsum = 0.0;

    for( int i=0; i< maxindiv(); ++i)
    {
      IDV* idv = indiv(i);
      double ftn = scale( idv->fitness(), a, b);

      idv->fitness( ftn );
      _ftnsum += ftn;
    }
  }
}

void PPL::statistics()
{
  // statistics

  _ftnsum = indiv(0)->fitness();
  _ftnmax = indiv(0)->fitness();
  _ftnmin = indiv(0)->fitness();

  for( int i=1; i< maxindiv(); ++i)
  {
    double ftn = indiv(i)->fitness();

    if( ftn > _ftnmax )
      _ftnmax = ftn;

    if( ftn < _ftnmin )
      _ftnmin = ftn;

    _ftnsum += ftn;
  }

  _ftnavg = _ftnsum / maxindiv();
}

int fittest( const void *a, const void *b)
{
   return  ((IDV*)a)->fitness() > ((IDV*)b)->fitness();
}

void PPL::geracao(void)
{
  if( !maxindiv() )
    exit(EXIT_FAILURE	);

    
  vector<IDV*> newINDIV;
  int nip = 0;

  // sort individuals by fitness

  sort( _indvs.begin(), _indvs.end(), fittest );

  // elite

  for( int i=0; i< _elitismo; ++i, ++nip)
    newINDIV.push_back( indiv(i) );

  // statistics
  
  statistics();
         
  // fitness scaling

  if( _scaling )
    scalepop();

  // generation of new indivuduals

  for( nip++; nip< maxindiv(); nip+=2)
  {
    IDV* parent1;
    IDV* parent2;

    //selecao dos pais: roleta

    parent1 = roleta( _ftnsum );
    parent2 = roleta( _ftnsum );

    IDV* child1 = new IDV(parent1);
    IDV* child2 = new IDV(parent2);

    // crossover

    if( flip( _pcross ) )
      crossover( parent1, parent2, child1, child2);

    // mutation

    child1->mutation( _pmut );
    child2->mutation( _pmut );

    // add new individuals

    newINDIV.push_back( child1 );
    newINDIV.push_back( child2 );
  }

  // remove old population

  for( int i= _elitismo; i< (int)newINDIV.size(); ++i)
  {
    IDV* idv = indiv(i);
    delete idv;
  }

  // copy new population

  _indvs = newINDIV;
}

//===
//==  Genetic Algorithm
//===

GA::GA()
{
  initrnd();
  _model = new IDV();
  _population = NULL;

}

GA::~GA()
{
  delete _model;
  delete _population;
}

void GA::criapopul(int MaxIdv)
{
  if( _population )
    delete _population;
    
  _population = new PPL(_model, MaxIdv);
}

}//end namespace

