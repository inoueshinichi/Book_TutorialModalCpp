#include "../all.hpp"
#include "allocator.hpp"

// 明示的なデストラクタ呼び出しをする関数テンプレート
template <class T>
void destroy_at(T* location)
{
    location->~T();
}
// 標準ライブラリにはstd::destroy_at()がある。
// これらをひっくるめたアロケータを使うためのライブラリであるallocator_traitsがある.

int main(int, char**)
{
    // std::allocator<T>の使い方
    // allocate(n)はT型のn個の配列を構築できるだけの生のメモリーを確保して、その先頭へのポインタを返す.
    // deallocate(p,n)はallocate(n)で確保されたメモリーを解放する.
    {
        std::allocator<std::string> a;
        // 生のメモリー確保
        // std::string [1]分のメモリーサイズ
        std::string* p = a.allocate(1);
        // メモリ解放
        a.deallocate(p,1);

        // 確保されるのは生メモリなので実際のT型として
        // 利用するには、new(p) 初期化子が必要
        p = a.allocate(1);
        // 構築
        std::string* s = new(p) std::string("hello");
        // 明示的なデストラクタ
        s->~basic_string(); // 明示的なデストラクタは本来のクラス名を記述する必要がある.
        // // 破棄
        // destroy_at(s);
        // メモリ解放
        a.deallocate(p,1);

        // 標準ライブラリにはstd::destroy_at()がある。
        // これらをひっくるめたアロケータを使うためのライブラリであるallocator_traitsがある.
    }


    // std::allocator_traits<Alloc>
    // std::allocator_traits<Alloc>はアロケータAllocを簡単に使うためのライブラリ.
    // allocator_traits<Alloc>はアロケータの型Allocを指定して使う。
    {
        // std::allocator<int> a;
        // int* p = a.allocate(1);
        // 上記を下記で書ける.
        std::allocator<int> a;
        int* p = std::allocator_traits<std::allocator<int>>::allocate(a,1);
        std::allocator_traits<std::allocator<int>>::deallocate(a, p, 1);
        // 上記では書きづらいのでエイリアスを使う
        using traits = std::allocator_traits<std::allocator<int>>;
        int* p2 = traits::allocate(a, 1);
        // int* pp = new (p2) int{0};
        // pp->~int();
        traits::deallocate(a, p2, 1);
        // まだ書きづらいのでdecltype(expr)を使う
        // int型
        decltype(0) b;
        // double型
        decltype(0.0) c;
        // int型
        decltype(1 + 1) d;
        // std::string型
        decltype("hello"s) e;
    }

    // 記述しやすさ重視
    {
        std::allocator<std::string> a;
        // allocator_traints型
        using traits = std::allocator_traits<decltype(a)>;

        // 生のメモリ確保
        std::string* p = traits::allocate(a,1); // void* p = ::operator new(sizeof(std::string) * 1);
        // 構築
        traits::construct(a, p, "Hello"); // new(p) std::string("Hello");
        // 破棄
        traits::destroy(a, p); // s->~basic_string();, std::destroy_at(s);
        // メモリ解放
        traits::deallocate(a,p,1); // ::operator delete(p);
    }

    // std::allocatorによるN個の配列の生成と解放
    {
        size_t N = 10;
        std::allocator<std::string> a;
        using traits = std::allocator_traits<decltype(a)>;

        // 10個分の生メモリを確保
        std::string* p = traits::allocate(a, N);

        // 10回構築を繰り返す
        for (auto i = p, last = p + N; i != last; ++i)
        {
            traits::construct(a, i, "Hello");
        }

        // 破棄も10回行う
        for (auto i = p + N, first = p; i != first; --i)
        {
            traits::destroy(a, i);
        }

        // 10個分の生メモリを解放
        traits::deallocate(a, p, N);
    }
}