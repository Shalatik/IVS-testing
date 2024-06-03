//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     SIMONA CESKOVA <xcesko00@stud.fit.vutbr.cz>
// $Date:       $2021-03-12
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author SIMONA CESKOVA
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include <iostream>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:

    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() 
    {
        //values vybrane tak aby pokryly ruznou skalu velikosti hodnot
        int values[] = { -53, 200009, 338, 164, 0, -83, 497, -98, 170, 104, 636, 145, -62, 25, 7 };

        for(int i = 0; i < 14; ++i)
            tree.InsertNode(values[i]);
    }
    BinaryTree tree;
};

class ThreeAxioms : public ::testing::Test
{
protected:
    
    BinaryTree tree;
};

//============================================================================//

TEST_F(NonEmptyTree, InsertNode)
{
    //testuji cisla ktera uz jsou v me rade, ze se znovu nepridaji
    int array1[] = {-53, 200009, 338, 164, 0};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.InsertNode( array1[i] );
        //cekam false, protoze uz tam jsou
        EXPECT_FALSE(output.first);
        //porovnam hodnoty na ktere uzuji s vlozenym prvkem
        EXPECT_EQ(output.second -> key, array1[i] );
    }

    //testuji pole cisel ktere se pridaji
    double array2[] = {-200008, 9, 24, -11, 1290};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.InsertNode( array2[i] );
        //cekam true, protoze se uspesne pridaly
        EXPECT_TRUE(output.first);
        //porovnam hodnoty na ktere uzuji s vlozenym prvkem
        EXPECT_EQ(output.second -> key, array2[i] );
    }
}

TEST_F(NonEmptyTree, DeleteNode)
{
    //hodnoty ktere tam jsou
    double array1[] = {-53, 200009, 338, 164, 0};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.DeleteNode( array1[i] );
        //true, protoze se uspesne smazaly
        EXPECT_TRUE(output);
    }

    //hodnoty ktere tam nejsou
    double array2[] = {-200008, 9, 24, -11, 7123};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.DeleteNode( array2[i] );
        //false, protoze protoze se nedaly smazat
        EXPECT_FALSE(output);
    }
}

TEST_F(NonEmptyTree, FindNode)
{
    //hodnoty ktere tam jsou
    double array1[] = {-53, 200009, 338, 164, 0};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.FindNode( array1[i] );
        //ocekavam true, protoze se uspesne nasly
        EXPECT_TRUE(output);
        EXPECT_EQ(output -> key, array1[i]);
    }

    //hodnoty ktere tam nejsou
    double array2[] = {-200008, 9, 24, -11, 7123};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.FindNode( array2[i] );
        //cekam false, protoze tam nejsou a nazeni se nepodarilo
        EXPECT_FALSE(output);
        //vrati mi ukatel na NULL
        EXPECT_EQ(output, nullptr);
    }

}
TEST_F(EmptyTree, InsertNode)
{
    double array[] = {-200008, 0, 23, 80, -3};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.InsertNode( array[i] );
        //true, protoze se uspesne vlozily
        EXPECT_TRUE(output.first);
        //kontroluji jestli ukazatel na vlozenou hodnotu sedi s hodnotou vkladaneho cisla
        EXPECT_EQ(output.second->key, array[i] );
    }
}

TEST_F(EmptyTree, DeleteNode)
{
    double array[] = {-200008, 0, 23, 80, -3};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.DeleteNode( array[i] );
        //false protoze strom je prazdny
        EXPECT_FALSE(output);
    }
}

TEST_F(EmptyTree, FindNode)
{
    double array[] = {-200008, 0, 23, 80, -3};
    for(int i = 0; i < 5; i++)
    {
        auto output = tree.FindNode( array[i] );
        //false protoze v prazdnem strome zadna hodnota se nenasla
        EXPECT_FALSE(output);
        //vraci mi ukazatel na NULL
        EXPECT_EQ(output, nullptr);
    }
}
//============================================================================//
//BinaryTree::RED
//Vsechny listove uzly (tedy uzly bez potomku) jsou cerne.
TEST_F(ThreeAxioms, Axiom1)
{
    //vztvorim pole ukazatelu pro LeafNodes
    std::vector<Node_t *> outLeafNodes;    
    tree.GetLeafNodes(outLeafNodes);
    //v cyklu se na kazdeho podivam, jestli ma opravdu barvu BLACK
    for(auto each : outLeafNodes)
    {
        EXPECT_EQ(each -> color, BLACK);
    }
}

//Pokud je uzel cerveny, pak jsou jeho oba potomci cerni.
TEST_F(ThreeAxioms, Axiom2)
{
    //vztvorim pole ukazatelu na AllNodes
    std::vector<Node_t *> outAllNodes;    
    tree.GetAllNodes(outAllNodes);
    //v cyklu vsechny projdu a hledam nejakeho rodice s barvou RED
    for(auto each : outAllNodes)
    {
        if(each -> pParent -> color == RED)
        {
            //pokud ho najdu, tak zkoumany potomek musi byt BLACK
            EXPECT_EQ(each -> color, BLACK);
        }
    }
}

//Kazda cesta od kazdeho uzlu ke koreni obsahuje stejny pocet cernych uzlu.
TEST_F(ThreeAxioms, Axiom3)
{
    std::vector<Node_t *> outLeafNodes;
    tree.GetLeafNodes(outLeafNodes);
    int number = 0;
    int temp_number = 0;
    auto root = tree.GetRoot();

    //vytvorim si for cyklus a projdu od 1. leafNode k root
    //spocitam pocet BLACK nodes a ten pocet pouziji jako konstantu a budu s ni kontrolovat ostatni
    //ostatni cesty musi mit shodny pocet BLACK nodes jako prvni cesta
    for(auto each : outLeafNodes)
    {         
        auto *node = each -> pParent;
        for(;node != root; node = node -> pParent)
        {
            if(node -> color == BLACK)
            {
                number++;
            }
        }
        break;
    }
    //tady projdu vsechny ostatni cesty
    for(auto each : outLeafNodes)
    {
        auto *node = each -> pParent;
        for(;node != root; node = node -> pParent)
        {
            if(node -> color == BLACK)
            {
                temp_number++;
            }
        }
        //kontroluji jestli se pocet BLACK nodes shoduje s poctem z prvni cestou
        EXPECT_EQ(number, temp_number);
        //po konci cesty vynuluji promennou
        temp_number = 0;
    }
}
/*** Konec souboru black_box_tests.cpp ***/
