a, b :: IO ()
-- >> is a sequencing operator (pronounced "then") that discards the value of the first action and returns the value of the second action.
a = putStrLn "Hello World" >> putStrLn "Wow this is great"
-- >>= is a sequencing operator that passes the value of the first action to the second action.
b = getLine >>= putStrLn
c = a >> b
main = c
