#ifndef LIBRARY_H
#define LIBRARY_H

#include <bits/stdc++.h>

#include "book.h"
#include "common.h"

using namespace std;

const int MAX_LIBRARIES = (int)1e5 + 10;

struct Library {
    int id;
    lint N, T, M;
    vector<Book*> books;

    Library();
    Library(Library *library);
};

Library* newLibrary();

Library* libraryById(int id);

#endif
