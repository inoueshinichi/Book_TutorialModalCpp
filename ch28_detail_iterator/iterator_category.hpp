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


// 出力イテレータ
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
        using iterator_category = std::output_iterator_tag;
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


// 入力イテレータ
namespace input_iterator_ns
{
    // std::cinからT型を読み込む入力イテレータ
    template <class T>
    struct cin_iterator
    {
        // --- ボイラープレートコード
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        // イテレータカテゴリーは入力イテレータ
        using iterator_category = std::input_iterator_tag;
        // --- ボイラープレートコード

        // コンストラクター
        cin_iterator(bool _fail = false)
            : fail(_fail) { ++(*this); }
        
        // キャッシュした値を返す
        const_reference operator *() const 
        { // const referenceだとエラーになるが、原因がわからない
            return value;
        }

        // 新しい値をキャッシュする
        cin_iterator& operator++()
        {
            if (!fail)
            {
                std::cin >> value;
                fail = std::cin.fail();
            }
            return *this;
        }

        // 後置インクリメント
        cin_iterator operator++(int)
        {
            auto old = *this;
            ++(*this);
            return old;
        }

        // イテレータの等価比較の状態
        bool fail;
        // 値のキャッシュ
        value_type value;
    };

    // 比較演算子
    template <class T>
    bool operator==(const cin_iterator<T>& l, const cin_iterator<T>& r)
    {
        return l.fail == r.fail;
    }

    template <class T>
    bool operator!=(const cin_iterator<T>& l, const cin_iterator<T>& r)
    {
        return !(l == r);
    }

    // イテレータが終了条件に達したかどうかを判定できる
    template <class InputIterator>
    void print(InputIterator iter, InputIterator end_iter)
    {
        // 終了条件に達するまで
        while (iter != end_iter)
        {
            std::cout << *iter;
            ++iter;
        }
    }
}


// 前方イテレータ
namespace forward_iterator_ns
{
    template <class T>
    struct iota_iterator
    {
        // イテレータ同士の距離を表現する型
        using difference_type = std::ptrdiff_t;
        // 要素の型
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        // イテレータカテゴリーは前方イテレータ
        using iterator_category = std::forward_iterator_tag;

        // 値を保持する
        value_type value;

        // コンストラクタ
        iota_iterator(value_type value = 0)
            : value(value) {}

        // コピーコンストラクタは自動生成される

        // 残りのコード
        // 非const版
        reference operator*() noexcept
        {
            return value;
        }

        // const版
        const_reference operator*() const noexcept
        {
            return value;
        }

        // 前置
        iota_iterator& operator++() noexcept
        {
            ++value;
            return *this;
        }

        // 後置
        iota_iterator operator++(int) noexcept
        {
            auto old = *this;
            ++*this;
            return old;
        }

        // 比較
        bool operator==(const iota_iterator& i) const noexcept
        {
            return value == i.value;
        }

        bool operator != (const iota_iterator& i) const noexcept
        {
            return !(*this == i);
        }
    };


    // 前方リンクリスト
    template <class T>
    struct forward_link_list
    {
        T value;
        forward_link_list* next;
    };

    // forward_link_list<T>へのイテレータの骨子
    template <class T>
    struct iterator
    {
        forward_link_list<T>* ptr;

        T& operator*() noexcept
        {
            return ptr->value;
        }

        iterator& operator++() noexcept
        {
            ptr = ptr->next;
            return *this;
        }

        // 残りのメンバ関数
    };


    // n+1番目の要素を返す関数
    template <class T>
    forward_link_list<T>& next(forward_link_list<T>& list) noexcept
    {
        // 次の要素
        return *(list.next);
    }

