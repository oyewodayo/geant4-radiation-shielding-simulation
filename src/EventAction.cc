#include "EventAction.hh"
#include "G4AnalysisManager.hh"

void EventAction::BeginOfEventAction(const G4Event*) {
    fTotalEnergyDeposit = 0.0; // Reset total accumulator for the new particle
}

void EventAction::EndOfEventAction(const G4Event* evt) {
    auto* analysisManager = G4AnalysisManager::Instance();

    // Fill columns row by row
    analysisManager->FillNtupleDColumn(0, evt->GetEventID());
    analysisManager->FillNtupleDColumn(1, fTotalEnergyDeposit);
    analysisManager->AddNtupleRow(); // Complete row insertion
}

