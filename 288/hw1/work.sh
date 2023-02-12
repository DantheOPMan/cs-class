#!/bin/bash

input=$1
declare -A balances

while read line; do
    tagNumber=${line:5:6}
    date=${line:16:10}
    amount=${line:11:5}

    if [ -z "${balances[$tagNumber,$date]}" ]; then
        balances[$tagNumber,$date]=$amount
    else
        balances[$tagNumber,$date]=$(echo "${balances[$tagNumber,$date]} + $amount" | bc)
    fi
done < $input

tagNumbers=($(echo "${!balances[@]}" | tr ' ' '\n' | cut -d ',' -f 1 | sort -u))
for tagNumber in "${tagNumbers[@]}"; do
    echo -n "" > $tagNumber
    
    dates=($(echo "${!balances[@]}" | tr ' ' '\n' | grep -E "$tagNumber," | cut -d ',' -f 2 | sort -n -t"/" -k3 -k1 -k2))
    balance=0
    for date in "${dates[@]}"; do
        balance=$(echo "$balance + ${balances[$tagNumber,$date]}" | bc)
        if [ ${balance:0:1} = "." ]; then
            echo "$date,0$balance" >> "$tagNumber"
        else
            echo "$date,$balance" >> "$tagNumber"
        fi
        
    done
done