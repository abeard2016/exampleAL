

#include "ALDetectorConstruction.hh"


#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"
#include "ALScintSD.hh"

ALDetectorConstruction::ALDetectorConstruction()
: G4VUserDetectorConstruction()
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

  G4double alu_sizeXY= 6*cm, alu_sizeZ= 6*cm;	//Aluminum box is 6cm^3
  G4Material* alu_mat = nist->FindOrBuildMaterial("G4_Al");   

  G4Box* solidAlu =
    new G4Box("Aluminum_box",
        0.5*alu_sizeXY, 0.5*alu_sizeXY, 0.5*alu_sizeZ);

  G4LogicalVolume* logicAlu =
    new G4LogicalVolume(solidAlu,			//Its solid
		        alu_mat,					//Its material
			"Aluminum_box");				//Its name

  	new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicAlu,                //its logical volume
                    "Aluminum_box",          //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Envelope
  //  

  G4double env_sizeXY = 5*cm, env_sizeZ= 5*cm;			//Makes Aluminum box .5cm thick
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
    new G4Box("Scintillator_#1",                      	//its name
              0.5*scint_sizeXY, 0.5*scint_sizeXY, 0.5*scint_sizeZ); //its size, each side length is actually that length from origin in both directions, so 0.5 makes it the actually size we want.
                
  G4LogicalVolume* logicScint1 =                         
    new G4LogicalVolume(solidScint1,        		//its solid
                        scint_mat,          		//its material
                        "Scintillator_#1");         //its name
               
    new G4PVPlacement(0,                       		//no rotation
                    pos1,                			//at position 1
                    logicScint1,             		//its logical volume
                    "Scintillator_#1",              //its name
                    logicEnv,                		//its mother  volume
                    false,                   		//no boolean operation
                    0,                       		//copy number
                    checkOverlaps);          		//overlaps checking

// Scintillator #2

  G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -1*cm);

G4Box* solidScint2 =    
    new G4Box("Scintillator_#2",                      	//its name
              0.5*scint_sizeXY, 0.5*scint_sizeXY, 0.5*scint_sizeZ); //its size
                
  G4LogicalVolume* logicScint2 =                         
    new G4LogicalVolume(solidScint2,        		//its solid
                        scint_mat,          		//its material
                        "Scintillator_#2");         //its name
               
    new G4PVPlacement(0,                       		//no rotation
                    pos2,                    		//at position 2
                    logicScint2,             		//its logical volume
                    "Scintillator_#2",              //its name
                    logicEnv,                		//its mother  volume
                    false,                   		//no boolean operation
                    0,                       		//copy number
                    checkOverlaps);          		//overlaps checking

//SiPM #1

G4double siPM_sizeXYZ = 0.5*cm;
G4Material* siPM_mat = nist->FindOrBuildMaterial("G4_Si");
G4ThreeVector pos1_siPM = G4ThreeVector(1.75*cm, 0*cm, 0*cm);

G4Box* solidSiPM1 =    
    new G4Box("SiPM_#1",                      	//its name
              0.5*siPM_sizeXYZ, 0.5*siPM_sizeXYZ, 0.5*siPM_sizeXYZ); //its size, each side length is actually that length from origin in both directions, so 0.5 makes it the actually size we want.
                
  G4LogicalVolume* logicSiPM1 =                         
    new G4LogicalVolume(solidSiPM1,        	//its solid
                        siPM_mat,           //its material
                        "SiPM_#1");         //its name
               
    new G4PVPlacement(0,                    //no rotation
                    pos1_siPM,              //at position 1
                    logicSiPM1,             //its logical volume
                    "SiPM_#1",              //its name
                    logicScint1,            //its mother  volume
                    false,                  //no boolean operation
                    0,                      //copy number
                    checkOverlaps);         //overlaps checking

//SiPM #2

G4ThreeVector pos2_siPM = G4ThreeVector(1.75*cm, 0*cm, 0*cm);

G4Box* solidSiPM2 =    
    new G4Box("SiPM_#2",                      	//its name
              0.5*siPM_sizeXYZ, 0.5*siPM_sizeXYZ, 0.5*siPM_sizeXYZ); //its size, each side length is actually that length from origin in both directions, so 0.5 makes it the actually size we want.
                
  G4LogicalVolume* logicSiPM2 =                         
    new G4LogicalVolume(solidSiPM2,        	//its solid
                        siPM_mat,           //its material
                        "SiPM_#2");         //its name
               
    new G4PVPlacement(0,                    //no rotation
                    pos2_siPM,              //at position 1
                    logicSiPM2,             //its logical volume
                    "SiPM_#2",              //its name
                    logicScint2,            //its mother  volume
                    false,                  //no boolean operation
                    0,                      //copy number
                    checkOverlaps);         //overlaps checking

  //
  //always return the physical World
  //
  return physWorld;
} 

 // Set "Scintillator #1" and "Scintillator #2" as scoring volumes
  //
void ALDetectorConstruction::ConstructSD()
{
	auto siPM_SD_1 
		= new ALScintSD("SiPM_SD_1", "SiPM_HitsCollection_1");
	  G4SDManager::GetSDMpointer()->AddNewDetector(siPM_SD_1);
	  SetSensitiveDetector("SiPM_#1",siPM_SD_1);

	auto siPM_SD_2 
		= new ALScintSD("SiPM_SD_2", "SiPM_HitsCollection_2");
	  G4SDManager::GetSDMpointer()->AddNewDetector(siPM_SD_2);
	  SetSensitiveDetector("SiPM_#2",siPM_SD_2);

}
