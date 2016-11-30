#ifndef TEXTCOMPRESSOR_BITWRITER_H
#define TEXTCOMPRESSOR_BITWRITER_H

#include <string>
#include <fstream>

class BitWriter
{
public:
    BitWriter(std::string path);

    // don't add new_part with length > INT32_MAX
    void add(std::string new_part);

    void finish();

    ~BitWriter() { finish(); }

private:
    std::string buffer;

    std::ofstream* file;

    bool finished;
};

#endif //TEXTCOMPRESSOR_BITWRITER_H
