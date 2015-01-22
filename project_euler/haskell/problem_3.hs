-- Project Euler Problem 3 find the largest prime factor of a number

-- divisors calculates all the divisors of a number not equal to 1 or itself.
divisors ::  Integral a  => a -> [a]
divisors num = concat [[x, div num x] | x <- [2..(limit-1)], num `mod` x == 0]
    where limit = (floor.sqrt.fromIntegral) num

-- isPrime determines if the input has any divisors other than 1 or itself
isPrime num | length (divisors num) == 0 = True
            | length (divisors num) > 0 = False

problem_3 :: Integral a => a -> [a]
problem_3 num = filter isPrime $ divisors num

main :: IO()
main = do
    y <- return $ maximum (problem_3 600851475143)
    putStrLn("Answer to problem 3 = " ++ show(y))
