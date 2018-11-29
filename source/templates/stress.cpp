#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>

using namespace std;

string flags = "-DLOCAL -O2 -std=c++14 -Wall -Wextra -Wno-unused-result -fsanitize=bounds";

void compile(const string &file) {
    auto command = "g++ " + file + ".cpp" + " -o " + file + " " + flags;
    cerr << "compiling " << file << endl;
    auto res = system(command.data());
    cerr << "result: " << res << endl;
}

// use this function only if you need <checker>!
bool compareFiles(const string& p1, const string& p2) {
    ifstream f1(p1, ifstream::binary|ifstream::ate);
    ifstream f2(p2, ifstream::binary|ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; //file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false; //size mismatch
    }

    //seek back to beginning and use equal to compare contents
    f1.seekg(0, ifstream::beg);
    f2.seekg(0, ifstream::beg);
    return equal(istreambuf_iterator<char>(f1.rdbuf()),
                      istreambuf_iterator<char>(),
                      istreambuf_iterator<char>(f2.rdbuf()));
}

string readFile(const string &file) {
    ifstream f(file);
    auto source = string(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
    return source;
}

int main() {
    compile("solution");
    compile("slow");
    compile("gen");

    auto t1 = clock();
    while (true) {
        cerr << "generator..." << endl;
        assert(!system("gen.exe > xxx.in"));
        cerr << "solution..." << endl;
        assert(!system("solution.exe < xxx.in > xxx.out"));
        cerr << "slow..." << endl;
        assert(!system("slow.exe < xxx.in > xxx.ans"));
        // if (!assert(!system("fc xxx.out xxx.ans"))) {
        if (!compareFiles("xxx.out", "xxx.ans")) {
            auto t2 = clock();
            cout << "time: " << (t2 - t1) * 1.0 / CLOCKS_PER_SEC << endl;

            cout << "test:" << endl;
            cout << readFile("xxx.in") << endl;
            cout << "solution:" << endl;
            cout << readFile("xxx.out") << endl;
            cout << "slow:" << endl;
            cout << readFile("xxx.ans") << endl;

            break;
        }
    }
    return 0;
}