run:
	g++-10 sol.cpp -Wall -Wshadow -O2 -std=c++20 -DHOME -g -o sol
	for f in sample.in*; do \
		echo File $$f... ;\
		time ./sol < $$f | diff -sNywbB - sample.out$${f#sample.in} ;\
	done

clean:
	rm *~ $p
