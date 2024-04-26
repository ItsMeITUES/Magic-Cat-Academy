# Magic Cat Academy (MCA)
- Cấu trúc code và thử nghiệm game: 
- Gameplay: 

## Giới thiệu 
Game sinh tồn vô hạn với cơ chế nhận dạng hình vẽ cơ bản.

- [0. Cách tải game](#0-cách-tải-game)
- [1. Bắt đầu game](#1-bắt-đầu-game)
- [2. Các thành phần trong game](#2-các-thành-phần-trong-game)
  * [a. Người chơi](#a-người-chơi)
  * [b. Kẻ địch](#b-kẻ-địch)
  * [c. Khác](#c-khác)
- [3. Điều khiển và gameplay](#3-điều-khiển-và-gameplay)
- [4. Một vài hình ảnh trong game](#4-một-vài-hình-ảnh-trong-game)
- [5. Về source code của game](#5-về-source-code-của-game)

## 0. Cách tải game
**Bước 1:** Clone repo này về hoặc chọn Code -> Download Zip

**Bước 2:** Cài codeblocks-20.03mingw

**Bước 3:** Thêm các file SDL2.dll, SDL2_image.dll, SDL2_mixer.dll, SDL2_ttf.dll vào thư mục gốc.

**Bước 4:** Chạy file [MCA.exe](MCA.exe) hoặc mở file [MCA.cbp](MCA.cbp) và chạy game bằng phím F9

## 1. Bắt đầu game

- Màn hình chính:

![image](https://github.com/ItsMeITUES/Magic-Cat-Academy/blob/main/images/MCA%20Screenshots/startMenu.png)

- Click vào nút "Play" hình tròn bên dưới để bắt đầu chơi

## 2. Các thành phần trong game
### a. Người chơi
- Mimo: là chú mèo phép thuật được người chơi điều khiển để đánh bại kẻ địch.
- Sử dụng chuột để vẽ những hình trên đầu những con ma. Tiêu diệt ma để nhận điểm.
- Để ma chạm phải, Mimo sẽ thua.
- "Mimo chỉ có một mạng duy nhất, không như những chú mèo khác, có lẽ do nó đã đánh đổi lấy ma thuật."
### b. Kẻ địch
- Ma thường: loại ma yếu, ít máu, tốc độ nhanh.
- Ma Elite: ma mạnh hơn, nhiều máu hơn, tốc độ chậm hơn.
- Các kẻ địch sẽ trở nên hung hãn hơn, nhiều máu hơn, di chuyển nhanh hơn mỗi khi đồng minh của chúng bị hạ gục.
- "Có lẽ nào bọn ma đến từ Hư Không?"
### c. Khác
- Score: số điểm Mimo đang có.
- Tiêu diệt 2 hoặc nhiều hơn kẻ địch bằng một lần vẽ sẽ tạo thành Combo, cho thêm nhiều điểm hơn.

## 3. Điều khiển và gameplay

- Điều khiển:
  * Mimo đứng im không di chuyển. Bạn sẽ giúp Mimo bằng cách dùng chuột vẽ hình trên đầu những con ma.
  * Mimo sẽ giúp bạn chuyển những hình vẽ thành phép thuật, tiêu diệt những con ma. 
- Về gameplay:
  * Bọn ma sẽ liên tục xuất hiện hòng trêu chọc Mimo. Nhiệm vụ của bạn và Mimo là trụ vững được lâu nhất có thể. 
   
## 4. Một vài hình ảnh trong game
![image](https://github.com/ItsMeITUES/Magic-Cat-Academy/assets/147250056/dd767b5b-b22a-4c71-8402-4e89f1daf84e)
![image](https://github.com/ItsMeITUES/Magic-Cat-Academy/assets/147250056/f45d0938-52e2-49cc-8eae-6c8c1b4b757c)
![image](https://github.com/ItsMeITUES/Magic-Cat-Academy/assets/147250056/3c4a898b-1d37-4956-a49a-b7e64a6e455c)


## 5. Về source code của game
- Các C++ source file:
  * main: file chạy chương trình.
  * animation: xử lí hoạt họa.
  * music: xử lí âm thanh.
  * button: xử lí các nút bấm.
  * enemy: xử lí tất cả tác vụ liên quan đến kẻ địch.
  * shapes: xử lí thông tin các hình vẽ.
  * player: xử lí thông tin của người chơi.
  * score: xử lí điểm, in điểm.
  * recognizer: thuật toán xử lí nhận dạng, khử nhiễu, encode hình vẽ.
  * comparer: so sánh, sủ dụng MLD quyết định hình vẽ được chọn. 
- Folder animation: lưu các spitesheet cho animation
  * blackCat: các spitesheet của Mimo.
- Folder data: lưu các thông số khởi tạo và đường dẫn file
  * shapes.txt: các hình vẽ.
  * enemy.txt: các template kẻ địch.
  * player.txt: các template người chơi (chỉ có Mimo thôi).
- Folder fonts: lưu các phông chữ được sử dụng
- Folder headers: lưu các headers được sử dụng
- Folder images: lưu các hình ảnh của game
  * backGrounds: lưu các màn hình khởi đầu, màn hình chơi, màn hình kết thúc game.
  * buttons: lưu hình ảnh các nút bấm.
  * enemy: lưu hình ảnh kẻ địch.
  * shapes: lưu hình ảnh các hình vẽ.
- Folder music: lưu các file âm thanh của game.
- Folder bin và obj: folder build project của Code::Blocks.
