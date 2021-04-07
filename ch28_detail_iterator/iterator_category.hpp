#include "../all.hpp"

/**
 * @brief イテレータカテゴリー
 * 入力イテレータ(Input Iterator)
 * 出力イテレータ(Output Iterator)
 * 前方イテレータ(Forward Iterator)
 * 双方向イテレータ(Bidirectional Iterator)
 * ランダムアクセスイテレータ(Random Access Iterator)
 */


// ランダムアクセスイテレータ
namespace random_access_iterator_ns 
{

    // nの型が符号付き整数型でよい
    template <class RandomAccessIterator>
    void f1(RandomAccessIterator i, int n)
    {
        i + n;
        i - n;
        n + i; // (i+n)と同じ
        n - i; // (n-i)と同じ

        i + (-n); // (i-n)と同じ

        i += n; // i=i+nと同じ
        i -= n; // i=i-nと同じ
    }

    // イテレータ間の距離を計算したいときは、イテレータ同士を引き算する
    template <class RandomAccessIterator>
    void f2(RandomAccessIterator a, RandomAccessIterator b)
    {
        b - a; // aからbまでの距離
        a - b; // aからbまでの距離
    }

    // イテレータ間の距離は負数にもなる
    template <class RandomAccessIterator>
    void f3(RandomAccessIterator a)
    {
        auto b = a;
        // bはaより3進んでいる
        ++b; ++b; ++b;
        b - a; // +3
        a - b; // -3
    }

    // イテレータiのn個先を参照したい場合
    template <class RandomAccessIterator>
    void f4(RandomAccessIterator i, std::size_t n)
    {
        // *(i + n)
        i[n];
    }

    // ランダムアクセスイテレータは大小比較ができる
    template <class RandomAccessIterator>
    void f5(RandomAccessIterator i, RandomAccessIterator j)
    {
        i < j;
        i > j;
        i <= j;
        i >= j;
    }

    // イテレータの比較は、イテレータが参照する値の比較ではなく、
    // イテレータが参照する要素の順番の比較.
    template <class Iterator>
    void f6(Iterator i) 
    {
        // jはn+i番目を指す
        auto j = i + 1;

        i < j; // true
        i > j; // false
    }

    // 双方向イテレータ以下のイテレータができる比較は、同値比較だけ。
    template <class Iterator>
    void f7(Iterator i, Iterator j) 
    {
        i == j;
        i != j;
    }

    // イテレータは同じn番目の要素を指しているときに等しいと比較される
    template <class Iterator>
    void f8(Iterator i )
    {
        auto j = i;
        i == j; // true
        ++j;
        i == j; // false
    }
}


// 双方向イテレータ
namespace bidirectional_iterator_ns
{
    // n番目の要素に対して、n-1番目、n+1番目の要素を参照できる
    template <class BidirectionalIterator>
    void f9(BidirectionalIterator i) 
    {
        ++i; // i+1
        --i; // i-1

        // r1, r2は変更する前のiの値
        auto r1 = i++;
        auto r2 = i--;
    }

    // n個進める方法
    // 双方向イテレータが提供される場合、ランダムアクセスが技術的に可能ではあるが、非効率的な場合.
    // e.g リンクリスト
    template <class BidirectionalIterator>
    void nth_next(BidirectionalIterator iter, std::size_t n)
    {
        for (std::size_t i = 0; i != n; ++i)
        {
            ++iter;
        }
        return iter;
    }
}



// 前方イテレータ
namespace forward_iterator_ns
{
    // 前方イテレータは前にしか進めない
    template <class ForwardIterator>
    void f10(ForwardIterator i)
    {
        ++i;
    }

