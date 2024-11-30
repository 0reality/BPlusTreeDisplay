#include <iostream>
#include <queue>
#include <QDebug>

class BPNode;

class LNode {
private:
    int key, value;
    LNode *next, *prev;
    BPNode *child;

public:
    int getKey() const { return key; }
    int getValue() const { return value; }
    LNode* getNext() const { return next; }
    LNode* getPrev() const { return prev; }
    BPNode* getChild() const { return child; }
    void setChild(BPNode *c) { child = c; }
    void setNext(LNode *n) { next = n; }
    void setPrev(LNode *p) { prev = p; }
    void setKey(int ke) { key = ke; }

public:
    LNode(int key, int value, BPNode* child, LNode* next = nullptr, LNode* prev = nullptr)
        : key(key), value(value), next(next), prev(prev), child(child) {}
    LNode() : key(0), value(0), next(nullptr), prev(nullptr), child(nullptr) {}
};

class LinkList {
private:
    LNode *head, *tail;
    int size;

public:
    LNode* getHead() const { return head; }
    LNode* getTail() const { return tail; }
    int getSize() const { return size; }
    int getHeadKey() const;
    bool insertNode(int key, int value, BPNode* child);
    LNode* getNode(LNode* node, bool (LinkList::*cmp)(LNode*, LNode*) const) const;
    LNode* getNode(int i) const;
    LinkList* splitList(int i);
    bool cmp(LNode* a, LNode* b) const { return b->getKey() >= a->getKey(); }
    LNode* findKey(int key) const;
    bool deleteNode(int key);

public:
    LinkList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkList() {
        LNode *p = head;
        while (p != nullptr) {
            LNode *q = p;
            p = p->getNext();
            delete q;
        }
    }
};

class BPNode {
private:
    BPNode *father;
    LinkList *linkList;
    bool isLeafs;

public:
    bool isLeaf() const { return isLeafs; }
    BPNode* getFather() const { return father; }
    void setFather(BPNode *fa) { father = fa; }
    LinkList* getLinkList() const { return linkList; }
    int getKey() const;
    void printKeys() const;
    void updateKey();
    void updateFather();

    LNode* findKey(int key) const;

public:
    BPNode(bool isLe = true, BPNode* fa = nullptr, LinkList* link = new LinkList())
        : isLeafs(isLe), father(fa), linkList(link) {}
    ~BPNode() { delete linkList; }
};


class BPlusTree {
private:
    BPNode *root;
    int rank;

public:
    BPNode* getRoot() const { return root; }
    void deleteBPlusTree(BPNode *root);
    bool insertBPlusTree(int key, int value, BPNode *node, BPNode* child = nullptr);
    BPNode* getBPNode(int key, BPNode *now) const;
    void splitBPNode(BPNode *node);
    void printBPlusTree() const;
    bool insertBPNode(int key, int value);
    bool deleteBPNodeTree(int key,BPNode *node);
    bool deleteBPNode(int key);
    LNode* findBPNode(int key);
    int getRank(){return rank;}

public:
    BPlusTree(int r = 4) : root(new BPNode()), rank(r) {}
    ~BPlusTree() { deleteBPlusTree(root); }
};
