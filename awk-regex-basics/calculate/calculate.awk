NR == 1 {printf("%s a+b*c\n", $0)}
NR > 1 {printf("%s %s\n", $0, $1+$2*$3)}