#ifndef TEXTCOMPRESSOR_BITREADER_H
#define TEXTCOMPRESSOR_BITREADER_H

#include <string>
#include <fstream>

class BitReader
{
public:
    BitReader(std::string path);

    std::string get_next(int size);

    void finish();

    ~BitReader() { finish(); }

private:

    std::string buffer;

    std::ifstream* file;

    bool finished;
};

#endif //TEXTCOMPRESSOR_BITREADER_H
