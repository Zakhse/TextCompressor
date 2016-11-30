#include <fstream>
#include <map>
#include <bitset>
#include <iostream>
#include "compressor.h"
#include "BitWriter.h"
#include "BitReader.h"
#include "huffman.h"
#include "shannon_fano.h"
#include "for_debug.h"

Alphabet find_alphabet(std::string path)
{
    setlocale(LC_ALL, "");

    Alphabet abc; // alphabet
    std::basic_ifstream<char32_t> file;
    file.open(path);
    char32_t ch;
    while (file.get(ch))//1 ops
    {
        if (abc.find(ch) == abc.end()) // 3 ops
        {
            abc.insert(AlphabetSymbol(ch, 0)); // 1 ops
            dbg Counter::add(1);
        }
        ++abc.at(ch); // 2 ops
        dbg Counter::add(6);
    }
    dbg Counter::add(1);
    file.close();
    return abc;
}

uint32_t count_chars(Alphabet &alphabet)
{
    uint32_t count = 0; // 1 op
    for (AlphabetSymbol ch:alphabet)
    {
        count += ch.second; // 2 ops
        dbg Counter::add(2);
    }
    dbg Counter::add(1);
    return count;
}

// counts minimum length of code
int min_code(CodeMapInversed &codes)
{
    int min = INT32_MAX;
    for (std::pair<std::string, char32_t> ch:codes)
    {
        if (ch.first.size() < min) min = ch.first.size(); // 5 ops
        dbg Counter::add(5);
    }
    return min;
}

void compress(std::string path_to_file, compression_algorithm algo)
{
    // check if file has .txt extension
    if (path_to_file.substr(path_to_file.size() - 4) != ".txt")
    {
        std::cout << "Incorrect file!";
        return;
    }

    // creating alphabet
    Alphabet alphabet = find_alphabet(path_to_file);

    // choosing algorithm
    CodeMap codes;
    std::string new_path;
    if (algo == compression_algorithm::HUFFMAN)
    {
        codes = create_huffman_codes(alphabet);
        new_path = path_to_file.substr(0, path_to_file.size() - 4) + ".huff";
    }
    else if (algo == compression_algorithm::SHANNON_FANO)
    {
        codes = create_shannon_codes(alphabet);
        new_path = path_to_file.substr(0, path_to_file.size() - 4) + ".shan";
    }
    else
    {
        std::cout << "Wrong choice, try again.\n";
        return;;
    }

    // initialize BitWriter with path to new compressed file
    BitWriter writer = BitWriter(new_path);


    // length of alphabet
    writer.add(std::bitset<32>(alphabet.size()).to_string());

    // writing alphabet
    for (std::pair<char32_t, std::string> el:codes)
    {
        writer.add(std::bitset<32>(el.first).to_string());
        writer.add(std::bitset<8>(el.second.length()).to_string());
        writer.add(el.second);
    }

    // number of chars in text
    uint32_t chars_in_text = count_chars(alphabet);
    writer.add(std::bitset<32>(chars_in_text).to_string());

    // reading text file and compressing it to new compressed file
    std::basic_ifstream<char32_t> file;
    file.open(path_to_file);
    char32_t ch;
    for (uint32_t i = 0; i < chars_in_text; ++i)
    {
        file.get(ch);
        writer.add(codes.at(ch));
    }
    writer.finish();
    file.close();
}

void decompress(std::string path_to_file)
{
    std::string new_file_path;

    if (path_to_file.length() <= 5)
    {
        if (path_to_file == "H" || path_to_file == "SF")
            std::cout << "Wrong usage! Argument ALGORITHM is not compatible with decompressing.\n";
        else
            std::cout << "Wrong choice, try again.\n";
        return;
    }
    else if (path_to_file.substr(path_to_file.size() - 5) == ".huff")
    {
        new_file_path = path_to_file.substr(0, path_to_file.size() - 5) + "-unz-h.txt";
    }
    else if (path_to_file.substr(path_to_file.size() - 5) == ".shan")
    {
        new_file_path = path_to_file.substr(0, path_to_file.size() - 5) + "-unz-s.txt";
    }
    else
    {
        std::cout << "Wrong choice, try again.\n";
        return;
    }

    CodeMapInversed codes;
    BitReader reader = BitReader(path_to_file);
    dbg Counter::add(1);

    // reading alphabet's length
    uint64_t alphabet_length = std::bitset<32>(reader.get_next(32)).to_ulong(); // 4 ops
    dbg Counter::add(4);

    // reading alphabet and creating CodeMap
    for (uint64_t i = 0; i < alphabet_length; ++i)
    {
        char32_t character = std::bitset<32>(reader.get_next(32)).to_ulong(); // 4 ops
        int code_length = std::bitset<8>(reader.get_next(8)).to_ulong(); // 4 ops
        std::string code = reader.get_next(code_length); // 2 ops
        codes.insert(std::pair<std::string, char32_t>(code, character)); // 1 op

        dbg Counter::add(12);
    }

    int min_code_length = min_code(codes);
    dbg Counter::add(1);

    // number of chars in text
    uint32_t chars_in_text = std::bitset<32>(reader.get_next(32)).to_ulong();
    dbg Counter::add(4);

    // writing text file
    std::basic_ofstream<char32_t> file;
    file.open(new_file_path);
    std::string key = "";
    for (uint32_t i = 0; i < chars_in_text; ++i)
    {
        key += reader.get_next(min_code_length); // 3 ops
        while (codes.find(key) == codes.end()) // 3 ops
        {
            key += reader.get_next(1); // 3 ops
            dbg Counter::add(6);
        }
        file << codes.at(key); // 2 ops
        key = ""; // 1 op
        dbg Counter::add(6);
    }
    reader.finish();
    file.close();
}
