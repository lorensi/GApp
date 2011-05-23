/*
**  Genetic Algorithm
**  Lucas Lorensi dos Santos
**  13/10/2004
**
**  ToDo:
**    Integer and real encoding
**    Parent selection: tournament
**    Fitness Scaling
*/

#ifndef _ag_
#define _ag_

#include <vector.h>

// types of fitness scaling
#define LIN_SCALE 1
#define NO_SCALE  0

namespace LLS
{

//------------------------------------------------------------------------------
//------------------------------ DECLARATIONS ----------------------------------
//------------------------------------------------------------------------------

class GENb;   // binary gene
class CROMS;  // chromosome
class IDV;    // individual
class PPL;    // population
class GA;     // genetic algorithm


// === Random Methods ===
void   initrnd ( void );
double random  ( void );
bool   flip    ( double Probability );
int    rnd     ( int LowLim, int HighLim );

// === Base class of the genes ===
template <class T> class GEN
{
  private:
    T _data;
    CROMS* _cro;

  public:

    //--- (Con/Des)tructor ---
    GEN(void)      {;}
    GEN(CROMS* Cro){ _cro = Cro; }
     ~GEN(void)    {;}

    //--- Data ---
    virtual void dado(T Data) { _data = Data; }
    virtual T    dado(void)   { return _data; }

    //--- Parent ---
    void   crom (CROMS* Cro) { _cro = Cro; }
    CROMS* crom (void)       { return _cro; }
};
     
//=== Binary gene ===
class GENb : public GEN<bool>
{
  private:
  public:

    //--- (Cons/Des)trutor ---
    GENb(){;}
    GENb(CROMS* Cro):GEN<bool>(Cro){;}
    ~GENb(){;}

    //--- Operação Genética---
    void  mutation (void) { dado( !dado()); }
};

//=== Chromosome ===
class CROMS
{
  private:
    vector<GENb*> _genes;

  public:
    CROMS();
    ~CROMS(){ clear(); }

     //--- Structure Definitions of the Chromosome ---
    GENb* newGeneBin (bool Data);
    void  clone      (CROMS* Cro);

    //--- Access ---
    int   maxgene (void)    { return _genes.size();  }
    GENb* gene    (int Idx) { return _genes[Idx]; }
    void  clear   (void);

    //--- Genetics Operators ---
    void  crossover (CROMS* Cro1, CROMS* Cro2, int Pos); // 1 ponto
    void  mutation  (double PMut);
};

//=== Individual ===
class IDV
{
  private:
    CROMS* _cro;
    double _fitness;

  public:
    //--- (Cons/Des)tructor ---
    IDV ()           {   _cro = new CROMS(); _fitness = 0.; }
    IDV (IDV* Mdl);
    IDV (int MaxGene);
    ~IDV();

    //--- Fitness ---
    double fitness()              { return _fitness; }
    void   fitness(double Fitness){ _fitness = Fitness; }

    //--- Access ---
    CROMS* cromossomo() { return _cro; }

    //--- Genetic Code ---
    void  clone    (IDV* Ind){ _cro->clone( Ind->cromossomo() ); }
    void  mutation (double PMut);
};

//=== Population ===
class PPL
{
  private:
    vector<IDV*> _indvs;

    //--- Probabilities ---
    double  _pcross;                // Crossover probability
    double  _pmut;                  // Mutation probability

    //--- Parameters ---
    int  _elitismo;                 // Elitism
    int  _scaling;                  // Fitness scaling (unstable)

    //--- Statistics ---
    double _ftnmax;
    double _ftnmin;
    double _ftnavg;
    double _ftnsum;

    //--- Fitness Scaling ---
    void   lin_coeff ( double &A, double &B );   // Linear Coefficients
    double scale     ( double Fitness, double A, double B);
    void   scalepop  ( void );

  public:
    PPL  (void) {;}
    PPL  (IDV* Mdl,int MaxIdv);
    ~PPL (void);

    //--- Probabilities ---
    void    pcross  (double Pcross) { _pcross = Pcross; }
    double  pcross  (void)          { return _pcross;    }
    void    pmut    (double Pmut)   { _pmut = Pmut; }
    double  pmut    (void)          { return _pmut;  }

    //--- Parameters GA ---
    void  elitismo   (int Elitismo) { _elitismo = Elitismo; }
    void  scaling    (int Scaling)  { _scaling = Scaling; }
    void  noscaling  (void)         { _scaling = NO_SCALE; }

    //--- Access ---
    IDV*  indiv    (int Idx) { return _indvs[Idx];   }
    int   maxindiv (void)    { return _indvs.size(); }
    IDV*  melhor   ();

    //--- Statistics ---
    void  statistics();
    double ftnmax() { return _ftnmax; }
    double ftnmin() { return _ftnmin; }
    double ftnavg() { return _ftnavg; }
    double ftnsum() { return _ftnsum; }

    //--- Genetics Operators ---
    IDV* roleta    (double Sum);
    void geracao   (void);
    void crossover (IDV* P1, IDV* P2, IDV* F1, IDV* F2);
};

//=== Genetic Algorithm ===
class GA
{
  private:
    //--- Model Individual ---
    IDV* _model;
    PPL* _population;

  public:
    GA();
    ~GA();

    //--- Model ---
    IDV*  model (void){ return _model; }
    
    //--- Access ---
    PPL*  populacao (void) { return _population; }
    void  criapopul (int MaxIdv);
};

}//end namespace

#endif

