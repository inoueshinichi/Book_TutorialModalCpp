#include "../all.hpp"


namespace class_pointer {
    struct C
    {
        int data_member;
        void member_function() {}
    };

    struct CC
    {
        int data {};

        // thisポインター
        void set(int n) {
            CC* pointer = this;
            std::printf("CC address: %p\n", pointer);
            this->data = n;
        }

        // constなメンバー関数の中では、thisの型もconstなクラス型へのポインターになる.
        // この理由は、constなメンバー関数はクラスのオブジェクトへの参照として、constなリファレンスを隠し引数としてもつから.
        void f() const 
        {
            // thisの型は const CC*
            const CC* pointer = this;
        }
    };
}


namespace member_pointer {
    struct Object 
    {
        static int static_data_member;

        int data_member;
        void member_function()
        {
            std::cout << "data_member: " << data_member << std::endl;
        }
    };
    int Object::static_data_member = 123;

    struct ABC {
        // int ABC::*
        int x;
        // int ABC::*
        int y;
        // double ABC::*
        double d;
        // int* ABC::*
        int* ptr;
    };

    struct DEF {
        // ABC* DEF::*
        ABC* abc;
    };

    struct C
    {
        int x = 1;
        int y = 2;

        int f(int) { return 0; }
    };

    auto ret_c_ptr(int) -> int C::*
    {
        return &C::x;
    }

    // // std::invoke(f, t1, ...)
    // template <class F, class T1>
    // auto std::invoke(F f, T1 t1)
    // {
    //     return t1.*f;
    // }
}


int main(int, char**)
{
    // クラスへのポインター
    {
        using namespace class_pointer;
        C object;
        C* pointer = &object;

        // // エラー
        // *pointer.data_member = 0;
        // // エラー
        // *pointer.member_function();
        
        // 解釈のされ方：演算子*より演算子.のほうが優先度が高い
        // *(pointer.data_member) = 0;
        // *(pointer.member_function());
        // 
        // 上記は以下のクラスメンバにアクセスする意味になる
        // struct Pointer {
        //  int data = 42;
        //  int* data_member = &data;
        //  int* member_function() {
        //    return &data;    
        //  }   
        // };

        // 演算子*の優先度をあげる
        (*pointer).data_member = 0;
        (*pointer).member_function();

        // リファレンスを使ってポインターを参照した結果をリファレンスに束縛して使える
        C& ref = *pointer;
        ref.data_member = 0;
        ref.member_function();

        // ポインターを介して直接呼べる
        // 演算子->
        pointer->data_member = 0;
        pointer->member_function();
    }

    // thisポインター
    {
        using namespace class_pointer;
        CC a;
        CC b;

        // a.dataを変更
        a.set(1);
        // b.dataを変更
        b.set(2);
    }

    // メンバーへのポインター
    {
        using namespace member_pointer;
        Object object;

        // これはクラスのサブオブジェクトへのポインタ
        int* pointer = &(object.data_member);
        std::printf("pointer of sub-object: %p\n", pointer);
        
        // Object::data_memberメンバーへのポインタ
        int Object::* int_ptr = &Object::data_member; // int* Object::int_ptr = はエラーになる!
        std::printf("member pointer of object: %p\n", int_ptr);

        // Object::static_data_memberクラスメンバーへのポインタ　
        // int Object::* static_int_ptr = &Object::static_data_member;
        // std::printf("static member pointer of object: %p\n", static_int_ptr);

        // Object::member_functionメンバーへのポインタ
        void (Object::* func_ptr)() = &Object::member_function;
        std::printf("member func pointer of object: %p\n", func_ptr);

        // objectに対するメンバーポインターを介した参照
        object.*int_ptr = 123;
        // objectに対するメンバーポインターを介した参照
        (object.*func_ptr)(); // 123

        // 別のオブジェクト
        Object another_object;
        another_object.data_member = 456;
        (another_object.*func_ptr)(); // 456

        /**
         * @brief メンバーポインタの肝心の機能
         * クラスのオブジェクトからは独立したデータメンバーやメンバー関数自体へのポインターを取得する
         */

        /**
         * @brief 文法
         * 型名 クラス名::*
         * T C::*
         */

        /**
         * @brief クラス名Cのメンバー名Mのメンバーへのポインターを得る方法
         * &クラス名::メンバー名
         * &C::M
         */

        // メンバー変数へのポインタ
        int C::* x_ptr = &C::x;
        int C::* y_ptr = &C::y;

        C c_obj;

        // 1
        std::cout << c_obj.*x_ptr << std::endl;
        // 2
        std::cout << c_obj.*y_ptr << std::endl;

        // メンバ関数へのポインタ
        int (C::*ptr)(int) = &C::f;

        std::cout << (c_obj.*ptr)(123) << std::endl;

        
        // 演算子の優先順位を考慮しないと
        c_obj.*ret_c_ptr(123);

        auto c_data_ptr = &C::x;
        auto c_obj_ptr = &c_obj;
        c_obj_ptr->*c_data_ptr = 123; // x = 123

        // std::cout << std::invoke(ptr, c_obj)(678) << std::endl;
        // std::cout << std::invoke(ptr, c_obj_ptr)(678) << std::endl;

        std::invoke(c_data_ptr, c_obj_ptr) = 123; // x = 123
        std::invoke(c_data_ptr, c_obj) = 456; // x = 456
        std::cout << std::invoke(ptr, c_obj, 789) << std::endl; // f(789) -> 0

    }

    return 0;
}