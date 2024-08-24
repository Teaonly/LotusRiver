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
    if ( argc < 3 ) {
        std::cerr << "gen_cpp [output_num] [dsp_class] <par1> <par2> <par3> ... " << std::endl;
        return -1;
    }

    const size_t output_num = atoi(argv[1]);
    const std::string dsp_name = argv[2];
    const size_t par_num = argc - 3;

    std::string DSP_NAME = dsp_name;
    std::transform(dsp_name.begin(), dsp_name.end(), DSP_NAME.begin(), ::toupper);

    std::stringstream ss;
    for (size_t i = 0; i < par_num; i++) {
        if ( isNumber( argv[3 + i] ) ) {
            continue;
        }
        ss << "    FAUSTFLOAT* " << argv[3 + i] << "_;" << std::endl;
    }
    const std::string dsp_parameters = ss.str();

    ss.str("");ss.clear();
    ss << "Vec outputs_[" << output_num << "];";
    const std::string output_names = ss.str();

    ss.str("");ss.clear();
    std::ifstream fis("./gen_tools/hpp.templ");
    ss << fis.rdbuf();

    std::string code = ss.str();

    replaceAll(code, "{dsp_name}", dsp_name);
    replaceAll(code, "{DSP_NAME}", DSP_NAME);
    replaceAll(code, "{dsp_parameters}", dsp_parameters);
    replaceAll(code, "{output_names}", output_names);

    std::cout << code << std::endl;
}
