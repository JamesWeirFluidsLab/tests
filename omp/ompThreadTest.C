#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include "gtest/gtest.h"
#include "fvCFD.H"
#include "mdPoly.H"
#include "ompThreads.H"

using namespace Foam;

TEST(TestOmpThreads,constructor){
    ompThreads omp;
}

int main(int argc, char *argv[]){
    //declare vectorize type
    ::testing::InitGoogleTest(&argc,argv);
    
    Foam::argList args(argc,argv);
    Foam::Time runTime(Foam::Time::controlDictName, args);
    Foam::fvMesh mesh
    (
     Foam::IOobject
     (
          Foam::fvMesh::defaultRegion,
          runTime.timeName(),
          runTime,
          Foam::IOobject::MUST_READ
     )
    );
    reducedUnits redUnits(runTime, mesh);
    potential pot(mesh, redUnits);
    polyMoleculeCloud molecules(runTime,mesh,pot,redUnits);
    ompThreads ompt(&molecules);
    ompt.readPolyMolecules();
    return RUN_ALL_TESTS();
}