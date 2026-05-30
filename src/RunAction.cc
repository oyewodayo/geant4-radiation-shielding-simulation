#include "RunAction.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction() : G4UserRunAction() {
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetDefaultFileType("csv"); // Force CSV output type

    // Create an Ntuple (data table structure)
    analysisManager->CreateNtuple("ShieldData", "Simulation Output Data");
    analysisManager->CreateNtupleDColumn("EventID");       // Column 0
    analysisManager->CreateNtupleDColumn("EnergyDeposit"); // Column 1 (MeV)
    analysisManager->FinishNtuple();
}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("simulation_output.csv"); // File name
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

