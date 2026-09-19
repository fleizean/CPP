# ex01 — RPN (Reverse Polish Notation)

> Ters Lehçe (postfix) notasyonundaki bir matematik ifadesini argüman olarak alıp
> sonucunu hesaplayan program.

---

## 1. Subject ne istiyor?

| Kural | Nerede karşılanıyor |
|---|---|
| Program adı `RPN` | [`Makefile`](../ex01/Makefile) → `NAME = RPN` |
| İfade tek argüman olarak gelir | [`main.cpp:6`](../ex01/main.cpp#L6) |
| Sayılar **her zaman 10'dan küçük** (tek haneli) | [`RPN.cpp:30`](../ex01/RPN.cpp#L30) |
| Ara sonuçlar ve sonuç bu kurala tabi **değil** | `int` ile hesaplanır |
| Desteklenen operatörler: `+ - / *` | [`RPN.cpp:36`](../ex01/RPN.cpp#L36) |
| Hata → **stderr**'e mesaj | [`main.cpp:8,20`](../ex01/main.cpp#L8) |
| **En az bir container** | `std::list<int>` |
| Parantez / ondalık sayı desteği gerekmiyor | — |

---

## 2. RPN nedir?

Normal (infix) yazımda operatör iki sayının **arasındadır**: `3 + 4`.
Ters Lehçe (postfix) yazımda operatör sayıların **arkasındadır**: `3 4 +`.

Avantajı: **parantez gerekmez**, işlem önceliği yoktur, soldan sağa tek geçişte
bir yığın (stack) ile hesaplanır.

### Çalışma kuralı

```
her token için:
    sayı ise   → yığına it
    operatör ise → yığından 2 sayı çek (b = üstteki, a = altındaki)
                   sonuc = a <op> b
                   sonucu yığına it
sonunda yığında tam 1 eleman kalmalı → o sonuçtur
```

### Elle takip: `"8 9 * 9 - 9 - 9 - 4 - 1 +"`

| Token | İşlem | Yığın (alt → üst) |
|---|---|---|
| `8` | it | `8` |
| `9` | it | `8 9` |
| `*` | `8 * 9 = 72` | `72` |
| `9` | it | `72 9` |
| `-` | `72 - 9 = 63` | `63` |
| `9` | it | `63 9` |
| `-` | `63 - 9 = 54` | `54` |
| `9` | it | `54 9` |
| `-` | `54 - 9 = 45` | `45` |
| `4` | it | `45 4` |
| `-` | `45 - 4 = 41` | `41` |
| `1` | it | `41 1` |
| `+` | `41 + 1 = 42` | `42` |

Yığında tek eleman kaldı → **42** ✓

> **Sıra önemli:** `a - b` hesaplanırken `b` önce çekilir (üstteki), `a` sonra.
> Ters yapılırsa `7 3 -` işlemi `4` yerine `-4` verir. Kod bunu
> [`RPN.cpp:42-45`](../ex01/RPN.cpp#L42-L45)'te doğru sırayla yapıyor.

---

## 3. Neden `std::list`? (savunmada sorulur)

Bu exercise'te asıl ihtiyaç bir **yığın (LIFO)**: sona ekle, sondan çek, sonuncuya bak.

`std::list` bunların hepsini O(1) yapar: `push_back`, `pop_back`, `back`, `size`, `empty`.

**Ama asıl sebep modül kuralı:**

> *"Once a container is used you cannot use it for the rest of the module."*

Modül genelindeki dağılım:

| Exercise | Container | Sebep |
|---|---|---|
| ex00 | `std::map` | sıralı arama + `lower_bound` |
| **ex01** | **`std::list`** | LIFO için yeterli, diğerleri rezerve |
| ex02 | `std::vector` + `std::deque` | subject iki container zorunlu tutuyor |

> **"Neden `std::stack` değil?"** — Çok önemli bir ayrıntı: `std::stack<int>`'in
> **varsayılan alt container'ı `std::deque`'tür**. `std::deque` ex02'de kullanıldığı için
> düz `std::stack<int>` modül kuralını ihlal ediyormuş gibi okunabilirdi.
> İlle stack istenirse `std::stack<int, std::list<int> >` yazılmalıydı; `std::list`'i
> doğrudan kullanmak hem daha açık hem daha güvenli.

> **"Neden `std::vector` değil?"** — Önceki hâlinde `std::vector` kullanılıyordu ve
> ex02 de `std::vector` kullandığı için **modül kuralı ihlal ediliyordu** (evaluation
> ex02'de dururdu). Bu yüzden `std::list`'e çevrildi.

---

## 4. Kod akışı

### `main.cpp` — [main.cpp](../ex01/main.cpp)

```cpp
if (argc != 2)                      → stderr "Error", return 1
try   { cout << rpn.evaluate(argv[1]) << endl; }
catch { stderr "Error", return 1; }
```

Tam olarak **bir** argüman beklenir. `./RPN "1 2 +" "3"` → `Error`.

### `RPN::evaluate` — [RPN.cpp:22](../ex01/RPN.cpp#L22)

```cpp
std::list<int> values;
std::istringstream iss(expression);
std::string token;

while (iss >> token)      // boşluklara göre parçala (birden fazla boşluk sorun değil)
{
    // 1) tek haneli rakam mı?
    if (token.size() == 1 && std::isdigit(token[0]))
        { values.push_back(token[0] - '0'); continue; }

    // 2) geçerli operatör mü?
    if (token.size() != 1 || (token[0] != '+' && ... ))
        throw std::runtime_error("Error");

    // 3) yığında en az 2 eleman var mı?
    if (values.size() < 2)
        throw std::runtime_error("Error");

    int b = values.back(); values.pop_back();   // ÜSTTEKİ = sağ operand
    int a = values.back(); values.pop_back();   // ALTTAKİ  = sol operand
    ... switch ile hesapla ...
    values.push_back(result);
}

if (values.size() != 1)   // fazla/eksik operand kaldıysa ifade bozuk
    throw std::runtime_error("Error");
return values.back();
```

**Dikkat edilecek 4 nokta:**

1. `token[0] - '0'` → karakteri sayıya çevirir (`'7'` → `7`). ASCII'de rakamlar ardışık
   olduğu için çalışır.
2. `token.size() == 1` şartı, subject'in "sayılar 10'dan küçük" kuralını **zorlar**:
   `"10"` iki karakterli olduğu için reddedilir.
3. `std::isdigit`'e `static_cast<unsigned char>` ile gönderilir — negatif `char`
   değerlerinde tanımsız davranıştan kaçınmak için (`<cctype>` fonksiyonlarının
   standart kullanımı).
4. Sıfıra bölme ([satır 60](../ex01/RPN.cpp#L60)) ayrıca kontrol edilir — yoksa program
   crash ederdi ve **savunmada crash = 0 puan**.

---

## 5. Hata durumları

| Girdi | Sonuç | Sebep |
|---|---|---|
| `"(1 + 1)"` | `Error` | `(` geçerli token değil |
| `""` / `"   "` | `Error` | Sonda yığın boş → `size() != 1` |
| `"5"` | `5` | Tek sayı geçerli bir ifadedir |
| `"+"` | `Error` | Operatör var ama operand yok |
| `"1 +"` | `Error` | Yığında 2 eleman yok |
| `"1 2 3 +"` | `Error` | Sonda 2 eleman kalır → `size() != 1` |
| `"1 0 /"` | `Error` | Sıfıra bölme |
| `"10 2 +"` | `Error` | `10` tek haneli değil (subject kuralı) |
| `"-5 2 +"` | `Error` | `-5` tek karakter değil; negatif giriş istenmiyor |
| `"1 2 %"` | `Error` | `%` desteklenen operatör değil |
| `"3 4 +x"` | `Error` | `+x` tek karakter değil |
| `"9 9 9 9 9 9 9 9 9 * * * * * * * *"` | `387420489` | Sonuç 10'dan büyük olabilir ✓ |
| `"3 7 -"` | `-4` | Sonuç negatif olabilir ✓ |
| `"9 2 /"` | `4` | Tamsayı bölmesi (subject ondalık istemiyor) |

Tüm hata mesajları **stderr**'e gider (`std::cerr`), sonuç **stdout**'a.

---

## 6. Subject kuralları kontrol listesi

- ✅ OCF: 4 üye fonksiyon da var — [RPN.cpp:7-20](../ex01/RPN.cpp#L7-L20)
  (sınıfın durumu olmadığı için kopyalama gövdeleri boş, `(void)other;` ile
  kullanılmayan parametre uyarısı susturulmuş)
- ✅ Header'da fonksiyon gövdesi yok, include guard var
- ✅ Header sadece `<string>` include ediyor; `<list>` .cpp'de — **arayüz sızdırmıyor**
- ✅ `*printf`, `*alloc`, `free`, `using namespace`, `friend` yok
- ✅ C++98, `-Wall -Wextra -Werror` ile uyarısız
- ✅ `new`/`delete` yok → leak imkânsız (valgrind temiz)
- ✅ Hatalar stderr'e, sonuç stdout'a

---

## 7. Savunmada sorulabilecekler

**S: Neden `std::list`?**
→ Yığın davranışı için `push_back`/`pop_back`/`back` yeterli ve hepsi O(1).
Asıl belirleyici modül kuralı: `map` ex00'de, `vector`+`deque` ex02'de kullanılıyor.

**S: Neden `std::stack` kullanmadın?**
→ `std::stack<int>` varsayılan olarak içinde `std::deque` tutar; `std::deque` ex02'ye ait.
Kullanacak olsaydım `std::stack<int, std::list<int> >` yazmam gerekirdi.

**S: `a` ve `b`'yi neden o sırayla çekiyorsun?**
→ Postfix'te son itilen sağ operanddır. Önce `b` (üstteki) çekilir, sonra `a`.
Çıkarma ve bölmede sıra sonucu değiştirir: `7 3 -` → `4`, ters olsa `-4` çıkardı.

**S: Sondaki `values.size() != 1` kontrolü ne işe yarıyor?**
→ `"1 2 3 +"` gibi operandı fazla olan ifadeleri yakalar. Sadece operatör anında
kontrol yapmak yeterli değil.

**S: Sonuç 9'dan büyük olabilir mi?**
→ Evet. Subject sadece **girdi** sayılarının 10'dan küçük olduğunu söylüyor;
ara sonuçlar ve sonuç `int` sınırları içinde serbest.

**S: Taşma (overflow) olursa?**
→ Subject kapsamı dışında; girdiler tek haneli olduğu için taşmaya ulaşmak için
çok uzun bir ifade gerekir.

---

## 8. Test komutları

```bash
cd ex01 && make

# subject örnekleri
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   # 42
./RPN "7 7 * 7 -"                   # 42
./RPN "1 2 * 2 / 2 * 2 4 - +"       # 0
./RPN "(1 + 1)"                     # Error

# checklist "usage advanced"
./RPN "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -"          # 42
./RPN "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 / "     # 15

# hata yolları
./RPN                    # Error
./RPN ""                 # Error
./RPN "1 0 /"            # Error
./RPN "10 2 +"           # Error

# leak kontrolü
valgrind --leak-check=full ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```
