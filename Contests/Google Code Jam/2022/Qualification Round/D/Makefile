run:
	g++-11 $p.cpp -Wall -Wshadow -O2 -std=c++20 -DHOME -g -o $p
	for f in c.in*; do \
		echo File $$f... ;\
		time ./$p < $$f | diff -sNywbB - c.out$${f#c.in} ;\
	done

clean:
	rm *~ $p
