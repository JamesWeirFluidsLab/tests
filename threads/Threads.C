#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include "gtest/gtest.h"
#ifndef SIZE
#define SIZE 15583
#endif

TEST(TestThreads,VectorAddSchedule){
    double v1[SIZE],v2[SIZE],v3	[SIZE],v4[SIZE];
    // initialise vectors
    
    for(int i = 0; i<SIZE; ++i)
    {
        v1[i] = v2[i] = 0.04782 * ((i+1)/0.365);
	v3[i] = 0.0;
    }
    
    for(int i = 0; i<SIZE;++i)
    {
        v3[i] = v1[i] + v2[i];
    }

#pragma omp parallel shared(v1,v2,v4)
{
#pragma omp for schedule(static,1)
    for(int i = 0; i<SIZE; ++i)
    {
        v4[i] = v1[i] + v2[i];
    }
}    
    for(int j=0;j<SIZE;j++)
      ASSERT_EQ(v3[j],v4[j]);
    
}

TEST(TestThreads,VectorAdd){
    double v1[SIZE],v2[SIZE],v3	[SIZE],v4[SIZE];
    // initialise vectors
    
    for(int i = 0; i<SIZE; ++i)
    {
        v1[i] = v2[i] = 0.04782 * ((i+1)/0.365);
	v3[i] = 0.0;
    }
    
    for(int i = 0; i<SIZE;++i)
    {
        v3[i] = v1[i] + v2[i];
    }


    
#pragma omp parallel shared(v1,v2,v4)
{
    for(int i = omp_get_thread_num(); i<SIZE; i+=omp_get_num_threads())
    {
        v4[i] = v1[i] + v2[i];
    }
}    
    
    for(int j=0;j<SIZE;j++)
      ASSERT_EQ(v3[j],v4[j]);

}    

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}