#!/bin/bash
logf="lsf.log"
errf="lsf.err"
test -f "$logf" && mv -v "$logf" "$logf-b4_$(date +'%F_%T')"
test -f "$errf" && mv -v "$errf" "$errf-b4_$(date +'%F_%T')"

bsub <<!
#!/bin/bash -l
#BSUB -q BatchXL
#BSUB -L /bin/csh
#BSUB -R "span[hosts=1] mem>6000"
#BSUB -J "$(basename $PWD)"
#BSUB -o "$logf"
#BSUB -e "$errf"

./benchmark.sh benchmark_\${LSB_HOSTS}_40.log 40
!
