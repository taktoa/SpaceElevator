module SConfig where

data SConfig = SConfig {
            cable :: SCable,
            planet :: SPlanet,
            run :: SRun,
            elevator :: SElevator
            }

data SCable = SCable {
            test1 :: Type,
            test2 :: Type
            }

data SPlanet = SPlanet {
            atmosphere :: Length -> Density,
            radius :: Length
            mass :: Mass
            }

data SRun = SRun {
            test1 :: Type,
            test2 :: Type
            }

data SElevator = SElevator {
            test1 :: Type,
            test2 :: Type
            }
