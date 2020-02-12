#ifndef ALEventAction_h
#define ALEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "ALScintillatorHit.hh"
#include "ALScintillatorSD.hh"
#include "G4THitsCollection.hh"



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
	//const G4VHitsCollection * 	GetHitsCollection (G4int hcID, G4int event=0);
	//const G4VHitsCollection	*   entries();

							
  private:
  ALScintillatorHitsCollection* GetHitsCollection (G4int hcID, const G4Event* event) const;
    ALRunAction* fRunAction;
    G4double     fEdep;
	G4int     fScintHCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
