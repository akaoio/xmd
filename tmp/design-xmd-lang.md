Tôi muốn ngôn ngữ xmd do tôi thiết kế nó kiểu này:

Nó hiểu được dạng file .md:
Hỗ trợ cả code block html comment : <!-- xmd -->, <!-- XMD -->, <!-- xmd
...
...
...
--->

Hỗ trợ cả loại code block tiêu chuẩn ```xmd ...```, ```XMD ```, ```xmd
...
...
...
```


```xmd
// Comment dạng 1 dòng cũng có
/*
Comment dạng này cũng có
*/
set text "hello world" // Hỗ trợ cả comment
print text

function say_hi name
    set text hi {{name}}, how are you
    print text

say_hi

class Person
    constructor props
        set self.name props.name
        set self.age props.age
    work what where
        set text {{self.name}} is working on {{what}} at {{where}}
        print text
        return text
    whatsgoingon
        return self.work "IT" "Hanoi"

set alice Person "Alice" 30

alice.whatsgoingon
alice.work "UI" "IT department"

set arr [1..10]
for num in arr
    print "Number is " + num
    
set max 10
for num in 1..10
    print num


for item in ["one", "two", "three"]
    print item
```

Nó cũng hiểu được dạng file .xmd. Trong dạng file xmd thì mã nguồn xmd có thể viết trần trụi, không cần code block. Nhưng sẽ có block cho markdown là ```markdown ....``` và ```md .....``` --> có thể dịch sang dạng file .md được. Bằng lệnh "xmd transpile <src> <dist>" -> xmd tự biết đuôi file và định dạng file để transpile đối xứng gương, ví dụ file là .md thì sẽ chuyển sang .xmd, và ngược lại.

Đây chỉ là demo do tôi viết vội. Lý do sinh ngôn ngữ xmd là vì ngày nay mọi người dùng điện thoại chứ không thích dùng máy tính nữa. Các IDE cũng phải chuyển dần sang điện thoại, mobile responsive.
XMD được thiết kế để tối ưu việc bấm trên màn hình điện thoại. Các bàn phím trên điện thoại rất tối giản -> gõ các ký tự lập trình như js rất mất thời gian. Ví dụ JS function thì có { }, nhiều khi file dài, quên mở hoặc đóng phải đi tìm rất mệt. Tôi gõ đoạn code trên hơi vội nên có thể nhiều chỗ không hợp lý.

Hãy giúp tôi phác thảo tiếp để có các tính năng phức tạp hơn:
Phải mạnh hơn JS
Phải gọn hơn python
Phải deep như Rust
Phải dễ như scratch code của học sinh -> ngu nhất thế giới cũng học được
Phải cực mạnh để đủ chạy chứng minh định lý Godel -> biến xmd + markdown thành công cụ nghiên cứu dành cho các nhà khoa học
Biến tự khai báo, gọi ra dùng là nó tự nhận biết



==> Phác thảo code vào blueprint/prototype.md rồi cùng thảo luận tiếp.