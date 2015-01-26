--Project Euler Problem 4 Find largest number smaller than 999^2 which is a 
--palindrome

isPalindrome x = (==) (show(x)) (reverse(show(x)))

-- Simple solution is to create string and compare it to its reverse
problem_4 = maximum [x*y | x <- [100..999], y <- [100..999], isPalindrome (x*y)]

main :: IO()
main = do 
    y <- return (problem_4)
    putStrLn("Answer to problem 4 = " ++ show(y))
