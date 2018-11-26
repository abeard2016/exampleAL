#ifndef ALSteppingAction_h
#define ALSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class ALEventAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class ALSteppingAction : public G4UserSteppingAction
{
  public:
    ALSteppingAction(ALEventAction* eventAction);
    virtual ~ALSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    ALEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
