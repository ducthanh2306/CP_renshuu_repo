import time, os, re
from playwright.sync_api import sync_playwright

# Thư mục lưu riêng cho trang 4
ROOT_DIR = "PTIT_Trang_4_Clean"
os.makedirs(ROOT_DIR, exist_ok=True)

def clean_name(name): 
    return re.sub(r'[\\/*?:"<>|]', "", name).strip()

def run():
    with sync_playwright() as p:
        # Giữ slow_mo=500 để tốc độ mượt mà nhưng không lỗi trang trắng
        browser = p.chromium.launch(headless=False, slow_mo=500)
        context = browser.new_context(viewport={'width': 1366, 'height': 1200})
        page = context.new_page()

        print(">>> BƯỚC 1: Đang mở trang chủ...")
        page.goto("https://code.ptit.edu.vn/student/question", wait_until="networkidle")
        
        print(">>> HÀNH ĐỘNG: Đăng nhập -> Chọn môn học -> Đợi bảng hiện ra.")
        page.wait_for_selector("table tbody tr", timeout=0)
        time.sleep(1.5)

        # NHẢY THẲNG ĐẾN TRANG 4 THEO GỢI Ý URL
        target_url = "https://code.ptit.edu.vn/student/question?page=4"
        print(f"\n--- [MỤC TIÊU] ĐIỀU HƯỚNG TRỰC TIẾP TỚI TRANG 4 ---")
        page.goto(target_url, wait_until="networkidle")
        
        # Đợi dữ liệu bảng của trang 4 load xong
        page.wait_for_selector("table tbody tr td a", timeout=15000)
        time.sleep(2) 

        # Quét danh sách dòng
        rows = page.query_selector_all("table tbody tr")
        num_rows = len(rows)
        print(f">>> Tìm thấy {num_rows} dòng. Đang lọc bỏ các mục Bài giảng...")

        for i in range(num_rows):
            # Lấy lại danh sách để tránh lỗi Stale Element
            current_rows = page.query_selector_all("table tbody tr")
            row = current_rows[i]
            
            # Kiểm tra an toàn để tránh lỗi AttributeError
            link_el = row.query_selector("td a")
            if not link_el:
                continue 
            
            p_id = link_el.inner_text().strip()
            # Bỏ qua các tiêu đề Chương/Bài giảng
            if "CHƯƠNG" in p_id or "Bài giảng" in p_id:
                continue

            try:
                cols = row.query_selector_all("td")
                topic_text = cols[4].inner_text().strip() if len(cols) > 4 else "Chung"
                topic_folder = clean_name(topic_text)

                print(f"  [+] ({i+1}/{num_rows}) Đang chụp bài: {p_id}")
                
                # Mở bài tập
                link_el.click()
                page.wait_for_selector(".question-content, .card-body", timeout=15000)
                time.sleep(1)

                # DỌN DẸP NỘI DUNG (Xóa Lịch sử & Nút nộp bài)
                page.evaluate("""
                    const keywords = ['Lịch sử', 'Bài giảng'];
                    document.querySelectorAll('h3, h4, .card, footer, .breadcrumb, button, .form-group').forEach(el => {
                        if(keywords.some(k => el.innerText.includes(k)) || el.tagName === 'FOOTER') {
                            let next = el.nextElementSibling;
                            while(next) { let t = next; next = next.nextElementSibling; t.remove(); }
                            el.remove();
                        }
                    });
                """)
                
                # Lưu vào folder theo chủ đề con
                save_path = os.path.join(ROOT_DIR, topic_folder)
                os.makedirs(save_path, exist_ok=True)
                page.screenshot(path=os.path.join(save_path, f"{p_id}.png"), full_page=True)
                
                # Quay lại danh sách trang 4
                page.go_back(wait_until="networkidle")
                page.wait_for_selector("table tbody tr", timeout=15000)
                
            except Exception:
                continue

        print("\n>>> CHÚC MỪNG! ĐÃ HOÀN THÀNH TOÀN BỘ TRANG 4.")
        browser.close()

if __name__ == "__main__":
    run()