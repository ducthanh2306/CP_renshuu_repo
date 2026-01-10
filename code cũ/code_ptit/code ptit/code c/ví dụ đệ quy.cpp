void recurse(int a) {
    if (/* điều kiện dừng */) {
        return;  // Điều kiện dừng để tránh vòng lặp vô hạn
    }
    
    // Thực hiện một số thao tác
    //code lines...

    recurse(a - 1);  // Gọi lại chính nó với tham số thay đổi
}
int recurse(int a) {
    if (/* điều kiện dừng */) {
        return /* giá trị cơ sở */;
    }
    return /* công thức đệ quy với recurse(a - 1) hoặc biến đổi khác */;
}
