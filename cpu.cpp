#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

int counter = 0;

std::vector <std::string> register_list = {"eax", "ebx", "ecx", "edx", "eex", "efx", "ejx", "ehx", "eix", "flag"};
std::vector <std::string> mnemonics = {"mov", "add", "sub", "mul", "div", "and", "or", "cmp"};
std::vector <std::string> mnemonics_jmp = {"jmp", "jl", "jle", "jg", "jge", "je"};                                
std::map <std::string, int> labels;
class FakeCPU {
   public:
    void mov (std::string& dest, int src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                m_registers[i] = src;
            }
        }
    }
    void mov (std::string& dest, std::string& src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src == register_list[j]){
                        m_registers[i] = m_registers[j];
                        break;
                    }
                }
            }
        }
    }
     void add (std::string& dest, int src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                m_registers[i] += src;
            }
        }
    }
    void add (std::string& dest, std::string& src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src == register_list[j]){
                        m_registers[i] += m_registers[j];
                        break;
                    }
                }
            }
        }
    }
    void sub (std::string& dest, int src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                m_registers[i] -= src;
            }
        }
    }
    void sub (std::string& dest, std::string& src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src == register_list[j]){
                        m_registers[i] -= m_registers[j];
                        break;
                    }
                }
            }
        }
    }
    void mul (std::string& dest, int src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                m_registers[i] *= src;
            }
        }
    }
    void mul (std::string& dest, std::string& src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src == register_list[j]){
                        m_registers[i] *= m_registers[j];
                        break;
                    }
                }
            }
        }
    }
    void div (std::string& dest, int src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                m_registers[i] /= src;
            }
        }
    }
    void div (std::string& dest, std::string& src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src == register_list[j]){
                        m_registers[i] /= m_registers[j];
                        break;
                    }
                }
            }
        }
    }
    void and_ (std::string& dest, int src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                m_registers[i] = m_registers[i] & src;
            }
        }
    }
    void and_ (std::string& dest, std::string& src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src == register_list[j]){
                        m_registers[i] = m_registers[i] & m_registers[j];
                        break;
                    }
                }
            }
        }
    }
    void or_ (std::string& dest, int src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                m_registers[i] = m_registers[i] | src;
            }
        }
    }
    void or_ (std::string& dest, std::string& src) {
        for (int i =0; i < register_list.size(); ++i){
            if (dest == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src == register_list[j]){
                        m_registers[i] = m_registers[i] | m_registers[j];
                        break;
                    }
                }
            }
        }
    }
    void cmp (std::string& src1, int src2) {
        for (int i =0; i < register_list.size(); ++i){
            if (src1 == register_list[i]) {
               if (m_registers[i] < src2) {
                m_registers[9] = -1;
                return;
               }
               else if (m_registers[i] > src2) {
                m_registers[9] = 1;
                return;
               }
               else {
                m_registers[9] = 0;
                return;
               } 
            }
        }
    }
    void cmp (std::string& src1, std::string& src2) {
        for (int i =0; i < register_list.size(); ++i){
            if (src1 == register_list[i]) {
                for (int j = 0; j < register_list.size(); ++j){
                    if (src2 == register_list[j]){
                        if (m_registers[i] < m_registers[j]) {
                            m_registers[9] = -1;
                            return;
                        }
                        else if (m_registers[i] > m_registers[j]) {
                            m_registers[9] = 1;
                            return;
                        }
                        else {
                            m_registers[9] = 0;
                            return;
                        } 
                    }
                }
            }
        }
    }
    int label_jump (std::string& mnem, std::string& label) {
        if ( (mnem == "jl" && m_registers[9] == -1) || (mnem == "jg" && m_registers[9] == 1) || 
             (mnem == "je" && m_registers[9] == 0) || (mnem == "jle" && m_registers[9] == 0) ||
             (mnem == "jle" && m_registers[9] == -1) || (mnem == "jge" && m_registers[9] == 0) ||
             (mnem == "jge" && m_registers[9] == 1) ) {
                return (labels[label + ':']);
             }
        else {
            return 0;
        }
    }
    void print_registers () {
        for (int i = 0; i < m_registers.size(); ++i) {
            std::cout << register_list[i] << " : " << m_registers[i] << std::endl;
        }
    }
    private: 
    std::vector <int> m_registers = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

