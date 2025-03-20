(define (domain traveler)
    (:requirements :adl)
    (:types
        planet teleport position puzzle
    )

    (:constants
        FREE - teleport
        FREE_P - puzzle
    )
    (:predicates
        (position ?p - planet)
        (connected ?p1 ?p2 - planet ?t - teleport)
        (available ?t - teleport)
        (lever ?p - planet ?t - teleport)

        (locked ?t - teleport ?p - planet)
        (unlocked_available ?t - teleport ?p - planet)

        (available_puzzle ?p - planet)
        (puzzle_pos ?pos - position ?puz - puzzle)

        (next ?pos1 ?pos2 - position)
    )
    (:action move
        :parameters (?p - planet)
        :precondition (and
            (exists
                (?p2 - planet)
                (position ?p2))
            (exists
                (?t)
                (connected ?p2 ?p ?t)
            )
            (or
                (available ?t)
                (= ?t FREE))

        )
        :effect (and
            (not (position ?p2))
            (position ?p)
            (not (available ?t))
        )
    )

    (:action openteleport
        :parameters (?p - planet ?t - teleport)
        :precondition (and
            (lever ?p ?t)
            (position ?p)
            (not (available ?t))
            (not (locked ?t ?p))
        )
        :effect (and
            (available ?t)
        )
    )

    (:action unlock_teleport
        :parameters (?p - planet
        )
        :precondition (and
            (position ?p)
            (exists
                (?t - teleport)
                (unlocked_available ?t ?p)
            )
            (exists
                (?p2)
                (locked ?t ?p2))
        )
        :effect (and
            (not (locked ?t ?p2))
        )
    )

    (:action move_puzzle
        :parameters (?puzzle - puzzle)
        :precondition (and
            (exists
                (?planet - planet)
                (and
                    (position ?planet)
                    (available_puzzle ?planet)
                )
            )
            (exists
                (?positon - position)
                (puzzle_pos ?positon ?puzzle)
            )
            (exists
                (?free_positon - position)
                (puzzle_pos ?free_positon FREE_P)
            )
            (or (next ?positon ?free_positon) (next ?free_positon ?positon))
        )
        :effect (and
            (not (puzzle_pos ?positon ?puzzle))
            (puzzle_pos ?free_positon ?puzzle)
            (not (puzzle_pos ?free_positon FREE_P))
            (puzzle_pos ?positon FREE_P)
        )
    )

)