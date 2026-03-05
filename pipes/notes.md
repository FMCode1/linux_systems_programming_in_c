Copy a file into another

cat file.txt | sort > sorted.txt

cat file.txt | grep -i we returns case sensitive

cat file.txt | grep -w we searches for whole words

cat file.txt | grep -wn we searches for where something appears on a line number

| > < less than gives input to a command from another file

wc file.txt can get the word count of a file

wc < file.txt

cat file.txt | (meaning pipe) wc

playing around with searching through pokemon.csv

cat pokemon.csv | grep True checks for legendary values that are true
cat pokemon.csv | wc -l gives number of returned

>> redirect and append without losig file

awk is a scrpting language that allows you split with commas

cat pokemon.csv | grep Charizard | awk -F, '{print S1}'

cat pokemon.csv | grep Charizard | awk -F, '{print S2 " is Type 2" $4}'

cat pokemon.csv | grep Charizard | awk -F, '{print S2 " Total is same as" $6 + $7}'


rename Charizard


we are creating an unnamed pipe between 2 different forks

cat colorFile.txt | sort sorts alphabetically

dup2 takes a file descriptor, and destination of where we wan to copy to, dup2(f_des[1], 1);

Looking for the word IS

grep is colorFile.txt or grep -v is colorFile.txt for the lines that doen't contain "Is"

-nv, -i, -H

to search a man page, run it and go

./-i or whatever command

-w searches for it as a whole word
-o provides a copy of the text of the match for every match, without any context

in the lab notes is execl but we can use execvp by using null terminated arrays of cstrings eg in catSort

exec