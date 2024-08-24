#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

bool isNumber(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void replaceAll(std::string& str, const char* from_, const std::string& to) {
    std::string from = from_;

    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


int main(int argc, const char* argv[]) {
    if ( argc < 4 ) {
        std::cerr << "gen_cpp [input_num] [output_num] [dsp_class] <par1> <par2> <par3> ... " << std::endl;
        return -1;
    }

    const std::string input_number = argv[1];
    const std::string output_number = argv[2];
    const std::string dsp_class = argv[3];
    const int par = 4;

    std::string code;
    std::stringstream ss;
    std::ifstream fis("./gen_tools/cpp.templ");
    ss << fis.rdbuf();
    code = ss.str();

    replaceAll(code, "{input_number}", input_number);
    replaceAll(code, "{output_number}", output_number);
    replaceAll(code, "{dsp_class}", dsp_class);

    ss.str("");ss.clear();
    ss << dsp_class << "~.hpp";
    replaceAll(code, "{dsp_file}", ss.str());

    ss.str("");ss.clear();
    ss << dsp_class << ".hpp";
    replaceAll(code, "{hpp_file}", ss.str());

    ss.str("");ss.clear();
    for (int ii = par; ii < argc; ii++) {
        int i = (argc - 1) - ii + par;
        if ( isNumber(argv[i]) ) {
            continue;
        }
        ss << "        " << argv[i] << "_ = ui.value(\"" << argv[i] << "\");" << std::endl;
    }
    replaceAll(code, "{init_parameters}", ss.str());

    ss.str("");ss.clear();
    for (int ii = par; ii < argc; ii++) {
        int i = (argc - 1) - ii + par;
        if ( isNumber(argv[i]) ) {
            continue;
        }
        ss << "    *" << argv[i] << "_ = stack.pop_number();" << std::endl;
    }
    replaceAll(code, "{load_parameters}", ss.str());

    std::cout << code << std::endl;
}
