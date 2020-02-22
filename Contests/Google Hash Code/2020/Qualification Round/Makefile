OBJDIR := obj
SRCDIR := src
INDIR := inputs
OUTDIR := outputs
CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(CPP_FILES))
CC := g++-9
CFLAGS := -O2
PROG_FLAGS :=

main: $(OBJ_FILES)
	$(CC) $^ -g -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $< -c -g -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	rm -rf $(OBJDIR)
	rm main
	rm src.zip

test: main
	./main $(PROG_FLAGS) < inputs/a_example.txt

run: main | $(OUTDIR)
	for f in $(INDIR)/*.txt; do \
		echo File $$f ;\
		time ./main $(PROG_FLAGS) < $$f > `echo $$f | sed s/$(INDIR)/$(OUTDIR)/` ;\
		echo ;\
	done
	zip -rq src.zip $(SRCDIR)/*
