module SConfig where

data SConfig = SConfig {
            cable :: SCable,
            planet :: SPlanet,
            run :: SRun,
            elevator :: SElevator
            }

data SCable = SCable {
            cableModulus :: Pressure,           -- Young's modulus
            cableStrength :: Pressure,          -- Ultimate tensile strength
            cableFriction :: Double,            -- Coefficient of friction
            cableDensity :: Density             -- Density
            }

data SPlanet = SPlanet {
            planetAtmos :: Length -> Density,   -- Atmospheric density function
            planetRadius :: Length,             -- Radius of planet
            planetMass :: Mass,                 -- Mass of planet
            planetRot :: Frequency              -- Rotational frequency of planet
            }

data SRun = SRun {
            timestep :: Time,                   -- Timestep
            timelength :: Time,                 -- Length of time
            safetyFactor :: Double,             -- Safety factor
            breakPoint :: Double                -- Breakpoint distance
            }

data SElevator = SElevator {
            elevatorMass :: Mass,               -- Mass of elevator
            elevatorSpeed :: Speed              -- Target speed of elevator
            }
