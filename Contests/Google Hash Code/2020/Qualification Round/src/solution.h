#ifndef SOLUTION_H
#define SOLUTION_H

#include <bits/stdc++.h>

#include "common.h"
#include "library.h"

using namespace std;

struct Solution {
    lint score;
    vector<Library> modified_libraries;

    Solution(const vector<Library*> &libraries);

    void print();
};

#endif
