#include <stdio.h>
#include <iostream>
#include "vectorize.H"
#include "vector.H"
#include "gtest/gtest.h"

TEST(TestSIMD,TestSize){
  Foam::vectorize v1;
  int size = v1.vectorSize();
  EXPECT_EQ(4,v1.vectorSize());
}

TEST(TestSIMD,TestParameterised){
    double Arr[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize v1(Arr[0],Arr[1],Arr[2],Arr[3]);
    SUCCEED();
}

TEST(TestSIMD,TestLoadUnalignedData){
   double Arr[4] = {0.1,2.0,0.009,0.45009};
   Foam::vectorize v1(Arr);
   SUCCEED();
}

TEST(TestSIMD,TestAccess){
    double Arr[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize v1(Arr);
    const Foam::vectorize v2 = v1;
    SUCCEED();
}

TEST(TestSIMD,TestSubstraction){
   double Arr[4] = {0.1,2.0,0.009,0.45009};
   Foam::vectorize v1(Arr);
   Foam::vectorize v2(Arr);
   Foam::vectorize sub = v1 - v2;
   sub.store(Arr);
   EXPECT_EQ(0.0,Arr[0]);
}

TEST(TestSIMD,TestComparison){
    double Arr[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize v1(Arr);
    Foam::vectorize v2(Arr);
    Foam::vectorize cp = v1 == v2;
    SUCCEED();
}

TEST(TestSIMD,TestFMA){
    double Arr1[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize val,val1(Arr1),val2(Arr1),val3(Arr1);
    Foam::vectorize ev = val(val1,val2,val3);
    ev.store(Arr1);
    ASSERT_EQ(6.0,Arr1[1]);
}

TEST(TestSIMD,TestAssignment){
    Foam::vectorize v1(0.1,0.2,0.3,0.4);
    Foam::vectorize v2 = v1;
    SUCCEED();
}
/*
void TestSetFoamVector(){
    Foam::vector v1(0.1,2.0,0.009);
    Foam::vectorize vec(v1);
    Foam::vector copied;
    vec.storeVec(copied);
}*/

int main(int argc, char *argv[]){
    //declare vectorize type
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}