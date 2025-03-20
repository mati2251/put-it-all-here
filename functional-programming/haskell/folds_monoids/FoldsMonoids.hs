data Tree a where
  Empty :: Tree a
  Node :: (Tree a) -> a -> (Tree a) -> Tree a
  deriving (Show)

treeFold :: b -> (b -> a -> b -> b) -> Tree a -> b
treeFold e _ Empty = e
treeFold e f (Node l v r) = f (treeFold e f l) v (treeFold e f r)

treeSize :: Tree a -> Integer
treeSize = treeFold 0 (\x _ z -> 1 + x + z)

newtype Sum a = Sum a
  deriving (Eq, Ord, Num, Show)

getSum :: Sum a -> a
getSum (Sum a) = a

class Num a => Monoid a where
  mempty  :: Sum a
  mempty = Sum 0
  mappend :: a -> a -> Sum a
  mappend a b = Sum (a + b)

