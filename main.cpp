/**
 * Created by Zakharov Sergey (aka Zakhse),
 * Student of NRU HSE, the Faculty of Computer Science, Software Engineering
 *
 * 2k16, November
 */

#include "for_debug.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <chrono>
#include <bitset>

int main(int argc, char* argv[])
{
    std::setlocale(LC_ALL, "");


    // Title of table:
    // file.txt | compress huff ops | compress shan ops| decompress huff ops| decompress shan ops
    dbg if (argc == 3 && std::string(argv[1]) == "debug")
    {
        test_table(std::string(argv[2]));
        return 0;
    }


    if ((argc != 3 && argc != 4) || (argc == 4 && argv[1] == "decompress"))
    {
        std::cout << "Usage of arguments: MODE ALGORITHM PATH\n" <<
        "MODE - compress/decompress\n" <<
        "ALGORITHM - H for Huffman or SF for Shannon-Fano (only use it for compressing)\n" <<
        "PATH - path to file.txt with UTF-8 to compress it or to file.huff/file.shan to decompress it\n";
        return 0;
    }

    if (std::string(argv[1]) == "compress")
    {
        if (std::string(argv[2]) == "H")
        {
            compress(std::string(argv[3]), compression_algorithm::HUFFMAN);
        }
        else if (std::string(argv[2]) == "SF")
        {
            compress(std::string(argv[3]), compression_algorithm::SHANNON_FANO);
        }
        else
        {
            std::cout << "Wrong usage!\n";
            return 0;
        }
    }
    else if (std::string(argv[1]) == "decompress")
        decompress(std::string(argv[2]));
    else
        std::cout << "Wrong usage!\n";
    dbg std::cout << "Number of steps: " << Counter::get() << "\n";
}

