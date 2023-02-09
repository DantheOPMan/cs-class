#!/bin/bash

# Store the input file name
input_file=$1

# Create an associative array to store the balance for each tag
declare -A balances

# Read the input file line by line
while IFS='' read -r line || [[ -n "$line" ]]; do
  # Extract the tag, date, and amount from the line
  tag=${line:5:6}
  date=${line:16:10}
  amount=${line:11:5}

  # If the tag is not in the balances array, initialize its balance to 0
  if [ -z "${balances["$tag"]}" ]; then
    balances["$tag"]=0
    echo -n "" > "$tag"
  fi

  # Add the amount to the balance for the current tag
  balances["$tag"]=$(echo "${balances["$tag"]} + $amount" | bc)

  # Write the date and balance to the output file for the current tag
  echo "$date ${balances["$tag"]}" >> "$tag"temp
done < "$input_file"

