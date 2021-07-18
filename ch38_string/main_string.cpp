#include "main_string.hpp"

/**
 * @brief 文字列
 * 
 * 基本実行文字セット = 基本ソース文字セット + \a + \b + \r + null文字
 * ASCII = 基本実行文字セット + $ + @ + ` + ...
 * 
 * Unicode・・・コードポイントについて定めた規格であり、バイト列で文字を表現する規格ではない。
 * 1コードポイント ≠ 1文字
 * 1コードポイント=21bit弱
 * 1文字 = a * コードポイント = a * (b * 1単位)
 * UTF-16(1単位 = 16bit) *16bitで表現できない文字はサロゲートペアと呼ばれる.
 * UTF-32(1単位 = 32bit) *32bitで1コードポイントを表現できる. しかし、すでに1コードポイント≠1文字でない
 * UTF-8(1単位 = 8bit) *1単位〜4単位で1コードポイント(21bit弱)を表現する. 1単位だけでコードポイントを表現するとき、下位7bitはASCIIに等しい.
 */

int main(int, char**) {

    // UTF-16, UTF-32は1単位が複数バイトからなるエンコード方式
    // UTF-16, UTF-32はエンディアン問題がある
    // 1単位が複数バイトからなる整数だから
    {
        // 1バイトが8bitの環境における2バイトの符号なし整数は2種類ある
        std::uint16_t value = 0b00000001'00000010;
        // 上位バイト：00000001
        // 下位バイト：00000010

        auto print = [](std::byte x) {
            std::cout << static_cast<unsigned int>(x);
        };

        // 2バイトの配列
        std::byte rep[2];

        // バイト列をコピー
        std::memcpy(rep, &value, 2);

        // 上位バイト
        print(rep[0]);
        // 下位バイト
        print(rep[1]);
        std::cout << std::endl;

        // リトルエンディアンは下位バイトから配置する
        // ビッグエンディアンは上位バイトから配置する
        // Intelはリトルエンディアン
        // AMDもリトルエンディアン
        // ネットワークなどバイナリで通信するときは、エンディアンに注意する必要がある
    }

    // リテラル
    {
        char a = 'a';
        char b = 'b';
        char c = 'c';

        char n = '\n'; // 改行
        char t = '\t'; // 水平タブ
        char v = '\v'; // 垂直タブ
        char _b = '\b'; // バックスペース
        char r = '\r'; // キャリッジ・リターン
        char f = '\f'; // フォームフィード
        char _a = '\a'; // アラート
        char s = '\\'; // バックスラッシュ
        char e = '\?'; // 疑問符
        char x = '\''; // 単一引用符
        char y = '\"'; // 二重引用符

        // A
        char oct = '\101';
        char hex = '\x41';

        // ユニバーサルキャラクター
        // \uNNNN     -> U+0000NNNN
        // \UNNNNNNNN -> U+NNNNNNNN
    }

    // 文字列リテラル
    {
        // const char []
        "abc";
        "hello";
        "This is a pen.";

        // 文字列リテラルが連続している場合、1つにまとめられる
        auto s = "abc" "def"; // "abcdef"
        // 通常の文字列リテラルの末尾にはnull文字が入る
        // "abc"
        const char s[4] = {'a', 'b', 'c', '\0'};
        // "hello"
        const char ss[6] = {'h', 'e', 'l', 'l', 'o', '\0'};

        // char型の配列の初期化に通常の文字列リテラルが使える
        char sss[6] = "hello";

        // 配列の添字を書かない場合、文字列リテラルのサイズになる
        // char [6]
        char ssss[] = "hello";

        // 文字列リテラルは配列であるので、先頭要素へのポインターに暗黙的に型変換される
        const char *p = "hello";

        // 文字列リテラルをautoで変数の初期化子に書くと、型はポインターとなる
        // const char *
        auto pointer = "hello";

        // decltype(auto)という別のキーワードだと配列への参照型となる
        // const char (&) [6]
        decltype(auto) reference = "hello";
    }

    // ワイド文字
    {
        // ワイド文字リテラル
        L'A';
        // ワイド文字列リテラル
        L"Hello";

        // windows -> UTF-16
        // その他のOS -> UTF-32
    }

    // UTF-8/UTF-16/UTF-32
    {
        char8_t utf8 = u8'a';
        char16_t utf16 = u'あ';
        char32_t utf32 = U'あ';

        // char8_t [6]
        char8_t s1[] = u8"hello";
        // char16_t [6]
        char16_t s2[] = u"hello";
        // char32_t [6]
        char32_t s3[] = U"hello";

        // "いろは"をそれぞれの文字列リテラルで表現すると以下になる
        // char8_t [10]
        char8_t a1[] = u8"いろは";
        // char16_t a2 [4]
        char16_t a2[] = u"いろは";
        // char32_t a3 [4]
        char32_t a3[] = U"いろは";

        // 以下と同じ
        char8_t a1_same[10] = { 0xe3, 0x81, 0x84, 0xe3, 0x82, 0x8d, 0xe3, 0x81, 0xaf, 0x0 };
        char16_t a2_same[4] = { 0x3044, 0x308d, 0x306f, 0x0 };
        char32_t a3_same[4] = { 0x3044, 0x308d, 0x306f, 0x0 };

        /**
         * @brief `い`のコードポイント
         * 文字`い`のUnicodeコードポイントはU+3-44で、これはUTF-16/UTF-32では1単位で表現できるが、
         * UTF-8では3単位で, 0xe3, 0x81, 0x84
         */

        /**
         * @brief `臼`のコードポイント
         * 臼(うすU+81FC)の別字である𦥑(うすU+26951)のコードポイントは、16bit符号なし整数で表現できないので、
         * UTF-16では、サロゲートペアを使って2単位表現される.
         * UTF-8では、4単位を使って表現される.
         */

        char8_t b1[] = u8"𦥑";
        char16_t b2[] = u"𦥑";
        char32_t b3[] = U"𦥑";
        // 以下と同じ
        char8_t b1_same[5] = { 0xf0, 0xa6, 0xa5, 0x91, 0x0 };
        char16_t b2_same[3] = { 0xd85a, 0xdd51, 0x0 };
        char32_t b3_same[2] = { 0x26951, 0x0 };

        /**
         * @brief 文字`が`はUnicodeコードポイントでは、結合済みコードポイントのU+304Cで表現できるが、
         * コードポイントU+304B(HIRAGANA LETTER KA)のあとに直ちに続いて、コードポイントU+3099(COMBINING KATAKANA-HIRAGANA VOICED SOUND MARK)を
         * 使って表現してもよい。macOSは分割が標準となる.
         * Unicodeでは同じ文字に対して複数の表現方法がある.
         */

        // u8"\u304C"
        char8_t ga1[] = u8"が";
        // u8"\u304B\u3099"
        char8_t ga2[] = u8"か\3099";
        // 以下のコードと等しい
        char8_t ga1_same[4] = { 0xe3, 0x81, 0x8c, 0x0 };
        char8_t ga2_same[7] = { 0xe3, 0x81, 0x8b, 0xe3, 0x82, 0x99, 0x0 };

        // Apple macOS: NFD
        // その他: NFC
    }

    // 生文字列リテラル
    {
        u8"\nは改行文字";
        u8"\\nは改行文字";

        u8"\'は単一引用符";
        u8"\"は二重引用符";

        "foo\nbar\nbaz";

        // 生文字列リテラル
        // R"()"
        R"(foo
        bar
        baz)";

        // エスケープシーケンスも書いたままに文字列となる
        R"(
            'は単一引用符
            "は二重引用符
            \nは改行文字
        )";
    }

    // 文字列の表現方法
    {
        // null終端文字列
        "abc";
        const char st[4] = { 'a', 'b', 'c', '\0' };

        auto process_string = [](const char *str) {
            // strが指す配列のサイズを取得
            auto str_size = std::strlen(str);
            // 残りの処理
        };

        auto my_strlen = [](const char *s) -> std::size_t {
            auto i = s;
            while (*i != '\0') {
                ++i;
            }
            return i - s;
        };
    }

    // std::basic_string
    {
        // template <
        //     typename charT,
        //     typename traits = char_traits<charT>,
        //     typename Allocator = allocator<charT>
        // >
        // class basic_string;

        // using string = basic_string<char>;
        // using u8string = basic_string<char8_t>;
        // using 16ustring = basic_string<char16_t>;
        // using u32string = basic_string<char32_t>;
        // using wstring = basic_string<wchar>;

        // 文字列リテラルのサフィックスにsをつけることで、文字列リテラルを対応するbasic_string
        // のクラスに変換できる

        // // string
        // auto str = "hello"s;
        // // u8string
        // auto u8str = u8"hello"s;
        // // u16string
        // auto u16str = u16"hello"s;
        // // u32string
        // auto u32str = u32"hello"s;
        // // wstring
        // auto wstr = L"hello"s;

        // ユーザー定義リテラル
        // std::string operator ""s(const char *ptr, std::size_t n) {
        //     return std::string(ptr, n);
        // }
        // std::u8string operator ""s(const char8_t *ptr, std::size_t n) {
        //     return std::u8string(ptr, n);
        // }
        // std::u16string operator ""s(const char16_t *ptr, std::size_t n) {
        //     return std::u16string(ptr, n);
        // }
        // std::u32string operator ""s(const char32_t *ptr, std::size_t n) { 
        //     return std::u32string(ptr, n);
        // }
        // std::wstring operator ""s(const wchar_t *ptr, std::size_t n) {
        //     return std::wstring(ptr, n);
        // }


    }


    // std::basic_string_view
    {
        // basic_string_viewはストレージを所有しないクラス
        // template <
        //     typename charT,
        //     typename traits = char_traits<charT>
        // >
        // class basic_string_view;

        // 実装は2つのポインタ or 1つのポインタ＋サイズ
        // charT *first;
        // charT *last;
        // or 
        // charT *first;
        // std::size_t size;

        // 特殊化
        // using string_view = basic_string_view<char>;
        // using u8string_view = basic_string_view<char8_t>;
        // using u16string_view = basic_string_view<char16_t>;
        // using u32string_view = basic_string_view<char32_t>;
        // using wstring_view = basic_string_view<wchar_t>;

        // ユーザー定義リテラルサフィックスsv
        // string_view
        auto str = "hello"sv;
        // u8string_view
        auto u8str = u8"hello"sv;
        // u16string_view
        auto u16str = U"hello"sv; // windows -> utf16, その他 -> utf32
        // u32string_view
        auto u32str = U"hello"sv;
        // wstring_view
        auto wstr = L"hello"sv;

        // string_viewは文字列がnull終端文字列とbasic_stringのどちらで表現されていても
        // 問題なく受け取るためのクラス
        // 2つの文字列表現を別々に扱う場合は、下記となる
        auto process_string1 = [](const char *s) {
            // 文字列に対する処理
        };

        auto process_string2 = [](const std::string &s) {
            // 文字列に対する上と同じ処理
        };

        auto null_terminated_string = "hello";
        auto basic_string = "hello"s;

        // const char *
        process_string1(null_terminated_string);
        // const std::string &
        process_string2(basic_string);

        // basic_string_viewを使えば、一つの関数で済む
        auto process_string3 = [](std::string_view s) {
            // 文字列に対する処理
        };

        // どちらも同じ関数を呼べる
        process_string3(null_terminated_string);
        process_string3(basic_string);
    }

    // 文字列の操作
    {
        /**
         * @brief null終端文字列の操作
         * いちいちnull終端文字列へのインクリメントを行う
         */
        auto f = [](const char *ptr) {
            auto size = std::strlen(ptr);
        };

        // 文字列リテラルの型はconstな文字型の配列なので、文字列を変更できない
        const char *ptr = "abc";
        // ptr[0] = 'x'; // エラー

        // 文字型への配列ならば変更できる
        char s[] = "abc";
        s[1] = '\0';
        // sは{'a', '\0', 'c', '\0'}
        // この変数sの型はchar [4]だが、null終端文字列としてのサイズは1である。

        // 文字列のサイズを長くするには、大きな配列が必要になる.
        char ss[10] = "abc";
        ss[3] = 'd';
        ss[4] = 'e';
        ss[5] = 'f';
        ss[6] = '\0';
        // ss : "abcdef"
        // 配列ssの要素数はnull終端文字列を含めるので7要素以上である必要がある.
        // 例えば、2つのnull終端文字列を結合する場合で、どちらもconstであったり、
        // 十分なサイズがなかった場合、2つの文字列を肘できるサイズのメモリーを確保して
        // コピーしなければならない.

        // s1, s2を結合してつかう関数
        auto concat_str = [](const char *s1, const char *s2) -> void {
            // 2つの文字列の合計サイズ + null文字
            auto size = std::strlen(s1) + std::strlen(s2) + 1;
            // 文字列を保持するメモリーを確保する
            char *ptr = new char[size];
            char *i = ptr;

            // s1をコピー
            while (*s1 != '\0')
            {
                *i = *s1;
                ++i; ++s1;
            }
            // std::strcpy(ptr, s1); // ptrの末尾は、null終端される

            // s2をコピー
            while (*s2 != '\0')
            {
                *i = *s2;
                ++i; ++s2;
            }
            // std::strcpy(ptr, s2); // ptrの末尾は、取り除かれて、新しくnull終端される

            // null終端する
            *i = '\0';

            // 結合した文字列を使う


            // 使い終わったのでメモリーを解放する
            delete[] ptr;
        };
    }

    // basic_stringの操作
    {
        auto concat_str = [](const char *s1, const char *s2) {
            std::string s = s1;
            s += s2;

            // sを使う
            // sは自動的に破棄される
        };

        // string_view版
        auto concat_str2 = [](std::string_view s1, std::string_view s2) -> void {
            std::string s = s1;
            s += s2;

            // sを使う
            // sは自動的に破棄される
        };

        // basic_stringはnull終端文字列, basic_string_view, basic_stringで初期化、代入できる.

        // null終端文字列
        std::string s1("hello");
        // basic_string_view
        std::string s2("hello"sv);
        // basic_string
        std::string s3("hello"s);

        // 結合
        // basic_stringはoperator+で文字列を結合できる.
        auto s = "foo"s + "bar"s;

        // operator+=は第一オペランドを書き換える
        auto ss = "foo"s;
        ss += "bar"s;
        // ssは"foobar".

        // basic_string::append(s);
        auto sss = "foo"s;
        sss.append("bar"sv);
        // sssは、"foobar"

        // イテレータ
        auto s4 = "hello"s;
        for (auto i = s.begin(); i != s4.end(); ++i) {
            std::cout << *i;
        }

        for (auto i = std::begin(s4); i != std::end(s4); ++i) {
            std::cout << *i;
        }

        // 部分文字列の検索
        {
            auto text = "quick from fox jumps over the lazy dog."s;
            auto word = "fox"s;

            auto i = std::search(std::begin(text), std::end(text), std::begin(word), std::end(word));

            if (i != std::end(text)) {
                std::cout << "fox found!"sv << std::endl;
            } else {
                std::cout << "no fox..."sv << std::endl;
            }

            // C++20ではRangeライブラリが追加され、以下のようにかける
            auto r = std::ranges::search(text, word);
            if (!std::ranges::empty(r)) {
                ///
            }

            // basic_string::find
            // 文字列から部分文字列を探し、その部分文字列に一致する文字へのインデックスを返す。
            auto fox = text.find("fox"sv); // 12
            auto dog = text.find("dog"sv); // 32

            // 通常、文字数と連続した文字型の要素へのインデックスは等しくならない.
            auto u8text = u8"すばしっこい狐がノロマな犬を飛び越した。"s;

            auto u8fox = u8text.find(u8"狐"sv);
            auto u8dog = u8text.find(u8"犬"sv);

            std::cout << "fox: "sv << u8fox << "\n"sv
                << "dog: "sv << dog << std::endl;
            // output
            // fox: 27
            // dog: 45

            // 見つからない場合は、nposが返る
            auto index = text.find("abc"sv);

            // 見つからなかった判定
            if (index != std::string::npos)
            {
                // 見つかった
                std::cout << "found." << std::endl;
            }
            else 
            {
                // 見つからなかった
            }


            // rfindは最後の部分文字列を見つける
            auto txt = "word word word"s;

            // 0
            auto first = txt.find("word"s);
            // 10
            auto last = txt.rfind("word"s);
        }
    }


    // c++20: starts_with/ends_with
    {
        auto text = "aa bb cc"s;

        // true
        bool b1 = text.starts_with("a"sv);
        bool b2 = text.starts_with("aa"sv);
        bool b3 = text.starts_with("aa "sv);

        // false
        bool b4 = text.starts_with("b"sv);
        bool b5 = text.starts_with("aaa"sv);

        // true
        bool b6 = text.ends_with("c"sv);
        bool b7 = text.ends_with("cc"sv);
        bool b8 = text.ends_with(" cc"sv);

        // false
        bool b9 = text.ends_with("b"sv);
        bool b10 = text.ends_with("ccc"sv);
    }

    // その他のメンバー関数
    {
        // size, empty, capacity, reserve, shirnk_to_fit, clearなど
        std::string s;
        s.size();
        s.resize(10);
        s.clear();
    }

    // 文字列の挿入 -> insert(pos, str)
    {
        auto text = "cat"s;
        text.insert(0, "long "sv);
        // textは"long cat"
        text.insert(text.size(), " is looong."sv);
        // textは"long cat is loong."

        // 中間への挿入　
        auto text2 = "big cat"s;
        text2.insert(text2.find("cat"sv), "fat "sv);
        // textは"big fat cat"
    }

    // 部分文字列の削除 -> erase(pos, n)
    {
        auto text = "dirty cat"s;
        auto dirty = "dirty "sv;
        text.erase(0, dirty.size());
        // textは"cat"
    }

    // 部分文字列の置換 -> replace(pos, n1, str)
    {
        // posからn1個までの文字型の値を文字列strで置き換える
        auto text = "ugly cat"s;
        auto ugly = "ugly"sv;
        auto pretty = "pretty"sv;
        text.replace(text.find(ugly), ugly.size(), pretty);
        // textは"pretty cat"
    }


    // 推奨されない操作
    {
        // 1
        {
            auto text = "abc"s;
            // 'a'
            std::cout << text[0];
            // 'b'
            std::cout << text[1];

            text[0] = 'x';
            // textは"xbc"
        }

        // UnicodeとUTFによるエンコードへの適用
        {
            auto text = u8"いろは";
            // 0xe3
            auto c = text[0];

            // u8"いろは”
            char8_t iroha[10] = {
                0xe3, 0x81, 0x84, 0xe3, 0x82, 0x8d, 0xe3, 0x81, 0xaf, 0x0
            };
        }

        // UTF系へのfind_first_ofは、成り立たない
        {
            auto text = "quick brown fox jumps over the lazy dog."s;
            // 3
            auto i = text.find_first_of("abc"sv); // これはOK
        }

        // remove_suffix/remove_prefix
        {
            auto text = "quick brown fox jumps over the lazy dog."s;
            text.remove_prefix("quick "sv.size());
            text.remove_suffix(" dog.".sv.size());
        }




    }



    return 0;
}