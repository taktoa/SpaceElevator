module Main where
import Graphics.UI.GLUT

myPoints :: [(GLfloat,GLfloat,GLfloat)]
myPoints = [ (sin (2*pi*k/24), cos (2*pi*k/24), 0) | k <- [1..24] ]
 
main = do
    initialize "TestMain" ["-geometry 640x480+15+15"]
    window <- createWindow "Testing"
    displayCallback $= display
    mainLoop

display :: DisplayCallback
display = do
    clear [ ColorBuffer ]
    renderPrimitive Polygon $
        mapM_ (\(x, y, z) -> vertex $ Vertex3 x y z) myPoints
    flush
