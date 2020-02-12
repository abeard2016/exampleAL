#ifndef ALScintillatorHit_h
#define ALScintillatorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

class ALScintillatorHit : public G4VHit
{
  public:
    ALScintillatorHit();
    ALScintillatorHit(const ALScintillatorHit&);
    virtual ~ALScintillatorHit();

    // operators                                                                
    const ALScintillatorHit& operator=(const ALScintillatorHit&);
    G4int operator==(const ALScintillatorHit&) const;
  
    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class                                                  
    virtual void Draw() {}
    virtual void Print();

    // methods to handle data                                                   
    void Add(G4double de, G4double dl);
  
    // get methods                                                              
    G4double GetEdep() const;
    G4double GetTrackLength() const;

  private:
    G4double fEdep;        ///< Energy deposit in the sensitive volume          
    G4double fTrackLength; ///< Track length in the  sensitive volume           
};

                                                                            

using ALScintillatorHitsCollection = G4THitsCollection<ALScintillatorHit>;

extern G4ThreadLocal G4Allocator<ALScintillatorHit>* ALScintillatorHitAllocator;


inline void* ALScintillatorHit::operator new(size_t)
{
  if (!ALScintillatorHitAllocator) {
    ALScintillatorHitAllocator = new G4Allocator<ALScintillatorHit>;
  }
  void *hit;
  hit = (void *) ALScintillatorHitAllocator->MallocSingle();
  return hit;
}

inline void ALScintillatorHit::operator delete(void *hit)
{
  if (!ALScintillatorHitAllocator) {
    ALScintillatorHitAllocator = new G4Allocator<ALScintillatorHit>;
  }
  ALScintillatorHitAllocator->FreeSingle((ALScintillatorHit*) hit);
}

inline void ALScintillatorHit::Add(G4double de, G4double dl) {
  fEdep += de;
  fTrackLength += dl;
}

inline G4double ALScintillatorHit::GetEdep() const {
  return fEdep;
}

inline G4double ALScintillatorHit::GetTrackLength() const {
  return fTrackLength;
}


#endif
