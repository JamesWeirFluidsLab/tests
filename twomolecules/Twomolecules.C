#include <stdio.h>
#include <iostream>
#include "fvCFD.H"
#include "mdPoly.H"

#include "gtest/gtest.h"


//class polyMoleculeCloudTest : public testing::Test {
//public:
//    
//    virtual void SetUp(reducedUnits& ru, potential& pot,polyMesh& mesh, Time& time){
//        ru_ = ru;
//        pot_ = pot;
//        mesh_ = mesh;
//        time_ = time;
//    }
//    
//// variables
//    reducedUnits ru_;
//    potential pot_;
//    polyMesh mesh_;
//    Time time_;
//};
TEST(TestTwoMolecules, checkPos){
    ASSERT_DOUBLE_EQ(0.0,0.002);
}

int main(int argc, char *argv[]){
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

    while(runTime.loop())
    {
        molecules.evolve();
        runTime.write();
    }
    
    IDLList<Foam::polyMolecule>::iterator mol(molecules.begin());
    
    for (mol = molecules.begin(); mol != molecules.end(); ++mol){
        int molsize = mol().siteForces().size();
        int m = 0;
        while(m<molsize){
            double tempx = mol().siteForces()[m].x();
            m++;
        }
    }
    
    
    return RUN_ALL_TESTS();
}