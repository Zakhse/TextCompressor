/**
 * Created by Zakharov Sergey (aka Zakhse),
 * Student of NRU HSE, the Faculty of Computer Science, Software Engineering
 *
 * 2k16, November
 */

#include "huffman.h"
#include "for_debug.h"

#include <queue>
#include <iostream>
#include <iterator>

class INode
{
public:
    const uint32_t weight; // weight of node (weigths of all children)

    virtual ~INode() { }

protected:
    INode(uint32_t weight) : weight(weight) { }
};

class InternalNode : public INode
{
public:
    INode* const left; // all left children
    INode* const right; // all right children

    InternalNode(INode* c0, INode* c1) : INode(c0->weight + c1->weight), left(c0), right(c1) { }

    ~InternalNode()
    {
        delete left;
        delete right;
    }
};

class LeafNode : public INode
{
public:
    const char32_t character; // character that this node presents

    LeafNode(uint32_t f, char32_t c) : INode(f), character(c) { }
};

struct NodeCompare
{
    bool operator()(const INode* lhs, const INode* rhs) const
    {
        dbg Counter::add(1);
        return lhs->weight > rhs->weight; // 1 op
    }
};

INode* BuildTree(Alphabet alphabet)
{
    std::priority_queue<INode*, std::vector<INode*>, NodeCompare> trees;

    for (AlphabetSymbol ch:alphabet)
    {
        if (ch.second != 0) // 2 op
        {
            trees.push(new LeafNode(ch.second, ch.first)); // 1 op
            dbg Counter::add(3);
        }
    }
    while (trees.size() > 1) // 1 op
    {
        INode* childR = trees.top(); // 2 ops
        trees.pop(); // 1 op

        INode* childL = trees.top(); // 2 ops
        trees.pop(); // 1 op

        INode* parent = new InternalNode(childR, childL);  // 1 op
        trees.push(parent);  // 1 op
        dbg Counter::add(9);
    }
    dbg Counter::add(2);
    return trees.top(); // 1 op
}

void GenerateCodes(const INode* node, const std::string &prefix, CodeMap &outCodes)
{
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node)) // 1 op
    {
        outCodes[lf->character] = prefix; // 2 ops
        dbg Counter::add(3);
    }
    else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node)) // 1 op
    {
        std::string leftPrefix = prefix; // 1 op
        leftPrefix += "0"; // 2 ops
        GenerateCodes(in->left, leftPrefix, outCodes);

        std::string rightPrefix = prefix; // 1 op
        rightPrefix += "1"; // 2 ops
        GenerateCodes(in->right, rightPrefix, outCodes);
        dbg Counter::add(7);
    }
}

CodeMap create_huffman_codes(Alphabet &alphabet)
{
    INode* root = BuildTree(alphabet); // 1 op
    CodeMap codes;
    GenerateCodes(root, "", codes);
    dbg Counter::add(1);
    return codes;
}