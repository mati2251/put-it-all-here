(define (domain merry)
    (:requirements :adl)

    (:types
        scolor color room block cord
    )
    (:constants
        FREE - block
    )
    (:predicates
        (from ?x ?y - room ?c - color)
        (iscolor ?x - room ?c - scolor)
        (avaliablecolor ?c - scolor)
        (tocolor ?c - color ?sc - scolor)
        (position ?x - room)
        (avaliablepuzzle ?p - room)
        (value ?c1 ?c2 - cord ?b - block)
        (next ?c1 ?c2 - cord)
    )
    (:action wez
        :parameters (?c - color)
        :precondition (and
            (exists
                (?p - room)
                (exists
                    (?sc)
                    (and
                        (tocolor ?c ?sc)
                        (iscolor ?p ?sc)
                        (position ?p))))
        )
        :effect (and
            (avaliablecolor ?sc)
            (not (iscolor ?p ?sc))
        )
    )
    (:action idz
        :parameters (?p - room)
        :precondition (and
            (exists
                (?p2 - room)
                (exists
                    (?sc - scolor)
                    (exists
                        (?c - color)
                        (and
                            (avaliablecolor ?sc)
                            (tocolor ?c ?sc)
                            (from ?p2 ?p ?c)
                            (position ?p2))))
            )
        )
        :effect (and
            (not (avaliablecolor ?sc))
            (not (position ?p2))
            (position ?p)
        )
    )
    (:action przesun
        :parameters (?b - block)
        :precondition (and
            (exists
                (?p - room)
                (and (position ?p) (avaliablepuzzle ?p)))
            (exists
                (?c3 - cord)
                (exists
                    (?c4 - cord)
                    (value ?c3 ?c4 ?b)))
            (exists
                (?c - cord)
                (exists
                    (?c2 - cord)
                    (value ?c ?c2 FREE)))
            (or (= ?c2 ?c4) (= ?c ?c3))
            (or (next ?c ?c3) (next ?c2 ?c4))
        )
        :effect (and
            (not (value ?c ?c2 FREE))
            (value ?c ?c2 ?b)
            (not (value ?c3 ?c4 ?b))
            (value ?c3 ?c4 FREE)
        )
    )
)