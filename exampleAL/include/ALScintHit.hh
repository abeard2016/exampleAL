#ifndef ALScintHit_h
#define ALScintHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

/// Calorimeter hit class
///
/// It defines data members to store the the energy deposit and track lengths
/// of charged particles in a selected volume:
/// - fEdep, fTrackLength

class ALScintHit : public G4VHit	//G4Hit is base class
{
  public:
	ALScintHit();
    ALScintHit(const ALScintHit&);	//Hit collection ID
    virtual ~ALScintHit();

    // operators
    const ALScintHit& operator=(const ALScintHit&);		//What are these operators for?
    G4int operator==(const ALScintHit&) const;			//They're defined below

    inline void* operator new(size_t);
    inline void  operator delete(void*);

	
    // methods from base class				//I don't think we need these currently
    virtual void Draw() {}					//But they're from base class so I leave them
    virtual void Print();
	

    // methods to handle data
    void Add(G4double de, G4double dl);		//For the total values in ALScintSD.cc

    // get methods
    G4double GetEdep() const;
    G4double GetTrackLength() const;
      
  private:
    G4double fEdep;        ///< Energy deposit in the sensitive volume
    G4double fTrackLength; ///< Track length in the  sensitive volume
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using ALScintHitsCollection = G4THitsCollection<ALScintHit>;

extern G4ThreadLocal G4Allocator<ALScintHit>* ALScintHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* ALScintHit::operator new(size_t)
{
  if (!ALScintHitAllocator) {
    ALScintHitAllocator = new G4Allocator<ALScintHit>;
  }
  void *hit;
  hit = (void *) ALScintHitAllocator->MallocSingle();
  return hit;
}

inline void ALScintHit::operator delete(void *hit)
{
  if (!ALScintHitAllocator) {
    ALScintHitAllocator = new G4Allocator<ALScintHit>;
  }
  ALScintHitAllocator->FreeSingle((ALScintHit*) hit);
}

inline void ALScintHit::Add(G4double de, G4double dl) {
  fEdep += de; 
  fTrackLength += dl;
}

inline G4double ALScintHit::GetEdep() const { 
  return fEdep; 
}

inline G4double ALScintHit::GetTrackLength() const { 
  return fTrackLength; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
