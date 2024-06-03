//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     SIMONA CESKOVA <xcesko00@stud.fit.vutbr.cz>
// $Date:       $2021-03-12
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author SIMONA CESKOVA
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

// m_pHead >= p_1 >= p_2 >= ... >= p_tail

PriorityQueue::PriorityQueue() : m_pHead(NULL) {}

PriorityQueue::~PriorityQueue()
{
    //projdu cely seznam a pokazde smazu jeden node
    //mazu od prvniho nodu
    Element_t *free_node = NULL;
    for (Element_t *temp_node = m_pHead; temp_node != NULL;)
    {
        free_node = temp_node;
        temp_node = temp_node->pNext;
        //vymazu node z pameti
        delete free_node;
    }
}

void PriorityQueue::Insert(int value)
{
    //vytvorim si novy node ktery budu vkladat
    Element_t *new_node = new Element_t{
        .pNext = NULL,
        .value = value
    };
    //pokud je seznam jeste prazdny tak do m_pHead vlozim prvni prvek s hodnotou value
    if (m_pHead == NULL)
        m_pHead = new_node;
    else
    {
        //kontroluji velikost hodnoty a podle toho ji zaradim do podminky kam patri
        if (value >= m_pHead->value)
        {
            //pomoci temp_node_head vlozim novy node do seznamu
            auto temp_node_head = m_pHead;
            new_node->pNext = temp_node_head;
            m_pHead = new_node;
        }
        else if (value < m_pHead->value)
        {
            //v cyklu prochazim po ukazatelych prvky a porovnavam jejich hodnotu s value s novou
            Element_t *fr_node = m_pHead;
            Element_t *temp_node = m_pHead;
            for (; temp_node != NULL; temp_node = temp_node->pNext)
            {
                if (value >= temp_node->value)
                {
                    new_node->pNext = temp_node;
                    fr_node->pNext = new_node;
                    return;
                }
                fr_node = temp_node;
            }
            new_node->pNext = temp_node;
            fr_node->pNext = new_node;
        }
    }
}

bool PriorityQueue::Remove(int value)
{
    //kdyz je seznam prazdny tak nemam co mazat
    if (m_pHead == NULL)
        return false;
    //kdyz mam smazat head, tak pomoci promenne ktera ukazuje na cestu od head k next node
    //do nove head dam dalsi node
    if (value == m_pHead->value)
    {
        auto temp_node_head = m_pHead;
        m_pHead = temp_node_head->pNext;
        delete temp_node_head;
        return true;
    }
    //projdu cyklem vsechny node a hledam hodnotu na smazani
    Element_t *fr_node = m_pHead;
    Element_t* temp_node = m_pHead;
    while(temp_node != NULL)
    {
        if (value == temp_node->value)
        {
            auto to_del = temp_node;
            fr_node->pNext = to_del->pNext;
            delete to_del;
            return true;
        }
        fr_node = temp_node;
        temp_node = temp_node->pNext;
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    //pomoci cyklu hledam hledanou hodnotu, vratim na ni ukazatel
    //jinak vratim ukazatel na NULL
    Element_t* temp_node = m_pHead;
    while(temp_node != NULL)
    {
        if (value == temp_node->value)
        {
            return temp_node;
        }
        temp_node = temp_node->pNext;
    }
    return NULL;
}

size_t PriorityQueue::Length()
{
    //spocitam delku seznamu tak ze spocitam vsechny node v seznamu
    size_t sum = 0;
    Element_t* temp_node = m_pHead;
    while (temp_node != NULL)
    {
        sum++;
        temp_node = temp_node->pNext;
    }
    return sum;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/