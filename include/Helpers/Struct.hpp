#ifndef STRUCT_HPP
#define STRUCT_HPP
#include <Enemy.hpp>
#include <Projectile.hpp>

/* A modifier pour lister les ennemis et projectiles, et faire deux listes */
typedef struct ennemies {
    Enemy* val;
    struct ennemies* next = nullptr;
} ennemies_t;

typedef struct projectiles {
    Projectile* val;
    struct projectiles* next = nullptr;
} projectiles_t;

/******************************************/

void freeList(ennemies_t* l)
{
    if (l != nullptr)
    {
        delete l->val;
        freeList(l->next);
        delete l;
    }
}

ennemies_t* remove(ennemies_t* from, Enemy* what)
{
    ennemies_t* current = from; 
    ennemies_t* previous = nullptr;

    while (current != nullptr && current->val != what)
    {
        previous = current;
        current = current->next;
        if (current->val == what) break;
        
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

/************************************************/

void freeList(projectiles_t* l)
{
    if (l != nullptr)
    {
        delete l->val;
        freeList(l->next);
        delete l;
    }
}

projectiles_t* remove(projectiles_t* from, Projectile* what)
{
    projectiles_t* current = from; 
    projectiles_t* previous = nullptr;

    while (current != nullptr && current->val != what)
    {
        previous = current;
        current = current->next;
        if (current->val == what) break;
        
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

/************************************************/

#endif