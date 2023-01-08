
# [goChuViet](https://github.com/thuongshoo/GoChuViet)
### [Download bản mới nhất](https://github.com/thuongshoo/thuongshoo.github.io/releases/latest)
[![GitHub release](https://img.shields.io/github/v/release/tuyenvm/goChuViet.svg)](https://github.com/thuongshoo/GoChuViet/releases/latest)

Bộ gõ tiếng Việt không bị lỗi gạch chân khó chịu. Hoàn toàn miễn phí và là nguồn mở, luôn cập nhật và phát triển.

### Mã nguồn của ứng dụng được công khai dưới giấy phép GPL. Điều này nghĩa là bạn hoàn toàn có thể tải mã nguồn về tự build, cải tiến theo mục đích của bạn. Nếu bạn tái phân phối bản cải tiến của bạn, thì nó cũng phải là mã nguồn mở.

### Lưu ý, khi sử dụng goChuViet, bạn nên tắt hẳn bộ gõ khác vì 2 chương trình bộ gõ sẽ xung đột nhau, dẫn đến thao tác không chính xác.

![Giao diện](https://raw.githubusercontent.com/thuongshoo/thuongshoo.github.io/main/images/screenshot1.png "Main UI")
![Giao diện](https://raw.githubusercontent.com/thuongshoo/thuongshoo.github.io/main/images/screenshot2.png "Main UI")
![Giao diện](https://raw.githubusercontent.com/thuongshoo/thuongshoo.github.io/main/images/screenshot3.png "Main UI")

* Tính năng hay nhất:
	* Gõ tắt phụ âm đầu: f->ph, j->gi, w->qu
	* Gõ tắt phụ âm cuối: g->ng, h->nh, k->ch
	* Gõ nhanh (cc=ch, gg=gi, kk=kh, nn=ng, qq=qu, pp=ph, tt=th)
  * Viết Hoa chữ cái đầu câu ( sau dấu . ? ! và đầu hàng )
  * Loại trừ ứng dụng thông minh
	* Tự ghi nhớ bảng mã theo ứng dụng	
	* Gõ tắt và công cụ soạn gõ tắt.
	* Chuyển mã với nhiều tùy chọn.
 
## Hỗ trợ kiểu gõ
- Telex
- VNI
- Simple Telex

## Bảng mã thông dụng:
- Unicode (Unicode dựng sẵn).
- TCVN3 (ABC).
- VNI Windows.
- Unicode Compound (Unicode tổ hợp).
- Vietnamese Locale CP 1258.
- ...

## Tính năng:
- **Modern orthography** (On/Off) - Đặt dấu oà, uý thay vì òa, úy.
- **Quick Telex** (On/Off) - Gõ nhanh (cc=ch, gg=gi, kk=kh, nn=ng, qq=qu, pp=ph, tt=th).
- **Grammar check** (On/Off) - Kiểm tra ngữ pháp.
- **Spelling check** (On/Off) - Kiểm tra chính tả.
- **Restore key if invalid word** (on/off) - Phục hồi phím với từ sai.
- **Run on startup** (On/Off) - Chạy cùng macOS.
- **Gray menu bar icon** (On/Off) - Biểu tượng xám trên thanh menu phù hợp với chế độ Dark mode.
- **Switch input mode by shortcut key** - Đổi chế độ gõ bằng phím tắt tùy chọn.
- **Autocorrect fixed** (On/Off) - Sửa lỗi autocorrect trên trình duyệt như Chrome, Safari, Firefox, Microsoft Excel.
- **Underline issue fixed on macOS** (On/Off) - Sửa lỗi gạch chân trên macOS.
- **Tạm tắt kiểm tra chính tả bằng phím Ctrl** (On/Off) (Bản 1.5 về sau).
- **Tạm tắt goChuViet bằng phím Cmd/Alt** (On/Off) (Bản 2.0.1 về sau).
- **Cho phép dùng f z w j làm phụ âm đầu** (On/Off) (Bản 1.5 về sau).
- **Gõ tắt phụ âm đầu: f->ph, j->gi, w->qu** (On/Off) (Bản 1.6 về sau).
- **Gõ tắt phụ âm cuối: g->ng, h->nh, k->ch** (On/Off) (Bản 1.6 về sau).
- **Hiện biểu tượng trên thanh Dock** (On/Off) (Bản 2.0.1 về sau). Bấm vào icon trên thanh Dock sẽ mở nhanh Bảng điều khiển.
- **Macro** - Tính năng gõ tắt vô cùng tiện lợi. Gõ tắt của macOS chỉ hỗ trợ 20 ký tự, còn goChuViet không giới hạn ký tự.
- **Chuyển chế độ thông minh:** (On/Off) (Bản 1.2 về sau) - Bạn đang dùng chế độ gõ Tiếng Việt trên ứng dụng A, bạn chuyển qua ứng dụng B trước đó bạn dùng chế độ gõ Tiếng Anh, goChuViet sẽ tự động chuyển qua chế độ gõ Tiếng Anh cho bạn, khi bạn quay lại ứng dụng A, goChuViet tất nhiên sẽ chuyển lại chế độ gõ tiếng Việt, rất cơ động.
- **Viết Hoa chữ cái đầu câu** (On/Off) (Bản 1.2 về sau) - Khi gõ văn bản dài, đôi khi bạn quên ghi hoa chữ cái đầu câu khi kết thúc một câu hoặc khi xuống hàng, tính năng này sẽ tự ghi hoa chữ cái đầu câu cho bạn, thật tuyệt vời.
- **Chế độ “Gửi từng phím”:** (On/Off) (Bản 1.1 về sau) mặc định dùng kỹ thuật mới gửi dữ liệu 1 lần thay vì gửi nhiều lần cho chuỗi ký tự, nên nếu có ứng dụng nào không tương thích, hãy bật tính năng này lên, mặc định thì nên tắt vì kỹ thuật mới sẽ chạy nhanh hơn.
- **Cập nhật tự động:** (Bản 1.3 về sau) tính năng hỗ trợ cập nhật phiên bản goChuViet mới nhất mỗi khi mở goChuViet hoặc tự check trong phần mục Giới thiệu.
- **Công cụ chuyển mã:** (Bản 1.4 về sau) hỗ trợ chuyển mã qua lại văn bản, thích hợp cho việc chuyển đổi văn bản cũ viết bằng VNI, TCVN3 qua Unicode,... Hỗ trợ cấu hình phím tắt chuyển mã nhanh, bảng cấu hình tùy chọn chuyển mã.
- **Tự ghi nhớ bảng mã theo ứng dụng:** (Bản 2.0.1 về sau) Phù hợp cho các bạn dùng Photoshop, CAD,... với các bảng mã VNI, TCVN3. goChuViet tự ghi nhớ ứng dụng nào dùng bảng mã nào để lần sau sử dụng Photoshop, CAD,... goChuViet có thể tự chuyển sang bảng mã đó.
- ...

## Tác giả
- thuongshoo.
- Mọi góp ý, gửi cho mình qua yuyoonshoo@gmail.com  
- Fanpage: [https://www.facebook.com/Dochoingonbore/)

## Liên kết
- [goChuViet cho Windows, xem chi tiết tại đây](https://github.com/thuongshoo/GoChuViet/tree/master/Sources/goChuViet/win32)
- [goChuViet cho Linux (đang phát triển)](https://github.com/thuongshoo/GoChuViet/tree/master/Sources/goChuViet/linux)
## Một điều nhỏ nhoi
Đừng quên ủng hộ:  
 ^^](https://paypal.me/lehoaithanh)  
Hoặc trực tiếp qua ví momo:   
![Donate by momo](https://github.com/thuongshoo/thuongshoo.github.io/blob/main/images/momo_thuongshoo.jpg "Momo").   

Cảm ơn các bạn rất nhiều.
