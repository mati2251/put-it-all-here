;; sets
(def s #{1 2 3 4 5})
(println s)
(println (conj s 6)) ;; adds 6 to the set
(println s) ;; sets are immutable
(println (disj s 3)) ;; removes 3 from the set
(println (contains? s 3)) ;; checks if 3 is in the set
(def s2 (sorted-set 3 2 1 4 5))
(println s2) ;; sorted set
(def l '(1 2 3 4 5 6 7 8 9 10))
(println (into s2 l)) ;; converts a list to a set
(def m {:a 1 :b 2 :c 3})
(println m)
(println (assoc m :d 4)) ;; adds a key-value pair to the map
(println m) ;; maps are immutable
(println (dissoc m :c)) ;; removes a key-value pair from the map
(println (get m :a)) ;; gets the value for a key
(println (keys m)) ;; gets the keys
(println (vals m)) ;; gets the values
(println (contains? m :a)) ;; checks if a key is in the map
(def ziped (zipmap s2 (repeat 0))) ;; creates a map from two collections
(println ziped)
(println (merge m ziped)) ;; merges two maps
(println (merge-with + m (select-keys m #{:a :b}))) ;; selects keys from a map
(println (sorted-map :a 1 :b 2 :c 3)) ;; sorted map
(println {:a {:data "test"}}) ;; nested maps
(defrecord Person [name age]) ;; creates a record
(def p (Person. "John" 30)) ;; creates a record instance
(println p)
