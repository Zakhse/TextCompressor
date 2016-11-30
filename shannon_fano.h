#ifndef TEXTCOMPRESSOR_SHANNON_FANO_H
#define TEXTCOMPRESSOR_SHANNON_FANO_H

#include "compressor.h"

#include <vector>
#include <map>


CodeMap create_shannon_codes(Alphabet &alphabet);

#endif //TEXTCOMPRESSOR_SHANNON_FANO_H
