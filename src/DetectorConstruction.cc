#include "DetectorConstruction.hh"
#include "MySensitiveDetector.hh" // New
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");

    // World Room
    G4Box* solidWorld = new G4Box("World", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // Lead Shield Target
    G4Box* solidShield = new G4Box("Shield", 5*cm, 5*cm, 2.5*cm);
    fLogicShield = new G4LogicalVolume(solidShield, lead, "Shield"); // Assigned to class pointer

    new G4PVPlacement(0, G4ThreeVector(0, 0, 15*cm), fLogicShield, "Shield", logicWorld, false, 0);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    // Create the sensitive detector manager instance
    auto* sdManager = G4SDManager::GetSDMpointer();

    auto* shieldSD = new MySensitiveDetector("ShieldSD");
    sdManager->AddNewDetector(shieldSD);

    // Bind the active tracking sensor directly onto our Lead Shield volume
    SetSensitiveDetector(fLogicShield, shieldSD);
}

