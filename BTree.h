//
// Created by Benjamin Tamási on 27/04/15.
//

#ifndef SZLAB2_NHF_BTREE_BTREE_H
#define SZLAB2_NHF_BTREE_BTREE_H

template <typename T, int n>
class Node {
private:
    int size;
public:
    Node();
    Node(const Node& node);
    T * keys;
    Node<T, n> ** nodes;
    void Insert(const T);
    void Delete(const T);
    Node Find(const T) const;
    Node& operator+(const Node& node) const;
    Node& operator=(const Node& node);
    ~Node();
};

template <typename T, int n>
class BTree {
private:
    Node<T, n>* root;
    void Balance();
public:
    BTree();
    BTree(const BTree& tree);
    void Insert(const T);
    void Delete(const T);
    Node Find(const T) const;
    BTree& operator+(const BTree& tree) const;
    Node& operator=(const BTree& tree);
    ~BTree();
};


#endif //SZLAB2_NHF_BTREE_BTREE_H
