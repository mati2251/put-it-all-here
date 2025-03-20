{
    for(i=1; i<=NF; i++){
        if(i != NF){
            if( $i != 0)
                printf("%s^%s+",$i,NF-i)
        } 
        else printf("%s",$i)
    }
    printf("\n")
}