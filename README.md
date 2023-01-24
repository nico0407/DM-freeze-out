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
