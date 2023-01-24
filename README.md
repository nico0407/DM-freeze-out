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
  F[5] == {                                                                       (*   >>>>>   HERE!   <<<<<   *)
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

END UP TOMORROW 
