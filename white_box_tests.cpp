//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     SIMONA CESKOVA <xcesko00@stud.fit.vutbr.cz>
// $Date:       $2021-03-12
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author SIMONA CESKOVA
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

/* oznaceni pro prehlednost:
    v ... pro vektory hodnot co vkladam do matic (vector)
    m ... matice (matrix)
    rs ... prave strana matice (rightSide)
    result ... vysledky reseni rovnic x1,x2,x3,...
*/

TEST(MatrixTests, Constructor)
{
    Matrix m{};
    //matice s 1x1 ma hodnotu 0
    EXPECT_EQ(m.get(0,0), 0);
    //nedovoli vytvorit matici s R=0 || C=0
    EXPECT_ANY_THROW(Matrix(1,0));
    EXPECT_ANY_THROW(Matrix(0,3));
}

TEST(MatrixTests, MatrixValue)
{
    Matrix m{3,3};
    int value = 4;
    m.set(2, 1, 4);
    //matice neobsahuje hodnoty na souradnich vetsich nez hodnota R,C matice
    EXPECT_FALSE(m.set(5, 5, value));
    //spravne vloyi do matice hodnotu
    EXPECT_TRUE(m.set(1, 2, value));
    //zkontroluji ze hodnota na souradnici opravdu odpovida vlozene hodnote
    EXPECT_EQ(m.get(1,2), value);
}

