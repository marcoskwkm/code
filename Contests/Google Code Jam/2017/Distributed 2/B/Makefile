dcj=/Users/Marcos/Desktop/tmp/dcj.sh

run:
	for f in $p.h*; do \
		echo File $$f... ;\
		cp $$f $p.h ;\
		$(dcj) test --source=$p.cpp --nodes=3 --output=all ;\
		rm $p.h ;\
	done

clean:
	rm *~ $p
