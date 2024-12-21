#include "BPlusTree.h"

using namespace std;

bool LinkList::deleteNode(int key){
    LNode *p = head;
    while (p != nullptr && p->getKey() != key) {
        p = p->getNext();
    }
    if (p == nullptr) return false;
    if (p->getPrev() != nullptr) {
        p->getPrev()->setNext(p->getNext());
        if(p->getNext())p->getNext()->setPrev(p->getPrev());
        else tail = p->getPrev();
    } else {
        head = p->getNext();
        if(head != nullptr)head->setPrev(nullptr);
    }
    delete p;
    size--;
    return true;
}

LNode* LinkList::findKey(int key) const {
    LNode *p = head;
    while (p != nullptr) {
        if (p->getKey() == key) return p;
        p = p->getNext();
    }
    return nullptr;
}

int LinkList::getHeadKey() const {
    if (head == nullptr) return -1;
    return head->getKey();
}

bool LinkList::insertNode(int key, int value, BPNode* child) {
    LNode *p = new LNode(key, value, child);
    if (head == nullptr) {
        head = tail = p;
    } else {
        LNode *q = getNode(p, &LinkList::cmp);
        if (q != nullptr) {
            if (q->getKey() == key) {delete p;return false;}
            p->setNext(q);
            p->setPrev(q->getPrev());
            if (q->getPrev() != nullptr) {
                q->getPrev()->setNext(p);
            } else {
                head = p;
            }
            q->setPrev(p);
        } else {
            tail->setNext(p);
            p->setPrev(tail);
            tail = p;
        }
    }
    size++;
    return true;
}

LNode* LinkList::getNode(int i) const {
    if (head == nullptr) return nullptr;
    LNode *p = head;
    for (int j = 1; j < i; j++) {
        p = p->getNext();
        if (p == nullptr) return nullptr;
    }
    return p;
}

LNode* LinkList::getNode(LNode* node, bool (LinkList::*cmp)(LNode*, LNode*) const) const {
    if (node == nullptr) return nullptr;
    LNode *p = head;
    while (p != nullptr) {
        if ((this->*cmp)(node, p)) {
            return p;
        }
        p = p->getNext();
    }
    return nullptr;
}

LinkList* LinkList::splitList(int i) {
    LNode* node = getNode(i);
    if (node == nullptr) return nullptr;
    int siz = size;
    size = max(0, i - 1);
    LNode* tmpTail = tail;
    tail = node->getPrev();
    if (tail != nullptr) {
        tail->setNext(nullptr);
    }
    node->setPrev(nullptr);
    LinkList* newList = new LinkList();
    newList->head = node;
    newList->tail = tmpTail;
    newList->size = siz - i + 1;
    return newList;
}

void LinkList::mergeList(LinkList* other){
    size += other->getSize();
    if(other->getHead()->getKey() > head->getKey()){
        tail->setNext(other->getHead());
        other->getHead()->setPrev(tail);
        qDebug()<<"tail1"<<tail;
        tail = other->getTail();
        qDebug() << tail->getKey();
        qDebug()<<"tail2"<<tail;
    }
    else{
        head->setPrev(other->getTail());
        other->getTail()->setNext(head);
        qDebug()<<"head1"<<head;
        head = other->getHead();
        qDebug()<<"head2"<<head;
    }

    other->setEmpty();
}

void LinkList::borrowNode(LinkList* other){
    LNode *oHead = other->getHead();
    insertNode(oHead->getKey(),oHead->getValue(),oHead->getChild());
    other->deleteNode(oHead->getKey());
}

LNode* BPNode::findKey(int key) const {
    return linkList->findKey(key);
}

void BPNode::updateFather() {
    LinkList* link = linkList;
    LNode* p = link->getHead();
    while (p != nullptr) {
        if (p->getChild() != nullptr) {
            p->getChild()->setFather(this);
        }
        p = p->getNext();
    }
}

void BPNode::updateKey() {
    if (father == nullptr) return;
    LinkList* link = father->getLinkList();
    LNode* p = link->getHead();
    bool isChanged = false;
    while (p != nullptr) {
        if (p->getKey() != this->getKey() && p->getChild() == this) {
            p->setKey(this->getKey());
            isChanged = true;
        }
        p = p->getNext();
    }
    if (isChanged) father->updateKey();
}

void BPNode::printKeys() const {
    if (linkList == nullptr) return;
    LNode* p = linkList->getHead();
    while (p != nullptr) {
        cout << p->getKey() << " ";
        p = p->getNext();
    }
    cout << endl;
}

int BPNode::getKey() const {
    if (linkList == nullptr) return -1;
    return linkList->getHeadKey();
}


bool BPlusTree::deleteBPNodeTree(int key,BPNode *node) {
    if(node == nullptr)return false;
    LinkList *linkList = node->getLinkList();
    bool isSuccess = linkList->deleteNode(key);
    if(!isSuccess)return false;
    if(node->getLinkList()->getSize() == 0 && node != root){
        deleteBPNodeTree(key,node->getFather());
        delete node;
    }else {
        qDebug() << "nodeSize:" << node->getSize();
        if(node->getSize() < rank / 2 && node != root){
            mergeBPNode(node->getFather());
        }else node->updateKey();
    }
    return isSuccess;
}

