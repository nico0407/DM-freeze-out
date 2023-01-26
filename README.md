# Dark Matter freeze-out

Things I still need to do:
- Unpolarize all the cross sections and recompute the freeze-out both for just the dark photon mediator and for the dark photon+dark scalar mediator;
- Find out if the parameters used are correct in the scalar cross section;
- Understand if the differential equation is solved correctly in the total model;
- Still the problem with the analytical formula of the decay diagram;
- Understand which kind of result physically am I getting.

Then vary the parameter space and look for possible pheno.

Copy the iDM.....unpolarized file and change masses of DM particles. Change the coannihilation cross section, need to insert the hadrons production in the final state. Same for the scalar coannihilation. Integrate again.




# Important
The code with all the model is working now. You just have to add the tilda to the Dark Matter candidates, not to every new particle.
At first the xf was 33.5 and the Omega was 10e-7. The relevant processes were just the ones involving the chi1 scalar going into HNL4,5,6. 
So I thought that the scalar cross section was fucked up, in particular the coupling which was "Y^chi" and at the beginnig was an internal parameter defined as:

 Ychi == {
 
    ParameterType    -> Internal, 
    
    BlockName        -> NP,
    
    Value            -> Sqrt[2]*mX1/vevscal ,
    
    Description      -> "Y^chi"
    
  }, 
  
But his value has way too high. Therefore I decided to use it as an external paramether to set. and just changing this one to Ychi=0.01 I got xf=25.9 and the Omega=1.89 e-3, still not the best but much better.
Probably the scalar iDM interaction needs to be checked again. Now also the inelastic current channel that sees the coannihilation of chi1 and chi2 into e+e- and mu+mu- are back.




# How to use Micromegas
First you need to write down your new model into a script that already has the Standard Model framework as a background. You can add new physical bosons and scalars and new particles, both majorana or dirac ones. The particles that should be dark matter has to have the tilda on the name, like follows:
 
 F[5] == {                               
  
    ClassName        -> X1,
    
    SelfConjugate    -> True,
    
    Mass             -> {mX1, 500},
    
    Width            -> {wX1, 0},
    
    PropagatorLabel  -> {"X1"},
    
    PropagatorType   -> Straight,
    
    PropagatorArrow  -> None,
    
    PDG              -> {71},
    
    ParticleName     -> {"~X1"},
    
    AntiParticleName -> {"~X1bar"},
    
    FullName         -> {"~fermion 1"}
    
  }, 
  
  If it's Majorana the self conjugate has to be True, and the Propagator arrow "None", is Dirac those things has t o be respectively False and "Forward" as in the definition of the quarks that follows
  
    F[3] == {
    
    ClassName        -> uq,
    
    ClassMembers     -> {u, c, t},
    
    Indices          -> {Index[Generation], Index[Colour]},
    
    FlavorIndex      -> Generation,
    
    SelfConjugate    -> False,
    
    Mass             -> {Mu, {MU, 2.55*^-3}, {MC,1.27}, {MT,172}},
    
    Width            -> {0, 0, {WT,1.50833649}},
    
    QuantumNumbers   -> {Q -> 2/3},
    
    PropagatorLabel  -> {"uq", "u", "c", "t"},
    
    PropagatorType   -> Straight,
    
    PropagatorArrow  -> Forward,
    
    PDG              -> {2, 4, 6}, 
    
    ParticleName     -> {"u",  "c",  "t" },
    
    AntiParticleName -> {"u~", "c~", "t~"},
    
    FullName         -> {"u-quark", "c-quark", "t-quark"}
    
  },
  
  After the script and the Lagranigian of the new Phuysics is ready you have to create an exegutable for Micromegas. This can be done following the Mathematica notebook "BSM.nb". this one allows to check the all model and if there are any issue and at the end where is written down (Micromegas) it creates 5 files that are necessare to run Micromegas. 
  
Once those files are ready has to be included in the new model folder inside the micromegas_5.3.41 directory. In particular in the path ../micromegas_5.3.41/NAMEOFTHEMODELFOLDER/work/models and those have to replace the existing ones. Once this is ready Micromega can be runned.

To create a new directory in micromegas the procedure to follow is the following:
in micromega directory lounch ./newProject NAMEOFTHEMODELFOLDER
This will create all the necessare thing to run micromega.
Then, lunch "make" inside the micromega folder and then go into your specific directory and lunch "make main=main.c"
Once this is done, modify the data.par in function of the esternal parameter your model need to have and then run "./main data.par". This will work.

