#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../CalcHEP_src/include/extern.h"
#include "../../CalcHEP_src/include/VandP.h"
#include "autoprot.h"
extern int  FError;
/*  Special model functions  */
extern int access(const char *pathname, int mode);

int nModelParticles=20;
static ModelPrtclsStr ModelPrtcls_[20]=
{
  {"a","a",1, 22, "0","0",2,1,2,0}
, {"Z","Z",1, 23, "MZ","WZ",2,1,3,0}
, {"W+","W-",0, 24, "MW","WW",2,1,3,3}
, {"g","g",1, 21, "0","0",2,8,16,0}
, {"X0","X0",1, 70, "mX0","wX0",2,1,3,0}
, {"ve","ve~",0, 12, "0","0",1,1,2,0}
, {"vm","vm~",0, 14, "0","0",1,1,2,0}
, {"vt","vt~",0, 16, "0","0",1,1,2,0}
, {"e-","e+",0, 11, "Me","0",1,1,2,-3}
, {"mu-","mu+",0, 13, "MMU","0",1,1,2,-3}
, {"ta-","ta+",0, 15, "MTA","0",1,1,2,-3}
, {"u","u~",0, 2, "MU","0",1,3,6,2}
, {"c","c~",0, 4, "MC","0",1,3,6,2}
, {"t","t~",0, 6, "MT","WT",1,3,6,2}
, {"d","d~",0, 1, "MD","0",1,3,6,-1}
, {"s","s~",0, 3, "MS","0",1,3,6,-1}
, {"b","b~",0, 5, "MB","0",1,3,6,-1}
, {"~X1","~X1",1, 71, "mX1","0",1,1,2,0}
, {"~X2","~X2",1, 72, "mX2","0",1,1,2,0}
, {"H","H",1, 25, "MH","WH",0,1,1,0}
};
ModelPrtclsStr *ModelPrtcls=ModelPrtcls_; 
int nModelVars=32;
int nModelFunc=2;
static int nCurrentVars=31;
int*currentVarPtr=&nCurrentVars;
static char*varNames_[34]={
 "aEWM1","Gf","aS","ymdo","ymup","yms","ymc","ymb","ymt","yme"
,"ymm","ymtau","cabi","gX","epsilondark","e0","MZ","mX0","Me","MMU"
,"MTA","MU","MC","MT","MD","MS","MB","mX1","mX2","MH"
,"E","Pi","aEW","MW"};
char**varNames=varNames_;
static REAL varValues_[34]={
   1.279000E+02,  1.166370E-05,  1.184000E-01,  5.040000E-03,  2.550000E-03,  1.010000E-01,  1.270000E+00,  4.700000E+00,  1.720000E+02,  5.110000E-04
,  1.056600E-01,  1.777000E+00,  2.277360E-01,  1.000000E-01,  1.000000E-01,  3.134314E-01,  9.118760E+01,  1.000000E+02,  5.110000E-04,  1.056600E-01
,  1.777000E+00,  2.550000E-03,  1.270000E+00,  1.720000E+02,  5.040000E-03,  1.010000E-01,  4.700000E+00,  5.000000E+02,  5.000000E+02,  1.250000E+02
,  2.718282E+00,  3.141593E+00};
REAL*varValues=varValues_;
int calcMainFunc(void)
{
   int i;
   static REAL * VV=NULL;
   static int iQ=-1;
   static int cErr=1;
   REAL *V=varValues;
   FError=0;
   if(VV && cErr==0)
   { for(i=0;i<nModelVars;i++) if(i!=iQ && VV[i]!=V[i]) break;
     if(i==nModelVars)     return 0;
   }
  cErr=1;
   nCurrentVars=32;
   V[32]=Pow(V[0],-1);
   if(!isfinite(V[32]) || FError) return 32;
   nCurrentVars=33;
   V[33]=Pow(Pow(V[16],2)/(2.)+Pow(Pow(V[16],4)/(4.)-V[32]*V[31]*Pow(2,-0.5)*Pow(V[1],-1)*Pow(V[16],2),0.5),0.5);
   if(!isfinite(V[33]) || FError) return 33;
   if(VV==NULL) 
   {  VV=malloc(sizeof(REAL)*nModelVars);
      for(i=0;i<nModelVars;i++) if(strcmp(varNames[i],"Q")==0) iQ=i;
   }
   for(i=0;i<nModelVars;i++) VV[i]=V[i];
   cErr=0;
   nCurrentVars++;
   return 0;
}