    // 前方イテレータが入力/出力イテレータと違う点は、マルチパス保証があること。
    // イテレータのコピーを使いまわして、複数回同じ要素をたどることができる。
    template <class ForwardIterator>
    void f(ForwardIterator first, ForwardIterator last)
    {
        using vector_type = std::vector<typename ForwardIterator::value_type>;

        // 全要素の値をv1にコピー
        vector_type v1;
        for (auto iter = first; iter != last; ++iter)
        {
            v1.push_back(*iter);
        }

        // 全要素の値をv2にコピー
        // イテレータがもう一度使われた
        vector_type v2;
        for (auto iter = first; iter != last; ++iter)
        {
            v2.push_back(*iter);
        }

        // マルチパス保証があれば、常にtrue
        bool b = (v1 == v2);
    }

    // ※前方イテレータ以上のイテレータにはマルチパス保証がある.
}


// 双方向イテレータ
namespace bidirectional_iterator_ns
{
    // 双方向化したiota_iterator
    template <class T>
    struct iota_iterator
    {
        // ------------ forward_iteratorでの定義

        // イテレータ同士の距離を表現する型
        using difference_type = std::ptrdiff_t;
        // 要素の型
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        // イテレータカテゴリーは前方イテレータ
        //using iterator_category = std::forward_iterator_tag;

        // 値を保持する
        value_type value;

        // コンストラクタ
        iota_iterator(value_type value = 0)
            : value(value) {}

        // コピーコンストラクタは自動生成される

        // 残りのコード
        // 非const版
        reference operator*() noexcept
        {
            return value;
        }

        // const版
        const_reference operator*() const noexcept
        {
            return value;
        }

        // 前置
        iota_iterator& operator++() noexcept
        {
            ++value;
            return *this;
        }

        // 後置
        iota_iterator operator++(int) noexcept
        {
            auto old = *this;
            ++*this;
            return old;
        }

        // 比較
        bool operator==(const iota_iterator& i) const noexcept
        {
            return value == i.value;
        }

        bool operator != (const iota_iterator& i) const noexcept
        {
            return !(*this == i);
        }

        // ------------


        // イテレータカテゴリ-
        using iterator_category = std::bidirectional_iterator_tag;

        iota_iterator& operator--() noexcept
        {
            --value;
            return *this;
        }

        iota_iterator& operator--(int) noexcept
        {
            auto old = *this;
            --(*this);
            return *this;
        }

        // 省略
    };

    // 双方向リンクリスト
    template <class T>
    struct bidirectional_link_list
    {
        T value;
        bidirectional_link_list* prev;
        bidirectional_link_list* next;
    };

    // 双方向リンクリストに対するイテレータ操作の骨子
    template <class T>
    struct iterator
    {
        bidirectional_link_list<T>* ptr;

        // 前方n+1
        iterator& operator++() noexcept
        {
            ptr = ptr->next;
            return *this;
        }

        // 後方n-1
        iterator& operator--() noexcept
        {
            ptr = ptr->prev;
            return *this;
        }
    };
}


// ランダムアクセスイテレータ
namespace random_access_iterator_ns
{
    // iota_iteratorをランダムアクセスイテレータに対応させる
    template <class T>
    struct iota_iterator
    {
        // ------------ bidirectional_iteratorでの定義
        // ------------ forward_iteratorでの定義
        // イテレータ同士の距離を表現する型
        using difference_type = std::ptrdiff_t;
        // 要素の型
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        // イテレータカテゴリーは前方イテレータ
        //using iterator_category = std::forward_iterator_tag;

        // 値を保持する
        value_type value;

        // コンストラクタ
        iota_iterator(value_type value = 0)
            : value(value) {}

        // コピーコンストラクタは自動生成される

        // 残りのコード
        // 非const版
        reference operator*() noexcept
        {
            return value;
        }

        // const版
        const_reference operator*() const noexcept
        {
            return value;
        }

        // 前置
        iota_iterator& operator++() noexcept
        {
            ++value;
            return *this;
        }

        // 後置
        iota_iterator operator++(int) noexcept
        {
            auto old = *this;
            ++*this;
            return old;
        }

