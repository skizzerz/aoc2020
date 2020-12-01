#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <cstdlib>
using namespace std;

struct ele {
    short v1; // if nonzero, individual number equals this position
    short v2; // if nonzero, sum of v2 and v3 equals this position
    short v3; // if nonzero, sum of v2 and v3 equals this position
};

int main() {
    fstream f{ "input.txt", fstream::in };
    vector<short> values;
    short v;
    while (!f.eof()) {
        f >> v;
        if (f.fail()) {
            break;
        }

        values.push_back(v);
    }

    sort(values.begin(), values.end());
    auto max = values.size();

    // allocate an array of 2020 x max to hold the subset-sum subproblems
    // array elements are 3-tuples of ints; 0 is used as placeholders if that int doesn't participate; see ele struct for more details
    ele* work = new ele[2020 * max];
    memset(work, 0, 2020 * max * sizeof(ele));
    ele dummy = {};

    for (size_t j = 0; j < 2020; ++j) {
        if (values[0] == j + 1) {
            work[j].v1 = values[0];
        }
    }

    for (size_t i = 1; i < max; ++i) {
        for (short j = 0; j < 2020; ++j) {
            auto index = i * 2020 + j;
            auto prevOffset = (i - 1) * 2020;
            const ele& prevNoAdd = work[prevOffset + j];
            ele& prevAdd = dummy;
            if (j - values[i] >= 0) {
                prevAdd = work[prevOffset + j - values[i]];
            }

            if (values[i] == j + 1) {
                // current value equals our target
                work[index].v1 = values[i];
            } else if (prevNoAdd.v1 != 0) {
                // previous single value already equalled our target
                work[index].v1 = prevNoAdd.v1;
            }

            if (prevNoAdd.v2 != 0) {
                // previous sum of 2 values already equalled our target
                work[index].v2 = prevNoAdd.v2;
                work[index].v3 = prevNoAdd.v3;
            } else if (j - values[i] >= 0 && prevAdd.v1 != 0) {
                // previous single value plus our current value equals our target
                work[index].v2 = prevAdd.v1;
                work[index].v3 = values[i];
            }

            if (prevAdd.v2 != 0 && j == 2019) {
                // previous sum of values plus our current value equals 2020 -- this is our solution
                cout << values[i] * prevAdd.v2 * prevAdd.v3;
                return 0;
            }
        }
    }

    cout << "Nothing found" << endl;
    return 0;
}
