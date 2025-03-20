;; function definition
(defn func [params] (str "Body " params))
;; function call
(println (func "params"))
;; multiarity function definition
(defn func2
  ([] (str "Body "))
  ([param1] (str (func2) param1))
  ([param1 param2] (str (func2 param1) " " param2)))
;; multiarity function call
(println (func2 "param1" "param2"))
;; variadic parameter
(defn func3
  [& rest]
  (str "Body " rest))
(println (func3 "param1" "param2" "param3"))
(defn func4
  [param1 & rest]
  (str "Body " param1 " " rest))
;; anonymous function
(def listA [1 2 3])
(println (filter (fn [x] (even? x)) listA))
(println (filter #(even? %1) listA))
;; gotcha - wrap elements to vector
(println (fn [x] [x]))
;; apply function
(println (apply + 1 listA)) ;; apply pass list as arguments to function
(println (+ 1 1 2 3))
;; let - lexical scope
(let [a 1 b 2]
  (println (+ a b)))
