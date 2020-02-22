#include <bits/stdc++.h>

#include "book.h"
#include "common.h"
#include "flags.h"
#include "grader.h"
#include "library.h"
#include "solution.h"

#include "library_score_solver.h"

using namespace std;

void parseCommandLineArguments(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            VERBOSE_MODE = 1;
        }
    }
}

vector<Book*> readBooks() {
    vector<Book*> books;

    for (int i = 0; i < B; i++) {
        Book *book = newBook();
        book->id = i;
        cin >> book->S;

        books.push_back(book);
    }

    return books;
}

vector<Library*> readLibraries(const vector<Book*> &books) {
    vector<Library*> libraries;

    for (int i = 0; i < L; i++) {
        Library *library = newLibrary();
        library->id = i;
        cin >> library->N >> library->T >> library->M;

        for (int j = 0; j < library->N; j++) {
            int book_id;
            cin >> book_id;
            Book *book = bookById(book_id);

            library->books.push_back(book);
            book->libraries.push_back(library);
        }

        sort(library->books.begin(), library->books.end(), [](Book *a, Book *b) {
            return a->S > b->S;
        });

        libraries.push_back(library);
    }

    return libraries;
}

int main(int argc, char* argv[]) {
    parseCommandLineArguments(argc, argv);

    cin >> B >> L >> D;

    vector<Book*> books = readBooks();
    vector<Library*> libraries = readLibraries(books);

    Solution solution = slowLibraryScoreSolver(libraries);
    fprintf(stderr, "Solution score: %lld\n", solution.score);
    solution.print();

    return 0;
}
