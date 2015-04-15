#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include "gtest/gtest.h"
#include "fvCFD.H"
#include "mdPoly.H"

using namespace Foam;
TEST(TestFoamThreads,foamVector){
    vector v1(0.023,0.0879,0.54);
    EXPECT_EQ(0.023,v1.x());
}

TEST(TestFoamThreads,foamVectorArray){
    List<vector> vecList;//(100000);
    vecList.setSize(100000);
    
    for(int i = 0; i< vecList.size(); ++i)
    {
        vecList[i] = vector(0.22,0.033,0.345);
    }

    vector* list0 = &vecList[0];
#pragma omp parallel for default(none) private(list0)   
    for(int i = 0; i<100000; ++i)
    {
        list0[i] = list0[i] * 0.22;
    }
    
    vector& vec = vecList[0];
    Info << vec << endl;
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
    
