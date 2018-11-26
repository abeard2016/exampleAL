#include "ALActionInitialization.hh"
#include "ALPrimaryGeneratorAction.hh"
#include "ALRunAction.hh"
#include "ALEventAction.hh"
#include "ALSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALActionInitialization::ALActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ALActionInitialization::~ALActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALActionInitialization::BuildForMaster() const
{
  ALRunAction* runAction = new ALRunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ALActionInitialization::Build() const
{
  SetUserAction(new ALPrimaryGeneratorAction);

  ALRunAction* runAction = new ALRunAction;
  SetUserAction(runAction);
  
  ALEventAction* eventAction = new ALEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new ALSteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
