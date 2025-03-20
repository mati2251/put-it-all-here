(define (domain hanoi)
    (:requirements :adl)
    (:types
        block stake
    )
    (:constants
        X Y Z - stake
    )
    (:predicates
        (on ?k1 - block ?k2 - block)
        (access ?x - stake ?k - block)
        (biggerr ?k1 - block ?k2 - block)
        (bigger ?k1 - block ?k2 - block)
    )
    (:derived
        (biggerr ?k1 ?k2 - block)
        (or
            (bigger ?k1 ?k2)
            (exists
                (?k3 - block)
                (and (bigger ?k1 ?k3) (biggerr ?k3 ?k2))
            )
        )
    )
    (:action przesun
        :parameters (?x ?y - stake ?k1 ?k2 - block)
        :precondition (and
            (access ?x ?k1)
            (access ?y ?k2)
            (biggerr ?k2 ?k1)
        )
        :effect (and
            (not (access ?x ?k1))
            (not (access ?y ?k2))
            (access ?y ?k1)
            (on ?k1 ?k2)
            (when
                (exists
                    (?k3 - block)
                    (on ?k1 ?k3))
                (and (access ?x ?k3) (not (on ?k1 ?k3))))
        )
    )
    (:action przesun-na-pusty
        :parameters (?x ?y - stake ?k1 - block)
        :precondition (and
            (access ?x ?k1)
            (forall
                (?k2)
                (not (access ?y ?k2)))
        )
        :effect (and
            (not (access ?x ?k1))
            (access ?y ?k1)
            (when
                (exists
                    (?k3 - block)
                    (on ?k1 ?k3))
                (and (access ?x ?k3) (not (on ?k1 ?k3))))
        )
    )
)