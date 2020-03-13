paste <(awk '{print $1"\t" $2"\t" $3"\t" $5"\t" $7}' offset_fit_data.dat) | sort -nk 2 < (awk'{print $8}' offset.txt)| sort -nk 3 >> prueba.txt 
