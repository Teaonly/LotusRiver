#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <chrono>

#include "lr.hpp"
#include "zz/zz_impl.hpp"
#include "fs/fs_impl.hpp"
#include "io/io_impl.hpp"
#include "nn/nn_impl.hpp"

std::string fileToString(const char* filename) {
    std::ifstream t(filename);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    return str;
}

int main(int argc, const char* argv[] ) {
    if ( argc < 4 ) {
        std::cout << "synth <sample_rate> <run_times> <code_file0> ..." << std::endl;
        return 0;
    }
    const int sr = atoi( argv[1] );
    if ( sr < 8000) {
        std::cout << "Sample rate can't be lower than 8K " << std::endl;
        return 0;
    }
    const int run_times = atoi( argv[2] );
    if ( run_times < 1) {
        std::cout << "Run times can't be lower than one" << std::endl;
        return 0;
    }

    lr::Enviroment env(sr);
    lr::zz::init_words(env);
    lr::io::init_words(env);
    lr::fs::init_words(env);
    lr::nn::init_words(env);

    std::string codes;
    for (int i = 3; i < argc; i++) {
        auto txt = fileToString(argv[i]);
        codes = codes + "\n" + txt;
    }

    auto rt = env.runtime(codes);
    for (int i = 0; i < run_times; i++) {
        rt.run();

        // in synth mode, we dont't play it
        rt.stack().clear();
    }
}

