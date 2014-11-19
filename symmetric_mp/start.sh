#! /bin/bash

#check in arguments
if [ $# -ne 3 ];then
    echo Usage $0 portid lcore_start queue_num
    exit
fi

#get arguments
portid=$1
portid_mask=`python -c "print 1 << $1"`
lcore_start=`python -c "print 1 << $2"`
queue_num=$3
process="./build/symmetric_mp"

for (( i=0; i< $queue_num; i++))
{
lcore_mask=`echo "obase=16;$lcore_start"|bc`
if [ $i -eq 0 ];then
	$process -c $lcore_mask -n 4 --proc-type=auto -- -p $portid_mask --num-procs=$queue_num --proc-id=$i --create-port=1 &
else
	$process -c $lcore_mask -n 4 --proc-type=auto -- -p $portid_mask --num-procs=$queue_num --proc-id=$i &
fi
pid_file="./port["$portid"]_proc["$i"].pid"
while [ ! -f "$pid_file" ]
do
    sleep 1s
done
lcore_start=${lcore_start}*2;
}
