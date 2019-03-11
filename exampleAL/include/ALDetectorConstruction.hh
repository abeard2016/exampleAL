#ifndef ALDetectorConstruction_h
#define ALDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
//ALScintSD∗ siPM_SD_1 ;
//ALScintSD∗ siPM_SD_2 ;

/// Detector construction class to define materials and geometry.

class ALDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ALDetectorConstruction();
	virtual void ConstructSD();
    virtual ~ALDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
   /* G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume; */


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
