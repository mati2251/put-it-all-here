(define (problem 5-paczek)
	(:domain paczki)
	(:objects
		a b c e d
	)
	(:init
		(clear c)
		(clear e)
		(on c b)
		(on b a)
		(on e d)
		(floor a)
		(floor d)
	)
	(:goal
		(and
			(on d b)
			(exists (?p) (on b ?p) )
		)
	)
)