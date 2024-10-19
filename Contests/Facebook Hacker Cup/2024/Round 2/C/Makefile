COMPILER=g++-14
COMPILE_FLAGS=-Wall -Wshadow -O2 -std=c++23 -DHOME -Wl,-stack_size -Wl,20000000

run:
	$(COMPILER) $p.cpp $(COMPILE_FLAGS) -o $p
	for f in $p.in*; do \
		echo File $$f... ;\
		time ./$p < $$f | diff -sNywbB - $p.out$${f#$p.in} ;\
	done

debug:
	$(COMPILER) $p.cpp $(COMPILE_FLAGS) -g -o $p
	for f in $p.in*; do \
		echo File $$f... ;\
		time ./$p < $$f | diff -sNywbB - $p.out$${f#$p.in} ;\
	done


clean:
	rm *~ $p
