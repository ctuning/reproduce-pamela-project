for i in `seq 1 1000`;
do
 ck run program extra_env="export OPENCL_DEVICE=0" cmd_key=cmd1 dataset_uoa=a142fe548c798362
done    
