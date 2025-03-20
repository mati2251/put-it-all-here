-- Monad definition
-- class Monad m where
--  return :: a -> m a
--  (>>=) :: m a -> (a -> m b) -> m b -- bind 
--  m1 >> m2 = m1 >>= \_ -> m2
--

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

instance Monad MyMaybe where
  (>>=) :: MyMaybe a -> (a -> MyMaybe b) -> MyMaybe b
  MyNothing >>= _ = MyNothing
  (MyJust x) >>= f = f x

check :: Int -> MyMaybe Int
check x = if x > 0 then MyJust x else MyNothing

halve :: Int -> MyMaybe Int
halve x = if even x then MyJust (x `div` 2) else MyNothing

ex = check 10 >>= halve

main = print ex
