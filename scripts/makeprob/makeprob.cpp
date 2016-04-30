#include <bits/stdc++.h>
using namespace std;

const int MAXL = 1000;
char FOLDER[] = "~/code/templates";

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr,"Usage: makeprob <foldername> <filename-no-extension>\n");
        return 0;
    }
    char line[MAXL];
    sprintf(line,"mkdir '%s'",argv[1]);
    system(line);
    sprintf(line, "cp %s/template.cpp '%s'/%s.cpp", FOLDER, argv[1], argv[2]);
    system(line);
    sprintf(line, "cp %s/Makefile '%s'/Makefile", FOLDER, argv[1]);
    system(line);
    sprintf(line, "touch '%s'/tags", argv[1]);
    system(line);
    return 0;
}
