

## GEANT4 RADIATION SHIELDING SIMULATION SYSTEM
------------------------------
## 🗺️ Part 1: System Overview & Architecture## What the Code Does (High-Level)
This system is an enterprise-grade Monte Carlo Particle Transport Simulation Application [link.aps.org]. Written in Object-Oriented C++ using the CERN Geant4 Toolkit, the software simulates a miniature radiation testing laboratory.
The application generates a highly focused beam of subatomic particles, fires them through an air-filled testing chamber, collides them with a block of high-density lead shielding, tracks every individual atomic interaction, and writes the resulting energy absorption metrics to spreadsheet files (.csv) using multi-threaded execution pipelines.

       [ MONTE CARLO PARTICLE GENERATOR ]

                       |
                       | (100 MeV Electron or Proton Beam)
                       v
    ======================================= [WORLD VOLUME: AIR] ===

    |                                                             |
    |                                                             |
    |                  [ SENSITIVE DETECTOR TARGET: LEAD ]        |
    |                         +-----------------+                 |
    |                         |  Ionization /   |                 |
    |  ======================>|  Bremsstrahlung |===============> |
    |   (Primary Track)       |  Collisions     | (Escaping Flux) |
    |                         +-----------------+                 |
    |                                  |                          |
    |                                  v                          |
    |                      [ G4ANALYSIS ENGINE PIPELINE ]         |
    |                                  |                          |
    |                                  +---> simulation_output_t0.csv
    ===============================================================

## The 3 Core Object-Oriented Pillars
Geant4 uses a modular inheritance model. To achieve this workflow, our codebase inherits from and overrides three mandatory structural interfaces:

   1. G4VUserDetectorConstruction: Shapes the physical landscape. It instructs the computer how to generate 3D solids, assign materials from the NIST atomic database, place them at coordinates in a 3D coordinate space, and mount a virtual sensor grid onto specific sub-volumes.
   2. G4VUserPrimaryGeneratorAction: Serves as the particle accelerator beamline. It controls an internal random-number generator engine to launch specific particles (e-, proton) at targeted kinetic energies, positions, and trajectories.
   3. G4VUserActionInitialization: The management bridge. It registers user tracking code (like RunAction and EventAction) to allow the application to hook into the system clock and write data tables.

------------------------------
## 🛠️ Part 2: Technical Directory Setup & Deployment
Follow these precise steps to manually verify or spin up a new configuration workspace:
## 1. Initialize the Target Workspace Directory

cd ~
mkdir -p geant4_shield_project/src
cd geant4_shield_project

## 2. File Verification & Manifest
Ensure the following exact folder structure is populated with your source code files:

geant4_shield_project/
├── CMakeLists.txt
├── main.cc
├── init_vis.mac
└── src/
    ├── DetectorConstruction.hh
    ├── DetectorConstruction.cc
    ├── PrimaryGeneratorAction.hh
    ├── PrimaryGeneratorAction.cc
    ├── RunAction.hh
    ├── RunAction.cc
    ├── EventAction.hh
    └── EventAction.cc

## 3. Compilation Framework Setup
Execute this sequence to clear dependencies, target the installation tree, and trigger compilation:

# Sourcing environmental production binaries
source ~/geant4/geant4-v11.4.0-install/bin/geant4.sh
# Entering independent build space
mkdir -p build && cd build
# Map dependencies and compile utilizing all processing cores
cmake ..
make -j$(nproc)
# Sync visual layout macros into active folder
cp ../init_vis.mac .

------------------------------
## 🔬 Part 3: Deep-Dive Simulation Experiments & Analysis## 🧪 Experiment A: 100 MeV Light Lepton (Electron) Collision## How to Execute
Launch the Graphical Engine and fire the default electron beam setup:

./ShieldSim# Inside the GUI Session Bar at the bottom, run:
/run/beamOn 20

## Visual Phenomenon Observed
A massive, chaotic explosion of lines erupts from the lead block:

* A few red lines (electrons) bend sharply inside the target.
* A dense, radiating spray of green lines (neutral gamma-ray photons) blasts outward in all directions, passing cleanly through the boundaries of the world box.

## The Underlying Physics Explained
This showcase demonstrates Bremsstrahlung (Braking Radiation) and Electromagnetic Cascades [CDS].
An electron is incredibly light. When a 100 MeV electron penetrates the lead block, it encounters the intense electric fields of the heavy lead nuclei (Atomic Number $Z=82$). As the electron is sharply deflected and decelerated by this field, it throws off its kinetic energy in the form of high-energy photon packets (the green tracks).
These photons then undergo Pair Production and Compton Scattering, creating secondary electrons, which create more photons, forming an ongoing cascade until the energy is fully dispersed. Lead alone cannot easily damp this without scattering significant secondary radiation.
------------------------------
## 🧪 Experiment B: 100 MeV Heavy Hadron (Proton) Capture## How to Execute
Clear your viewport screen, shift the gun ammunition configuration to a proton, and run the simulation:

