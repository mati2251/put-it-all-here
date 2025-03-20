toDigits :: Integer -> [Integer]
toDigits n
  | n <= 0 = []
  | otherwise = toDigits (div n 10) ++ [mod n 10]

toDigitsRev :: Integer -> [Integer]
toDigitsRev n = reverse (toDigits n)

doubleEverySecond :: [Integer] -> [Integer]
doubleEverySecond [] = []
doubleEverySecond [x] = [x]
doubleEverySecond (x : y : zs) = x : (y * 2) : doubleEverySecond zs

sumDigits :: [Integer] -> Integer
sumDigits [] = 0
sumDigits [x]
  | x < 10 = x
  | otherwise = div x 10 + mod x 10
sumDigits (x : ys) = sumDigits [x] + sumDigits ys

validateCondition :: Integer -> Bool
validateCondition x = mod x 10 == 0

validate :: Integer -> Bool
validate = validateCondition . sumDigits . doubleEverySecond . toDigitsRev

main :: IO ()
main = do
  number :: Integer <- readLn
  print (validate number) 
