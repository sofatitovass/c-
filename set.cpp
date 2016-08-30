#include <string>
#include "set.h"

set::Node::Node():key (NULL), l(nullptr), r(nullptr), p(nullptr) {}
set::Node::Node(std::string value):key (value), l(nullptr), r(nullptr), p(nullptr) {}
set::Node::Node(std::string value, Node *parent): key (value), l(nullptr), r(nullptr), p(parent) {}

set::Node::Node set::Node::Node *insert(value_type x, Node *Tree)
{
    if (Tree == nullptr)
    {
        Tree = new Node(x);
        return Tree;
    }
    else
    {
        if (x == Tree->key)
        {
            return Tree;
        }
        else if (x < Tree->key)
        {
            if (Tree->l != nullptr)
            {
                return insert(x, Tree->l);
            }
            else {
                Tree->l = new Node(x, Tree);
                return Tree->l;
            }
        }
        else if (Tree->r != nullptr)
            {
                return insert(x, Tree->r);
            }
            else
            {
                Tree->r = new Node(x, Tree);
                return Tree->r;
            }
     }
 }

set::Node::Node *deleting(value_type x, Node *Tree) {
                if (Tree == nullptr)
                    return nullptr;
                if (x < Tree->key)
                    return deleting(x, Tree->l);
                if (x > Tree->key)
                    return deleting(x, Tree->r);
                if (x == Tree->key)
                {
                    if ((Tree->l == nullptr) && (Tree->r == nullptr))
                    {
                        if (Tree->p == nullptr) {
                            return Tree;
                        }
                        Tree->p->l->key = x ? Tree->p->l = nullptr : Tree->p->r = nullptr;
                        return Tree;
                }
                 if ((Tree->l == nullptr) && (Tree->r != nullptr)) || (((Tree->l != nullptr) && (Tree->r == nullptr)) )) {

                        if (Tree->p == nullptr) {
                            if (Tree->r != nullptr)
                            {
                                Tree->r->p = nullptr;
                            } else
                            {
                                Tree->l->p = nullptr;
                            }
                            return Tree;
                        }
                        if ((Tree->p->r != nullptr) && (Tree->p->r->key == x)) {
                            if ( (Tree->r != nullptr)))
                            {
                                Tree->r->p = Tree->p;
                                Tree->p->r = Tree->r;
                            }
                            else
                            {
                                Tree->l->p = Tree->p;
                                Tree->p->r = Tree->l;
                            }
                        }
                        if ((Tree->p->l != nullptr) && (Tree->p->l->key == x)) {
                            if ((Tree->r != nullptr))
                            {
                                Tree->r->p = Tree->p;
                                Tree->p->l = Tree->r;
                            }
                            else
                            {
                                Tree->l->p = Tree->p;
                                Tree->p->l = Tree->l;
                            }
                        }
                        return Tree;
                    }
                    if ((Tree->l != nullptr) && (Tree->r != nullptr)) {
                        Node *temp = Tree->r;
                        while (temp->l != nullptr) {
                            temp = temp->l;
                        }
                        std::swap(Tree->key, temp->key);
                        return deleting(x, temp);
                    }
                }
         }
set::Node::Node *next(value_type x, Node *Tree) {
                if (Tree == nullptr)
                    return nullptr;
                if (Tree->r != nullptr) {
                    Tree = Tree->r;
                    while (Tree->l != nullptr)
                        Tree = Tree->l;
                    return Tree;
                } else {
                    while ((Tree->p != nullptr) && (Tree->p->r != nullptr) && (Tree->p->r->key == Tree->key))
                        Tree = Tree->p;
                    if (Tree->p == nullptr)
                        return nullptr;
                    if ((Tree->p->l != nullptr) && (Tree->p->l->key == Tree->key))
                        return Tree->p;
                }
            }

