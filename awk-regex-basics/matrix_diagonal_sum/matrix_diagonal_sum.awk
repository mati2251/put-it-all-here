BEGIN { i=0; }
{
    i+=1;
    sum+=$i
}
END{ print sum + 0}