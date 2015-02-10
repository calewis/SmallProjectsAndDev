import Graphics.Rendering.Chart.Easy
import Graphics.Rendering.Chart.Backend.Cairo
import System.Environment

main = do
    [f,g] <- getArgs
    s     <- readFile f
    writeFile g s
