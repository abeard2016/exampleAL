#ifndef ALEventAction_h
#define ALEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class ALRunAction;

/// Event action class
///

class ALEventAction : public G4UserEventAction
{
  public:
    ALEventAction(ALRunAction* runAction);
    virtual ~ALEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    ALRunAction* fRunAction;
    G4double     fEdep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
