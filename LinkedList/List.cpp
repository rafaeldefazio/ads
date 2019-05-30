#include "List.h"
 //---------------------------------------------------------------
List::List() {
        head = NULL;
        count = 0;
}
//---------------------------------------------------------------
List::~List() {
        clear();
}
//---------------------------------------------------------------
bool List::empty() {
        return (head == NULL);
}
//---------------------------------------------------------------
bool List::full() {
        return false;
}
//---------------------------------------------------------------
void List::clear() {
        ListPointer q;

        while (head != NULL) {
                q = head;
                head = head->nextNode;
                delete q;
        }
        count = 0;
}
//---------------------------------------------------------------
long List::size() {
        return count;
}
//---------------------------------------------------------------
void List::insert(long p, ListEntry x) {
        ListPointer newNode, current;

        if (p < 1 || p > count + 1) {
                cout << "Posicao invalida" << endl;
                abort();
        }
        newNode = new ListNode;
        newNode->entry = x;
        if (p == 1) {
                newNode->nextNode = head;
                head = newNode;
        } else {
                setPosition(p - 1, current);
                newNode->nextNode = current->nextNode;
                current->nextNode = newNode;
        }
        count++;
}
//---------------------------------------------------------------
void List::remove(long p, ListEntry & x) {
        ListPointer node, current;

        if (p < 1 || p > count) {
                cout << "Posicao invalida" << endl;
                abort();
        }
        if (p == 1) {
                node = head;
                head = node->nextNode;
        } else {
                setPosition(p - 1, current);
                node = current->nextNode;
                current->nextNode = node->nextNode;
        }
        x = node->entry;
        delete node;
        count = count - 1;
}
//---------------------------------------------------------------
void List::retrieve(long p, ListEntry & x) {
        ListPointer current;

        setPosition(p, current);
        x = current->entry;
}
//---------------------------------------------------------------
long List::search(ListEntry x) {
        long p = 1;
        ListPointer q = head;

        while (q != NULL && q->entry != x) {
                q = q->nextNode;
                p++;
        }
        return (q == NULL ? 0 : p);
}
//---------------------------------------------------------------
string List::toString() {
        ListPointer q = head;
        string s;
        stringstream ss;

        while (q != NULL) {
                ss << q->entry << ",";
                q = q->nextNode;
        }
        s = ss.str();
        return "[" + s.substr(0, s.length() - 1) + "]";
}
//---------------------------------------------------------------
string List::toStringAddr() {
        ListPointer q = head;
        string s;
        stringstream ss;

        while (q != NULL) {
                ss << q << ",";
                q = q->nextNode;
        }
        s = ss.str();
        return "[" + s.substr(0, s.length() - 1) + "]";
}
//---------------------------------------------------------------
void List::setPosition(long p, ListPointer & current) {
        long i;

        if (p < 1 || p > count + 1) {
                cout << "Posicao invalida" << endl;
                abort();
        }
        current = head;
        for (i = 2; i <= p; i++)
                current = current->nextNode;
}
//---------------------------------------------------------------
long long List::getAddr(ListEntry x) {
        ListPointer current = NULL;
        long p = search(x);
        if (p != 0)
                setPosition(p, current);
        return (long long) current;
}

//---------------------------------------------------------------
bool List::swap(ListEntry a, ListEntry b) {

        ListPointer currentp, p, currentq, q, r;
        bool foundA = false, foundB = false;

        // se a for igual à b, se a lista tiver apenas 1 elemento, ou se estiver vazia, retornar false
        if (a == b || size() <= 1) {
                return false;
        } else {

                currentp = NULL;
                p = head;

                // percorre ate encontrar a ou b ou chegar no fim da lista
                while (p->nextNode != NULL && !(p->entry == a || p->entry == b)) {

                        // se estiver apontado por head
                        if (p == head) {
                                currentp = head;
                                p = currentp->nextNode;

                                // senao, continuar while
                        } else {
                                currentp = currentp->nextNode;
                                p = currentp->nextNode;

                        }

                }

                currentq = currentp;
                q = p;

                // se o elemento encontrado for a
                if (p->entry == a) {
                        foundA = true;

                        while (q->nextNode != NULL && q->entry != b) {

                                // se b estiver apontado por head
                                if (q == head) {
                                        currentq = head;
                                        q = currentq->nextNode;

                                        // senao, continuar while

                                } else {

                                        currentq = currentq->nextNode;
                                        q = currentq->nextNode;

                                }

                        }

                        if (q->entry == b)
                                foundB = true;

                        // se o elemento encontrado for b
                } else if (p->entry == b) {
                        foundB = true;

                        while (q->nextNode != NULL && q->entry != a) {

                                // se a estiver apontado por head
                                if (q == head) {
                                        currentq = head;
                                        q = currentq->nextNode;

                                        // senao, continuar while
                                } else {
                                        currentq = currentq->nextNode;
                                        q = currentq->nextNode;

                                }

                        }

                        if (q->entry == a)
                                foundA = true;

                }

                // se a e b forem encontrados, realizar troca

                if (foundA && foundB) {

                        // se p estiver no começo da lista

                        if (p == head) {

                                // se forem elementos adjacentes
                                if (q == p->nextNode) {

                                        p->nextNode = q->nextNode;
                                        q->nextNode = p;
                                        head = q;
                                        return true;

                                } else {

                                        r = p->nextNode;

                                        p->nextNode = q->nextNode;
                                        q->nextNode = r;
                                        currentq->nextNode = p;
                                        head = q;
                                        return true;

                                }

                                // se p nao estiver no começo da lista

                        } else {

                                // se forem elementos adjacentes
                                if (q == p->nextNode) {

                                        p->nextNode = q->nextNode;
                                        q->nextNode = p;
                                        currentp->nextNode = q;
                                        return true;

                                } else {

                                        r = p->nextNode;

                                        p->nextNode = q->nextNode;
                                        q->nextNode = r;
                                        currentq->nextNode = p;
                                        currentp->nextNode = q;
                                        return true;

                                }

                        }

                } else {
                        return false;
                }

        }

}
//---------------------------------------------------------------