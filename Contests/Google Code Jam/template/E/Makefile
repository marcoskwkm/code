run:
	g++-9 $p.cpp -Wall -Wshadow -O2 -std=gnu++0x -DHOME -g -o $p
	for f in $p.in*; do \
		echo File $$f... ;\
		time ./$p < $$f | diff -sNywbB - $p.out$${f#$p.in} ;\
	done

clean:
	rm *~ $p
