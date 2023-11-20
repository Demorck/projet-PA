#ifndef STRUCT_HPP
#define STRUCT_HPP
// #include <Enemy.hpp>
// #include <Projectile.hpp>

typedef struct list {
    void* val;
    struct list* next;
} list_t;

void freeList(list_t* l)
{
    if (l != nullptr)
    {
        delete l->val;
        freeList(l->next);
        delete l;
    }
}

list_t* remove(list_t* from, list_t* what)
{
    list_t* current = from; 
    list_t* previous = nullptr;

    while (current != nullptr && current->val != what)
    {
        previous = current;
        current = current->next;
        if (current == what) break;
        
    }

    if (current != nullptr)
    {
        if (previous != nullptr)
        {
            previous->next = current->next;
        }
        else
        {
            from = current->next;
        }

        delete current->val;
        delete current;
    }

    return from;
}

#endif