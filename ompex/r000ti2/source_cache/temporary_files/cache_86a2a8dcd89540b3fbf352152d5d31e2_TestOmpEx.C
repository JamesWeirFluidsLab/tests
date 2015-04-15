#include <omp.h>
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class Sample1 {
public:
    Sample1(){
        cout << "Sample1:: constructor " << endl;
    }
    ~Sample1(){
        cout << "Sample1:: destructor " << endl;
    }
    Sample1(const Sample1& s){
        cout << "Sample1:: copy constructor " << endl;
    }
    Sample1 &operator=(Sample1& s){
        cout << "Sample1:: assignment operator " << endl;
	return *this;
    }
    
    void dummyFunc() const {
        cout << "Sample:: dummyFunc " << endl;
    }
};


/// main function for test

int main(int argc, char *argv[]){
    Sample1 s1;
    
#pragma omp parallel shared(s1)
    {
//         cout << "Thread #" << omp_get_thread_num() << endl;
        s1.dummyFunc();
    }
    return 0;
}