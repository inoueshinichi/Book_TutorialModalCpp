#include "../all.hpp"

// 動的確保したメモリをT型の値として使う
template <class T>
void dynamic_allocate()
{
    // 1. その型のサイズ分のメモリを確保する
    void* ptr = ::operator new (sizeof(T));
    // 2. ポインタを型変換
    T* T_ptr = static_cast<T*>(ptr);
    // 3. 適切な値を代入
    *T_ptr = T{};
    ::operator delete (ptr);
}

struct Logger
{
    std::string name;
    Logger(std::string name)
        : name(name) {
            std::cout << name << " is constructed. \n";
        }
    
    ~Logger() {
        std::cout << name << " is destructed.\n";
    }
};


int main(int, char**)
{
    // void* malloc(std::size_t size);
    // void free(void* ptr);
    {
        // 5バイトのメモリーを確保
        void* ptr = std::malloc(5);
        // 解放
        std::free(ptr);
        // これ以降、ptrは無効
    }

    // void* operator new(std::size_t size);
    // void operator delete(void* ptr);
    {
        void* ptr = ::operator new(5);
        ::operator delete(ptr);
    }

    // 生のバイト列を基本的な型の値として使う方法
    {
        // 確保
        void* void_ptr = ::operator new(sizeof(int));
        // 型変換
        int* int_ptr = static_cast<int*>(void_ptr);
        int& int_ref = *int_ptr; // リファレンスを使ってもよい
        // 代入
        *int_ptr = 0;
        // 解放
        ::operator delete(void_ptr);
    }

    // mallocやoperator newが返すメモリの値は不定なので、
    // 確保した生のメモリへのポインタを実際に使う型のポインタに型変換して
    // その値を参照しようとすると、結果は未定義
    {
        // ここまでは定義された挙動
        int* ptr = static_cast<int*>(::operator new(sizeof(int)));
        // 未定義の挙動
        std::cout << *ptr << std::endl;
    }


    // メモリ確保の失敗
    {
        // mallocが失敗すると、nullptrが返される。
        void* ptr = std::malloc(1);
        if (ptr == nullptr) {
            // メモリ確保失敗
            std::abort();
        } else {
            // メモリ確保成功
        }

        // operator newが失敗すると、std::bad_alloc例外が投げられる
        try {
            void* ptr = ::operator new(1);
            // メモリ確保成功
        } catch (std::bad_alloc e)
        {
            // メモリ確保失敗
        }
    }
    // 例外の場合、catchしなければプログラムが終了する.


    // クラス型の値の構築
    {
        // この方法は、殆どのクラスには使えない
        dynamic_allocate<int>();
        dynamic_allocate<double>();

        // エラー
        // dynamic_allocate<std::vector<int>>(); // 実行時エラー

        // 生のメモリ上にクラスのような複雑な型を構築するには、newプレイスメントを使う.
        // new (生のポインタ) 型 new 初期化子
        // new初期化子：()or{}で囲んだコンストラクタへの引数. 引数がない場合、省略できる.
        // e.g std::vector<T>
        //  生のメモリーを動的確保
        void* ptr = ::operator new ( sizeof(std::vector<int>) );
        // 生のメモリー上に型を構築
        std::vector<int>* vector_ptr = new (ptr) std::vector<int>{};
        vector_ptr->~vector();
        ::operator delete (ptr);
        ptr = nullptr;

        // newプレイスメントを使用すると適切にクラスのコンストラクタが呼ばれる
        ptr = ::operator new (sizeof(Logger));
        // 構築
        Logger* logger_ptr = new(ptr) Logger("Allice");
        // デストラクタの明示的な呼び出し
        logger_ptr->~Logger();
        // 破棄
        ::operator delete(ptr);
    }

}