import time
import os
from playwright.sync_api import sync_playwright

# Thư mục lưu ảnh
SAVE_DIR = "CodePTIT_DeBai_Sach"
if not os.path.exists(SAVE_DIR):
    os.makedirs(SAVE_DIR)

def run():
    with sync_playwright() as p:
        # Dùng py để gọi đúng bản Python 3.14
        # slow_mo=1000 để máy chạy từ từ, dễ theo dõi
        browser = p.chromium.launch(headless=False, slow_mo=1000)
        # Đặt màn hình to để đề bài hiển thị đẹp nhất
        context = browser.new_context(viewport={'width': 1366, 'height': 800})
        page = context.new_page()

        print(">>> BƯỚC 1: Đăng nhập và chọn môn học.")
        print(">>> Hãy chọn môn học (ví dụ: DSA) để bảng bài tập hiện ra.")
        page.goto("https://code.ptit.edu.vn/student/question", wait_until="networkidle")
        
        # Đợi bạn chọn môn và bảng bài tập xuất hiện
        page.wait_for_selector("table tbody tr", timeout=0)
        print("\n>>> Đã thấy danh sách bài tập. Bắt đầu quét tự động...")

        page_number = 1
        while True:
            print(f"\n--- ĐANG XỬ LÝ TRANG {page_number} ---")
            
            # Lấy lại danh sách các dòng bài tập ở đầu mỗi trang
            rows = page.query_selector_all("table tbody tr")
            num_rows = len(rows)
            print(f"Tìm thấy {num_rows} bài tập trên trang này.")

            for i in range(num_rows):
                # Lấy lại danh sách row để tránh lỗi stale element
                current_rows = page.query_selector_all("table tbody tr")
                if i >= len(current_rows): break # Phòng trường hợp danh sách thay đổi

                link = current_rows[i].query_selector("td a")
                
                if link:
                    problem_id = link.inner_text().strip().replace("/", "_")
                    print(f"  [+] ({i+1}/{num_rows}) Đang vào bài: {problem_id}")
                    
                    # Bấm vào link để mở đề bài
                    link.click()
                    
                    try:
                        # 1. Đợi đề bài load xong
                        # Đợi tiêu đề bài tập hoặc nội dung chính hiện ra
                        page.wait_for_selector("h3, .card-body", timeout=15000)
                        time.sleep(2) # Đợi thêm 2s cho ảnh và công thức toán render đẹp
                        
                        # 2. "ẢO THUẬT": Ẩn phần Lịch sử và Footer đi
                        print("      => Đang dọn dẹp trang web...")
                        page.evaluate("""
                            // Tìm thẻ tiêu đề H3 hoặc H4 có chữ "Lịch sử"
                            const headers = Array.from(document.querySelectorAll('h3, h4'));
                            const historyHeader = headers.find(el => el.textContent.trim().includes('Lịch sử'));
                            
                            if (historyHeader) {
                                // Ẩn tiêu đề "Lịch sử"
                                historyHeader.style.display = 'none';
                                
                                // Ẩn tất cả các phần tử nằm sau tiêu đề "Lịch sử" (bảng kết quả)
                                let nextSibling = historyHeader.nextElementSibling;
                                while(nextSibling) {
                                    nextSibling.style.display = 'none';
                                    nextSibling = nextSibling.nextElementSibling;
                                }
                            }
                            // Ẩn luôn chân trang (footer) nếu có cho sạch
                            const footer = document.querySelector('footer');
                            if (footer) footer.style.display = 'none';
                        """)
                        time.sleep(0.5) # Đợi xíu cho web ẩn xong

                        # 3. Chụp ảnh (Lúc này chỉ còn lại phần đề bài)
                        page.screenshot(path=f"{SAVE_DIR}/{problem_id}.png", full_page=True)
                        print(f"      => Đã chụp ảnh sạch!")

                    except Exception as e:
                        print(f"      [!] Lỗi: Không thể chụp bài {problem_id}. Nội dung chưa load kịp.")
                    
                    # Quay lại trang danh sách để làm bài tiếp theo
                    print("      => Quay lại danh sách...")
                    page.go_back(wait_until="networkidle")
                    page.wait_for_selector("table tbody tr") # Đảm bảo bảng hiện lại rồi mới tiếp tục
            
            # Chuyển trang tiếp theo (Logic cho bản Beta)
            next_btn = page.query_selector("li.page-item:not(.disabled) a[aria-label='Next »'], li.next:not(.disabled) a")
            if next_btn:
                print("\n>>> Chuyển sang trang tiếp theo...")
                next_btn.click()
                time.sleep(3)
                page_number += 1
            else:
                print("\n>>> ĐÃ HOÀN THÀNH TẤT CẢ CÁC TRANG!")
                break

        browser.close()

if __name__ == "__main__":
    run()