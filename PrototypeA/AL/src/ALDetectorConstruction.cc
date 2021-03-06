#include "ALDetectorConstruction.hh"
#include "ALScintillatorSD.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
//#include "G4Cons.hh"
//#include "G4Orb.hh"
//#include "G4Sphere.hh"
//#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

ALDetectorConstruction::ALDetectorConstruction()
: G4VUserDetectorConstruction()
  //fScoringVolume(0)
{ }

ALDetectorConstruction::~ALDetectorConstruction()
{ }


G4VPhysicalVolume* ALDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

   //
  // World
  //
  G4double world_sizeXY = 10*cm;
  G4double world_sizeZ  = 10*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking




  //Aluminium box
  G4double alu_sizeXY = 6*cm, alu_sizeZ = 6*cm;
  G4Material* alu_mat = nist->FindOrBuildMaterial("G4_Al");

    //

  G4Box* solidAlu =
    new G4Box("Aluminum box",
        0.5*alu_sizeXY, 0.5*alu_sizeXY, 0.5*alu_sizeZ);

  G4LogicalVolume* logicAlu =
    new G4LogicalVolume(solidAlu,
		        alu_mat,
			"Aluminum box");
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicAlu,                //its logical volume
                    "Aluminum box",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  // Envelope parameters
  //
  G4double env_sizeXY = 5*cm, env_sizeZ = 5*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");





  //
  // Envelope
  //
  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicAlu,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



// Scintillator solid
  G4double scint_sizeXY = 3*cm, scint_sizeZ = 1*cm;

G4Material* scint_mat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, 1*cm);

  // G4double shape1_dxa = .85*alu_sizeXY, shape1_dxb = .85*alu_sizeXY;
  //G4double shape1_dya = .85*alu_sizeXY, shape1_dyb = .85*alu_sizeXY;
  //G4double shape1_dz  = .85*alu_sizeZ;

G4Box* solidScint1 =
    new G4Box("Scintillator_#1",                      //its name
              0.5*scint_sizeXY, 0.5*scint_sizeXY,
              0.5*scint_sizeZ); //its size

  G4LogicalVolume* logicScint1 =
    new G4LogicalVolume(solidScint1,         //its solid
                        scint_mat,          //its material
                        "Scintillator_#1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicScint1,             //its logical volume
                    "Scintillator_#1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //Scint 2
   G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -1*cm);

   G4Box* solidScint2 =
    new G4Box("Scintillator_#2",                      //its name
              0.5*scint_sizeXY, 0.5*scint_sizeXY,
              0.5*scint_sizeZ); //its size

  G4LogicalVolume* logicScint2 =
    new G4LogicalVolume(solidScint2,         //its solid
                        scint_mat,          //its material
                        "Scintillator_#2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicScint2,             //its logical volume
                    "Scintillator_#2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

/*  //SiPM
  G4double SiPM_sizeXYZ = 0.5*cm;

G4Material* SiPM_mat = nist->FindOrBuildMaterial("G4_Si");

 G4ThreeVector pos1_SiPM = G4ThreeVector(1.75*cm, 0*cm, 0*cm);
 // SiPM 1
 G4Box* solidSiPM1 =
    new G4Box("SiPM_#1",                      //its name
              0.5*SiPM_sizeXYZ, 0.5*SiPM_sizeXYZ,
              0.5*SiPM_sizeXYZ); //its size

  G4LogicalVolume* logicSiPM1 =
    new G4LogicalVolume(solidSiPM1,         //its solid
                        SiPM_mat,          //its material
                        "SiPM_#1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos1_SiPM,                    //at position
                    logicSiPM1,             //its logical volume
                    "SiPM_#1",                //its name
                    logicScint1,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


   G4ThreeVector pos2_SiPM = G4ThreeVector(1.75*cm, 0*cm, 0*cm);
 // SiPM 2
 G4Box* solidSiPM2 =
    new G4Box("SiPM_#2",                      //its name
              0.5*SiPM_sizeXYZ, 0.5*SiPM_sizeXYZ,
              0.5*SiPM_sizeXYZ); //its size

  G4LogicalVolume* logicSiPM2 =
    new G4LogicalVolume(solidSiPM2,         //its solid
                        SiPM_mat,          //its material
                        "SiPM_#2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos1_SiPM,                    //at position
                    logicSiPM2,             //its logical volume
                    "SiPM_#2",                //its name
                    logicScint2,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

                    */
  // Set Shape1 as scoring volume
  //
  // fScoringVolume = logicScint1;


  //
  //always return the physical World
  //
  return physWorld;
}

void ALDetectorConstruction::ConstructSD()
{
  //Sensitive Detector

  auto SSD1
  = new ALScintillatorSD("SSD1", "SSD1HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(SSD1);
  SetSensitiveDetector("Scintillator_#1", SSD1);

  auto SSD2
  = new ALScintillatorSD("SSD2", "SSD2HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(SSD2);
  SetSensitiveDetector("Scintillator_#2", SSD2);

/*  auto SiPMSD_1
    = new ALScintillatorSD("SiPMSD_1", "SiPM_1HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(SiPMSD_1);
  SetSensitiveDetector("SiPM_#1",SiPMSD_1);

   auto SiPMSD_2
    = new ALScintillatorSD("SiPMSD_2", "SiPM_2HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(SiPMSD_2);
  SetSensitiveDetector("SiPM_#2",SiPMSD_1);
*/


}
