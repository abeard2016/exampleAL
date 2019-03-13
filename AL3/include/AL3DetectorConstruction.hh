//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// Created 3/11/2019 by Ashley Beard and Loriza Hasa, based off of Geant4 ex.B2a
//
/// \file AL3DetectorConstruction.hh
/// \brief Definition of the AL3DetectorConstruction class

#ifndef AL3DetectorConstruction_h
#define AL3DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

/// Detector construction class to define materials, geometry.

class AL3DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    AL3DetectorConstruction();
    virtual ~AL3DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSD();

    // Set methods
    void SetCheckOverlaps(G4bool);

  private:
  
    // data members
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
