#include "MySensitiveDetector.hh"
#include "G4RunManager.hh"
#include "EventAction.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {}

G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    // Get the energy deposited during this micro-step
    G4double edep = step->GetTotalEnergyDeposit();

    if (edep > 0.) {
        // Safely locate our EventAction manager and add the energy
        auto* eventAction = (EventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
        if (eventAction) {
            eventAction->AddEnergy(edep);
        }
    }
    return true;
}

