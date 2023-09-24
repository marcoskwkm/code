run:
	g++-12 $p.cpp -Wall -Wshadow -O2 -std=c++20 -DHOME -Wl,-stack_size -Wl,20000000 -o $p
	for f in $p.in*; do \
		echo File $$f... ;\
		time ./$p < $$f | diff -sNywbB - $p.out$${f#$p.in} ;\
	done

debug:
	g++-12 $p.cpp -Wall -Wshadow -std=c++20 -DHOME -Wl,-stack_size -Wl,20000000 -g -o $p
	for f in $p.in*; do \
		echo File $$f... ;\
		time ./$p < $$f | diff -sNywbB - $p.out$${f#$p.in} ;\
	done


clean:
	rm *~ $p
