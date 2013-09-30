module Segment where
import Constants

data Segment = Segment {
            position :: Vector,
            velocity :: Vector,
            force :: Vector,
            mass :: Double,
            kval :: Double,
            lenInit :: Double,
            tension :: Double,
            crossS :: Double
            }

segmentP :: Int -> Int -> Vector

initSegmentPs :: Int -> [Vector]
initSegmentPs n = map (\i -> Vector ((cCl * i / n) + cRe) 0 0) [0 .. n]

initSegmentVs :: Int -> [Vector]
initSegmentVs n = replicate n zero

initOtherShit :: Int -> Double -> Double -> Double -> [
initOtherShit n mt fcoef tens 


initSegments :: Int -> [Segment]
initSegments n = 
    where
    aL = cCl / n
    ks = cCr * cEc * n / cCl
    ls = map (\k -> aL - (cMp / k)) ks
    fr = replicate n cFr
    

        mt += points[i].m = points[i].initlen * points[i].crosssect * c_Dcnt;

        fcoef = c_Ge / (points[i].pos.x * points[i].pos.x) - points[i].pos.x * c_Vang * c_Vang;
        tension += fcoef * points[i].m;
    }
