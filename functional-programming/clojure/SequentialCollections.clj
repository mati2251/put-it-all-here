;; vectors are sequential indexed collections
(println [1 2 3]) ; normal vector
(println '(vector 1 2 3)) ; quoted vector
(println (get (vector 1 2 3) 0)) ; get element 
(println (get (vector 1 2 3) 4)) ; get invalid element return nil
(println (count (vector 1 2 3))) ; count elements
(println (conj (vector 1 2 3) 4)) ; add element
;; clojure collections are immutable
(def my-vec (vector 1 2 3))
(println (conj my-vec 4))
(println my-vec)

;; lists are sequential linked lists that add elements at the head
(println (list 1 2 3)) ; normal list
(println '(1 2 3)) ; qutoed list 
;; becouse code is represented as list, to create a list you can use quote
(println (conj '(1 2 3) 4)) ; add element
;; stack operations
(println (peek (list 1 2 3))) ; get last element
(println (pop (list 1 2 3))) ; remove last element

