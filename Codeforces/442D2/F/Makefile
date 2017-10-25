compile:
	g++ -g $p.cpp -Wall -O2 -lm -DHOME -std=c++0x -o $p 
	./$p < $p.in | diff -sNywbB - $p.out
	./$p < $p.in2 | diff -sNywbB - $p.out2
