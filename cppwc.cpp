#include <CLI11.hpp>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iterator>
#include <cstring>

namespace fs = std::filesystem;

void print_file_size(std::string fname) {
    fs::path filename = fname;
    std::cout << fs::file_size(filename);
}

void print_file_num_lines(std::string fname) {
    std::ifstream inFile(fname);
    auto cnt = std::count(std::istreambuf_iterator<char>(inFile),
    std::istreambuf_iterator<char>(), '\n');
    std::cout << cnt;
}

void print_file_num_words(std::string fname) {
    std::ifstream inFile(fname);
    std::string line;
    int spaces = 0;
    while(std::getline(inFile, line)) {
        std::stringstream stream(line);
        spaces += std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
    }
    std::cout << spaces;
}

void print_file_num_chars(std::string fname) {
    std::ifstream inFile(fname);
    char ch;
    int cnt = 0;
    while(inFile >> std::noskipws >> ch)
        ++cnt;
    std::cout << cnt;
}

int main(int argc, char** argv) {
    CLI::App app{"App description"};
    std::string filename;

    auto print_bytes = app.add_option("-c", filename, "print size of file in bytes");
    print_bytes->check(CLI::ExistingFile);

    auto print_num_lines = app.add_option("-l", filename, "print number of lines in the file");
    print_num_lines->check(CLI::ExistingFile);

    auto print_num_words = app.add_option("-w", filename, "print number of words in the file");
    print_num_words->check(CLI::ExistingFile);

    auto print_num_chars = app.add_option("-m", filename, "print number of characters in the file");
    print_num_words->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    if(*print_bytes) {
        print_file_size(print_bytes->as<std::string>());
    }

    if(*print_num_lines) {
        print_file_num_lines(print_num_lines->as<std::string>());
    }

    if(*print_num_words) {
        print_file_num_words(print_num_words->as<std::string>());
    }

    if(*print_num_chars) {
        print_file_num_chars(print_num_chars->as<std::string>());
    }

    std::cout << " " << filename << "\n";

    return 0;
}