    // 前方イテレータにはマルチパス保証がある.
    // イテレータの指す要素を動かす前のイテレータの値を保持しておき、
    // 保持した値を動かしたとき、2つのイテレータは同一の値を指す.
    template <class ForwardIterator>
    void f11(ForwardIterator i)
    {
        // 動かす前の値を保持
        auto prev = i;
        // 次の要素を指す
        ++i;
        // 動かす前の値も次の要素を指すようにする
        ++prev;

        // true
        bool b = (i == prev);

        // r1, r2は同じ要素を指す
        auto& r1 = *i;
        auto& r2 = *prev;
    }
}



// 入力イテレータ
namespace input_iterator_ns
{
    // 入力イテレータは、イテレータの比較、イテレータの参照、イテレータのインクリメントが可能.
    template <class InputIterator>
    void f12(InputIterator i, InputIterator j)
    {
        // 比較
        bool b1 = (i == j);
        bool b2 = (i != j);

        // 参照
        *i;
        // (*i).mと同じ
        i->m;

        // インクリメント
        ++i;
        i++;
    }

    // 入力イテレータは読み込むことしか保証されていない
    template <class InputIterator>
    void f13(InputIterator i)
    {
        // OK
        auto value = *i;
        // エラー
        *i = value;
    }
}


// 出力イテレータ
namespace output_iterator_ns
{
    // 出力イテレータは、イテレータのインクリメントとイテレータの参照への代入ができる
    template <class OutputIterator>
    void f14(OutputIterator i, typename OutputIterator::value_type v)
    {
        // 参照への代入
        *i = v;

        // インクリメント
        ++i;
        i++;
    }

    // 出力イテレータを参照した結果は定められていない。voidかも。
    // 出力イテレータの値を読むのは意味がない
    template <class OutputIterator>
    void f15(OutputIterator i)
    {
        // 意味がない
        auto value = *i;
    }
}


// イテレータトレイツ
namespace iterator_traits_ns
{
    // difference_typeは、イテレータ同士の距離を指す数値
    template <class Iterator>
    void f16(Iterator i, Iterator j)
    {
        // イテレータ同士の距離
        typename std::iterator_traits<Iterator>::defference_type diff = j - i;
    }

    // value_type: イテレータの参照する値の型
    // pointer: そのポインター型
    // reference: そのリファレンス型
    template <class Iterator>
    void f17(Iterator i)
    {
        // 値型
        typename std::iterator_traits<Iterator>::value_type v = *i;
        // ポインター型
        typename std::iterator_traits<Iterator>::pointer p = &v;
        // リファレンス型
        typename std::iterator_traits<Iterator>::reference r = v;
    }

    /**
     * @brief イテレータカテゴリー
     * struct input_iterator_tag {};
     * struct output_iterator_tag {};
     * struct forward_iterator_tag : public input_iterator_tag, output_iterator_tag {};
     * struct bidirectional_iterator_tag : public forward_iterator_tag {};
     * struct random_access_iterator_tag : public bidirectional_iterator_tag {}:
     */
    // あるイテレータがあるイテレータカテゴリーを満たすかどうかを調べる
    template <class Tag, class Iterator>
    constexpr bool is_category_of()
    {
        using iter_tag = typename std::iterator_traits<Iterator>::iterator_category;
        return std::is_base_of_v<Tag, iter_tag>;
    }
}

namespace output_iterator_ns
{
    // 出力イテレータの要件しか満たさないイテレータ
    struct cout_iterator
    {
        // ボイラープレートコード
        //      出力イテレータではつかわないのでvoidでいい
        using difference_type = void;
        using value_type = void;
        using referece = void;
        using pointer = void;
        //      イテレータカテゴリーは出力イテレータ
        using uterator_category = std::output_iterator_tag;
        // 何もしない
        // 自分自身を返すだけ
        cout_iterator& operator*() { return *this; }
        cout_iterator& operator++() { return *this; }
        cout_iterator& operator++(int) { return *this; }
        // ボイラープレートコード

        //  ここが肝心
        template <class T>
        cout_iterator& operator=(const T& x)
        {
            std::cout << x;
            return *this;
        }
    };

    
}