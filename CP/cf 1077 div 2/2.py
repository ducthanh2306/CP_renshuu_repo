import sys

def solve(s):
    n = len(s)
    # Lấy nhanh danh sách vị trí các số 1
    pos = [i for i, char in enumerate(s) if char == '1']
    oneNum = len(pos)

    # TH1: Không có số 1 nào
    if oneNum == 0:
        return (n + 2) // 3

    total_added = 0
    
    # 1. Xử lý đoạn trống bên trái số 1 đầu tiên (Prefix)
    # Khoảng trống thực sự: từ 0 đến pos[0]-2 -> độ dài = pos[0]-1
    total_added += max(0, (pos[0] - 1 + 2) // 3)

    # 2. Xử lý các khoảng trống ở giữa các số 1
    for i in range(1, oneNum):
        gap = pos[i] - pos[i-1] - 1
        # Ghế trống thực sự có thể đặt: gap - 2
        if gap >= 3:
            total_added += (gap - 2 + 2) // 3

    # 3. Xử lý đoạn trống bên phải số 1 cuối cùng (Suffix)
    # Khoảng trống thực sự: từ pos[-1]+2 đến n-1 -> độ dài = n-pos[-1]-2
    last_gap_len = n - 1 - pos[-1]
    total_added += max(0, (last_gap_len - 1 + 2) // 3)

    return total_added + oneNum

# Tối ưu đọc dữ liệu cho Competitive Programming
input_data = sys.stdin.read().split()
if input_data:
    t = int(input_data[0])
    pointer = 1
    for _ in range(t):
        # Đề bài cho n sau đó đến chuỗi s
        n_val = int(input_data[pointer])
        s_val = input_data[pointer + 1]
        print(solve(s_val))
        pointer += 2