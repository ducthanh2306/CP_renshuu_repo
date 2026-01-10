import time, os, re
from playwright.sync_api import sync_playwright

# Cấu hình thư mục lưu trữ
ROOT_ON_TAP = "PTIT_OnTap_Trang_2_3_4"
os.makedirs(ROOT_ON_TAP, exist_ok=True)

def clean_name(name): 
    """Dọn dẹp tên thư mục để tránh lỗi Windows"""
    return re.sub(r'[\\/*?:"<>|]', "", name).strip()

def run():
    with sync_playwright() as p:
        # slow_mo để đảm bảo các thao tác render kịp
        browser = p.chromium.launch(headless=False, slow_mo=800)
        context = browser.new_context(viewport={'width': 1366, 'height': 1200})
        page = context.new_page()

        # BƯỚC 1: Đăng nhập
        print(">>> BƯỚC 1: Đang mở trang đăng nhập...")
        page.goto("https://code.ptit.edu.vn/student/question", wait_until="networkidle")
        
        print(">>> HÀNH ĐỘNG: Bạn hãy Đăng nhập và CHỌN MÔN HỌC (ví dụ DSA).")
        print(">>> Sau khi bảng bài tập hiện ra, Script sẽ tự nhảy trang.")
        page.wait_for_selector("table tbody tr td a", timeout=0)
        time.sleep(2)

        # DANH SÁCH CÁC TRANG CẦN CHỤP
        target_pages = [2, 3, 4]

        for current_page in target_pages:
            # ĐIỀU HƯỚNG TRỰC TIẾP QUA URL (Gợi ý của bạn)
            target_url = f"https://code.ptit.edu.vn/student/question?page={current_page}"
            print(f"\n--- [TIẾN ĐỘ] NHẢY THẲNG TỚI: {target_url} ---")
            
            page.goto(target_url, wait_until="networkidle")
            # Đảm bảo bảng dữ liệu của trang mới đã hiện ra
            page.wait_for_selector("table tbody tr td a", timeout=15000)
            time.sleep(2) 

            # Lấy danh sách bài tập của trang này
            rows = page.query_selector_all("table tbody tr")
            num_rows = len(rows)
            print(f">>> Trang {current_page} có {num_rows} bài tập.")

            for i in range(num_rows):
                # Lấy lại danh sách dòng để tránh Stale Element
                current_rows = page.query_selector_all("table tbody tr")
                cols = current_rows[i].query_selector_all("td")
                
                if len(cols) < 2: continue
                
                link_el = cols[1].query_selector("a")
                p_id = link_el.inner_text().strip()
                # Cột 5 là Chủ đề con
                topic_folder = clean_name(cols[4].inner_text().strip()) if len(cols) > 4 else "Chung"

                print(f"  [+] ({i+1}/{num_rows}) Đang xử lý: {p_id}")
                
                # Mở đề bài
                link_el.click()
                
                try:
                    # Đợi nội dung đề bài hiện ra
                    page.wait_for_selector(".question-content, .card-body", timeout=15000)
                    time.sleep(1.5)

                    # XÓA PHẦN THỪA (Lịch sử, Bài giảng, Chân trang)
                    page.evaluate("""
                        const keywords = ['Lịch sử', 'Bài giảng'];
                        document.querySelectorAll('h3, h4, .card, footer, .breadcrumb').forEach(el => {
                            const hasKeyword = keywords.some(k => el.innerText.includes(k));
                            if(hasKeyword || el.tagName === 'FOOTER') {
                                let next = el.nextElementSibling;
                                while(next) { let t = next; next = next.nextElementSibling; t.remove(); }
                                el.remove();
                            }
                        });
                        // Xóa các nút nộp bài để ảnh 'sạch' hoàn toàn
                        document.querySelectorAll('.form-group, button').forEach(el => {
                            if(el.innerText.includes('Nộp bài')) el.remove();
                        });
                    """)
                    
                    # Tạo folder và chụp ảnh
                    save_path = os.path.join(ROOT_ON_TAP, topic_folder)
                    os.makedirs(save_path, exist_ok=True)
                    page.screenshot(path=os.path.join(save_path, f"{p_id}.png"), full_page=True)
                except:
                    print(f"      [!] Lỗi không chụp được bài {p_id}")
                
                # Quay lại trang danh sách (vẫn ở đúng trang ?page=x)
                page.go_back(wait_until="networkidle")
                page.wait_for_selector("table tbody tr", timeout=15000)

        print("\n>>> HOÀN THÀNH TẤT CẢ! Bạn đã có bộ đề sạch trang 2, 3, 4.")
        browser.close()

if __name__ == "__main__":
    run()