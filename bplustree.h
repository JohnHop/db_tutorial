#if !defined(BPLUSTREE)
#define BPLUSTREE

#include <iostream>
#include <vector>
#include <utility>

#include "row.h"

#define CORMEN_ORDER 46 //Ora sizeof(Node) == 4032. Mancano 64 byte per arrivare a 4096 //FIXME non si ragiona così...

struct Node {
  int key_count;
  int keys[2*CORMEN_ORDER-1];
  Row values[2*CORMEN_ORDER-1];
  Node* children[2*CORMEN_ORDER];
  bool leaf;
  Node* next;

  Node(): key_count{0}, children{nullptr}, leaf{true}, next{nullptr} { }
  Node(const char k): key_count{1}, children{nullptr}, leaf{true}, next{nullptr} { keys[0] = k; }
  Node(std::initializer_list<char>);
  Node(const bool l): Node{} { leaf = l; };

  bool full() const { return (2*CORMEN_ORDER-1) == key_count; };  //FIXME dipendenza da costante simbolica
  bool less_than_min_keys() const { return CORMEN_ORDER-1 > key_count; }; //true se il numero do chiavi è minore del minimo richiesto
  bool more_than_min_keys() const { return key_count > CORMEN_ORDER-1; };

  void right_shift(const int = 1);
  void left_shift();

  int last_key() const { return keys[key_count-1]; };
};

class BPlusTree {
  Node* root;

public:
  BPlusTree(): root{new Node{}} { };  //di default l'albero, se vuoto, possiede comunque un nodo
  BPlusTree(Node* p): root{p} { };  //DEBUG //TODO rimuovi

  Row search(const int) const;
  BPlusTree& insert(const int, const Row&);
  BPlusTree& remove(const int);

  Node* first();

  void print();
  void print_leaves();

  void destructor_helper(Node*);
  ~BPlusTree();

private:
  void print(std::vector<Node*>&);

  void split_child(Node*, const int);
  void insert_nonfull(Node*, const int, const Row&);

  void delete_key_in_leaf(Node*, const int);
  char delete_helper(const int, Node*);
  void rotate(Node*, const int);
  void update_key(Node*, const int);
  Node* merge(Node*, const int);
};

inline std::ostream& operator<<(std::ostream& os, const Node& n) {
  os << "[";
  for(int i = 0; i < n.key_count-1; ++i) {
    os << n.keys[i] << ", ";
  }
  return os << n.keys[n.key_count-1] << "]";
}

#endif // BPLUSTREE
