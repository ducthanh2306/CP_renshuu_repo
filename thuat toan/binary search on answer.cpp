
int l,r;

while(l <= r){
    mid = (l + r) / 2;
    if(check(mid))
        l = mid + 1;   // mid ok → thử lớn hơn
    else
        r = mid - 1;   // mid sai → giảm
}

//truong hop tim min possible
// ---->return l
// truong hop tim max possible
 // ---> return r
