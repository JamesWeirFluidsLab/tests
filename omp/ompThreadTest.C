#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include "gtest/gtest.h"
#include "ompThreads.H"

using namespace Foam;

TEST(TestOmpThreads,constructor){
    ompThreads omp;
}
int main(int argc, char *argv[]){
    //declare vectorize type
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}