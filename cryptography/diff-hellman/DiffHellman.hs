import Data.Set (Set, fromList, map, toList)
import Math.NumberTheory.Primes
import System.Random

bigInt :: Integer
bigInt = 5000

n :: Integer
n = unPrime (precPrime bigInt)

allModOfPower :: Integer -> Integer -> Set Integer
allModOfPower g n = Data.Set.map (\x -> mod (g ^ x) n) (fromList [1 .. n - 1])

g_ :: Integer -> Integer
g_ n = until (\x -> length (toList $ allModOfPower x n) == (fromIntegral n - 1)) (+ 1) 2

g :: Integer
g = g_ n

publicKey :: Integer -> Integer -> Integer -> Integer
publicKey g x = mod (g ^ x)

k_ :: Integer -> Integer -> Integer -> Integer
k_ public private = mod (public^private)

main :: IO ()
main = do
  y <- randomRIO (1, 10^6) :: IO Integer
  x <- randomRIO (1, 10^6):: IO Integer
  let x_public = publicKey g x n
  let y_public = publicKey g y n
  let a_session = k_ y_public x n
  let b_session = k_ x_public y n
  print (a_session == b_session)
  putStr "A session key "
  print a_session
  putStr "B session key "
  print b_session


