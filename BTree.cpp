//
// Created by Benjamin Tamási on 27/04/15.
//

#include "BTree.h"
#include <iostream>

using namespace std;

template <typename T, int n>
Node<T, n>::Node() {
    this->size = 0;
    keys = new T[2*n];
    nodes = new Node*[2*n + 1];
}

template <typename T, int n>
Node<T, n>::Node(const Node& node) {
    keys = new T[2*n];
    nodes = new Node*[2*n + 1];

    for(size = 0; size < node.size; size++){
        
    }
}