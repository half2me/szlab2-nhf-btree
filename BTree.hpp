//
// Created by Benjamin Tamási on 27/04/15.
//


#ifndef SZLAB2_NHF_BTREE_BTREE_H
#define SZLAB2_NHF_BTREE_BTREE_H

#include <iostream>
using namespace std;

template <typename T, int n>
class Node {
private:
    int size;
    T* keys;
    Node<T, n> ** nodes;
    Node<T, n> * parent;

    void Split(const T& data, Node<T, n>* right = 0){
        if(size == 2*n){
            // Full, lets split
            if(parent == 0){
                // Root node split
                Node<T, n> *leftNode = new Node<T, n>();
                Node<T, n> *rightNode = new Node<T, n>();
                leftNode->parent = (Node<T, n>*) this;
                rightNode->parent = (Node<T, n>*) this;
                T tmp[2*n+1];
                Node<T, n>* tmp2[2*n+2];
                int i, j;
                for(i=0; i<2*n;i++){
                    if(keys[i] > data) break;
                }
                // insert at i
                for(j=0; j<i;j++){
                    tmp[j] = keys[j];
                    tmp2[j] = nodes[j];
                }
                tmp2[j] = nodes[j];
                tmp[j] = data;
                tmp2[j+1] = right;
                for(int j=i+1; j<2*n+1; j++){
                    tmp[j] = keys[j-1];
                    tmp2[j+1] = nodes[j];
                }
                // Copy sorted data to left, right nodes
                for(i = 0; i<n; i++){
                    leftNode->keys[i] = tmp[i];
                    leftNode->nodes[i] = tmp2[i];
                }
                leftNode->nodes[i] = tmp2[i];
                leftNode->size = n;
                for(i = 0; i<n; i++){
                    rightNode->keys[i] = tmp[i+n+1];
                    rightNode->nodes[i] = tmp2[i+n+1];
                }
                rightNode->nodes[i] = tmp2[i+n+1];
                rightNode->size = n;
                // link nodes
                nodes[0] = leftNode;
                nodes[1] = rightNode;
                keys[0] = tmp[n];
                size = 1;
                // Child nodes still point to root node, lets fix this
                for(i=0; i<=leftNode->size; i++){
                    if(leftNode->nodes[i] != 0){
                        leftNode->nodes[i]->parent = leftNode;
                    }
                }
                for(i=0; i<=rightNode->size; i++){
                    if(rightNode->nodes[i] != 0){
                        rightNode->nodes[i]->parent = rightNode;
                    }
                }
                return;
            }
            // Split simple node
            T tmp[2*n+1];
            Node<T, n>* tmp2[2*n+2];
            int i, j;
            for(i=0; i<2*n;i++){
                if(keys[i] > data) break;
            }
            // insert at i
            for(j=0; j<i;j++){
                tmp[j] = keys[j];
                tmp2[j] = nodes[j];
            }
            tmp2[i] = nodes[j];
            tmp[i] = data;
            tmp2[i+1] = right;
            for(j=i+1; j<2*n+1; j++){
                tmp[j] = keys[j-1];
                tmp2[j+1] = nodes[j];
            }
            for(j=0; j<n; j++){
                keys[j] = tmp[j];
                nodes[j] = tmp2[j];
            }
            nodes[j] = tmp2[j];
            size = n;
            Node<T,n>* r = new Node<T, n>;
            for(i=0; i<n; i++){
                r->keys[i] = tmp[i+1+n];
                r->nodes[i] = tmp2[i+1+n];
            }
            r->nodes[n] = tmp2[2*n+1];
            r->parent = parent;
            r->size = n;
            // sync child nodes' parent pointer if not leaf

            /* enable if parent pointers are invalid
            if(!isLeaf()){
                for(i=0; i<=size; i++){
                    if(nodes[i] !=0){
                        nodes[i]->parent = this;
                    }
                }
            }
            */

            if(!r->isLeaf()){
                for(i=0; i<=r->size; i++){
                    if(r->nodes[i] !=0){
                        r->nodes[i]->parent = r;
                    }
                }
            }
            parent->Split(tmp[n], r);
        }
        else{
            // data fits, just insert
            for(int i=0; i<size; i++){
                if(keys[i] > data){
                    // Upper bound found
                    T tmp[2*n];
                    Node<T, n>* tmp2[2*n+1];
                    for(int j = i; j<size; j++){
                        tmp[j] = keys[j];
                        tmp2[j+1] = nodes[j+1];
                    }
                    keys[i] = data;
                    nodes[i+1] = right;
                    size++;
                    for(int j=i+1; j<size; j++){
                        keys[j] = tmp[j-1];
                        nodes[j+1] = tmp2[j];
                    }
                    return;
                }
            }
            // insert data after last block
            keys[size] = data;
            size++;
            nodes[size] = right;
        }
    }

