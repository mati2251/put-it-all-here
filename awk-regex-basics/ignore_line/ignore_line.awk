BEGIN{
    start = 0;
    it = 0;
    while ((getline) > 0){
        if($0 ~ /^\$\$\$/) start+=1;
        if(start > 0){
            gsub(" ", "_", $0);
            lines[it] = $0;
            it+=1
        }
        if($0 ~ /^!!!/){
            for(i in lines){
                print(lines[i])
            }
        }
    }
}