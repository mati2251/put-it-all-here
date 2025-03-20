(if (even? 2)
  (println "2 is even")
  (println "2 is odd"))
(if (even? 5)
  (do (println "5 is even") true)
  (do  (println "5 is odd") false))
(when (even? 2)
  (println "2 is even"))
(println (let [x 4]
           (cond
             (< x 3) "less than 3"
             (< x 5) "less than 5"
             (< x 7) "less than 7")))
(println (let [x 4]
           (cond
             (< x 3) "less than 3"
             :else "greater than 3")))
(println (case 2
           1 "one"
           2 "two"
           3 "three"
           "other"))
(dotimes [i 5] ;; 0 to 4, return nil
  (print i " "))
(println)
(doseq [i (range 5)] ;; 0 to 4, return nil
  (print i " "))
(println)
(doseq [i [:a :b :c]] ;; like for-each, return nil
  (print i " "))
(println)
(println (for [i (range 5)] ;; 0 to 4, return a list
           i))
(loop [x 0]
  (if (< x 5)
    (do
      (print x " ")
      (recur (inc x)))))
(println)
(defn increase [x]
  (if (< x 5)
    (do
      (print x " ")
      (recur (inc x)))
    x))
(println (increase 0))
(try
  (/ 2 0)
  (catch ArithmeticException _
    (println "ArithmeticException"))
  (finally
    (println "finally")))
(try
  (throw (ex-info "There was a problem" {:detail 42}))
  (catch Exception e
    (prn (:detail (ex-data e)))))
