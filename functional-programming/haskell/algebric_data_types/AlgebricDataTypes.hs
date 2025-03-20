import GHC.RTS.Flags (ProfFlags(typeSelector))
-- enums
data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday
    deriving Show

isWeekend :: Day -> Bool
isWeekend Saturday = True
isWeekend Sunday = True
isWeekend _ = False

-- Beyond enum 
data FailableDouble = Failure | OK Double
    deriving Show

safeDivide :: Double -> Double -> FailableDouble
safeDivide _ 0 = Failure
safeDivide x y = OK (x / y)

data Person where
  Person :: String -> Int -> Person
  Baby :: String -> Person
  Adult :: String -> Person
  PersonDetails :: String -> Int -> String -> String -> Person
  deriving Show

brother :: Person
brother = PersonDetails "Brother" 20 "Brown" "Brown"
sister :: Person
sister = Baby "Sister"

foo :: Person -> String
foo (PersonDetails name _ _ eyes) = "This is " ++ name ++ " and he has " ++ eyes ++ " eyes."

foo2 :: Person -> String
foo2 person = case person of 
  PersonDetails name _ _ eyes -> "This is " ++ name ++ " and he has " ++ eyes ++ " eyes."
  Baby name -> "This is " ++ name ++ " and he is a baby."
  Adult name -> "This is " ++ name ++ " and he is an adult."
  Person name _ -> "This is " ++ name ++ "."

-- recursive data types

data IntList where
  Empty :: IntList
  Cons :: Int -> IntList -> IntList

data Tree where
  Leaf :: Char -> Tree
  Node :: Tree -> Int -> Tree -> Tree

tree :: Tree
tree = Node (Leaf 'x') 1 (Node (Leaf 'y') 2 (Leaf 'z'))

main :: IO ()
main = do
  putStrLn (foo brother)
  -- putStrLn (foo sister) -- This will throw an error
  putStrLn (foo2 sister)

-- records type data
data PersonRecord where
  PersonRecord :: {name :: String, age :: Int} -> PersonRecord
  deriving Show
