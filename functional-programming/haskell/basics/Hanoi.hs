type Peg = String
type Move = (Peg, Peg)
hanoi :: Int -> Peg -> Peg -> Peg -> [Move]
hanoi 0 _ _ _ = []
hanoi 1 a _ c = [(a, c)]
hanoi n a b c = hanoi (n-1) a c b ++ [(a,c)] ++ hanoi (n-1) b a c

main :: IO ()
main = print (hanoi 5 "a" "b" "c")
