(define (domain words)
    (:requirements :adl)
    (:types
        position letter
    )
    (:constants
        EMPTY - letter
    )
    (:predicates
        (pos ?x - position ?l - letter)
        (next ?x - position ?y - position)
        (inword ?x - position)
    )
    (:action swap
        :parameters (?x - position ?y - position)
        :precondition (and
            (inword ?x)
            (inword ?y)
            (exists
                (?l1)
                (pos ?x ?l1))
            (exists
                (?l2)
                (pos ?y ?l2))
        )
        :effect (and
            (not (pos ?x ?l1))
            (pos ?x ?l2)
            (not (pos ?y ?l2))
            (pos ?y ?l1)
        )
    )
    (:action remove
        :parameters (?x - position)
        :precondition (and
            (inword ?x)
            (exists
                (?l1)
                (pos ?x ?l1))
            (exists
                (?xb)
                (= ?xb ?xb))
            (exists
                (?xa)
                (= ?xa ?xa))
        )
        :effect (and
            (not (pos ?x ?l1))
            (when
                (and (next ?x ?xa) (next ?xb ?x))
                (next ?xb ?xa))
            (when
                (next ?x ?xa)
                (not (next ?x ?xa)))
            (when
                (next ?xb ?x)
                (not (next ?xb ?x)))
            (not (inword ?x))
        )
    )
    (:action add-letter
        :parameters (?before - position ?new - position ?l - letter)
        :precondition (and
            (inword ?before)
            (not (inword ?new))
            (exists
                (?after - position)
                (= ?after ?after)
            )
        )
        :effect (and
            (next ?before ?new)
            (when
                (next ?before ?after)
                (and
                    (not (next ?before ?after))
                    (next ?new ?after)
                ))
            (inword ?new)
            (pos ?new ?l)
        )
    )

    (:action add-letter-start
        :parameters (?new - position ?l - letter)
        :precondition (and
            (not (inword ?new))
            (exists
                (?after)
                (and
                    (inword ?after)
                    (not (forall
                            (?p)
                            (next ?p ?after)))
                )
            )
        )

        :effect (and
            (next ?new ?after)
            (inword ?new)
            (pos ?new ?l)
        )
    )
)
