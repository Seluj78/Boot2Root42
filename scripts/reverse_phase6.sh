#!/bin/bash
input="./brute5"
while IFS= read -r line
do
  echo "$line"
	echo -e "Public speaking is very easy.\n1 2 6 24 120 720\n2 b 755\n9\nopekma\n$line\n" | ./bomb
done < "$input"
