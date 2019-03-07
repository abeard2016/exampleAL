

#include "ALDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
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

   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXYZ = 10*cm;  //World is 10cm^3
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
        0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume. World Volumes are ONLY ones without mother volumes.
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  
 
  //  Aluminum Box

  G4double alu_sizeXY= 6*cm, alu_sizeZ= 6*cm;	//Aluminum box is 5cm-4cm-4cm
  G4Material* alu_mat = nist->FindOrBuildMaterial("G4_Al");   

  G4Box* solidAlu =
    new G4Box("Aluminum box",
        0.5*alu_sizeXY, 0.5*alu_sizeXY, 0.5*alu_sizeZ);

  G4LogicalVolume* logicAlu =
    new G4LogicalVolume(solidAlu,			//Its solid
		        alu_mat,					//Its material
			"Aluminum box");				//Its name

  	new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicAlu,                //its logical volume
                    "Aluminum box",          //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Envelope
  //  

  G4double env_sizeXY = 5*cm, env_sizeZ= 5*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidEnv =    
    new G4Box("Envelope",                   			//its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicAlu ,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// Scintillator #1

  G4double scint_sizeXY = 3*cm, scint_sizeZ = 1*cm;
  G4Material* scint_mat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, 1*cm);

G4Box* solidScint1 =    
    new G4Box("Scintillator #1",                      	//its name
              0.5*scint_sizeXY, 0.5*scint_sizeXY, 0.5*scint_sizeZ); //its size, each side length is actually that length from origin in both directions, so 0.5 makes it the actually size we want.
                
  G4LogicalVolume* logicScint1 =                         
    new G4LogicalVolume(solidScint1,        		//its solid
                        scint_mat,          		//its material
                        "Scintillator #1");         //its name
               
    new G4PVPlacement(0,                       		//no rotation
                    pos1,                			//at position 1
                    logicScint1,             		//its logical volume
                    "Scintillator #1",              //its name
                    logicEnv,                		//its mother  volume
                    false,                   		//no boolean operation
                    0,                       		//copy number
                    checkOverlaps);          		//overlaps checking

// Scintillator #2

  G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -1*cm);

G4Box* solidScint2 =    
    new G4Box("Scintillator #2",                      	//its name
              0.5*scint_sizeXY, 0.5*scint_sizeXY, 0.5*scint_sizeZ); //its size
                
  G4LogicalVolume* logicScint2 =                         
    new G4LogicalVolume(solidScint2,        		//its solid
                        scint_mat,          		//its material
                        "Scintillator #2");         //its name
               
    new G4PVPlacement(0,                       		//no rotation
                    pos2,                    		//at position 2
                    logicScint2,             		//its logical volume
                    "Scintillator #2",              //its name
                    logicEnv,                		//its mother  volume
                    false,                   		//no boolean operation
                    0,                       		//copy number
                    checkOverlaps);          		//overlaps checking

  // Set "Scintillator #1" and "Scintillator #2" as scoring volumes
  //
  fScoringVolume = logicScint1;

  //
  //always return the physical World
  //
  return physWorld;
}
