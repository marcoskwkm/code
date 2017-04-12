run: compile
	time ./$p < $p.in | diff -sNywbB - $p.out

compile:
	g++ $p.cpp -Wall -Wshadow -O2 -std=gnu++0x -pthread -DHOME -g -o $p
