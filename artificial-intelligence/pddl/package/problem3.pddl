(define (problem 5-paczek)
	(:domain paczki)
	(:objects
		a b c e d f
	)
	(:init
		(floor a)
		(clear a)
		(floor b)
		(clear b)
		(floor c)
		(clear c)
		(floor d)
		(clear d)
		(floor e)
		(clear e)
		(floor f)
		(clear f)
	)
	(:goal
		(and
			(exists
				(?p)
				(and
					(floor ?p)
					(forall
						(?d)
						(or
							(= ?p ?d)
							(exists
								(?e)
								(on ?d ?e)
							)
						)
					)
				)
			)
		)
	)
)