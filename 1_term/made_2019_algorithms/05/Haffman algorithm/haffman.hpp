//
//  haffman.hpp
//  Haffman algorithm
//
//  Created by Илья Башаров on 28/11/2019.
//  Copyright © 2019 MIPT. All rights reserved.
//

#ifndef haffman_hpp
#define haffman_hpp

#include <queue>
#include "extra_functions.hpp"
#include "bits_workers.hpp"

inline std::unordered_map<byte, std::vector<bool>> CreateCodesEncode(pBinaryNode root)
{
    if (!root)
        throw std::invalid_argument{"Binary tree is empty."};

    std::unordered_map<byte, std::vector<bool>> map;
    std::vector<bool> buffer;
    
    if (root -> right && root -> left)
        Traversal(root, buffer, nullptr, &map);
    else
    {
        buffer.push_back(false);
        map.insert({root -> key, buffer});
    }
    return map;
}

inline pBinaryNode CreateHaffmanTree(std::vector<std::pair<byte,std::size_t>>& frequences)
{
    std::queue<std::pair<pBinaryNode, std::size_t>> extra_buffer;
    std::size_t i = 0;
    
    while (i < frequences.size())
    {
        auto root = std::make_pair(new BinaryNode{frequences[i].first},
                                   frequences[i].second);
        i++;
        
        if (frequences.size() - i > 0)
        {
            if (extra_buffer.empty() || frequences[i].second <= extra_buffer.front().second)
            {
                
                root.first = MergeNodes(root.first,
                                        new BinaryNode{frequences[i].first});
                root.second += frequences[i].second;
                i++;
            }
            else
            {
                auto current = extra_buffer.front();
                extra_buffer.pop();
                root.first = MergeNodes(root.first, current.first);
                root.second += current.second;
            }
        }
        else if (!extra_buffer.empty())
        {
            auto current = extra_buffer.front();
            extra_buffer.pop();
            root.first = MergeNodes(current.first, root.first);
            root.second += current.second;
        }
        
        extra_buffer.push(root);
    }
    
    while (extra_buffer.size() > 1)
    {
        auto right = extra_buffer.front();
        extra_buffer.pop();
        auto left = extra_buffer.front();
        extra_buffer.pop();
        
        right.first = MergeNodes(left.first, right.first);
        right.second += left.second;
        extra_buffer.push(right);
    }
    
    return extra_buffer.front().first;
}

inline void WritingTreeToStream(pBinaryNode root, BitsWriter& writer)
{
    if (root -> left)
    {
        writer.WriteBit(false);
        WritingTreeToStream(root -> left, writer);
    }
    
    if (root -> right)
        WritingTreeToStream(root -> right, writer);
    
     if (!root -> right && !root -> left)
     {
         writer.WriteBit(true);
         writer.WriteByte(root -> key);
     }
}

inline void WritingToStream(pBinaryNode tree, std::vector<byte>& buffer,
                     std::unordered_map<byte, std::vector<bool>>& codes,
                     IOutputStream& compressed)
{
    BitsWriter writer;
    WritingTreeToStream(tree, writer);
    
    for (auto& element: buffer)
        for (std::size_t i = 0; i < codes[element].size(); ++i)
            writer.WriteBit(codes[element][i]);
    
    auto stream_result = writer.GetResult();
    
    for (auto& byte: stream_result)
        compressed.Write(byte);
}

inline void CreateHaffmanTree_(BitsReader& reader,
                        IInputStream& compressed,
                        pBinaryNode root)
{
    bool bit;
    if (!reader.ReadBit(compressed, bit))
        return;
    
    if (bit)
    {
        byte byte_;
        if (!reader.ReadByte(compressed, byte_))
            return;
        
        root -> key = byte_;
        return;
    }
    
    root -> left = new BinaryNode;
    CreateHaffmanTree_(reader, compressed, root -> left);
    
    root -> right = new BinaryNode;
    CreateHaffmanTree_(reader, compressed, root -> right);
}

inline pBinaryNode CreateHaffmanTree(BitsReader& reader,
                              IInputStream& compressed)
{
    pBinaryNode tree = new BinaryNode;
    CreateHaffmanTree_(reader, compressed, tree);
    return tree;
}

inline void buildGraphWithGraphViz(std::ofstream& fp, pBinaryNode node)
{
    std::string current = " [label=\"key=";
    fp << "TreeNode_" << node << current + (const char)node -> key  << "\"]" << std::endl;

    if (node -> left)
    {
        buildGraphWithGraphViz(fp, node -> left);
        fp << "TreeNode_" << node << " -> TreeNode_" << node -> left  << " [label=\"0\"]" << std::endl;
        fp << "TreeNode_" << node << current + (const char)node -> key  << "\"]" << std::endl;
    }

    if (node -> right)
    {
        buildGraphWithGraphViz(fp, node -> right);
        fp << "TreeNode_" << node << " -> TreeNode_" << node -> right << " [label=\"1\"]" << std::endl;
        fp << "TreeNode_" << node << current + (const char)node -> key  << "\"]" << std::endl;
    }
}

inline void createGraph(pBinaryNode root)
{
    std::ofstream dotFile("graph.gv");
    dotFile << "digraph G{" << std::endl << "graph [dpi = 300]" << std::endl;
    buildGraphWithGraphViz(dotFile, root);
    dotFile << "}";
    dotFile.close();
}

inline std::unordered_map<std::vector<bool>, byte> CreateCodesDecode(pBinaryNode root)
{
    if (!root)
        throw std::invalid_argument{"Binary tree is empty."};
    
    std::unordered_map<std::vector<bool>, byte> map;
    std::vector<bool> buffer;
    
    if (root -> right && root -> left)
        Traversal(root, buffer, &map);
    else
    {
        buffer.push_back(false);
        map.insert({buffer, root -> key});
    }
    
    return map;
}

inline void Encode(IInputStream& original, IOutputStream& compressed)
{
    byte value = 0;
    std::vector<byte> buffer;
    std::unordered_map<byte, std::size_t> map;
    
    while(original.Read(value))
    {
        map[value] ++;
        buffer.push_back(value);
    }
    
    auto frequences = CountingSort(map);
    auto tree = CreateHaffmanTree(frequences);
    auto codes = CreateCodesEncode(tree);
    
    WritingToStream(tree, buffer, codes, compressed);
    FreeMemory(tree);
}

inline void Decode(IInputStream& compressed, IOutputStream& original)
{
    BitsReader reader;
    
    pBinaryNode tree = CreateHaffmanTree(reader, compressed);
    auto codes = CreateCodesDecode(tree);
    FreeMemory(tree);
    
    std::vector<bool> buffer;
    bool temp = 0;
    while (reader.ReadBit(compressed, temp))
        buffer.push_back(temp);
    
    std::size_t bits_count = 0, pow = 1;
    for (std::size_t i = buffer.size() - 8; i < buffer.size(); ++i)
    {
        bits_count += buffer[i] * pow;
        pow *= 2;
    }
    
    std::vector<bool> extra_buffer;
    for (std::size_t i = 0; i < buffer.size() - 16 + bits_count; ++i)
    {
        extra_buffer.push_back(buffer[i]);
        auto element = codes.find(extra_buffer);
        if (element != codes.end())
        {
            original.Write(element -> second);
            extra_buffer.clear();
        }
    }
}

#endif /* haffman_hpp */
