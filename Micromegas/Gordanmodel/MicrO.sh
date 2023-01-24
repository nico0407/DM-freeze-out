#!/bin/csh

#########################
### inputs parameters ###
#########################
rm data_out
echo ""mX1" "mX2" "mX0" "epsilondark"" >> data_out #######

#########################
###    scan STARTS    ###
#########################
for (( j=1; j<=1000; j+=1 ))
do

#########################
###    read inputs    ###
#########################
file="data_in"
k1=1;
while read var1 var2 var3 var4;
do
if [ "$k1" == "$j" ];
then
v1=$var1
v2=$var2
v3=$var3
v4=$var4
fi
((k1+=1))
done <"$file"

# change the imputs of the MadEvent file
cat data0.par | sed -e "s/xxx/$v1/"\
			-e "s/yyy/$v2/"\
			-e "s/zzz/$v3/"\
                        -e "s/www/$v4/" > data.par  ###########

#########################
###    run MadGraph   ###
#########################

./main data.par

omega=`cat output.txt`  

#########################
###       print       ###
#########################
echo "$v1 $v2 $v3 $v4 $omega" >> data_out

done
