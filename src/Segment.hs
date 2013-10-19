module Segment where
import Constants
import Vector

a // b = (fromIntegral a) / (fromIntegral b)

data Segment = Segment {
            position :: VectorD,
            velocity :: VectorD,
            force :: VectorD,
            mass :: Double,
            kval :: Double,
            lenInit :: Double,
            tension :: Double,
            crossS :: Double
            }

segmentP :: Int -> Int -> VectorD
segmentP n i = Vector ((cCl * (i // n)) + cRe) 0 0

initSegmentPs :: Int -> [VectorD]
initSegmentPs n = map (segmentP n) [0 .. n]

initOtherShit' :: Int -> Double -> Double -> Double -> [Segment] -> [Segment]
initOtherShit' _ _ _ _ [] = []
initOtherShit' n mt fc t (x:xs) = newSeg : (initOtherShit' n mtN fcN tN xs)
    where
    Segment xp xv xf _ _ _ _ _ = x
    al = cCl / (fromIntegral n)
    dist = normVec (position x)
    cs = cFs * t / cLm
    kv = (cs * cEc) / al
    il = al - (t / kv)
    ms = il * cs * cDc
    mtN = mt + ms
    fcN = (cGe - (dist^3 * cVg^2)) / (dist^2)
    tN = fcN * ms
    newSeg = Segment xp xv xf ms kv il t cs
    
initOtherShit :: [Segment] -> [Segment]
initOtherShit segs = initOtherShit' (length segs) 0 0 cMp segs

initTotal :: Int -> [Segment]
initTotal n = initOtherShit initSegs
    where
    initSeg p = Segment p zero zero 0 0 0 0 0
    initSegs = map initSeg (initSegmentPs n)
