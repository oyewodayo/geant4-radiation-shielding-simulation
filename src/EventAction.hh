#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction {
public:
    EventAction() = default;
    ~EventAction() override = default;
    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;
    void AddEnergy(G4double edep) { fTotalEnergyDeposit += edep; }
private:
    G4double fTotalEnergyDeposit = 0.0;
};
#endif

