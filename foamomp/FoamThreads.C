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
    List<vector> vecList(100000);
    
    for(int i = 0; i< vecList.size(); ++i)
    {
        vecList[i] = vector(0.22,0.033,0.345);
    }

#pragma omp parallel for default(none) private(vecList)   
    for(int i = 0; i<vecList.size(); ++i)
    {
        vecList[i] = vecList[i] * 0.22;
    }
}


TEST(TestFoamThreads,foamMallocArray){
    vector* vecList;
    
    vecList = (vector*) malloc(sizeof(vector)*100000);
    
    for(int i = 0; i< 100000; ++i)
    {
        vecList[i] = vector(0.22,0.033,0.345);
    }
    
#pragma omp parallel for default(none) private(vecList)
    for(int i = 0; i<100000; ++i)
    {
        vecList[i] = vecList[i] * 0.22;
    }
}

TEST(TestFoamThreads,foamPolyMolecule){
    List<polyMolecule*> polyList(100000);
    
#pragma omp parallel for default(none) private(polyList)
    for(int i = 0; i<100000;i++){
        polyMolecule* temp = polyList[i];
    }
}
int main(int argc, char *argv[]){
   /* List<polyMolecule*> polyList(100000);
    
#pragma omp parallel for default(none) private(polyList)
    for(int i = 0; i<100000;i++){
        polyMolecule* temp = polyList[i];
    }
    return 0;
  */
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
    