# Inside the active GUI Session Bar, execute:
/vis/viewer/clear
/gun/particle proton
/run/beamOn 5

## Visual Phenomenon Observed
The massive green photon cloud completely vanishes. The viewport appears almost completely empty. If you zoom in close to the front face of the lead target block, you will see 5 short blue track segments that terminate almost instantly (within millimeters) inside the lead material. No secondary radiation escapes.
## The Underlying Physics Explained
This demonstrates the Bethe-Bloch Formula and the Bragg Peak.
A proton is a composite hadron and is 1,836 times heavier than an electron. Because it is so massive, it acts like a bowling ball rolling through pins; it does not easily deflect or decelerate rapidly when passing nuclear fields, meaning it emits virtually zero Bremsstrahlung radiation (hence no green lines).
Instead, the proton loses its energy continuously by colliding with and knocking out the atomic electrons surrounding the lead atoms (Coulomb ionization). Because it is heavy and slow-moving, its rate of energy loss skyrockets the slower it gets, depositing almost all its energy in a dense, localized destructive spike (the Bragg Peak) right before coming to a dead stop deep inside the front wall of the shield.
------------------------------
## 🧪 Experiment C: 1.5 GeV Relativistic Hadronic Punch-Through## How to Execute
Clear the engine tracks, boost the particle accelerator velocity line into the Giga-electron-volt threshold, and fire:

# Inside the active GUI Session Bar, execute:
/vis/viewer/clear
/gun/energy 1.5 GeV
/run/beamOn 5

## Visual Phenomenon Observed
Clean, rigid blue track lines blast through space from the origin, punch completely straight through the center of the solid lead shield block without bending, and exit the right side of your experimental chamber. At the point of impact inside the lead block, small, localized bursts of green photons fly out.
## The Underlying Physics Explained
This demonstrates Relativistic Kinematics and Hadronic Inelastic Smashes.
By raising the energy to 1.5 GeV ($1500\text{ MeV}$), the proton's velocity approaches the speed of light. At this extreme momentum, the ionization stopping power of a 5 cm lead block is completely bypassed—the shield is simply too thin to absorb a particle with that much kinetic energy.
Furthermore, because the proton's wavelength is now smaller than an atomic nucleus, it occasionally collides head-on with a lead nucleus. This triggers Inelastic Hadronic Scattering or nuclear spallation, fracturing the nucleus and releasing secondary particles, which causes the small green photon bursts seen inside the shield volume.
------------------------------
## 💾 Part 4: Technical Analysis of Data Output Pipelines## The Multi-Threaded File Strategy
When executing simulations via macro files (./ShieldSim run1.mac), Geant4 automatically runs in highly efficient Multi-Threaded (MT) Mode to maximize performance on modern multi-core processors.
To prevent multiple CPU cores from writing to the same file simultaneously—which would corrupt the data—the system creates separate spreadsheet files for each active worker core on your system:

simulation_output_nt_ShieldData_t0.csv   <-- Processed by CPU Core 0
simulation_output_nt_ShieldData_t1.csv   <-- Processed by CPU Core 1
simulation_output_nt_ShieldData_t2.csv   <-- Processed by CPU Core 2
...

## Deconstructing the Spreadsheet Format
When you inspect the data using a command like head -n 20 simulation_output_nt_ShieldData_t0.csv, you will find structured rows tracking the results of the Monte Carlo random numbers:

#class tools::wcsv::ntuple
#title Simulation Output Data
#separator 44
#vector_separator 59
#column double EventID
#column double EnergyDeposit
0,14.5241
1,0.0000
2,82.1194
3,11.0542


* # Metadata Lines: These declare configuration parameters (e.g., column formats and comma delimiters) so data frameworks like Pandas, ROOT, or Excel can parse the spreadsheet automatically.
* Column 1 (EventID): The unique index tracking ID number of the specific particle fired from the gun (ranging from 0 to your total event limit).
* Column 2 (EnergyDeposit): This represents the cumulative value of all ionizing energy deposits (measured in Mega-electron-volts) left inside your lead block by that specific particle.
* A row showing 0.0000 indicates a particle that missed the target or passed through without interacting.
   * A row showing positive decimal numbers (e.g., 82.1194) tells you that the particle was heavily absorbed, depositing a massive percentage of its initial 100 MeV energy directly inside the lead shield matrix.

------------------------------
## 🤝 Support & Contact

If you run into any compilation errors, package path conflicts, or syntax problems while deploying this simulation system, please feel free to reach out directly:

* **X (Twitter)**: [https://x.com/oyewodayo](https://x.com/oyewodayo)
* **LinkedIn**: [https://linkedin.com/in/oyewodayo](https://linkedin.com/in/oyewodayo)

