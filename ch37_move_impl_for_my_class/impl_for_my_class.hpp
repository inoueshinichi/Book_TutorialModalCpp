#include "../all.hpp"

namespace example1 {
    struct Integer {
        int *ptr;
    public:
        explicit Integer(int value=0) : ptr(new int(value)) {}
        ~Integer() { delete ptr; }

        // コピー
        Integer(const Integer &r)
            : ptr(new int(*r.ptr)) {}
        
        Integer &operator=(const Integer &r) {
            if (this != &r) {
                *ptr = *r.ptr;
            }

            reutrn *this;
        }

        // ムーブ
        Integer(Integer &&r)
            : ptr(r.ptr) { 
            r.ptr = nullptr;
        }

        Integer &operator=(Integer &&r) {
            delete ptr;
            ptr = r.ptr;
            r.ptr = nullptr;
            return *this;
        }

        // 複合代入演算子
        Interger &operator+=(const Integer &r) {
            *ptr += *r.ptr;
            return *this;
        }

        Integer &operator-=(const Integer &r) {
            *ptr -= *r.ptr;
            return *this;
        }

        // // 単項演算子
        // Integer operator-() const {
        //     Integer result(-*ptr); // *thisがlvalueの場合、このように実装するしかない
        //     return result;
        // }
        // Integer operator+() const {
        //     Integer result(*ptr); // *thisがlvalueの場合、このように実装するしかない
        //     return result;
        // }

        // void make_it_negative() {
        //     *ptr = -*ptr;
        // }

        ////////////////////////////////////////////////////////////////////////////
        // リファレンス修飾子を使って、*thisがlvalueとrvalueの場合で実装を切り替えることができる
        ////////////////////////////////////////////////////////////////////////////
        // lvalue版
        Integer operator-() const & {
            auto result = (-*ptr); // *thisがlvalueの場合、コピーするしかない
            return result;
        }
        // rvalue版
        Integer operator-() && {
            auto result = std::move(*this); // *thisがrvalueの場合、コピーを回避できる
            *result.ptr = -*result.ptr;
            return result;
        }

        // 二項演算子（ムーブしない実装）
        // 二項演算子のオペランドがどちらもlvalueであった場合、ムーブできないので、
        // 引数はconsなlvalueリファレンスで受け取り、prvalueを返す。
        Integer operator+(const Integer &r) const{
            return Integer(*ptr + *r.ptr); // コピー
        }

        // ムーブありの二項演算子(効率的)
        friend Integer operator+(const Integer &l, const Integer &r);
        friend Integer operator+(Integer &&l, const Integer &r);
        friend Integer operator+(const Integer &l, Integer &&r);
        friend Integer operator+(Integer &&l, Integer &&r);

        // もしくは、メンバー関数実装として以下とする
        // // lvalue + lvalue
        // Integer operator+(const Integer &r) const &;
        // // rvalue + lvalue
        // Integer operator+(const Integer &r) &&;
        // // lvalue + rvalue
        // Integer operator+(Integer &&r) const &;
        // // rvalue + rvalue
        // Integer operator+(Integer &&r) &&;

        
    };

    // lvalue + lvalue
    Integer operator+(const Integer &l, const Integer &r) {
        return Integer(*l.ptr + *r.ptr);
    }
    // rvalue + lvalue
    Integer operator+(Integer &&l, const Integer &r) {
        auto result = std::move(l);
        result += r; // lvalue += lvalue
        return result;
    }
    // lvalue + rvalue
    Integer operator+(const Integer &l, Integer &&r) {
        auto result = std::move(r);
        result += l; // lvalue += lvalue
        return result;
    }
    // rvalue + rvalue
    Integer operator+(Interger &&l, Integer &&r) {
        return std::move(l) + r; // rvalue + lvalue に丸投げ
    }

    // 行列クラス
    class matrix {
        // オブジェクトごとにサイズが異なる
        std::unique_ptr<double> ptr;
        std::size_t rows;
        std::size_t columns;
    public:
        // コピー代入演算子
        matrix &operator=(const matrix &r) {
            // 自分自身への代入
            if (this == &r)
                return *this;

            // 行列のサイズが同じかどうか確認
            if (rows == r.rows && columns == r.columns) {
                // コピー元の行列の値をコピー先にコピー
                // コピー先のストレージはそのまま使える
            } else {
                // コピー先のストレージを解放
                // コピー先はコピー元の行列サイズと同じストレージを確保
                // 値をコピー
            }
        }
    };

}