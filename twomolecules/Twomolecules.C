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
    
    std::vector<double> expectPositions(24);
    expectPositions[0] = 13.87527764;
    expectPositions[1] = 7.86002214;
    expectPositions[2] = 7.50948467;
    expectPositions[3] = 14.08388005;
    expectPositions[4] = 7.42784505;
    expectPositions[5] = 7.51958947;
    expectPositions[6] = 13.87527764;
    expectPositions[7] = 7.59702001;
    expectPositions[8] = 7.66092649;
    expectPositions[9] = 13.90281172;
    expectPositions[10] = 7.60939936;
    expectPositions[11] = 7.62229790;
    expectPositions[12] = 12.67240769;
    expectPositions[13] = 7.40345187;
    expectPositions[14] = 7.62258231;
    expectPositions[15] = 12.59998852;
    expectPositions[16] = 7.84172644;
    expectPositions[17] = 7.44074453;
    expectPositions[18] = 12.45678454;
    expectPositions[19] = 7.61246793;
    expectPositions[20] = 7.57872243;
    expectPositions[21] = 12.50412739;
    expectPositions[22] = 7.61513867;
    expectPositions[23] = 7.56630471;
    
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
    
    int particles = 0;
    for (mol = molecules.begin(); mol != molecules.end(); ++mol){
        int molsize = mol().sitePositions().size();
        int m = 0;
        while(m<molsize){
            EXPECT_NEAR(expectPositions[particles],mol().sitePositions()[m].x(),2.0);
	    EXPECT_NEAR(expectPositions[particles+1],mol().sitePositions()[m].y(),2.0);
	    EXPECT_NEAR(expectPositions[particles+2],mol().sitePositions()[m].z(),2.0);
            m++;
        }
        particles+=3;
    }
    
    
    return RUN_ALL_TESTS();
}