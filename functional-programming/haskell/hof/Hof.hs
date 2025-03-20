-- anonymouse functions
l :: [Int]
l = [1, 2, 3, 4, 5]
l1 = map (\x -> x + 1) l
l2 = map (+) l
l3 = foldr (\x y -> x + y) 0 l
l4 = foldr (+) 0 l
-- function composition
f :: Int -> Int
f x = x + 1
g :: Int -> Int
g x = x * 2
h = f . g
h' n = f (g n)
-- currying
-- every function in Haskell takes exactly one argument
-- currying is the process of transforming a function that takes multiple arguments into a function that takes just a single argument
transformToString :: [Int] -> (Int -> Char) -> String
transformToString l f = map f l

main :: IO ()
main = do
  putStrLn (transformToString [1, 2, 3] (\x -> toEnum (x + 64) :: Char))
