import time
import os
from playwright.sync_api import sync_playwright

# Khởi tạo thư mục
DIR_KY_NIEM = "PTIT_KyNiem_Full"
DIR_ON_TAP = "PTIT_OnTap_ChiDe"

for folder in [DIR_KY_NIEM, DIR_ON_TAP]:
    if not os.path.exists(folder):
        os.makedirs(folder)

def run():
    with sync_playwright() as p:
        # slow_mo giúp máy chạy ổn định hơn trên nền tảng Beta
        browser = p.chromium.launch(headless=False, slow_mo=1000)
        context = browser.new_context(viewport={'width': 1366, 'height': 1200})
        page = context.new_page()

        print(">>> BƯỚC 1: Đăng nhập và chọn môn học (ví dụ: C++ hoặc DSA)...")
        page.goto("https://code.ptit.edu.vn/student/question", wait_until="networkidle")
        
        # Đợi bảng bài tập hiện ra
        page.wait_for_selector("table tbody tr", timeout=0)
        print(">>> Đã thấy danh sách. Bắt đầu thu hoạch 'Song bản'...")

        page_idx = 1
        while True:
            print(f"\n--- ĐANG XỬ LÝ TRANG {page_idx} ---")
            rows = page.query_selector_all("table tbody tr")
            
            for i in range(len(rows)):
                current_rows = page.query_selector_all("table tbody tr")
                link = current_rows[i].query_selector("td a")
                
                if link:
                    p_id = link.inner_text().strip().replace("/", "_")
                    print(f"  [+] ({i+1}/{len(rows)}) Đang xử lý bài: {p_id}")
                    link.click()
                    
                    try:
                        # Đợi đề bài load xong
                        page.wait_for_selector(".question-content, .card-body, h3", timeout=20000)
                        time.sleep(3) # Cho phép công thức toán học load hết

                        # --- CHỤP BẢN 1: KỶ NIỆM (NGUYÊN BẢN) ---
                        page.screenshot(path=f"{DIR_KY_NIEM}/{p_id}_full.png", full_page=True)
                        print("      => Đã lưu bản Kỷ niệm.")

                        # --- BƯỚC "HỦY DIỆT" PHẦN LỊCH SỬ ---
                        # Chúng ta sẽ tìm thẻ chứa chữ "Lịch sử" và xóa nó cùng toàn bộ các thẻ sau nó
                        page.evaluate("""
                            const findAndDestroy = () => {
                                // 1. Tìm tất cả các tiêu đề h3, h4, h5 trên trang
                                const headers = Array.from(document.querySelectorAll('h3, h4, h5'));
                                // 2. Tìm đúng cái tiêu đề có chữ "Lịch sử"
                                const historyHeader = headers.find(el => el.textContent.includes('Lịch sử'));
                                
                                if (historyHeader) {
                                    // Tìm cái "Card" hoặc "Container" chứa cái tiêu đề này
                                    let container = historyHeader.closest('.card') || historyHeader.parentElement;
                                    
                                    if (container) {
                                        // Xóa sạch các phần tử đứng sau container này (thường là footer, v.v.)
                                        let next = container.nextElementSibling;
                                        while (next) {
                                            let toDelete = next;
                                            next = next.nextElementSibling;
                                            toDelete.remove();
                                        }
                                        // Cuối cùng là xóa chính cái container chứa Lịch sử
                                        container.remove();
                                    }
                                }
                                // Xóa nốt cái Footer nếu còn sót
                                const footer = document.querySelector('footer');
                                if (footer) footer.remove();
                                
                                // Xóa luôn nút "Nộp bài" và các trình chọn ngôn ngữ cho ảnh nó 'sạch' hẳn
                                const submitArea = document.querySelector('.card:has(button[type="submit"]), .form-group');
                                if (submitArea) submitArea.remove();
                            };
                            findAndDestroy();
                        """)
                        time.sleep(1) # Đợi layout co lại sau khi xóa

                        # --- CHỤP BẢN 2: ÔN TẬP (CHỈ CÒN ĐỀ) ---
                        page.screenshot(path=f"{DIR_ON_TAP}/{p_id}_clean.png", full_page=True)
                        print("      => Đã lưu bản Ôn tập sạch sẽ.")

                    except Exception as e:
                        print(f"      [!] Lỗi bài {p_id}: {e}")
                    
                    # Quay lại danh sách
                    page.go_back(wait_until="networkidle")
                    page.wait_for_selector("table tbody tr")

            # Chuyển trang
            next_btn = page.query_selector("li.page-item.next:not(.disabled) a, a[aria-label='Next »']")
            if next_btn:
                next_btn.click()
                time.sleep(4)
                page_idx += 1
            else:
                break

        browser.close()
        print("\n>>> HOÀN TẤT! Hãy kiểm tra 2 thư mục để thấy sự khác biệt.")

if __name__ == "__main__":
    run()