    void Balance(){
        if(size < n && parent != 0){
            if(size == 0){
                // TODO: Handle empty nodes
            }
            // Underflow
            int index = parent->Index(*this);
            if(index != parent->size){
                // We have a right neighbor
                if(parent->nodes[index+1]->size > n){
                    // rotate left
                    keys[size] = parent->keys[index]; // Get parent's divider as our key
                    size++;
                    parent->keys[index] = parent->nodes[index+1]->keys[0]; // Set parent's divider to right neighbor's key
                    parent->nodes[index+1]->Delete(parent->keys[index]); // Delete right neighbor's old key
                    return;
                }
            }
            else{
                // We have a left neighbor
                if(parent->nodes[index-1]->size > n){
                    // rotate right
                    for(int i=size; i > 0; i--){
                        keys[i] = keys[i-1];
                    }
                    keys[0] = parent->keys[index-1]; // Get parent's divider as our key
                    size++;
                    parent->keys[index-1] = parent->nodes[index-1]->keys[parent->nodes[index-1]->size]; // Set parent
                    parent->nodes[index-1]->Delete(parent->keys[index-1]); // Delete left neighbors old key
                    return;
                }
            }
            // Our neighbors don't have extra keys... lets merge :)
            if(index != parent->size){
                // Merge with right neighbor
                Node<T, n>* neighbor = parent->nodes[index+1];
                keys[size] = parent->keys[index];
                size++;
                int i;
                for(i=0; i<neighbor->size; i++){
                    keys[i+size] = neighbor->keys[i];
                    nodes[i+size] = neighbor->nodes[i];
                }
                nodes[i+size] = neighbor->nodes[i]; // Copy last node
                size += neighbor->size;

                if(!neighbor->isLeaf()){
                    // If neighbor is not a leaf, we need to sync changes to siblings
                    // And reset all his nodes to 0 before we delete him
                    for(i=0; i<=neighbor->size; i++){
                        if(neighbor->nodes[i] !=0){
                            neighbor->nodes[i]->parent = this;
                            neighbor->nodes[i] = 0;
                        }
                    }
                }

                // Delete neighbor
                parent->nodes[index+1] = 0;
                delete neighbor;

                // Delete stolen key from parent
                parent->Delete(parent->keys[index]);
            }
            else{
                // Merge with left neighbor
                Node<T, n>* neighbor = parent->nodes[index-1];
                neighbor->keys[neighbor->size] = parent->keys[index-1];
                neighbor->size++;
                int i;
                for(i=0; i<size; i++){
                    neighbor->keys[i+neighbor->size] = keys[i];
                    neighbor->nodes[i+neighbor->size] = nodes[i];
                }
                neighbor->nodes[i+neighbor->size] = nodes[i]; // Copy last node
                neighbor->size += size;

                if(!isLeaf()){
                    // If we are not a leaf, we need to sync changes to siblings
                    // And reset all his nodes to 0 before we delete him
                    for(i=0; i<=size; i++){
                        if(nodes[i] !=0){
                            nodes[i]->parent = neighbor;
                            nodes[i] = 0;
                        }
                    }
                }

                // Delete ourselves
                parent->nodes[index] = 0;
                delete this;

                // Delete stolen key from parent
                neighbor->parent->Delete(neighbor->parent->keys[index]);
            }
        }
    }

    const int Index(const Node<T, n>& node) const{
        for(int i=0; i<=size; i++){
            if(nodes[i] == &node) return i;
        }
        throw "Node not found!";
    }

public:
    Node(){
        parent = 0;
        size = 0;
        keys = new T[2*n];
        nodes = new Node<T, n>*[2*n + 1];
        for(int i=0; i<(2*n + 1); i++){
            nodes[i] = 0;
        }
    }

    Node(const Node<T, n>& node){
        parent = node.parent;
        keys = new T[2*n];
        nodes = new Node<T, n>*[2*n + 1];
        for(int i=0; i<(2*n + 1); i++){
            nodes[i] = 0;
        }

        for(size = 0; size < node.size; size++){
            keys[size] = node.keys[size];
            nodes[size] = new Node<T,n>((const Node<T, n> &) node.nodes[size]);
        }
        nodes[size] = node.nodes[size];
    }

