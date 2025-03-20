-- define variables
x :: Int
x = 3
-- variables are immutable. x is defined as 3
-- machined size integers are limited and are diffrent beetwen architechtures
biggestInt, smallestInt :: Int
biggestInt = maxBound
smallestInt = minBound
-- arbitrary precision integers are limited only by the amount of memory
biggerInt :: Integer
biggerInt = 2^1000^1000
-- double precision floating point
pi :: Double
pi = 3.14159
-- boolean
isTrue :: Bool
isTrue = True
-- unicode characters
myChar :: Char
myChar = 'a'
-- strings
myString :: String
myString = "Hello, World!"
-- arithmetic
-- +, -, *, /, ^, %, div, mod
i1 = 2 + 15
i2 = 49 - 23
i3 = 12 * 3
f4 = 12.0 / 3.0 -- division is always work on floating point numbers
i5 = 2 ^ 3
i6 = 12 `mod` 3 -- to use mod as infix operator use backticks
i7 = mod 12 3
i8 = (-1) * (-2) -- negative numbers are in parentheses
-- operations beetwen diffrent types are not allowed
-- 3 + 4.0
-- you must use fromIntegral, round, floor, ceiling
-- boolean operations
-- &&, ||, not
b1 = True && False
b2 = True || False
b3 = not True
-- comparison
-- ==, /=, <, >, <=, >=
b4 = 5 /= 5
-- defining functions by cases
mySum :: Int -> Int
mySum 0 = 10 
mySum n = 5 * n + mySum (n - 1)
-- defining the same by guards
mySum' :: Int -> Int
mySum' n
  | n == 0 = 10
  | mod n 10 == 0 = 20
  | otherwise = 5 * n + mySum' (n - 1)
-- pairs
p :: (Int, Char)
p = (3, 'a')
f :: Int -> Int -> Int -> Int
f x y z = x + y + z
ex17 = f 3 (4+1) 5 -- 4+1 is evaluated must be in parentheses
-- lists
l1, l2, l3 :: [Int]
l1 = [1, 2, 3, 4, 5]
l2 = [1..5]
l3 = 1 : l1
-- strings are lists of characters
s1 :: String
s1 = "Hello"
s2 :: [Char]
s2 = ['H', 'e', 'l', 'l', 'o']
helloSame = s1 == s2
-- pattern matching
sumList :: [Int] -> Int
sumList [] = 0
sumList (x:xs) = x + sumList xs
main = putStrLn "Hello, World!" 
