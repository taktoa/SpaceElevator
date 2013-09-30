module Constants where

a `e` b = a * (10**b)
cbrt x = x**(1/3)

cRe = 6.36 `e` 6            -- Radius of the Earth
cGe = 3.68 `e` 14           -- Gravity of the Earth
cLm = 1.30 `e` 11           -- Maximum resistance of nanotubes
cVg = 7.30 `e` -5           -- Rotation of the Earth
cEc = 1.00 `e` 12           -- Young's modulus of nanotubes
cDc = 1.30 `e` 3            -- Density of nanotubes
cCl = 9.10 `e` 7            -- Length of cable
cFs = 2.00 `e` 1            -- Factor of safety
cMp = 1.20 `e` 3            -- Mass of payload
cFr = 1.00 `e` 1            -- Coefficient of friction of nanotubes
cVe = 5.55 `e` 1            -- Target speed of elevator
cRg = cbrt (cGe / (cVg**2)) -- Radius of geosynchronous orbit
