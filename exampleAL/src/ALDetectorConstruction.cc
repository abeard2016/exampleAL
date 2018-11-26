#include "ALDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
//#include "G4Cons.hh"
//#include "G4Orb.hh"
//#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


ALDetectorConstruction::ALDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

ALDetectorConstruction::~ALDetectorConstruction()
{ }


G4VPhysicalVolume* ALDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 30*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //Aluminium box
  G4double alu_sizeXY = env_sizeXY, alu_sizeZ = env_sizeZ;
  G4Material* alu_mat = nist->FindOrBuildMaterial("G4_Al");
	

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
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
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
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
  
// Scintillator solid

G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4ThreeVector pos1 = G4ThreeVector(1*cm, 1*cm, -1*cm);


  G4double shape1_dxa = .85*alu_sizeXY, shape1_dxb = .85*alu_sizeXY;
  G4double shape1_dya = .85*alu_sizeXY, shape1_dyb = .85*alu_sizeXY;
  G4double shape1_dz  = .85*alu_sizeZ;

G4Trd* solidShape1 =    
    new G4Trd("Shape1",                      //its name
              0.5*shape1_dxa, 0.5*shape1_dxb, 
              0.5*shape1_dya, 0.5*shape1_dyb, 0.5*shape1_dz); //its size
                
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Set Shape1 as scoring volume
  //
  fScoringVolume = logicShape1;

  //
  //always return the physical World
  //
  return physWorld;
}
