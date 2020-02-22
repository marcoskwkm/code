#include <bits/stdc++.h>

#include "book.h"

using namespace std;

Book books[MAX_BOOKS];
int n_books = 0;

Book* newBook() {
    return &books[n_books++];
}

Book* bookById(int id) {
    return &books[id];
}
