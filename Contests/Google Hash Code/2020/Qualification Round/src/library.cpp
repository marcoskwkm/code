#include <bits/stdc++.h>

#include "library.h"

using namespace std;

Library libraries[MAX_LIBRARIES];
int n_libraries = 0;

Library::Library() {}

Library::Library(Library *library) {
    id = library->id;
    N = library->N;
    T = library->T;
    M = library->M;
}

Library* newLibrary() {
    return &libraries[n_libraries++];
}

Library* libraryById(int id) {
    return &libraries[id];
}