        // 比較
        bool operator==(const iota_iterator& i) const noexcept
        {
            return value == i.value;
        }

        bool operator != (const iota_iterator& i) const noexcept
        {
            return !(*this == i);
        }
        
        // ------------

        // イテレータカテゴリ-
        //using iterator_category = std::bidirectional_iterator_tag;

        using iterator_category = std::random_access_iterator_tag;

        iota_iterator& operator--() noexcept
        {
            --value;
            return *this;
        }

        iota_iterator& operator--(int) noexcept
        {
            auto old = *this;
            --(*this);
            return old;
        }
        // ----------

        iota_iterator& operator += (difference_type n)
        {
            value += n;
            return *this;
        }

        iota_iterator operator + (difference_type n) const // メンバ関数orフリー関数どっちでもよい
        {
            auto temp = *this;
            temp += n;
            return temp;
        }

        iota_iterator& operator -= (difference_type n)
        {
            value -= n;
            return *this;
        }

        iota_iterator operator - (difference_type n) // メンバ関数orフリー関数どっちでもよい
        {
            auto temp = *this;
            temp -= n;
            return temp;
        }

        // 省略
    };


    // difference_type + iota_iteratorの場合 (必ずクラス外のフリー関数として実装する)
    template <class T>
    iota_iterator<T> operator + (typename iota_iterator<T>::difference_type n,
                                 const iota_iterator<T>& i)
    {
        return i + n;
    }

    // difference_type - iota_iteratorの場合 (必ずクラス外のフリー関数として実装する)
    template <class T>
    iota_iterator<T> operator - (typename iota_iterator<T>::difference_type n,
                                 const iota_iterator<T>& i)
    {
        return i - n;
    }


    // イテレータの距離の実装はiota_iteratorの場合、単にvalueの差である。
    // メンバー関数orフリー関数どっちでもよい。以下はフリー関数
    template <class T>
    typename iota_iterator<T>::difference_type operator -
    (const iota_iterator<T>& a, const iota_iterator<T>& b) {
        return a.value - b.value;
    }


    // 大小比較はvalueを比較するだけ
    template <class T>
    bool operator < (const iota_iterator<T>& a,
                     const iota_iterator<T>& b)
    {
        return a.value < b.value;
    }

    template <class T>
    bool operator <= (const iota_iterator<T>& a,
                      const iota_iterator<T>& b)
    {
        return a.value <= b.value;
    }

    template <class T>
    bool operator > (const iota_iterator<T>& a,
                     const iota_iterator<T>& b)
    {
        return a.value > b.value;
    }

    template <class T>
    bool operator >= (const iota_iterator<T>& a,
                      const iota_iterator<T>& b)
    {
        return a.value >= b.value;
    }



    // ランダムアクセスイテレータ：連続したメモリー上に構築された要素の集合
    // std::vectorやstd::arrayのイテレータが該当
    template <class T>
    struct iterator
    {
        T* ptr;

        T& operator*() { return *ptr; }
        iterator& operator++() noexcept
        {
            ++ptr;
            return *this;
        }

        // その他のメンバー
    };

    // vectorやarrayのイテレータの実装は、ポインターとほぼ同じ処理をしている.
    // その実装は上にあるように、単にポインターにデリゲートするだけ.
    // C++の標準ライブラリの実装によっては、vectorやarrayの実装は単に生のポインター
    // を返す.
    template <class T, std::size_t N>
    struct array
    {
        T storage[N];

        T* begin() noexcept
        {
            return storage;
        }

        T* end() noexcept
        {
            return storage + N;
        }
    };


    // イテレータはクラスであり、そのネストされた型名にvalue_typeやdifference_type, 
    // iterator_categoryなどの型がある
    template <class Iterator>
    // ネストされた型名を使う
    typename Iterator::reference_type
    get_value(Iterator i) {
        return *i;
    }

