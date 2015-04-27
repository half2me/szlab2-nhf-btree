//
// Created by Benjamin Tamási on 27/04/15.
//

#ifndef SZLAB2_NHF_BTREE_BTREE_H
#define SZLAB2_NHF_BTREE_BTREE_H

template <typename T, int n>
class Node {
public:
    T* keys;
    Node<T, n>** nodes;
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
    BTree operator+(const BTree tree) const;
    void operator=(const BTree tree);
};


#endif //SZLAB2_NHF_BTREE_BTREE_H
