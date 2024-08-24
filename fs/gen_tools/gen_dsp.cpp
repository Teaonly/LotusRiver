#include <iostream>
#include <algorithm>

bool isNumber(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int main(int argc, const char* argv[]) {
    if ( argc < 2 ) {
        std::cerr << "gen_dsp [dsp_name] <par1> <par2> <par3> ... " << std::endl;
        return -1;
    }
    const char* dsp_name = argv[1];
    const size_t par_num = argc - 2;

    std::cout << "import(\"stdfaust.lib\");" << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < par_num; i++) {
        const char* par_name = argv[i+2];

        if ( isNumber(par_name) ) {
            continue;
        }

        std::cout << par_name << " = nentry(\"";
        std::cout << par_name << "\", 0, 0, 1.0, 0.1);" << std::endl;
    }
    std::cout << std::endl;

    if ( par_num == 0) {
        std::cout << "process = " << dsp_name << ";" << std::endl;
    } else {
        std::cout << "process = " << dsp_name << "(";
        for (size_t i = 0; i < par_num; i++) {
            const char* par_name = argv[i+2];

            std::cout << par_name ;
            if ( i == par_num - 1) {
                std::cout << ");" << std::endl;
            } else {
                std::cout << ", ";
            }
        }
    }
}