    // そのため、イテレータのネストされた型名を使うときは、直接使うのではなく、
    // 一度、iterator_traitsを経由して使うとよい.
}




// イテレータの操作
namespace iterator_operation_ns
{
    // イテレータはそのまま使うこともできるが、一部の操作を
    // 簡単に行うための標準ライブラリがある

    // advance(i, n): n移動する
    // ランダムアクセスイテレータ i += n
    // 前方イテレータ for ++i
    // 双方向イテレータ for ++i or for --i
    // std::advance(i, n)はイテレータカテゴリーごとに最適なn進める処理をよしなにやってくれる

    // iを1前方に進める
    // std::advance(i, 1);
    // iを5前方に進める
    // std::advance(i, 5);
    // iを5後方に進める
    // std::advance(i, -5);
    // iは移動しない
    // std::advance(i, 0);

    // std::advance(i,n)はi自体が変化する

    // -----------------

    // distance(first, last): firstからlastまでの距離
    // ランダムアクセスイテレータ auto dist = last - first;
    // それ以外のイテレータ 
    // std::size_t dist = 0;
    // for (auto iter = first; iter != last; ++iter)
    //     ++dist;

    // iからjまでの距離を返す
    // auto dist = std::distance(i, j);

    // distanceに渡したイテレータは変更されない


    // -----------------


    // next/prev: 移動したイテレータを返す
    // advance(i,n)はイテレータiを変更してしまう.
    // イテレータを変更させず、移動後のイテレータも欲しい場合、
    // 以下のように書かなければならない
    // template <class Iterator>
    // void f(Iterator i)
    // {
    //   auto j = i;
    //   std::advance(j, 3);
    //   // jはiより3前方に移動している
    // }

    // next
    template <class Iterator>
    void f1(Iterator i)
    {
        auto j = std::next(i, 3);
        // jはiより3前方に移動している
    }

    // prev
    template <class Iterator>
    void f2(Iterator i)
    {
        auto j = std::prev(i ,3);
        // jはiより3後方に移動している
        // jはstd::advance(i, 3)したあとのiと同じ値
    }

    // next/prevに第二引数を渡さない場合、前後1だけ移動する.
    template <class Iterator>
    void f(Iterator i)
    {
        auto j = std::next(i);
        // jは++iしたのと同じ値
        auto k = std::prev(i);
        // kは--iしたのと同じ値
    }
}



// リバースイテレータ
namespace reverse_iterator_ns
{
    // 通常のイテレータは、要素を順番どおりにたどる.
    template <class Iterator>
    void print(Iterator first, Iterator last)
    {
        for (auto iter = first; iter != last; ++iter)
        {
            std::cout << *iter;
        }
        std::cout << std::endl;
    }


    // 双方向イテレータ以上であれば、逆順にたどることはできる.
    template <class Iterator>
    void reverse_print(Iterator first, Iterator last)
    {
        for (auto iter = std::prev(last); iter != first; --iter)
        {
            std::cout << *iter;
        }
        std::cout << std::endl;
    }

    // イテレータを正順にたどるか逆順にたどるかという違いだけで、
    // 本質てkに同じアルゴリズム、同じコードを2度も書きたくない.
    // そこで、役に立つのがリバースイテレータ
    // std::reverse_iterator<Iterator>はイテレータIteratorに
    // 対するリバースイテレータを提供する.
    // リバースイテレータは、イテレータのペア[first, last)を受け取り
    // lastの一つ前の要素が先頭でfirstの要素が末尾になるような順番のイテレータにしてくれる.
    template <class Iterator>
    void reverse_iterator_sample(Iterator i)
    {
        std::vector<int> v = {1,2,3,4,5};

        // std::reverse_iterator<std::vector<int>::iterator>
        std::reverse_iterator first {std::end(v)};
        std::reverse_iterator last {std::begin(v)};

        // 54321
        std::for_each(first, last, [](auto x) {
            std::cout << x;
        });
        std::cout << std::endl;
    }
}
