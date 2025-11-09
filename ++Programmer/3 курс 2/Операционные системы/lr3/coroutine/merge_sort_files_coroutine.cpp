#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <ctime>
#include <boost/coroutine2/all.hpp>

namespace coro = boost::coroutines2;

using namespace std;

// Coroutine to read numbers from file and sort them
coro::coroutine<vector<int>> sort_coroutine(const string& filename, coro::coroutine<vector<int>>::push_type& sink) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        throw runtime_error("Error opening file");
    }

    vector<int> numbers;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int num;
        while (ss >> num) {
            numbers.push_back(num);
            if (numbers.size() >= 1000) {
                sort(numbers.begin(), numbers.end());
                sink(numbers);
                numbers.clear();
            }
        }
    }

    if (!numbers.empty()) {
        sort(numbers.begin(), numbers.end());
        sink(numbers);
    }
}

// Coroutine to merge sorted numbers
coro::coroutine<int> merge_coroutine(coro::coroutine<vector<int>>::pull_type& source, ofstream& output_file) {
    auto cmp = [](const pair<int, vector<int>>& a, const pair<int, vector<int>>& b) {
        return a.second.front() > b.second.front();
    };
    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, decltype(cmp)> pq(cmp);

    while (source) {
        auto numbers = source.get();
        pq.push({numbers.front(), numbers});
        source();
    }

    while (!pq.empty()) {
        auto [num, numbers] = pq.top();
        pq.pop();
        output_file << num << " ";
        numbers.erase(numbers.begin());
        if (!numbers.empty()) {
            pq.push({numbers.front(), numbers});
        }
    }
}

int main() {
    const vector<string> files = {"file1.txt", "file2.txt", "file3.txt"}; // List your input files here
    ofstream output_file("output.txt");

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    coro::coroutine<vector<int>>::push_type merge_sink(merge_coroutine(coro::coroutine<vector<int>>::pull_type(sort_coroutine(files[0], merge_sink)), output_file));
    for (size_t i = 1; i < files.size(); ++i) {
        sort_coroutine(files[i], merge_sink);
    }
    merge_sink(); // Complete the coroutine chain

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    cout << "Merge sort completed in " << elapsed_time << " seconds." << endl;

    return 0;
}

