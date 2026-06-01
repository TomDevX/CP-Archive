#include <iostream>
#include <array>

using namespace std;

constexpr int N = 10;

// Khởi tạo std::array tại compile-time bằng Lambda gọi ngay lập tức ()
constexpr std::array<int, N> cnt = []() {
    std::array<int, N> temp{}; // Khởi tạo mảng tạm bằng 0
    for (int i = 0; i < N; ++i) {
        temp[i] = i * 2; // Logic tính toán tùy ý (Ví dụ: x2)
    }
    return temp; // Bắt buộc phải return mảng tạm này
}(); // Cặp dấu () ở đây để thực thi Lambda ngay lập tức lúc dịch code

int main() {
    // Truy cập mượt mà như mảng thường, tốc độ O(1) ở Runtime
    cout << cnt[5] << '\n'; // In ra 10
    cout << cnt[8] << '\n'; // In ra 16
    return 0;
}