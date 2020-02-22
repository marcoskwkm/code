#include "library_score_solver.h"

#include <bits/stdc++.h>

#include "library.h"
#include "solution.h"

using namespace std;

vector<int> book_freq;
vector<bool> book_scanned;
vector<bool> library_done;

long double t_exp = 1;
long double book_exp = 2;

void getBookFrequencies(const vector<Library*> &libraries) {
    book_freq = vector<int>(B, 0);

    for (Library *library: libraries) {
        if (library_done[library->id]) continue;
        for (Book *book: library->books) {
            book_freq[book->id]++;
        }
    }
}

long double calculateScore(const Library *library, lint elapsed_time) {
    long double score = 0;

    int n_scanned = 0;
    for (Book *book: library->books) {
        if (elapsed_time + library->T + (n_scanned + library->M) / library->M >= D) {
            break;
        }
        if (book_scanned[book->id]) continue;

        n_scanned++;
        score += book->S / pow(book_freq[book->id], book_exp);
    }

    score /= pow((long double)library->T, t_exp);

    return score;
}

vector<long double> calculateScores(vector<Library*> &libraries, lint elapsed_time) {
    vector<long double> library_scores(L, 0);

    for (Library *library: libraries) {
        library_scores[library->id] = calculateScore(library, elapsed_time);
    }

    return library_scores;
}

Solution libraryScoreSolver(vector<Library*> libraries) {
    book_scanned = vector<bool>(B, 0);
    library_done = vector<bool>(L, 0);

    getBookFrequencies(libraries);

    Solution best_solution(libraries);

    lint elapsed_time = 0;
    vector<long double> library_scores = calculateScores(libraries, elapsed_time);
    sort(libraries.begin(), libraries.end(), [&](Library *a, Library *b) {
        return library_scores[a->id] > library_scores[b->id];
    });

    Solution new_solution(libraries);
    if (new_solution.score > best_solution.score) {
        best_solution = new_solution;
    }

    return best_solution;
}

bool checkTooSlow(const vector<Library*> libraries) {
    lint total_books = 0;
    for (Library *library: libraries) {
        total_books += library->books.size();
    }

    debug("Data size: %lld\n", total_books * (lint)libraries.size());
    return total_books * (lint)libraries.size() > 1e10;
}

Solution slowLibraryScoreSolver(vector<Library*> libraries) {
    if (checkTooSlow(libraries)) {
        fprintf(stderr, "Data too large to use slow solver, defaulting to one-step solution\n");
        return libraryScoreSolver(libraries);
    }

    book_scanned = vector<bool>(B, 0);
    library_done = vector<bool>(L, 0);

    getBookFrequencies(libraries);

    Solution best_solution(libraries);

    lint elapsed_time = 0;
    for (size_t i = 0; i < libraries.size(); i++) {
        vector<long double> library_scores = calculateScores(libraries, elapsed_time);

        size_t best_idx = i;
        for (size_t j = i + 1; j < libraries.size(); j++) {
            if (library_scores[j] > library_scores[best_idx]) {
                best_idx = j;
            }
        }

        swap(libraries[i], libraries[best_idx]);

        library_done[libraries[i]->id] = 1;
        int n_scanned = 0;
        for (Book *book: libraries[i]->books) {
            if (elapsed_time + libraries[i]->T + (n_scanned + libraries[i]->M) / libraries[i]->M >= D) {
                break;
            }
            book_scanned[book->id] = 1;
            n_scanned++;
        }
    }

    Solution new_solution(libraries);
    if (new_solution.score > best_solution.score) {
        best_solution = new_solution;
    }

    return best_solution;
}