bool BPlusTree::deleteBPNode(int key){
    BPNode *node = getBPNode(key,root);
    if(node == nullptr)return false;
    bool isSuccess = deleteBPNodeTree(key, node);
    while(root->getSize() == 1 && !root->isLeaf()){
        BPNode * tmp = root;
        root = root->getLinkList()->getHead()->getChild();
        root->setFather(nullptr);
        delete tmp;
    }
    if(root->getSize() == 0){delete root;root = new BPNode();}
    return isSuccess;
}

LNode* BPlusTree::findBPNode(int key) {
    BPNode *node = getBPNode(key, root);
    if (node == nullptr) return nullptr;
    return node->findKey(key);
}

bool BPlusTree::insertBPNode(int key, int value) {
    BPNode* p = getBPNode(key, root);
    if (p == nullptr) return false;
    return insertBPlusTree(key, value, p);
}

void BPlusTree::printBPlusTree() const {
    queue<BPNode*> q;
    q.push(root);
    while (!q.empty()) {
        BPNode* p = q.front();
        q.pop();
        p->printKeys();
        LinkList* link = p->getLinkList();
        LNode* h = link->getHead();
        while (h != nullptr) {
            if (h->getChild()) q.push(h->getChild());
            h = h->getNext();
        }
    }
}

void BPlusTree::splitBPNode(BPNode *node) {
    LinkList* linkList = node->getLinkList();
    if (linkList->getSize() < rank) return;
    int mid = (rank + 1) / 2 + 1;
    LinkList* newLink = linkList->splitList(mid);
    BPNode* newBPNode = new BPNode(node->isLeaf(), node->getFather(), newLink);
    if (node->getFather() == nullptr) {
        BPNode* newBPNodeRoot = new BPNode(false);
        insertBPlusTree(node->getKey(), 0, newBPNodeRoot, node);
        insertBPlusTree(newBPNode->getKey(), 0, newBPNodeRoot, newBPNode);
        root = newBPNodeRoot;
        node->setFather(newBPNodeRoot);
        newBPNode->setFather(newBPNodeRoot);
    } else {
        newBPNode->setFather(node->getFather());
        insertBPlusTree(newBPNode->getKey(), 0, node->getFather(), newBPNode);
    }
    node->updateFather();
    newBPNode->updateFather();
}

void BPlusTree::deleteBPlusTree(BPNode *root) {
    if (root == nullptr) return;
    LinkList *linkList = root->getLinkList();
    LNode *p = linkList->getHead();
    while (p != nullptr) {
        deleteBPlusTree(p->getChild());
        p = p->getNext();
    }
    delete root;
}

bool BPlusTree::insertBPlusTree(int key, int value, BPNode *node, BPNode* child) {
    LinkList *linkList = node->getLinkList();
    bool isSuccess = linkList->insertNode(key, value, child);
    if (!isSuccess) return false;
    node->updateKey();
    splitBPNode(node);
    return isSuccess;
}

BPNode* BPlusTree::getBPNode(int key, BPNode *now) const {
    if (now->isLeaf()) return now;
    LinkList *linkList = now->getLinkList();
    LNode *p = linkList->getHead();
    BPNode *nextNode = p->getChild();
    while (p != nullptr && key >= p->getKey()) {
        nextNode = p->getChild();
        p = p->getNext();
    }
    return getBPNode(key, nextNode);
}

void BPlusTree::mergeBPNode(BPNode *node){
    LinkList *linkList = node->getLinkList();
    LNode *p = linkList->getHead();
    while(p != nullptr){
        if(p->getChild() != nullptr && p->getChild()->getSize() < rank / 2)break;
        p = p->getNext();
    }
    if(p == nullptr)return;
    LNode *bro = nullptr;
    if(p->getPrev() != nullptr)bro = p->getPrev();
    else if(p->getNext() != nullptr)bro = p->getNext();
    else return ;
    BPNode *pNode = p->getChild(),*broNode = bro->getChild();
    int broSize = broNode->getSize();
    int nowSize = pNode->getSize();
    if(nowSize + broSize >= rank){
        pNode->getLinkList()->borrowNode(broNode->getLinkList());
        broNode->updateKey();
    }
    else{
        pNode->getLinkList()->mergeList(broNode->getLinkList());
        deleteBPNodeTree(bro->getKey(),node);
        pNode->updateKey();
        delete broNode;
    }
    pNode->updateFather();

}

// int main() {
//     BPlusTree tree;
//     int op , k, v;
//     cin >> op >> k >> v;
//     while (k && v) {
//         if(op == 1){
//             bool isSuccess = tree.insertBPNode(k, v);
//             if (!isSuccess) cout << "节点重复" << endl;
//             tree.printBPlusTree();
//         }else if(op == 2){
//             LNode* node = tree.findBPNode(k);
//             if(node == nullptr)cout << "未找到" << endl;
//             else cout << "Value: " << node->getValue() << endl;
//         }
//         else{
//             bool isSuccess = tree.deleteBPNode(k);
//             if (!isSuccess) cout << "未找到" << endl;
//             tree.printBPlusTree();
//         }
        
//         cin >> op >> k >> v;
//     }
//     return 0;
// }
