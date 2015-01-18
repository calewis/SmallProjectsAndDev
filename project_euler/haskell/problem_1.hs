--Project Euler Problem 1

main :: IO()
main = do 
    y <- return (sum[x | x <- [1..999], mod x 3 == 0 || mod x 5 == 0])
    putStrLn("Answer to problem 1 = " ++ show(y))
