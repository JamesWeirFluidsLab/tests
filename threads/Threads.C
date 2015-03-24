#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include "gtest/gtest.h"
#include "vector.H"
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

TEST(TestThreads,ThreadSum){
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
    
    double sumv3 = 0;
    double sumv3test = 0;
    
    for(int i = 0;i<SIZE;++i)
        sumv3 += v3[i];
#pragma omp parallel shared(v3) reduction(+:sumv3test)
{
#pragma omp master
    sumv3test = 0;
#pragma omp barrier
    for(int i = omp_get_thread_num(); i<SIZE; i+=omp_get_num_threads())
      sumv3test = sumv3test + v3[i];
}      

    EXPECT_NEAR(sumv3,sumv3test,1.0);
}

TEST(TestThreads,objectTest){
    Foam::List<Foam::vector> vecList(100000);
    for(int i = 0; i < 100000; ++i)
    {
        vecList[i].x() = 1.0;
	vecList[i].y() = 1.0;
	vecList[i].z() = 1.0;
    }
    
#pragma omp parallel for private(vecList)
    for(int i = 0;i<100000;i++)
    {
        vecList[i].x() = 1.0 + 0.09963;
	vecList[i].y() = 1.0 + 0.09963;
	vecList[i].z() = 1.0 + 0.09963;
    }


    double check = 1.0 + 0.09963;
    ASSERT_EQ(check,vecList[10].x());
    ASSERT_EQ(check,vecList[10].y());
    ASSERT_EQ(check,vecList[10].z());
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}