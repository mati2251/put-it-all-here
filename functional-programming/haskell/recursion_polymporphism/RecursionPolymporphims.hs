-- recursion patterns
l1, l2 :: [Int]
l1 = [1,2,3,4,5]
addOne :: Int -> Int
addOne x = x + 1
l2 = map addOne l1
l3 = filter even l1
l4 = foldr (+) 0 l1
-- polymorphism
data List t = E | C t (List t)
  deriving Show

lst1 :: List Int
lst1 = C 3 (C 5 (C 2 E))
lst2 :: List Char
lst2 = C 'x' (C 'y' (C 'z' E))
lst3 :: List Bool
lst3 = C True (C False E)

filterList :: (t -> Bool) -> List t -> List t
filterList _ E = E
filterList p (C x xs)
  | p x = C x (filterList p xs)
  | otherwise = filterList p xs
-- use pattern matching instead of head and tail
