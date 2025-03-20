BEGIN{
    getline < "description.txt"
    row = $1
    row_check = "x{"$2"}"
    while((getline < "rectangle.txt") > 0){
        if($0 ~ row_check) row-=1
    }
    if(row == 0){
        print("Dobry")
    }
    else {
        print("Zły")
    }
}