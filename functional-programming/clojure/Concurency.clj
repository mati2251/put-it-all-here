(import '(java.util.concurrent Executors))
(import '(java.util.concurrent TimeUnit))

(println "Atom concurency test")
(def atom-counter (atom 0))
(defn inc-counter []
  (swap! atom-counter inc))

(defn concurency-test []
  (let [executors (Executors/newFixedThreadPool 5)
    counter (atom 0)]
    (dotimes [_ 10000]
      (.execute executors (fn [] (swap! counter inc))))
    (.shutdown executors)
    (.awaitTermination executors 60 TimeUnit/SECONDS)
@counter))

(println (concurency-test))

(println "Agent concurency test")

(defn agent-counter []
  (agent 0))

(defn agent-inc-counter [counter]
  (send counter inc))

(def counter1 (agent-counter))
(def counter2 (agent-counter))

(defn println-counter [counter]
  (println @counter))

(defn concurency-test-agent []
  (dotimes [_ 10000]
    (agent-inc-counter (rand-nth [counter1 counter2])))
  (send-off counter1 inc)
  (send-off counter2 inc)
  (await counter1)
  (await counter2))

(concurency-test-agent)
(println-counter counter1)
(println-counter counter2)
