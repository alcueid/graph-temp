#! /bin/sh

fname="$(date +%F)_temp.log"
name_flag=0

# check arguments
if [ $# -ne 1 ]
then
	echo "usage: $0 dir"
fi

# serach file
for file in *
do
	if [ "$file" = "$fname" ]
	then
		name_flag=1
	fi
done


# make log file
if [ $name_flag -eq 0 ]
then
	touch "$fname"
fi


# save cpu temp
data="$(date +%H:%M)"
val="$(cat /sys/class/thermal/thermal_zone0/temp)"
val=`echo "scale=3; $val / 1000" | bc`
echo "$data $val" >> $1$fname
