#ifndef BOOK_H
#define BOOK_H

#include <bits/stdc++.h>

#include "common.h"

using namespace std;

const int MAX_BOOKS = (int)1e5 + 10;

struct Library;

struct Book {
    int id;
    lint S;
    vector<Library*> libraries;
};

Book* newBook();

Book* bookById(int id);

#endif
