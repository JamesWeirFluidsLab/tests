#include <stdio.h>
#include <iostream>
#include "vectorize.H"
#include "vector.H"
#include "gtest/gtest.h"

void TestSize(void){
  Foam::vectorize v1;
  int size = v1.vectorSize();
  if(size == 4)
      std::cout << "TestSize -> Success" << std::endl;
}

void TestArgument(Foam::vectorize& arg1){
    if(arg1.vectorSize())
        std::cout << "TestArgument -> Success" << std::endl; 
}

void TestParameterised(){
    double Arr[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize v1(Arr[0],Arr[1],Arr[2],Arr[3]);
    std::cout << "TestParameterised -> Success" << std::endl;
}

void TestLoadUnalignedData(){
   double Arr[4] = {0.1,2.0,0.009,0.45009};
   Foam::vectorize v1(Arr);
   std::cout << "TestLoadUnalignedData -> Success " << std::endl;
}

void TestAccess(){
    double Arr[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize v1(Arr);
    const Foam::vectorize v2 = v1;
    std::cout << "TestAccess -> Success " << std::endl;
}

void TestSubstraction(){
   double Arr[4] = {0.1,2.0,0.009,0.45009};
   Foam::vectorize v1(Arr);
   Foam::vectorize v2(Arr);
   Foam::vectorize sub = v1 - v2;
   sub.store(Arr);
   if(Arr[1] == 0.0)
       std::cout << "TestSubstraction -> Success"<< std::endl;
   else
       std::cout << "TestSubstraction -> Failed"<< std::endl;
}

void TestComparison(){
    double Arr[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize v1(Arr);
    Foam::vectorize v2(Arr);
    Foam::vectorize cp = v1 == v2;
    std::cout << "TestComparison -> Success" << std::endl;
}

void TestFMA(){
    double Arr1[4] = {0.1,2.0,0.009,0.45009};
    Foam::vectorize val,val1(Arr1),val2(Arr1),val3(Arr1);
    Foam::vectorize ev = val(val1,val2,val3);
    ev.store(Arr1);
    if(Arr1[1] == 6.00)
        printf("TestFMA -> Success\n");
    else
        printf("TestFMA -> Failed\n");
}

void TestSetFoamVector(){
    Foam::vector v1(0.1,2.0,0.009);
    Foam::vectorize vec(v1);
    Foam::vector copied;
    vec.storeVec(copied);
}
int main(int argc, char *argv[]){
    TestSize();
    //declare vectorize type
    Foam::vectorize v1;
    TestArgument(v1);
    TestParameterised();
    TestLoadUnalignedData();
    TestAccess();
    TestSubstraction();
    TestComparison();
    TestFMA();
    TestSetFoamVector();
    return 0;
}