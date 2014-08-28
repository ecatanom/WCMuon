 #!/bin/bash

umask 002 #Ensure that files are user and group writable by default

source /lbne/app/users/ecatanom/WCSimAnalysis/setupWCSimAnalysis.sh

export DISPLAY=localhost0.0
export OutDir=/lbne/data2/users/ecatanom/042214_muon400_200kton_13per_025ns
#export DataFilesDir=/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc
#export DataFilesDir=/lbne/data/users/ecatanom/samples
export DataFilesDir=/lbne/data2/users/txin/Samples

export myrel=/lbne/app/users/ecatanom/WCSimAnalysis

#for file in $( find $DataFilesDir -maxdepth 1  -name 'muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root' |sort -r )
for file in $( find $DataFilesDir -maxdepth 1  -name 'muplus_400mev_200kton_10inch_13per_hqe_MuSct.root' |sort -r )
do {
  for (( ii=1; ii<1000; ii++ ))
  #for ii in 117 207 216 282 35 340 333 31 313 34 445 440 56 543 695 684 626 61 747 832 829 855 976 967 949 913 930
  do {
    filename=`basename $file` # extract file name
    echo $filename
    shortname=${filename:36}
    tim=_reco_test_
    outFile=ntuple_$ii$tim$filename
    
    jobcmd=$CONDOR_EXEC/recoJob-$shortname$ii-.sh
        
    if [ -e $jobcmd ]; then
    rm -f $jobcmd
    fi

    echo "#!/bin/bash" >> $jobcmd
    echo "umask 002"   >> $jobcmd
    echo "source $myrel/setupWCSimAnalysis.sh" >> $jobcmd
    echo "cd $myrel/" >> $jobcmd # cd to scratch directory
    echo "export DISPLAY=localhost0.0" >> $jobcmd
# this makes sure we have the appropriate commands to cp and mv on the grid
    echo "export CPN=/grid/fermiapp/minos/scripts/cpn" >> $jobcmd
    echo "export MVN=/grid/fermiapp/minos/scripts/mvn" >> $jobcmd
# makes the temporary scratch directories for grid work
    echo 'mkdir ${_CONDOR_SCRATCH_DIR}/input' >> $jobcmd 
    echo 'mkdir ${_CONDOR_SCRATCH_DIR}/output' >> $jobcmd 
    echo 'cd ${_CONDOR_SCRATCH_DIR}/input/' >> $jobcmd 
    echo '${CPN}'" $DataFilesDir/$filename ./" >> $jobcmd 
#    echo "root -b -q -l 'macros/Ioana_wc_eventntuple_MultiJobs.C(\"$DataFilesDir/$filename\",\"Reco\",\"$OutDir/$outFile\","$ii")'" >> $jobcmd 
#    echo "root -b -q -l '/lbne/app/users/txin/WCSimAnalysis/macros/Ioana_wc_eventntuple_MultiJobs.C(\"$filename\",\"Reco\",\"$outFile\","$ii")'" >> $jobcmd 
#    echo "root -b -q -l '/lbne/app/users/txin/WCSimAnalysis_condor/macros/Ioana_wc_eventntuple_MultiJobs.C(\"$DataFilesDir/$filename\",\"Reco\",\"${_CONDOR_SCRATCH_DIR}/input/$outFile\","$ii")'" >> $jobcmd 
#    echo "root -b -q -l '/lbne/app/users/txin/WCSimAnalysis_condor/macros/Ioana_wc_eventntuple_MultiJobs.C(\"$DataFilesDir/$filename\",\"Reco\",\"$outFile\","$ii")'" >> $jobcmd 
#    echo "root -b -q -l '/lbne/app/users/txin/WCSimAnalysis_condor/macros/Ioana_wc_eventntuple_MultiJobs.C(\"${_CONDOR_SCRATCH_DIR}/input/$filename\",\"Reco\",\"$outFile\","$ii")'" >> $jobcmd
   
# echo "root -b -q -l '/lbne/app/users/txin/WCSimAnalysis_condor/macros/Ioana_wc_eventntuple_MultiJobs.C(\"$filename\",\"Reco\",\"$outFile\","$ii")'" >> $jobcmd


#Last modification!!! read from condor scratch, not DataFilesDir

 #echo "root -b -q -l '/lbne/app/users/ecatanom/WCSimAnalysis/macros/Ioana_wc_eventntuple_MultiJobs.C(\"$DataFilesDir/$filename\",\"Reco\",\"$outFile\","$ii")'" >> $jobcmd 

 echo "root -b -q -l '/lbne/app/users/ecatanom/WCSimAnalysis/macros/Ioana_wc_eventntuple_MultiJobs.C(\"$filename\",\"Reco\",\"$outFile\","$ii")'" >> $jobcmd




# moving and finally copying output file to your /nova/data area
 echo '$MVN ${_CONDOR_SCRATCH_DIR}/input/'"$outFile"' ${_CONDOR_SCRATCH_DIR}/output/'"$otFile" >> $jobcmd
 echo '${CPN} ${_CONDOR_SCRATCH_DIR}/output/'"$outFile"' /lbne/data2/users/ecatanom/042214_muon400_200kton_13per_025ns/' >> $jobcmd

    chmod a+rwx $jobcmd
    jobsub --use_gftp -q -g --opportunistic  $jobcmd
    
  } done 
} done
