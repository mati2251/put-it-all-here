BEGIN{
    getline < "description.txt"
    row = $1
    it = row
    row_check = "x{"$2"}"
    empty_row_check = "x[[:space:]]{"$2-2"}x"
    while((getline < "rectangle.txt") > 0){
        if(it == row || it == 1){
            if($0 ~ row_check) it-=1
        }
        space_number = columns - 2
        if($0 ~ empty_row_check) it-=1
    }
    if(it == 0){
        print("Dobry")
    }
    else {
        print("Zły")
    }
}