If you need to add FREEZE IN or delete something that main.c do by default you can open and modify the main.c file commenting or uncommenting sections.

There is also a way to run micromegas as many times as you want for different paramethers. Look up to the folder Gordanmodel. In particular the file dta.par has to be called data0.par, then you need to create a file txt called data_in and one calle data_out. The data0.par has to contain all the paramethers, and the ones that are fixed over all the process has to have the proper right number they need, instead the paramethers that need to vary in the process has to have a "value definition" as a variable and so tipically xxx or yyy or eee, but all different.

Then a new file need to be added, called Micro.sh and the main.c need to be extended in producing and saving the relic value in the file as:

# How to write the relic density result in the file and run it many times

Duplicate data.par and call it data0.par

Create an "output.txt" file where Micromega is going to write the Omega result. Now if you run ./main data.par the value is gonna be stored in the output.txt file. But you need to modify the Omega section of main.c adding the piece:

     FILE *infileR;
     infileR = fopen("output.txt","w");
     fprintf(infileR,"%f",Omega);
     fclose(infileR);
     printf("\n ** the relic density has been printed in file \"output.txt\" ** \n");
     
It has to be added specifically so that the Omega section of main.c looks like:
{
#ifdef OMEGA
{ int fast=1;
  double Beps=1.E-4, cut=0.01;
  double Omega;  
  int i,err; 
  printf("\n==== Calculation of relic density =====\n");   

  if(CDM1 && CDM2) 
  {
  
    Omega= darkOmega2(fast,Beps,&err);

/*
  displayPlot("vs11","T",Tend,Tstart,0,5
      ,"vs1100",0,vs1100F,NULL
      ,"vs1120",0,vs1120F,NULL
      ,"vs1122",0,vs1122F,NULL
      ,"vs1110",0,vs1110F,NULL
      ,"vs1112",0,vs1112F,NULL
      );
      
  displayPlot("vs12","T",Tend,Tstart,0,4
             ,"vs1210",0,vs1210F,NULL
             ,"vs1222",0,vs1222F,NULL
             ,"vs1120",0,vs1120F,NULL
             ,"vs1211",0,vs1211F,NULL);
                                
  displayPlot("vs22","T",Tend,Tstart,0,5
             ,"vs2200",0,vs2200F,NULL
             ,"vs2210",0,vs2210F,NULL
             ,"vs2211",0,vs2211F,NULL
             ,"vs2220",0,vs2220F,NULL
             ,"vs2221",0,vs2221F,NULL
             );
  displayPlot("dY","T",  Tend,Tstart,0,2,"dY1",0,dY1F,NULL,"dY2",0,dY2F,NULL);
  displayPlot("Y","T",   Tend,Tstart,0,2,"Y1" ,0,Y1F,NULL,"Y2",0,Y2F,NULL);
*/                                
      
       
    printf("Omega_1h^2=%.2E Omega_2h^2=%.2E err=%d \n", Omega*(1-fracCDM2), Omega*fracCDM2,err);
  } else
  {  double Xf;
     Omega=darkOmega(&Xf,fast,Beps,&err);
     printf("Xf=%.2e Omega=%.2e\n",Xf,Omega);
     if(Omega>0)printChannels(Xf,cut,Beps,1,stdout);
  }
     FILE *infileR;
     infileR = fopen("output.txt","w");
     fprintf(infileR,"%f",Omega);
     fclose(infileR);
     printf("\n ** the relic density has been printed in file \"output.txt\" ** \n");
}

}




To run Micromega more times create other text file called "data_in", "data_out". First in data0.par assign all the fixed values to the parameters and for the values call them with different names such as "xxx", "yyy"... 

Then in data_in you just need to assign as many values you want to the variables you need. Use the Micro.sh file and modify it accordingly to how many variables you have. and then you are good to run the command "sh Micro.sh".

I AM UPLOADING AN EXAMPLE DIRECTORY THAT WORKS CALLED "Gordanmodel".





# UPDATE 25.01.2023

Maybe all the internal variables has to go into order of use. So if the external paramether is theta and there is an internal paramether that need cos theta you need to define an other internal paramther that is costeta. 
