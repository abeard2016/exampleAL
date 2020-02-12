#ifndef ALActionInitialization_h
#define ALActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class ALActionInitialization : public G4VUserActionInitialization
{
  public:
    ALActionInitialization();
    virtual ~ALActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