set::Node::Node *prev(value_type x, Node *Tree) {
                if (Tree == nullptr)
                    return nullptr;
                if (Tree->l != nullptr) {
                    Tree = Tree->l;
                    while (Tree->r != nullptr)
                        Tree = Tree->r;
                    return Tree;
                } else {
                    while ((Tree->p != nullptr) && (Tree->p->l != nullptr) && (Tree->p->l->key == Tree->key))
                        Tree = Tree->p;
                    if (Tree->p == nullptr)
                        return nullptr;
                    if ((Tree->p->r != nullptr) && (Tree->p->r->key == Tree->key))
                        return Tree->p;
                }
            }

set::Node::Node set::Node::*find(value_type x, Node *Tree) {
                if (Tree == nullptr)
                    return nullptr;
                if (x == Tree->key)
                    return Tree;
                if ((Tree->l != nullptr) && (Tree->key > x))
                    return find(x, Tree->l);
                if ((Tree->r != nullptr) && (Tree->key < x))
                    return find(x, Tree->r);
                return nullptr;
            }

void set::Node::clear(Node *Tree) {
    if (Tree != nullptr) {
        clear(Tree->l);
        clear(Tree->r);
        delete(Tree);
    }
}




set::iterator::iterator() : pointer(nullptr), _set(pointer) {};

set::iterator::iterator(iterator const &other) pointer(other.pointer), _set(other._set)
{
    _set->iters.push_back(this);
}

set::iterator::iterator(Node *other,set *other2) : pointer(other), _set(other2)
{
    ptr = other;
    _set->iters.push_back(this);
}

set::iterator::~iterator()
{
    for (size_t i = 0; i < set->iters.size(); i++)
        if (set->iters[i] == this)
        {
            std::swap(set->iters[i], set->iters.back());
            set->iters.pop_back();
            break;
        }
}

 std::string set::iterator::&operator*() const
 {
                assert(ptr != nullptr && "invalid iterator");
                assert(ptr != &set->fake_end && "tried to get value type from end");
                return ptr->key;
}


iterator set::iterator::&operator++() {
    if (ptr != nullptr) {
        if (ptr == &set->fake_end)
            assert(false);
        Node *temp = Node::next(ptr->key, ptr);
        if (temp == nullptr)
            ptr = &set->fake_end;
        else
            ptr = temp;
    } else
        assert(false);
    return *this;
}

iterator set::iterator::&operator--() {
    if (ptr != nullptr) {
        Node *temp;
        if (ptr == &set->fake_end) {
            temp = set->head;
            assert(temp != nullptr);
            while (temp->r != nullptr)
                temp = temp->r;
        }
        else
            temp = Node::prev(ptr->key, ptr);
        if (temp == nullptr)
            assert(false);
        ptr = temp;
    } else
        assert(false);
    return *this;
}

bool set::iterator::operator==(iterator const &other) const {
    assert(this->set != nullptr && other.set != nullptr);
    assert(this->set == other.set );
    return (this->ptr == other.ptr);
}

bool set::iterator::operator!=(iterator const &other) const {
    return !(*this == other);
}

set::set() : head(nullptr) {}

void set::copy(Node *Tree)
{
    insert(Tree->key);
    if (Tree->l != nullptr)
        copy(Tree->l);
    if (Tree->r != nullptr)
        copy(Tree->r);
}

set::set(set const &other) : head(nullptr)
{
    copy(other.head);
}

set::set &operator=(set const &other)
{
            set temp(other);
            std::swap(temp.iters, iters);
            std::swap(temp.head, head);
            return *this;
}

set::~set()
{
    clear();
    for (size_t i = iters.size(); i > 0; i--) {
        iters[i - 1]->ptr = nullptr;
        iters[i - 1]->_set = nullptr;
    }
    iters.clear();
}

iterator insert(value_type const &x)
{
    set::Node *temp = set::Node::insert(x, head);
    if (head == nullptr)
        head = temp;
    return iterator(temp, this);
}

iterator find(value_type const &x)
{
    Node *temp = Node::find(x, head);
    if (temp == nullptr)
        return iterator(&fake_end, this);
    else
        return iterator(temp, this);
}
