import Data.Bits (Bits(xor))
-- Functor is defined in the Prelude 
-- class Functor f where
--   fmap :: (a -> b) -> f a -> f b

data Tree a where
  Leaf :: a -> Tree a
  Node :: (Tree a) -> (Tree a) -> Tree a
  deriving Show

instance Functor Tree where
  fmap :: (a -> b) -> Tree a -> Tree b
  fmap f (Leaf a) = Leaf (f a)
  fmap f (Node l r) = Node (fmap f l) (fmap f r)

-- class Functor f => Applicative f where
--  pure :: a -> f a
--  (<*>) :: f (a -> b) -> f a -> f b
-- 
-- <*> - applicative alias
-- <$> - fmap alias

instance Applicative Tree where
  pure :: a -> Tree a
  pure = Leaf
  (<*>) :: Tree (a -> b) -> Tree a -> Tree b
  (Leaf f) <*> t = fmap f t
  (Node l r) <*> t = Node (l <*> t) (r <*> t)

data MyMaybe a where
  MyNothing :: MyMaybe a
  MyJust :: a -> MyMaybe a
  deriving Show

instance Functor MyMaybe where
  fmap :: (a -> b) -> MyMaybe a -> MyMaybe b
  fmap _ MyNothing = MyNothing
  fmap f (MyJust a) = MyJust (f a)

instance Applicative MyMaybe where
  pure :: a -> MyMaybe a
  pure = MyJust
  (<*>) :: MyMaybe (a -> b) -> MyMaybe a -> MyMaybe b
  MyNothing <*> _ = MyNothing
  _ <*> MyNothing = MyNothing
  (MyJust f) <*> (MyJust t) = MyJust (f t) 


type Name = String
type Surname = String
type Age = Int

data Person where
  Person :: {name :: Name, surname :: Surname, age :: Age} -> Person
  deriving Show

age1, age2 :: MyMaybe Age
age1 = MyJust 20
age2 = MyNothing

name1, name2 :: MyMaybe Name
name1 = MyJust "John"
name2 = MyNothing

surname1, surname2 :: MyMaybe Surname
surname1 = MyJust "Doe"
surname2 = MyNothing

p1 = Person <$> name1 <*> surname1 <*> age1 
p2 = Person <$> name2 <*> surname2 <*> age2
p3 = Person <$> name1 <*> surname2 <*> age2
-- Type of p1, p2, p3
-- (Name -> Surname -> Age -> Person) -> (MyMaybe Surname -> MyMaybe Age -> MyMaybe Person)
-- Person <$> name1 :: MyMaybe (Surname -> Age -> Person)
-- MyMaybe (Surname -> Age -> Person) <*> surname1 :: MyMaybe (Age -> Person)
-- MyMaybe (Age -> Person) <*> age1 :: MyMaybe Person

newAge :: Age
newAge = 30

p4 = Person <$> name1 <*> surname1 <*> pure newAge

-- law of applicative
-- f `fmap` x = pure f <*> x

main :: IO ()
main = do
  print p1
  print p2
  print p3
  print p4
  
