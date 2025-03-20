(define (domain sokoban)
    (:requirements :adl)
    (:predicates
        (paczka ?x)
        (robot ?x)
        (poziomo ?x ?y)
        (pionowo ?x ?y)
    )
    (:action idz
        :parameters (?x ?y)
        :precondition (and
            (robot ?x)
            (or
                (poziomo ?x ?y)
                (pionowo ?x ?y)
            )
            (not (paczka ?y))
        )
        :effect (and
            (not(robot ?x))
            (robot ?y))
    )
    (:action pchaj
        :parameters (?x ?y ?z)
        :precondition (and
            (robot ?x)
            (or
                (and (poziomo ?x ?y) (poziomo ?y ?z) (not (= ?z ?x)))
                (and (pionowo ?x ?y) (pionowo ?y ?z) (not (= ?z ?x)))
            )
            (paczka ?y)
        )
        :effect (and
            (not(robot ?x))
            (robot ?y)
            (not (paczka ?y))
            (paczka ?z)
        )
    )
)