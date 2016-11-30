/**
 * Created by Zakharov Sergey (aka Zakhse),
 * Student of NRU HSE, the Faculty of Computer Science, Software Engineering
 *
 * 2k16, November
 */

#include "BitWriter.h"

#include <bitset>


BitWriter::BitWriter(std::string path)
{
    file = new std::ofstream;
    file->open(path, std::ios_base::out | std::ios_base::trunc);
    buffer = "";
    finished = false;
}

void BitWriter::add(std::string new_part)
{
    if (finished) throw std::logic_error("BitWriter is finished!");

    buffer += new_part;
    if (buffer.length() >= 8)
    {
        unsigned long number_of_bytes = buffer.length() / 8;
        char* bytes = new char[number_of_bytes];
        for (unsigned long i = 0; i < number_of_bytes; ++i)
        {
            std::string temp_str = buffer.substr(i * 8, 8);
            bytes[i] = (unsigned char) std::bitset<8>(temp_str).to_ulong();
        }
        buffer = buffer.substr(number_of_bytes * 8);
        file->write(bytes, number_of_bytes);
        delete[] bytes;
    }
}

void BitWriter::finish()
{
    if (finished) return;;

    while (buffer.length() < 8)
        buffer += "0";
    char* byte = new char[1];
    byte[0] = (unsigned char) std::bitset<8>(buffer).to_ulong();
    file->write(byte, 1);
    file->close();
    buffer = "";
    delete file;
    finished = true;
}