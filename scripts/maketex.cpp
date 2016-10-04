#include <bits/stdc++.h>
using namespace std;

const int MAXL = 1000;
char FOLDER[] = "~/code/templates";

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr,"Usage: maketex file-name\n");
        return 0;
    }
    char line[MAXL];
    sprintf(line, "cp %s/template.tex %s", FOLDER, argv[1]);
    system(line);
    return 0;
}
