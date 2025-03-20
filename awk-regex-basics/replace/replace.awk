/#replace./ {
    replaces[$2] = $3
}
!/#replace./ {
    for(i=1; i<=NF; i++){
        for(replace in replaces){
            gsub(replace, replaces[replace], $0)
        }
    }
    print($0)
}