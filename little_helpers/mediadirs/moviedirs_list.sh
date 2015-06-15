time ./moviedirs_largefiles.sh $(ls -1d /mnt/*/{Filme_upload,Filme_sortiert} | grep -v oracle) | sort > /mnt/drop/movielist_20150606_largefiles.txt
time ./moviedirs_comma_rec.sh $(ls -1d /mnt/*/{Filme_upload,Filme_sortiert} | grep -v oracle) | sort > /mnt/drop/movielist_20150606_commarec.txt

# go online, generate candidates
cat /mnt/drop/movielist_20150606_commarec.txt | ./moviedirs_query.sh

# sort candidates by their matching points
cat /mnt/drop/movielist_20150606_commarec.txt | ./moviedirs_match.sh | tee /dev/stderr | sort -t $'\t' -n -k2 -r >/mnt/drop/movielist_20150606_match2.dat

# stats
awk -F'\t' '{if($2==100) ++p; if($2>0 && $2<100) ++l; if($2<=0) ++n} END{print p,l,n, "\n", p/NR, l/NR, n/NR}' /mnt/drop/movielist_20150606_match2.dat
