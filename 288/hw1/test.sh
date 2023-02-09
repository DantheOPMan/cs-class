#!/bin/bash

input_file=$1
output_file="output"
temp_file="temp_file"

# Read each line of the input file, extract the columns, and write to a temporary file
while read line; do
  dates=($(cat $input_file))
  echo "$transaction_date $account_number $tag_number $amount_paid" >> $temp_file
done < $input_file

# Sort the temporary file by transaction date
sort -k1 $temp_file -o $output_file

# Remove the temporary file
rm $temp_file