void alu (std::string& mnem, std::string& w1, std::string& w2, FakeCPU& myCPU) {
    bool w2_is_num = true;
    int w2_int = 0;
    for (int i =0; i < (register_list.size() - 1); ++i) {
        if (w2 == register_list[i]) {
            w2_is_num = false;
            break;
        }
    }
    if (w2_is_num)  {
        w2_int = std::stoi (w2);
        if (mnem == "mov") {
            myCPU.mov (w1, w2_int);
        }
        else if (mnem == "add") {
            myCPU.add (w1, w2_int);
        }
        else if (mnem == "sub") {
            myCPU.sub (w1, w2_int);
        }
        else if (mnem == "mul") {
            myCPU.mul (w1, w2_int);
        }
        else if (mnem == "div") {
            myCPU.div (w1, w2_int);
        }
        else if (mnem == "and") {
            myCPU.and_ (w1, w2_int);
        }
        else if (mnem == "or") {
            myCPU.or_ (w1, w2_int);
        }
        else if (mnem == "cmp") {
            myCPU.cmp (w1, w2_int);
        }
    }
    else {
        if (mnem == "mov") {
            myCPU.mov (w1, w2);
        }
        else if (mnem == "add") {
            myCPU.add (w1, w2);
        }
        else if (mnem == "sub") {
            myCPU.sub (w1, w2);
        }
        else if (mnem == "mul") {
            myCPU.mul (w1, w2);
        }
        else if (mnem == "div") {
            myCPU.div (w1, w2);
        }
        else if (mnem == "and") {
            myCPU.and_ (w1, w2);
        }
        else if (mnem == "or") {
            myCPU.or_ (w1, w2);
        }
        else if (mnem == "cmp") {
            myCPU.cmp (w1, w2);
        }
    }
}

bool is_label (std::string str) {
    if (str[str.size()-1] == ':') {
        return true;
    }
    else return false;
}

void jumper (std::string& mnem, std::string& w1, FakeCPU& myCPU, std::ifstream& fin) {
    if (mnem == "jmp") {
        std::string tmp;
        for (int i = 0; i < (labels[w1 + ':'] - counter); ++i) {
            std::getline (fin, tmp);
        }
        counter += (labels[w1 + ':'] - counter);
        return;
    }
    else {std::string tmp;
        int label_jump = myCPU.label_jump (mnem, w1);
        if (label_jump == 0) {
            return;
        }
        else {
            for (int i = 0; i < (label_jump - counter); ++i) {
                std::getline (fin, tmp);
            }
            counter += (label_jump - counter);
            return;
        }
    }
}

void parser (std::string& str, FakeCPU& myCPU, std::ifstream& fin) {
    std::string mnem, w1, w2;
    int pos1 = str.find (" ");
    int pos2 = str.find (',');
    mnem = str.substr (0, pos1);
    w1 = str.substr (pos1 + 1, pos2 - pos1 - 1);
    w2 = str.substr (pos2 + 1, str.length() - pos2 - 1);
    for (int i = 0; i < mnemonics_jmp.size(); ++i) {
        if (mnemonics_jmp[i] == mnem) {
            jumper (mnem, w1, myCPU, fin);
            return;
        }
    } 
    alu (mnem, w1, w2, myCPU);
}

void line_line (std::ifstream& fin, FakeCPU& myCPU) {
    std::string line;
    while (!fin.eof()) {
        ++ counter;
        std::getline (fin, line);
        if (is_label(line)) {
            ++ counter;
            std::getline (fin, line);
        }
        parser (line, myCPU, fin);
        
    }
}

void labelization (std::ifstream& fin) {
    int current_string_num = 0;
    std::string line;
    while (!fin.eof()) {
        ++ current_string_num;
        std::getline (fin, line);
        if (is_label (line)) {
            labels[line] = current_string_num;
        }
        
    }
    fin.close();
}


int main () {
    FakeCPU myCPU;
    std::ifstream fin;
    fin.open ("file.txt");
    if (fin.is_open()) {
        labelization (fin);
    }
    else {std::cout << "input file problem!!!";
    exit(1);
    }
    fin.open ("file.txt");
    if (fin.is_open()) {
        line_line (fin, myCPU);
    }
    else {std::cout << "input file problem!!!";
    exit(1);
    }
    myCPU.print_registers();
    fin.close();
}
