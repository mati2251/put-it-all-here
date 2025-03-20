(define (domain paczki)
	(:requirements :adl)
	(:predicates
		(on ?x ?y)
		(clear ?x)
		(floor ?x)
		(top ?x)
	)
	(:action podnies-z-paczki
		:parameters (?x ?y)
		:precondition (and
			(forall
				(?p)
				(not (top ?p)))
			(not (floor ?x))
			(on ?x ?y)
			(clear ?x)
		)
		:effect (and
			(not (clear ?x))
			(clear ?y)
			(not (on ?x ?y))
			(top ?x)
		)
	)
	(:action podnies-z-podlogi
		:parameters (?x)
		:precondition (and
			(forall
				(?p)
				(not (top ?p)))
			(floor ?x)
			(clear ?x)
		)
		:effect (and
			(not (clear ?x))
			(not (floor ?x))
			(top ?x)
		)
	)
	(:action opusc-na-paczke
		:parameters (?y ?x)
		:precondition (and
			(top ?x)
			(clear ?y)
		)
		:effect (and
			(clear ?x)
			(not (clear ?y))
			(on ?x ?y)
			(not (top ?x))
		)
	)
	(:action opusc-na-podloge
		:parameters (?x)
		:precondition (and
			(top ?x)
		)
		:effect (and
			(clear ?x)
			(floor ?x)
			(not (top ?x))
		)
	)
)