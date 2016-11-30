/**
 * Created by Zakharov Sergey (aka Zakhse),
 * Student of NRU HSE, the Faculty of Computer Science, Software Engineering
 *
 * 2k16, November
 */

#include "BitReader.h"

#include <bitset>


BitReader::BitReader(std::string path)
{
    file = new std::ifstream;
    file->open(path, std::ios_base::in);
    buffer = "";
    finished = false;
}

std::string BitReader::get_next(int size)
{
    char ch;
    while (buffer.length() < size && file->get(ch))
    {
        buffer += std::bitset<8>(ch).to_string();
    }
    std::string result = buffer.substr(0, size);
    buffer = buffer.substr(size);
    return result;
}

void BitReader::finish()
{
    if (finished) return;
    file->close();
    buffer = "";
    delete file;
    finished = true;
}