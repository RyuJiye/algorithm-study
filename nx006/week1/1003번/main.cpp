#include <iostream>
#include <vector>
#include <memory>

struct Fibo {
    Fibo(const int x, const int y) :
        count0(x), count1(y) {}
        
    Fibo(const Fibo& rhs) :
        count0(rhs.count0),
        count1(rhs.count1) {}
    
    inline auto operator+(const Fibo& rhs) {
        return Fibo(this->count0 + rhs.count0, this->count1 + rhs.count1);
    }
    
    friend inline std::ostream& operator<<(std::ostream&, const Fibo&);
    
    int count0 = 0;
    int count1 = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Fibo& rhs) {
        os << rhs.count0 << ' ' << rhs.count1;
        return os;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int N = 0;
    std::cin >> N;
    
    for (int i = 0; i < N; i++) {
        std::unique_ptr<Fibo> prev0 = std::make_unique<Fibo>(1, 0); // 0번 인덱스
        std::unique_ptr<Fibo> prev1 = std::make_unique<Fibo>(0, 1); // 1번 인덱스
        int num = 0;
        std::cin >> num;
        
        for (int j = 0; j < num; j++){
            auto temp = *prev0 + *prev1;
            *prev0 = *prev1;
            *prev1 = temp;
        }
        
        std::cout << *prev0 << '\n';
    }    
    return 0;
}