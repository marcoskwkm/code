
run:
	g++-10 sol.cpp -Wall -Wshadow -O2 -std=c++17 -DHOME -g -o sol
	for f in sample.in*; do \
		echo Sample $${f#sample.in}... ;\
		time ./sol < $$f | diff -sNywbB - sample.out$${f#sample.in} ;\
	done

clean:
	rm *~ sol

submit:
	cf-crawler submit -p=cf -i=1519 -P=B sol.cpp