TEST(MatrixTests, MatrixReady)
{
    std::vector<std::vector<double>> v = {{1,2},{3,4}};
    Matrix m1{2,2};
    Matrix m2{6,6};
    //podari se vlozit obsah matice kdyz vzhovuje velikost vektoru vlozenych hodnot
    EXPECT_TRUE(m1.set(v));
    //hodnoty davane do matice nemaji spravnou velikost
    EXPECT_FALSE(m2.set(v));
}
TEST(MatrixTests, ReturnValue)
{
    std::vector<std::vector<double>> v = {{1,4,9},{3,0,7}};
    Matrix m{2,3};
    m.set(v);
    //vyhodi chybu protoze jsou spatne zadane souradnice, ktere v matici nejsou
    EXPECT_ANY_THROW(m.get(3,5));
    //get vrati spravnou hodnotu
    EXPECT_EQ(m.get(0,1), 4);
}
TEST(MatrixTests, Compare)
{
    std::vector<std::vector<double>> v1 = {{1,2},{3,4}};
    std::vector<std::vector<double>> v2 = {{1,1},{3,3}};
    Matrix m1{2,2};
    Matrix m2{2,2};
    Matrix m3{2,10};
    m1.set(v1);
    m2.set(v1);
    //matice jsou stejne, stejne velikosti i hodnoty uvnitr
    EXPECT_TRUE(m1 == m2);
    m2.set(v2);
    //chyba, stejne velikosti, ale ruzne hodnoty
    EXPECT_FALSE(m1 == m2);
    //chyba, ruzna velikost matic
    EXPECT_ANY_THROW(m1 == m3);
    
}
TEST(MatrixTests, Count)
{
    std::vector<std::vector<double>> v1 = {{1,2},{3,4}};
    std::vector<std::vector<double>> v2 = {{1,1},{3,3}};
    Matrix m1{2,2};
    Matrix m2{2,2};
    Matrix m3{2,10};
    m1.set(v1);
    m2.set(v2);
    //porovnam vsechny vysledky na vsech souradnich po souctu
    EXPECT_EQ((m1+m2).get(0,0), 2);
    EXPECT_EQ((m1+m2).get(0,1), 3);
    EXPECT_EQ((m1+m2).get(1,0), 6);
    EXPECT_EQ((m1+m2).get(1,1), 7);
    //nemuzu scitat 2 matice nevyhovujicich velikosti
    EXPECT_ANY_THROW(m1 + m3);    
}
TEST(MatrixTests, Product)
{
    std::vector<std::vector<double>> v1 = {{1,2},{3,4}};
    std::vector<std::vector<double>> v2 = {{1,1},{3,3}};
    Matrix m1{2,2};
    Matrix m2{2,2};
    Matrix m5{4,10};
    m1.set(v1);
    m2.set(v2);
    //porovnam vsechny vysledky na vsech souradnich po soucinu
    EXPECT_EQ((m1*m2).get(0,0), 7);
    EXPECT_EQ((m1*m2).get(0,1), 7);
    EXPECT_EQ((m1*m2).get(1,0), 15);
    EXPECT_EQ((m1*m2).get(1,1), 15);
    //nemuzu nasobit 2 matice nevyhovujicich velikosti
    EXPECT_ANY_THROW(m1*m5);
    
    
    std::vector<std::vector<double>> v3 = {{3,1}};
    std::vector<std::vector<double>> v4 = {{2},{3}};
    Matrix m3{1,2};
    Matrix m4{2,1};
    m3.set(v3);
    m4.set(v4);
    //kontroluji soucin pro rozdilne velikosti matic
    EXPECT_EQ((m3*m4).get(0,0), 9);
}
TEST(MatrixTests, Scalar)
{
    std::vector<std::vector<double>> v1 = {{1,2},{3,4},{3,4}};
    Matrix m1{3,2};
    double value = 120;
    m1.set(v1);
    //zkontroluji jestli vrati opravdu spravne hodnoty v matici
    EXPECT_EQ((m1*value).get(0,0), 120);
    EXPECT_EQ((m1*value).get(0,1), 240);
    EXPECT_EQ((m1*value).get(1,0), 360);
    EXPECT_EQ((m1*value).get(1,1), 480);
    EXPECT_EQ((m1*value).get(2,0), 360);
    EXPECT_EQ((m1*value).get(2,1), 480);

}
TEST(MatrixTests, LinearEquation)
{
    //kontrola chyb:

    std::vector<std::vector<double>> v_f = {{1,2},{1,1}};
    std::vector<double> rs_f = {3,2};
    std::vector<double> rs1 = {1,2,3,4} ;
    Matrix m_f{2,2};
    m_f.set(v_f);
    //velikost rozlohy prave strany rovnice neodpovida poctu radku v matici
    EXPECT_ANY_THROW(m_f.solveEquation(rs1));

    std::vector<std::vector<double>> v_2x4 = {{1,2},{3,20},{5,6},{13,8}};
    Matrix m_2x4{2,4};
    m_2x4.set(v_2x4);
    //pomoci Cramerova pravidla lze resit pouze matice nxn
    EXPECT_ANY_THROW(m_2x4.solveEquation(rs1));

    std::vector<std::vector<double>> v_singular = {{1,2,3},{4,8,12},{-1,-2,-3}};
    std::vector<double> rs3 = {6,4,8};
    Matrix m_singular{3,3};
    m_singular.set(v_singular);
    //matice 3x3 je singularni a proto nejde resit - nulovy determinant
    EXPECT_ANY_THROW(m_singular.solveEquation(rs3));
 
    std::vector<std::vector<double>> v_2x2_singular = {{1,2},{2,4}};
    Matrix m_2x2_singular{2,2};
    m_2x2_singular.set(v_2x2_singular);
    //chyba pro reseni 2x2 singularni matice - nulovy deteminant
    EXPECT_ANY_THROW(m_2x2_singular.solveEquation(rs_f));

    Matrix m_1x1_2{1,1};
    m_1x1_2.set({{0}});
    std::vector<double> rs_1x1 = {0};
    //determinant teto matice je 0 a v tom pripade nelze resit rovnici
    EXPECT_ANY_THROW(m_1x1_2.solveEquation(rs_1x1));

//============================================================================//
    // uspesne vyresene rovnice:

    Matrix m_1x1{1,1};
    m_1x1.set({{4}});
    std::vector<double> rs2= {1,1};
    std::vector<double> rs_1x1_2= {4};
    std::vector<double> result= {1};
    //reseni pro matici 2x2
    EXPECT_EQ(m_f.solveEquation(rs_f), rs2);
    //reseni 1x1 matice, resenim je jeji determinant, neboli hodnota na [0][0]
    EXPECT_EQ(m_1x1.solveEquation(rs_1x1_2), result);
    EXPECT_EQ(m_1x1.get(0,0), 4); //FIXME

    std::vector<std::vector<double>> v_3x3 = {{1,2,0},{0,1,-3},{3,0,-1}};
    std::vector<double> rs_3x3 = {5,5,4};
    std::vector<double> result_3x3 = {1,2,-1};
    Matrix m_3x3{3,3};
    m_3x3.set(v_3x3);
    //reseni pro matici 3x3
    EXPECT_EQ(m_3x3.solveEquation(rs_3x3), result_3x3);

    std::vector<std::vector<double>> v_4x4 = {{20,20,-10,10},{4,3,-1,2},{8,5,-3,4},{3,3,-2,2}};
    std::vector<double> rs_4x4 = {40, 6, 12, 6};
    std::vector<double> result_4x4 = {1,1,-1,-1};
    Matrix m_4x4{4,4};
    m_4x4.set(v_4x4);
    //reseni pro matici 4x4
    EXPECT_EQ(m_4x4.solveEquation(rs_4x4), result_4x4);

}
TEST(MatrixTests, MatrixTranspose)
{
    std::vector<std::vector<double>> v1 = {{1,2},{3,4},{7,8}};
    Matrix m1{3,2};
    m1.set(v1);
    //kontroluji jestli na vsech souradnich je spravna hodnota transponovane matice
    //pro jistotu si je vypisu
    EXPECT_EQ((m1.transpose()).get(0,0), 1);   
    EXPECT_EQ((m1.transpose()).get(0,1), 3);   
    EXPECT_EQ((m1.transpose()).get(0,2), 7);   
    EXPECT_EQ((m1.transpose()).get(1,0), 2);   
    EXPECT_EQ((m1.transpose()).get(1,1), 4);   
    EXPECT_EQ((m1.transpose()).get(1,2), 8);   
}
TEST(MatrixTests, Inverse)
{
    std::vector<std::vector<double>> v_3x3_singular = {{1,2,3},{4,8,12},{-1,-2,-3}};
    Matrix m_3x3_singular{3,3};
    m_3x3_singular.set(v_3x3_singular);
    //nemuze byt inverzni protoze je singularni
    EXPECT_ANY_THROW(m_3x3_singular.inverse());

    std::vector<std::vector<double>> v_2x4 = {{1,2},{3,20},{5,6},{13,8}};
    Matrix m_2x4{2,4};
    m_2x4.set(v_2x4);
    //matice neni 2x2 || 3x3
    EXPECT_ANY_THROW(m_2x4.inverse());

    std::vector<std::vector<double>> v_4x4 = {{1,2,3,4}, {50,6,7,8}, {9,10,4,12}, {3,14,1,16}};
    Matrix m_4x4{4,4};
    m_4x4.set(v_4x4);
    //chyba protoze matice neni 3x3 || 2x2
    EXPECT_ANY_THROW(m_4x4.inverse());

    Matrix m_1x1{1,1};
    //matice neni 2x2 || 3x3
    EXPECT_ANY_THROW(m_1x1.inverse());

    std::vector<std::vector<double>> v_2x2_singular = {{1,2},{2,4}};
    Matrix m_2x2_singular{2,2};
    m_2x2_singular.set(v_2x2_singular);
    //matice je singularni
    EXPECT_ANY_THROW(m_2x2_singular.inverse());

    std::vector<std::vector<double>> v_2x2 = {{1,2},{3,5}};
    Matrix m_2x2{2,2};
    m_2x2.set(v_2x2);
    //kontroluji kazdou hodnotu pro invezni matici 2x2
    EXPECT_EQ((m_2x2.inverse()).get(0,0), -5);
    EXPECT_EQ((m_2x2.inverse()).get(0,1), 2);
    EXPECT_EQ((m_2x2.inverse()).get(1,0), 3);
    EXPECT_EQ((m_2x2.inverse()).get(1,1), -1);
    
    std::vector<std::vector<double>> v_3x3 = {{1,2,-3},{0,1,2},{0,0,1}};
    Matrix m_3x3{3,3};
    m_3x3.set(v_3x3);
    //kontroluji kazdou hodnotu pro invezni matici 3x3.
    EXPECT_EQ((m_3x3.inverse()).get(0,0), 1);
    EXPECT_EQ((m_3x3.inverse()).get(0,1), -2);
    EXPECT_EQ((m_3x3.inverse()).get(0,2), 7);
    EXPECT_EQ((m_3x3.inverse()).get(1,0), 0);
    EXPECT_EQ((m_3x3.inverse()).get(1,1), 1);
    EXPECT_EQ((m_3x3.inverse()).get(1,2), -2);
    EXPECT_EQ((m_3x3.inverse()).get(2,0), 0);
    EXPECT_EQ((m_3x3.inverse()).get(2,1), 0);
    EXPECT_EQ((m_3x3.inverse()).get(2,2), 1);
}
/*** Konec souboru white_box_tests.cpp ***/
