/**
 * Created by Zakharov Sergey (aka Zakhse),
 * Student of NRU HSE, the Faculty of Computer Science, Software Engineering
 *
 * 2k16, November
 */

#include "shannon_fano.h"
#include "for_debug.h"

#include <iostream>
#include <algorithm>

class SymbolCode
{
public:
    SymbolCode(char32_t in_symbol, int in_frequency)
    {
        symbol = in_symbol;
        frequency = in_frequency;
        code = "";
    };

    char32_t getSymbol()
    {
        return symbol;
    };

    int getFrequency()
    {
        return frequency;
    };

    std::string getCode() { return code; };

    void addCode(std::string code_part)
    {
        code += code_part;
    };

private:
    char32_t symbol;
    int frequency;
    std::string code;
};

void shannonFano(std::vector<SymbolCode> &chars, int in_begin, int in_end)
{
    // not a valid parameters input
    if (in_begin >= in_end) // 1 op
    {
        return;
    }
    dbg Counter::add(1);

    // only 2 symbol left
    if (in_begin == in_end - 1) // 3 ops
    {
        chars.at(in_begin).addCode("0"); // 2 ops
        chars.at(in_end).addCode("1"); // 2 ops
        dbg Counter::add(4);
        return;
    }
    dbg Counter::add(3);

    // highPtr will go down
    int highPtr = in_begin; // 1 op
    int lowPtr = in_end; // 1 op
    int highSum = chars.at(highPtr).getFrequency(); // 3 ops
    int lowSum = chars.at(lowPtr).getFrequency(); // 3 ops
    dbg Counter::add(8);

    // move the highPtr down and lowPtr up until highSum and lowSum meet each other
    while (highPtr != lowPtr - 1) // 3 opd
    {
        if (highSum > lowSum) // 2 ops
        {
            lowPtr--; // 1 op
            lowSum += chars.at(lowPtr).getFrequency(); // 4 ops
            dbg Counter::add(5);
        } else
        {
            highPtr++;
            highSum += chars.at(highPtr).getFrequency();
            dbg Counter::add(5);
        }
        dbg Counter::add(2);
    }
    dbg Counter::add(3);

    int i;
    for (i = in_begin; i <= highPtr; i++)
    {
        chars.at(i).addCode("0");
        dbg Counter::add(2);
    }
    for (i = lowPtr; i <= in_end; i++)
    {
        chars.at(i).addCode("1");
        dbg Counter::add(2);
    }

    shannonFano(chars, in_begin, highPtr);
    shannonFano(chars, lowPtr, in_end);
}

CodeMap create_shannon_codes(Alphabet &alphabet)
{
    std::vector<SymbolCode> chars;
    for (AlphabetSymbol ch:alphabet)
    {
        chars.push_back(SymbolCode(ch.first, ch.second));
        dbg Counter::add(1);
    }

    std::sort(chars.begin(), chars.end(),
              [](SymbolCode a, SymbolCode b) { return a.getFrequency() < b.getFrequency(); });
    dbg Counter::add(1);

    shannonFano(chars, 0, chars.size() - 1);

    CodeMap code_map;
    for (int i = 0; i < chars.size(); ++i)
    {
        code_map.insert(std::pair<char32_t, std::string>(chars[i].getSymbol(), chars[i].getCode()));
        dbg Counter::add(1);
    }
    return code_map;
}
