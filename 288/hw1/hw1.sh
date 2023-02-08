#!/bin/bash

# Store the input file as a variable
input_file=$1

# Create an array to store the unique tag numbers
declare -a tag_array

# Loop through the input file, line by line
while read line; do
  # Extract the tag number from each line
  tag=`echo $line | cut -c 6-11`

  # Check if the tag is already in the tag array
  found=0
  for i in "${tag_array[@]}"; do
    if [ "$i" == "$tag" ]; then
      found=1
      break
    fi
  done

  # If the tag is not found in the tag array, add it
  if [ $found -eq 0 ]; then
    tag_array+=($tag)
  fi

  # Extract the date and amount from each line
  date=`echo $line | cut -c 17-26`
  amount=`echo $line | cut -c 12-16`

  # Append the date and amount to the corresponding tag file
  echo $date $amount >> $tag
done < $input_file

# Loop through the tag array and process each tag file
for tag in "${tag_array[@]}"; do
  # Create a temporary file to store the processed data
  temp_file="temp_$tag"

  # Sort the tag file by date
  sort $tag > $temp_file

  # Initialize the balance to 0
  balance=0.00

  # Loop through the temporary file and calculate the balance for each date
  while read line; do
    # Extract the date and amount from each line
    date=`echo $line | awk '{print $1}'`
    amount=`echo $line | awk '{print $2}'`

    # Add the amount to the balance
    balance=$(echo "$balance + $amount" | bc)

    # Append the date and balance to the final output file
    echo $date,$balance >> "$tag.out"
  done < $temp_file

  # Remove the temporary file
  rm $temp_file

  # Remove the tag file
  rm $tag
done
