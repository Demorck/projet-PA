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

typedef struct equipements {
    Equipement* val;
    struct equipements* next = nullptr;
} equipements_t;

/******************************************/

void freeList(ennemies_t* l)
{
    if (l != nullptr)
    {
        delete l->val;
        ennemies_t* nextNode = l->next;
        delete l;
        freeList(nextNode);
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
        projectiles_t* nextNode = l->next;
        delete l;
        freeList(nextNode);
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

void freeList(equipements_t* l)
{
    if (l != nullptr)
    {
        delete l->val;
        equipements_t* nextNode = l->next;
        delete l;
        freeList(nextNode);
    }
}


equipements_t* remove(equipements_t* from, Equipement* what)
{
    equipements_t* current = from; 
    equipements_t* previous = nullptr;

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