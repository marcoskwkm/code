#include <bits/stdc++.h>

#include "book.h"
#include "common.h"
#include "flags.h"
#include "library.h"
#include "solution.h"

using namespace std;

Solution::Solution(const vector<Library*> &libraries) {
    lint elapsed_time = 0;
    vector<bool> scanned_book(B, 0);

    score = 0;

    for (Library *library: libraries) {
        if (elapsed_time + library->T >= D) {
            // Can't register this library in time
            continue;
        }

        Library modified_library(library);

        int scanned_cnt = 0;
        for (Book *book: library->books) {
            if (elapsed_time + library->T + (scanned_cnt + library->M) / library->M >= D) {
                break;
            }
            if (scanned_book[book->id])  {
                continue;
            }

            scanned_book[book->id] = 1;
            scanned_cnt++;
            score += book->S;
            modified_library.books.push_back(book);
        }

        if (scanned_cnt > 0) {
            modified_libraries.push_back(modified_library);
            elapsed_time += library->T;
        }
    }
}

void Solution::print() {
    printf("%d\n", (int)modified_libraries.size());
    for (const Library &library: modified_libraries) {
        printf("%d %d\n", library.id, (int)library.books.size());
        for (Book *book: library.books) {
            printf("%d ", book->id);
        }
        printf("\n");
    }
}
