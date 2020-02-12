#include "ALScintillatorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

ALScintillatorSD::ALScintillatorSD(
                            const G4String& name,
                            const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr),
   mParticleCount(0)

{
  collectionName.insert(hitsCollectionName);
}

ALScintillatorSD::~ALScintillatorSD()
{
}

void ALScintillatorSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection
    = new ALScintillatorHitsCollection(SensitiveDetectorName, collectionName[0]);
  G4cout<< fHitsCollection << G4endl;

  // Add this collection in hce
  auto hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );

  // Create hits
  // fNofCells for cells + one more for total sums
  // for (G4int i=0; i<fNofCells+1; i++ ) {
    fHitsCollection->insert(new ALScintillatorHit());
    // }
    //Print fHitsCollection;
}

G4bool ALScintillatorSD::ProcessHits(G4Step* step,
                                     G4TouchableHistory*)
{
  // energy deposit
  auto edep = step->GetTotalEnergyDeposit();

// step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
  }

  auto particle = step->GetTrack()->GetDefinition()->GetParticleName();

  //mParticleCount++; //Count the particles
          //Print Information
         G4cout <<">>> Track "<<step->GetTrack()->GetTrackID()
         << std::setw(10)<<" Total energy: " << edep << std::setw(5)
         << std::setw(10)<<" particle: " <<particle<< std::setw(10)
         << std::endl;

//  if ( edep==0. && stepLength == 0. ) return false;

  //auto touchable = (step->GetPreStepPoint()->GetTouchable());

// Get calorimeter cell id  a.k.a scintillator
//  auto layerNumber = touchable->GetReplicaNumber(1);

  // Get hit accounting data for this cell
/*  auto hit = (*fHitsCollection);//[layerNumber];
  if ( ! hit ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hit "; //<< layerNumber;
    G4Exception("ALScintillatorSD::ProcessHits()",
      "MyCode0004", FatalException, msg);
  }*/
  // Get hit for total accounting
  auto hitTotal
    = (*fHitsCollection)[fHitsCollection->entries()-1];

  // Add values
  //hit->Add(edep, stepLength);
  hitTotal->Add(edep, stepLength);

  return true;
}

void ALScintillatorSD::EndOfEvent(G4HCofThisEvent*)
{
  //if ( verboseLevel>1 ) {
     auto nofHits = fHitsCollection->entries();
     G4cout
       << G4endl
       << "-------->Hits Collection: in this event they are " << nofHits
       << " hits in the tracker chambers: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  //}
}
