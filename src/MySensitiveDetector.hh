#ifndef MySensitiveDetector_h
#define MySensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"

class MySensitiveDetector : public G4VSensitiveDetector {
public:
    MySensitiveDetector(G4String name);
    ~MySensitiveDetector() override = default;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
};
#endif

