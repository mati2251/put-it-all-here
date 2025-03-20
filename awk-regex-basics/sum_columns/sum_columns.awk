{
    sum = 0
    for(i=2; i<NF;i++){
        sum+=$i
    }
    printf("%-15s %-10s %s \n", $1, $2, sum)
}