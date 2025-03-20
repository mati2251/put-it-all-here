(define (problem hanoi)
    (:domain hanoi)
    (:objects
        k1 k2 k3 k4 k5 - block
    )
    (:init
        (access X k1)
        (on k1 k2)
        (on k2 k3)
        (on k3 k4)
        (on k4 k5)
        (bigger k2 k1)
        (bigger k3 k2)
        (bigger k4 k3)
        (bigger k5 k4)
    )
    (:goal
        (and
            (access Z k1)
            (on k1 k2)
            (on k2 k3)
            (on k3 k4)
            (on k4 k5)
        )
    )
)