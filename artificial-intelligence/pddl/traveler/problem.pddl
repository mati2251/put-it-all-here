(define (problem traveler)
    (:domain traveler)
    (:objects
        p1 p2 p3 p4 p5 p6 p7 - planet
        d1 d2 d3 d4 d5 d6 - teleport
        pos1 pos2 pos3 pos4 pos5 pos6 - position
        a b c d e - puzzle
    )
    (:init
        (position p1)

        (connected p1 p2 d1)
        (connected p2 p1 d1)
        (connected p1 p6 d5)
        (connected p6 p1 d5)
        (connected p2 p3 FREE)
        (connected p3 p2 FREE)
        (connected p3 p4 d3)
        (connected p4 p3 d3)
        (connected p3 p5 d4)
        (connected p5 p3 d4)
        (connected p4 p5 FREE)
        (connected p5 p4 FREE)
        (connected p6 p7 d6)
        (connected p7 p6 d6)

        (lever p1 d1)
        (lever p2 d3)
        (lever p4 d4)
        (lever p4 d1)
        (lever p5 d5)
        (lever p6 d6)

        (locked d1 p4)
        (unlocked_available d1 p5)

        (puzzle_pos pos1 d)
        (puzzle_pos pos2 e)
        (puzzle_pos pos3 a)
        (puzzle_pos pos4 b)
        (puzzle_pos pos5 FREE_P)
        (puzzle_pos pos6 c)
        (available_puzzle p6)

        (next pos1 pos2)
        (next pos2 pos3)
        (next pos3 pos4)
        (next pos4 pos5)
        (next pos5 pos1)
        (next pos1 pos6)
        (next pos2 pos6)
        (next pos3 pos6)
        (next pos4 pos6)
        (next pos5 pos6)
    )
    (:goal
        (and
            (position p7)
            (puzzle_pos pos1 a)
            (puzzle_pos pos2 b)
            (puzzle_pos pos3 c)
            (puzzle_pos pos4 d)
            (puzzle_pos pos5 e)
        )
    )
)