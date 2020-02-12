#include "ALEventAction.hh"
#include "ALRunAction.hh"
#include "G4SDManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "ALAnalysis.hh"
#include "G4THitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4HCofThisEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALEventAction::ALEventAction(ALRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  fScintHCID(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALEventAction::~ALEventAction()
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Trying to print hitscollection stuff to see if it actually gets filled but we haven't been able to printed.
ALScintillatorHitsCollection* 
ALEventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
auto hitsCollection
	= static_cast<ALScintillatorHitsCollection*>(
		event->GetHCofThisEvent()->GetHC(hcID));
return hitsCollection;
G4cout << "------------------------------------------------------------------------------------------------------" << hitsCollection << G4endl;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALEventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALEventAction::EndOfEventAction(const G4Event* event)
{
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);

  fScintHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("SSD1HitsCollection");

 // Get hits collections
  auto scintHC = GetHitsCollection(fScintHCID, event);
 // Get hit with total values
  auto scintHit = (*scintHC)[scintHC->entries()-1];

  // Fill histograms, ntuple
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
 
  // fill histograms
  analysisManager->FillH1(0, scintHit->GetEdep());
  analysisManager->FillH1(1, scintHit->GetTrackLength());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
