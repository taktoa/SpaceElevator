module Constants where

a `e` b = a * (10**b)
cbrt x = x**(1/3)

cRe = 6.36 `e` (6)          -- Radius of the Earth (m)
cGe = 3.68 `e` (14)         -- Gravity of the Earth (m^3 / s^2) (Me * G)
cLm = 1.30 `e` (11)         -- Maximum tensile strength of nanotubes (Pa)
cVg = 7.30 `e` (-5)         -- Rotation of the Earth (rad/s)
cEc = 1.00 `e` (12)         -- Young's modulus of nanotubes (Pa)
cDc = 1.30 `e` (3)          -- Density of nanotubes (kg/m^3)
cCl = 9.10 `e` (7)          -- Length of cable (m)
cFs = 2.00 `e` (1)          -- Factor of safety (DL)
cMp = 1.20 `e` (3)          -- Mass of payload (kg)
cFr = 1.00 `e` (1)          -- Coefficient of friction of nanotubes (DL)
cVe = 5.55 `e` (1)          -- Target speed of elevator (m/s)
cRg = cbrt (cGe / (cVg**2)) -- Radius of geosynchronous orbit (m)
