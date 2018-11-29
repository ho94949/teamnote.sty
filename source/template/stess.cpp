#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>

using namespace std;

std::string flags = "-O0 -std=c++11";

void compile(const std::string &file) {
    auto command = "g++ " + file + ".cpp" + " -o " + file + " " + flags;
    cerr << "compiling " << file << endl;
    auto res = system(command.data());
    cerr << "result: " << res << endl;
}

bool compareFiles(const std::string& p1, const std::string& p2) {
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; //file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false; //size mismatch
    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

std::string readFile(const std::string &file) {
    std::ifstream f(file);
    auto source = std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
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