module Vector where

data Vector a = Vector {
            getX :: a,
            getY :: a,
            getZ :: a
            }

instance (Show a, Num a) => Show (Vector a) where
    show (Vector x y z) = show (x, y, z)

type VectorD = Vector Double

zero :: Num a => Vector a
zero = Vector 0 0 0

addVec :: Num a => Vector a -> Vector a -> Vector a
addVec v1 v2 = Vector (x1 + x2) (y1 + y2) (z1 + z2)
    where
    (x1, y1, z1) = (getX v1, getY v1, getZ v1)
    (x2, y2, z2) = (getX v2, getY v2, getZ v2)

scaleVec :: Num a => a -> Vector a -> Vector a
scaleVec s v = Vector (s * getX v) (s * getY v) (s * getZ v)

dotVec :: Num a => Vector a -> Vector a -> a
dotVec v1 v2 = (x1 * x2) + (y1 * y2) + (z1 * z2)
    where
    (x1, y1, z1) = (getX v1, getY v1, getZ v1)
    (x2, y2, z2) = (getX v2, getY v2, getZ v2)

crossVec :: Num a => Vector a -> Vector a -> Vector a
crossVec v1 v2 = Vector xn yn zn
    where
    (x1, y1, z1) = (getX v1, getY v1, getZ v1)
    (x2, y2, z2) = (getX v2, getY v2, getZ v2)
    xn = (y1 * z2) - (z1 * y2)
    yn = (z1 * x2) - (x1 * z2)
    zn = (x1 * y2) - (y1 * x2)

normVec :: Floating a => Vector a -> a
normVec v = sqrt (dotVec v v)

addScaleVec :: Num a => a -> Vector a -> Vector a -> Vector a
addScaleVec s v1 = addVec (scaleVec s v1)

subVec :: Num a => Vector a -> Vector a -> Vector a
subVec = flip (addScaleVec (-1))

distVec :: Floating a => Vector a -> Vector a -> a
distVec v1 v2 = normVec (subVec v1 v2)
