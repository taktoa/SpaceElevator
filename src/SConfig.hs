module SConfig where

data SConfig = SConfig {
            cable :: SCable,
            planet :: SPlanet,
            run :: SRun,
            elevator :: SElevator
            }

data SCable = SCable {
            youngsModulus :: YModulus,
            tensileStrength :: Tensile,
            frictionCoeff :: FrictionCoeff,
            cableDensity :: Density,
            }

data SPlanet = SPlanet {
            planetAtmos :: Length -> Density,
            planetRadius :: Length,
            planetMass :: Mass,
            planetRot :: Time,
            }

data SRun = SRun {
            timestep :: Time,
            timelength :: Time,
            safetyFactor :: Double
            }

data SElevator = SElevator {
            elevatorMass :: Mass,
            elevatorSpeed :: Speed
            }
