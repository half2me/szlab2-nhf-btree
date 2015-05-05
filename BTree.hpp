//
// Created by Benjamin Tamási on 27/04/15.
//

#ifndef SZLAB2_NHF_BTREE_BTREE_H
#define SZLAB2_NHF_BTREE_BTREE_H

template <typename T, int n>
class Node {
private:
    int size;
    T * keys;
    Node<T, n> ** nodes;
public:
    Node(){
        size = 0;
        keys = new T[2*n];
        nodes = new Node<T, n>*[2*n + 1];
        for(int i=0; i<(2*n + 1); i++){
            nodes[i] = 0;
        }
    }

    Node(const Node<T, n>& node){
        keys = new T[2*n];
        nodes = new Node<T, n>*[2*n + 1];
        for(int i=0; i<(2*n + 1); i++){
            nodes[i] = 0;
        }

        for(size = 0; size < node.size; size++){
            keys[size] = node.keys[size];
            nodes[size] = node.nodes[size];
        }
        nodes[size] = node.nodes[size];
    }

    void Insert(const T data){
        if(size == 0){
            // Empty node
            keys[0] = data;
            size++;
        }
        else{
            for(int i=0; i<size; i++){
                if(keys[i] > data){
                    // Upper bound found, lets go down the line
                    if(nodes[i] == 0){
                        // No more linked nodes in our path
                        if(size == 2*n){
                            // Node is full, link new node
                            nodes[i] = new Node<T, n>;
                            nodes[i]->Insert(data);
                        }
                        else{
                            // Node is not full, add key to node
                            T tmp[2*n+1];
                            for(int j = i; j<size; j++){
                                tmp[j] = keys[j];
                            }
                            keys[i] = data;
                            for(int j = i+1; j<size; j++){
                                keys[j] = tmp[j];
                            }
                            size++;
                        }
                        return;
                    }
                    else{
                        // data must be passed to a linked node
                        nodes[i]->Insert(data);
                        return;
                    }
                }
                if(keys[i] == data) return; // duplicate key!
            }
            // Insert data after last key
            if(nodes[size] == 0){
                // No more linked nodes in our path
                if(size == 2*n){
                    // Node is full, link new node
                    nodes[size] = new Node<T, n>;
                    nodes[size]->Insert(data);
                }
                else{
                    // Node is not full, add key to node
                    keys[size] = data;
                    size++;
                }
            }
            else{
                // Pass to next linked node
                nodes[size]->Insert(data);
            }
        }
    }

    void Delete(const T);
    Node Find(const T) const;
    Node<T, n>& operator+(const Node<T, n>&) const;

    Node<T, n>& operator=(const Node<T, n>& node){
        for(size = 0; size < node.size; size++){
            keys[size] = node.keys[size];
            nodes[size] = node.nodes[size];
        }
        nodes[size] = node.nodes[size];
    }

    ~Node(){
        for(int i=0; i<2*n+1; i++){
            if(nodes[i] != 0){
                delete nodes[i]; // Free up linked nodes
            }
            // Free up self
            delete[] keys;
            delete[] nodes;
        }
    }
};


#endif //SZLAB2_NHF_BTREE_BTREE_H
