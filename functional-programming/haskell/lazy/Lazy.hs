-- Haskell is lazy evaluation language. It means that the evaluation of an expression is not done until it is really needed.
-- If you pass data to a function, that data is not evaluated until it is really needed. These data are called "thunks".
-- This is a simple example of lazy evaluation, where evaluation is not needed
lazyEvaluate :: Maybe a -> [Maybe a]
lazyEvaluate x = [x]
-- This is a simple example of lazy evaluation, where evaluation is needed for pattern matching
partlyLazyEvaluate :: Maybe a -> a
partlyLazyEvaluate (Just x) = x
partlyLazyEvaluate Nothing = error "Nothing"
-- Evaluate is needed for pattern matching. But haskell evaluate only as far as it is needed.
