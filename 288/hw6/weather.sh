#!/bin/bash

while true
do
  websites=$(cat sources.txt)
  
  counter=1
  current_time=$(date +"%Y-%m-%d-%H-%M-%S")
  tagsoup_url="https://repo1.maven.org/maven2/org/ccil/cowan/tagsoup/tagsoup/1.2.1/tagsoup-1.2.1.jar"
  tagsoup_name="tagsoup-1.2.1.jar"

  if [ ! -e "$tagsoup_name" ]; then
    curl -O "$tagsoup_url"
  fi

  for site in $websites
  do
    case $counter in
      1) url="$current_time-NY";;
      2) url="$current_time-CA";;
      3) url="$current_time-IL";;
      4) url="$current_time-TX";;
      5) url="$current_time-AZ";;
      6) url="$current_time-PA";;
      7) url="$current_time-FL";;
    esac
    wget -qO- $site > $url.html
    counter=$((counter+1))
    java -jar $tagsoup_name --files $url.html
    python3 parser.py $url.xhtml
    rm $url.html
    rm $url.xhtml
  done
 
  sleep 6h
done
