--Project Euler Problem N

problem_N = sum[x | x <- [1..999], mod x 3 == 0 || mod x 5 == 0]

main :: IO()
main = do 
    y <- return (problem_N)
    putStrLn("Answer to problem N = " ++ show(y))
