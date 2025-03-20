(defmacro make-printer [name to-print]
  `(defn ~name [] (println ~to-print)))
(make-printer say-hello "Hello, mate")
(say-hello)
