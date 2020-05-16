run:
	for f in $p.in*; do \
		echo File $$f... ;\
		time python $p.py < $$f | diff -sNywbB - $p.out$${f#$p.in} ;\
	done

clean:
	rm *~ $p
