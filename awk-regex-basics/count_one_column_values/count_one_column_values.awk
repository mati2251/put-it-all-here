NR > 1 { 
    sub(/\./, ",", $3);
    profit += $3 
}
END { print(profit) }