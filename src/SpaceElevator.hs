module Main where
import Segment

main = mapM putStrLn $ segs
    where
    segs = map (\(Segment a b c d e f g h) -> show (a, b, c, round d, round e, round f, round g, round h)) (initTotal 100)
--import Graphics.UI.GLUT
--import Data.IORef
--import Bindings

--myPoints :: [(GLfloat,GLfloat,GLfloat)]
--myPoints = [ (sin (2*pi*k/24), cos (2*pi*k/24), 0) | k <- [1..24] ]
 
--main = do
--    initialize "TestMain" ["-geometry 640x480+15+15"]
--    initialDisplayMode $= [DoubleBuffered]
--    window <- createWindow "Testing"
--    angle <- newIORef 0
--    delta <- newIORef 0.1
--    displayCallback $= display angle
--    mainLoop

--display :: IORef GLfloat -> DisplayCallback
--display angle = do
--    clear [ ColorBuffer ]
--    a <- get angle
--    let sph = Sphere' 0.5 30 30
--    rotate a $ sph
--    renderObject Wireframe sph
--    --renderPrimitive (Sphere' 0.5 30 30)
--    --renderPrimitive Polygon $
--    --    mapM_ (\(x, y, z) -> vertex $ Vertex3 x y z) myPoints
--    swapBuffers

--idle :: IORef GLfloat -> IORef GLfloat -> IdleCallback
--idle angle delta = do
--    d <- get delta
--    angle $~! (+ d)
--    postRedisplay Nothing
