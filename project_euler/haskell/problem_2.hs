-- Project Euler Problem 2
-- Faster solution with the fib sequence being taken from
-- https://www.haskell.org/haskellwiki/The_Fibonacci_sequence


fibs = scanl (+) 0 (1:fibs)

main :: IO()
main = do 
    ans <- return $ sum [x | x <- takeWhile (<=4000000) fibs, x `mod` 2 == 0]
    putStrLn("Answer problem 2 = " ++ show(ans))
