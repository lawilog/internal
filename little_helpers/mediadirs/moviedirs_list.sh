time ./moviedirs_largefiles.sh $(ls -1d /mnt/*/{Filme_upload,Filme_sortiert} | grep -v oracle) | sort > /mnt/drop/movielist_20150606_largefiles.txt
time ./moviedirs_comma_rec.sh $(ls -1d /mnt/*/{Filme_upload,Filme_sortiert} | grep -v oracle) | sort > /mnt/drop/movielist_20150606_commarec.txt

# go online, generate candidates
cat /mnt/drop/movielist_20150606_commarec.txt | ./moviedirs_query.sh

# sort candidates by their matching points
cat /mnt/drop/movielist_20150606_commarec.txt | ./moviedirs_match.sh | tee /dev/stderr | sort -t $'\t' -n -k2 -r >/mnt/drop/movielist_20150606_match2.dat

# corrections
cat /mnt/drop/movielist_20150606_commarec.txt | while read dir; do echo "$dir"; test -e "$dir/imdb_match_list.dat" && awk '(NF>1){gsub("http://","",$0); gsub("&amp;","and",$0); print $0}' "$dir/imdb_match_list.dat" > "$dir/imdb_candidates.dat"; rm -f "$dir/imdb_match_candidates.dat" "$dir/imdb_match_list.dat"; done

# stats
awk -F'\t' '{if($2==100) ++p; if($2>0 && $2<100) ++l; if($2<=0) ++n} END{print p,l,n, "\n", p/NR, l/NR, n/NR}' /mnt/drop/movielist_20150606_match2.dat
