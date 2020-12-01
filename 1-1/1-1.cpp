#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    fstream f{ "input.txt", fstream::in };
    vector<int> values;
    int v;
    while (!f.eof()) {
        f >> v;
        if (f.fail()) {
            break;
        }

        values.push_back(v);
    }

    sort(values.begin(), values.end());
    auto max = values.size();
    for (auto i : values) {
        auto prevHigh = max - 1;
        auto prevLow = 0;
        // do a binary search for things that add to 2020
        while (true) {
            auto cur = (prevHigh - prevLow) / 2 + prevLow;
            if (i + values[cur] == 2020) {
                cout << i * values[cur] << endl;
                return 0;
            } else if (i + values[cur] > 2020) {
                if (cur == prevHigh) {
                    break;
                }

                prevHigh = cur;
            } else {
                if (cur == prevLow) {
                    break;
                }

                prevLow = cur;
            }
        }
    }

    cout << "Nothing found" << endl;
    return 0;
}
