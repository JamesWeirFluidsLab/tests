#include <stdio.h>
#include <iostream>
#include "fvCFD.H"
#include "mdPoly.H"

#include "gtest/gtest.h"


//class polyMoleculeCloudTest : public testing::Test {
//public:
//    virtual void SetUp(){
//    }
//// variables
//    Foam::Time* time_;
//    Foam::polyMoleculeCloud* molecules_;
//
//    void setPolyMoleculeData(Foam::Time& time,Foam::polyMoleculeCloud molecules){
//        time_ = &time;
//        molecules_ = &molecules;
//    }
//};
//
//TEST_F(polyMoleculeCloudTest, checkPos){
//    Foam::argList args(argc,argv);
//}

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
//    polyMoleculeCloudTest::setPolyMoleculeData(runTime,molecules);

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