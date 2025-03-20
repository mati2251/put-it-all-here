{ 
for(i=1; i<=NF; i++)
{
    if($i ~ /^[A-Z]\.[A-Z]/){
        t = split($i, name_surname, ".");
        if(t == 2){
            printf("%s.%s ",name_surname[2], name_surname[1])
        }
    }
    else {
        printf("%s ", $i)
    }
}
printf("\n")
}