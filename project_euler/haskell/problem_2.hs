-- Project Euler Problem 2
-- This solution is quite slow, I need to come back and do this intelligently

fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

fibSeq n = [fib x | x <- [1..n]]

sumEvenFib n = sum[x | x <- fibSeq n, even x]

main :: IO()
main = do 
    ans <- return (sumEvenFib 33)
    putStrLn("Answer problem 2 = " ++ show(ans))
