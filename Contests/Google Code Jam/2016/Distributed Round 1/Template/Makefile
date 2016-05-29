dcj=/home/marcos/dcj/dcj.sh

run:
	for f in $p.h*; do \
		echo File $$f... ;\
		cp $$f $p.h ;\
		$(dcj) test --source=$p.cpp --nodes=10 --output=all ;\
		rm $p.h ;\
	done

clean:
	rm *~ $p