    const int Height() const {
        if(isLeaf()) return 1;
        for(int i = 0; i<size; i++){
            if(nodes[i] != 0){
                return 1 + nodes[i]->Height();
            }
        }
        throw "Internal Error";
    }

    void Insert(const T& data){
        for(int i=0; i<size; i++){
            if(keys[i] > data){
                // Key needs to be inserted before keys[i]
                if(isLeaf()){
                    if(size == 2*n){
                        // Leaf is full
                        return this->Split(data);
                    }
                    else{
                        // Leaf is not full, add key
                        T tmp[2*n];
                        for(int j = i; j<size; j++){
                            tmp[j] = keys[j];
                        }
                        keys[i] = data;
                        int j;
                        for(j=i+1; j<=size; j++){
                            keys[j] = tmp[j-1];
                        }
                        size++;
                    }
                    return;
                }
                else{
                    // Insertion only on leaves
                    return nodes[i]->Insert(data);
                }
            }
            if(keys[i] == data) throw "Duplicate key!"; // duplicate key!
        }
        // Insert data after last key or empty root node
        if(isLeaf()){
            if(size == 2*n){
                // Leaf is full, split
                return this->Split(data);
            }
            else{
                // Leaf is not full, add key
                keys[size] = data;
                size++;
            }
        }
        else{
            // Insertion only on leaves
            nodes[size]->Insert(data);
        }
    }

    Node<T, n>& Find(const T& data){
        for(int i=0; i<size; i++){
            if(keys[i] > data){
                // Upper bound found, lets go down the line
                if(nodes[i] == 0){
                    // No more linked nodes in our path
                    throw "Not found!";
                }
                else{
                    // Search must continue in a linked node
                    return nodes[i]->Find(data);
                }
            }
            if(keys[i] == data) return *this; // key found!!
        }
        // check after last key
        if(nodes[size] == 0){
            // No more linked nodes in our path
            throw "Not found!";
        }
        else{
            // Pass to next linked node
            nodes[size]->Insert(data);
        }
        throw "Not found!";
    }

    void Delete(const T& data){
        if(!isLeaf()){
            Node<T, n>* node = 0;
            try{
                node = &Find(data);
            }
            catch (char* ex){
                throw ex;
            }

            if(node != this){
                node->Delete(data);
            }
            else{
                // Delete from internal node
                int i;
                for(i=0; i<size; i++){
                    if(keys[i] == data){
                        break;
                    }
                }
                T max = nodes[i]->max();
                keys[i] = max;
                nodes[i]->Delete(max);
            }
        }
        else{
            // Delete from leaf node
            int i;
            for(i=0; i<size; i++){
                if(keys[i] == data){
                    break;
                }
            }
            if(i>=size) throw "Key not found!";
            size--;
            for(; i<size; i++){
                keys[i] = keys[i+1];
            }
            Balance();
        }
    }

    bool isLeaf() const{
        for(int i=0; i<=size; i++){
            if(nodes[i] != 0){
                return false;
            }
        }
        return true;
    }

    T max() const {
        if(isLeaf()){
            return keys[size-1];
        }
        else{
            return nodes[size]->max();
        }
    }

    Node<T, n>& operator=(const Node<T, n>& node){
        parent = node.parent;
        for(size = 0; size < node.size; size++){
            keys[size] = node.keys[size];
            nodes[size] = new Node<T, n>((const Node<T, n> &) node.nodes[size]);
        }
        nodes[size] = node.nodes[size];
    }

    template <typename U, int k>
    friend ostream& operator<<(ostream& out, const Node<U, k> & node);

    ~Node(){
        if(!isLeaf()){
            for(int i=0; i<=size; i++){
                delete nodes[i]; // Free up linked nodes
            }
        }
        delete[] keys;
        delete[] nodes;
    }
};

template <typename T, int n>
ostream& operator<<(ostream& out, const Node<T, n> & node){
    out << "{";
    for(int i=0; i<node.size; i++){
        if(!node.isLeaf()){
            if(node.nodes[i] !=0){
                out << *node.nodes[i] << ",";
            }
        }
        out << node.keys[i] << ",";
    }
    if(node.nodes[node.size] != 0){
        out << *node.nodes[node.size] << ",";
    }
    return out << "}";
}


#endif //SZLAB2_NHF_BTREE_BTREE_H
