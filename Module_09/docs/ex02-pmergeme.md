# ex02 — PmergeMe (Ford-Johnson / merge-insert sort)

> Pozitif tamsayı dizisini **Ford-Johnson (merge-insertion)** algoritmasıyla,
> **iki farklı container** üzerinde ayrı ayrı sıralayıp sürelerini karşılaştıran program.

---

## 1. Subject ne istiyor?

| Kural | Nerede karşılanıyor |
|---|---|
| Program adı `PmergeMe` | [`Makefile`](../ex02/Makefile) |
| Pozitif tamsayı dizisi argüman olarak gelir | [`parseToken`](../ex02/main.cpp#L11) |
| **Merge-insert (Ford-Johnson)** kullanılmalı | [`fordJohnsonVector`](../ex02/PmergeMe.cpp#L60) / [`fordJohnsonDeque`](../ex02/PmergeMe.cpp#L167) |
| Hata → **stderr** | [`main.cpp:34`](../ex02/main.cpp#L34), [`main.cpp:78`](../ex02/main.cpp#L78) |
| **En az iki farklı container** | `std::vector` + `std::deque` |
| **En az 3000 sayı**, tekrarlar dahil | ✅ test edildi |
| 1. satır: açıklama + sırasız dizi | `Before: ...` |
| 2. satır: açıklama + sıralı dizi | `After: ...` |
| 3./4. satır: her container için süre | `Time to process a range of N elements with std::... : X us` |
| Süre **hem sıralama hem veri yönetimini** kapsamalı | [`main.cpp:50-62`](../ex02/main.cpp#L50-L62) |
| Algoritma her container için **ayrı** yazılmalı (generic fonksiyon önerilmiyor) | iki ayrı implementasyon |

---

## 2. Dosya haritası ve sorumluluk dağılımı

```
ex02/
├── Makefile
├── main.cpp        → argüman doğrulama, ekrana basma, zaman ölçümü   (83 satır)
├── PmergeMe.hpp    → sınıf arayüzü                                   (29 satır)
└── PmergeMe.cpp    → SADECE sıralama algoritması                    (252 satır)
```

`PmergeMe` sınıfı bilinçli olarak **dar tutuldu**: dışarıya sadece iki fonksiyon açıyor.

| Üye | Erişim | Görev |
|---|---|---|
| `sortVector(seq)` | public | `std::vector<int>` alır, sıralanmış kopyasını döndürür |
| `sortDeque(seq)` | public | `std::deque<int>` alır, sıralanmış kopyasını döndürür |
| `fordJohnsonVector/Deque` | private | Asıl özyinelemeli algoritma (indeksler üzerinde) |
| `lowerBoundVector/Deque` | private | Sınırlı ikili arama |
| `jacobsthalInsertionOrder` | private | Ekleme sırasını üretir |

Argüman okuma, yazdırma ve kronometre `main.cpp`'de — sınıfın işi değil.

---

## 3. Ford-Johnson neden var?

Normal sıralama algoritmaları (quicksort, mergesort) hızlıdır ama **karşılaştırma sayısı**
açısından optimal değildir. Ford-Johnson, *n* elemanı sıralamak için gereken
karşılaştırma sayısını teorik alt sınıra (`log₂(n!)`) çok yaklaştırır.

Knuth'un verdiği üst sınır:

```
F(n) = Σ (k=1..n) ⌈log₂(3k/4)⌉
```

Fikir şu: **hiçbir karşılaştırmayı boşa harcama.**
- Elemanları ikişerli eşle, her çiftin büyüğünü bul (n/2 karşılaştırma).
- Sadece **büyükleri** özyinelemeli olarak sırala → *ana zincir*.
- Küçükleri, eşlerinin konumu sayesinde **daraltılmış aralıkta ikili aramayla** yerleştir.
- Yerleştirme sırasını **Jacobsthal sayılarına** göre seç ki her ikili arama
  tam `2^k − 1` büyüklüğünde bir aralığa denk gelsin.

> ⚠️ **Karıştırılan şey:** "merge sort + küçük dilimlerde insertion sort" hibriti
> Ford-Johnson **değildir**. Orada eşleştirme, ana zincir/pend ayrımı, Jacobsthal ve
> sınırlı ikili arama yoktur. Subject bu konuda net: *"To clarify, yes, you need to use
> the Ford-Johnson algorithm (Art Of Computer Programming, Vol.3, Page 184)"*,
> checklist ise *"In case of doubt, the evaluation stops here"* diyor.

---

## 4. Algoritmanın adımları (kodla birebir)

`fordJohnsonVector(values, indices)` — [PmergeMe.cpp:60](../ex02/PmergeMe.cpp#L60)

```
1) indices.size() <= 1  ->  zaten sıralı, döndür                     [satır 62]

2) Tek sayıda eleman varsa sondakini "stray" olarak ayır             [satır 65-72]

3) Kalanları ikişer eşle (çift başına TEK karşılaştırma):
      büyük -> bigIdx[],  partner[büyük] = küçük                     [satır 74-84]

4) bigIdx'i ÖZYİNELEMELİ sırala -> chain (ana zincir)                [satır 86-87]

5-7) Tek geçişte:                                                    [satır 89-103]
      pend[i]     = partner[chain[i]]
      chainPos[i] = i + 1   (baştaki ekleme baştan hesaba katılır)
      pend[0]'ı KARŞILAŞTIRMASIZ başa ekle
      (çünkü pend[0] < chain[0] = tüm büyüklerin en küçüğü)

8) Kalan pend elemanlarını Jacobsthal sırasıyla, [0, chainPos[j])
   aralığında lowerBoundVector ile yerleştir                         [satır 105-120]

9) Stray varsa tüm zincirde ikili aramayla yerleştir                 [satır 122-127]
```

Deque sürümü [satır 167](../ex02/PmergeMe.cpp#L167)'de birebir aynı adımlarla.

---

## 5. Elle takip: `./PmergeMe 3 5 9 7 4`

`values = [3, 5, 9, 7, 4]`, `indices = [0,1,2,3,4]`

**Adım 2** — 5 tek sayı → `stray = index 4` (değer **4**), `indices = [0,1,2,3]`

**Adım 3** — eşleme:

| Çift | Değerler | büyük | `partner` |
|---|---|---|---|
| (0,1) | 3 vs 5 | `1` (5) | `partner[1] = 0` (3) |
| (2,3) | 9 vs 7 | `2` (9) | `partner[2] = 3` (7) |

`bigIdx = [1, 2]` → değerler **5, 9**

**Adım 4** — `fordJohnsonVector(values, [1,2])` özyinelemesi:
> 2 eleman → eşle: 5 vs 9 → büyük=`2`, `partner[2]=1` → `bigIdx=[2]`
> `fordJohnsonVector(values,[2])` → tek eleman → `[2]`
> `pend=[partner[2]]=[1]`, `result=[2]`, pend[0] başa → `result=[1,2]` (değerler **5, 9**)

`chain = [1, 2]` → değerler **5, 9**

**Adım 5-7** — tek geçişte: `pend = [partner[1], partner[2]] = [0, 3]` → değerler **3, 7**
`chainPos = [1, 2]` (doğrudan `i + 1` olarak kurulur — baştaki ekleme baştan hesaba katılır)
pend[0]=0 (değer 3) karşılaştırmasız başa → `result = [0,1,2]` → değerler **3, 5, 9**

**Adım 8** — `jacobsthalInsertionOrder(2)` → `[1]`
- `j=1` → `pend[1]=3` (değer **7**), arama aralığı `[0, chainPos[1]) = [0,2)`
  - `mid=1` → `result[1]=1` → değer 5 < 7 → `lo=2` → `lo==hi` → konum **2**
- `result = [0,1,3,2]` → değerler **3, 5, 7, 9**
- `chainPos` güncelle: `chainPos[0]=1` (2'den küçük, değişmez), `chainPos[1]=2→3`

**Adım 9** — stray = index 4 (değer **4**), tüm zincirde ikili arama `[0,4)`:
- `mid=2` → değer 7 < 4? hayır → `hi=2`
- `mid=1` → değer 5 < 4? hayır → `hi=1`
- `mid=0` → değer 3 < 4? evet → `lo=1` → konum **1**
- `result = [0,4,1,3,2]` → değerler **3, 4, 5, 7, 9** ✓

```
$ ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
```

---

## 6. Neden değerler değil **indeksler** sıralanıyor?

`fordJohnsonVector` `std::vector<int>` değil `std::vector<size_t>` (indeks listesi) döndürür.
Sebep **adım 5'teki eşleştirme**: "sıralanmış büyük"ün hangi çiftten geldiğini bilmemiz lazım.

Değerlerle çalışsaydık, **tekrarlı sayılarda** (`5 5 5 5`) hangi 5'in hangi çiftten geldiği
ayırt edilemezdi. İndeksler benzersiz olduğu için bu sorun yok.

Eşleştirme bir **arama tablosuyla** yapılır — eşleme anında yazılır, sonra tek geçişte okunur:

```cpp
partner[big] = firstWins ? indices[i+1] : indices[i];  // [satır 83] eşleme anında
...
pend.push_back(partner[chain[i]]);                     // [satır 100] tablo okuması
```

Bu sayede eşleştirme **O(n)**. (İlk sürümde her büyük için `bigIdx` baştan taranıyordu → O(n²).)

`sortVector` üç adımlı — [PmergeMe.cpp:132](../ex02/PmergeMe.cpp#L132):

```cpp
indices = [0,1,2,...,n-1]                       // indeks listesi kur
sortedIdx = fordJohnsonVector(seq, indices);    // indeksleri sırala
result[i] = seq[sortedIdx[i]]                   // değerlere geri çevir
```

---

## 7. Jacobsthal sırası — [PmergeMe.cpp:19](../ex02/PmergeMe.cpp#L19)

### Neden gerekli?

`pend` elemanlarını 0,1,2,3… sırayla eklersek, her ekleme öncekilerin konumlarını
kaydırır ve ikili aramanın aralığı "güzel" (`2^k − 1`) büyüklüklere denk gelmez —
bazı aramalar bir karşılaştırma fazla harcar.

Jacobsthal sayıları (`J(k) = J(k-1) + 2·J(k-2)` → `1, 3, 5, 11, 21, 43…`) tam bu
kaydırmayı hesaba katar. Her `(J(k-1), J(k)]` penceresi **büyükten küçüğe** taranır.

### Üretilen sıra

`pend` 0-tabanlı olduğu için `b(t) = pend[t-1]`; 0. indeks hiç üretilmez çünkü
`pend[0]` adım 7'de zaten karşılaştırmasız eklenmiştir.

| `pend.size()` | Ekleme sırası (pend indeksleri) |
|---|---|
| 2 | `1` |
| 3 | `2 1` |
| 5 | `2 1 4 3` |
| 6 | `2 1 4 3 5` |
| 12 | `2 1 4 3 10 9 8 7 6 5 11` |

Fonksiyon 20 satır ve yardımcı dizi kullanmıyor: iki değişken (`prev`, `curr`) ile
pencereler ilerletiliyor, `hi` değeri `n` ile sınırlanıyor.

---

## 8. `chainPos` ve sınırlı ikili arama ⭐

Ford-Johnson'ın özü burası. `pend[j]`'yi yerleştirirken **tüm zinciri taramaya gerek yok**:

> `pend[j]`, çiftteki eşi olan `chain[j]`'den **kesinlikle küçüktür**
> (eşleme adımında öyle seçildi). O hâlde yeri, `chain[j]`'nin bulunduğu
> konumdan **önce** olmak zorundadır.

```cpp
size_t pos = lowerBoundVector(values, result, chainPos[j], values[pend[j]]);
//                                            ^^^^^^^^^^^ üst sınır = eşinin konumu
result.insert(result.begin() + pos, pend[j]);
```

`lowerBoundVector` ([satır 44](../ex02/PmergeMe.cpp#L44)) `std::lower_bound` semantiğinde:
eşit değerlerin **önüne** ekler, yani tekrarlı sayılarda da doğru çalışır.

### `chainPos` neden gerekli?

Her ekleme diziyi kaydırdığı için `chain[j]`'nin konumu sabit kalmaz.
`chainPos[j]` bu konumu canlı tutar ve her eklemeden sonra güncellenir
([satır 115-119](../ex02/PmergeMe.cpp#L115-L119)):

```cpp
for (size_t i = 0; i < chainPos.size(); ++i)
{
    if (chainPos[i] >= pos)     // ekleme noktasından sonrakilerin hepsi 1 kayar
        ++chainPos[i];
}
```

### Ölçülen etki

| n | Knuth F(n) | Lineer arama | Sınırsız ikili arama | **Sınırlı (mevcut)** |
|---|---|---|---|---|
| 21 | 66 | 94 | 78 | **68** |
| 100 | 534 | 1668 | 613 | **529** |
| 500 | 3823 | — | 4267 | **3789** |
| 3000 | 30546 | — | 33472 | **30407** |

Sınırı kaldırmak karşılaştırma sayısını %10-15 artırıp Knuth sınırının **üstüne** çıkarıyor.
Yani `chainPos` bir optimizasyon değil, algoritmanın kendisi.

Küçük n'lerde sınırın 1-2 karşılaştırma üstüne çıkılması, "stray" elemanın tüm zincirde
(sınırsız) aranmasından kaynaklanır — klasik FJ tanımında da böyledir. F(n) zaten
**en kötü durum** üst sınırıdır.

---

## 9. Neden iki ayrı implementasyon?

Subject açıkça söylüyor:

> *"It is strongly advised to implement your algorithm for each container and thus to
> avoid using a generic function."*

Bu yüzden `fordJohnsonVector`/`fordJohnsonDeque` ve `lowerBoundVector`/`lowerBoundDeque`
neredeyse birebir aynı ama **ayrı** yazıldı. Template kullanılsaydı tek fonksiyon olurdu
ve subject'in istediği "her container için ayrı implementasyon" gösterilemezdi.
`PmergeMe.cpp`'nin 252 satırının ~100'ü bu bilinçli ikizlikten geliyor.

### Neden `std::vector` + `std::deque`?

| Container | Özellik | Bu problemde etkisi |
|---|---|---|
| `std::vector` | Tek blok bellek, `insert` sonrası tek `memmove` | Ortaya ekleme hızlı, cache dostu |
| `std::deque` | Parçalı bloklar, rastgele erişim O(1) ama dolaylı | Ortaya ekleme daha pahalı, blok sınırları cache'i bozar |

İkisi de **rastgele erişimli iterator** sunar — `result.begin() + pos` ve `result[mid]`
her ikisinde de çalışır, bu yüzden ikili arama iki tarafta da aynı şekilde yazılabildi.
`std::list` ile bu mümkün olmazdı (ikili arama rastgele erişim ister) — `std::list` bu
yüzden ex01'e ayrıldı.

> **Küçük pragmatizm:** `jacobsthalInsertionOrder` deque yolunda da `std::vector<size_t>`
> döndürür ([satır 215](../ex02/PmergeMe.cpp#L215)). Bu bir veri container'ı değil,
> sadece "hangi sırayla eklenecek" listesi; `std::vector` zaten ex02'nin iki
> container'ından biri olduğu için kural ihlali değil.

---

## 10. `main.cpp`: doğrulama, çıktı ve zamanlama

### Argüman doğrulama — [main.cpp:11](../ex02/main.cpp#L11)

```cpp
static int parseToken(const char *arg)
{
	std::stringstream stream(arg);
	int value;

	if (!(stream >> value) || !stream.eof() || value < 0)
		throw std::runtime_error("Error");

	return value;
}
```

Üç koşul üç ayrı işi yapıyor:

| Koşul | Ne eler |
|---|---|
| `!(stream >> value)` | Sayı olmayanlar (`abc`, boş string) **ve tamsayı taşması** (`2147483648` → failbit) |
| `!stream.eof()` | Arkasında fazlalık kalanlar (`1abc`, `1.5`, `0x10`) |
| `value < 0` | Negatifler (`-1`) |

Ölçülen davranış:

| Girdi | Sonuç |
|---|---|
| `-1 2` / `abc` / `1 2 x` | `Error` |
| `2147483648` / `99999999999999999` | `Error` (taşma) |
| `2147483647` | Kabul (INT_MAX sınırı) |
| `""` / `" "` / `1abc` / `1.5` / `0x10` | `Error` |
| `+7 +3` | Kabul → `3 7` |
| `007` | Kabul → `7` |
| `5 5 5 5` / `0 0 1` / `1` | Kabul (tekrarlar ✓) |
| (argümansız) | `Error` — [main.cpp:32](../ex02/main.cpp#L32) |

Hata `std::runtime_error` olarak fırlatılır, `main` yakalayıp **stderr**'e `Error` basar
ve `1` döner ([main.cpp:76-80](../ex02/main.cpp#L76-L80)).

### Zamanlama — [main.cpp:50-62](../ex02/main.cpp#L50-L62)

```cpp
std::clock_t startVec = std::clock();
std::vector<int> vec;
for (int i = 1; i < argc; ++i)
    vec.push_back(parseToken(argv[i]));      // ← veri yönetimi ÖLÇÜME DAHİL
std::vector<int> sortedVec = sorter.sortVector(vec);
std::clock_t endVec = std::clock();
```

Subject: *"you have to indicate the time used to perform all your operations, **both the
sorting part and the data management part**."*

Bu yüzden her kronometre **kendi container'ının argv'den doldurulmasını** da kapsıyor.
İlk döngü ([satır 43-45](../ex02/main.cpp#L43-L45)) ölçüm dışı — o sadece doğrulama ve
`Before:` satırı için. Hatalı girdi varsa program hiçbir şey basmadan çıkar.

`std::clock()` C++98'de mevcut; `<chrono>` C++11 olduğu için yasak.
Sonuç `CLOCKS_PER_SEC`'e bölünüp `1000000` ile çarpılarak mikrosaniyeye çevrilir.

> `(void)sortedDeq;` ([satır 74](../ex02/main.cpp#L74)) — deque sonucu hesaplanır ama
> ekrana basılmaz; subject tek bir `After:` satırı istiyor. Cast, `-Wunused-variable`
> uyarısını (dolayısıyla `-Werror` hatasını) engellemek için.

### Ölçülen süreler (3000 eleman)

```
Time to process a range of 3000 elements with std::vector : ~12000 us
Time to process a range of 3000 elements with std::deque  : ~147000 us
```

**Farkın açıklaması (savunmada sorulur):** Ekleme sayısı ikisinde de aynı, fark
bellek düzeninde. `std::vector` bitişik bellek tuttuğu için ortaya ekleme tek bir
`memmove` ile hallolur ve CPU cache'i verimli kullanılır. `std::deque` ise sabit
boyutlu blokların bir indeks tablosuyla yönetildiği yapıdır; ortaya ekleme blok blok
kaydırma gerektirir ve erişim bir seviye dolaylıdır — bu da cache isabetini düşürür.

---

## 11. Subject kuralları kontrol listesi

- ✅ OCF: 4 üye fonksiyon — [PmergeMe.cpp:4-10](../ex02/PmergeMe.cpp#L4-L10)
- ✅ Header'da fonksiyon gövdesi yok, include guard var, tek başına derleniyor
- ✅ İki farklı container, ikisi de önceki exercise'lerde kullanılmamış
- ✅ Her container için **ayrı** implementasyon (generic fonksiyon yok)
- ✅ `*printf`, `*alloc`, `free`, `using namespace`, `friend` yok
- ✅ `<algorithm>` kullanılmadı — **Module 09'da serbesttir**, ikili arama bilinçli olarak elle yazıldı
- ✅ C++98 (`<chrono>` değil `<ctime>`)
- ✅ `new`/`delete` yok → leak imkânsız (valgrind temiz, hata yolları dahil)
- ✅ 3000 eleman, tekrarlar dahil test edildi
- ✅ Makefile: `all clean fclean re $(NAME)`, relink yok

---

## 12. Savunmada sorulabilecekler

**S: Ford-Johnson'ı kısaca anlat.**
→ Elemanları ikişer eşleyip büyükleri özyinelemeli sıralarım (ana zincir). Küçükleri
Jacobsthal sırasıyla, eşlerinin konumundan önceki aralıkta ikili aramayla yerleştiririm.
Böylece karşılaştırma sayısı teorik alt sınıra çok yaklaşır.

**S: Neden Jacobsthal?**
→ Ekleme yapıldıkça dizi büyüdüğü için, ikili aramanın her seferinde tam `2^k − 1`
boyutunda bir aralığa denk gelmesini sağlar; aksi hâlde bazı aramalar bir karşılaştırma
israf eder.

**S: `pend[0]`'ı neden karşılaştırmadan ekliyorsun?**
→ `pend[0]`, en küçük büyük elemanın (`chain[0]`) eşidir ve ondan küçüktür.
`result` o an sadece büyüklerden oluştuğu için `pend[0]` hepsinden küçüktür.

**S: `chainPos` ne işe yarıyor?**
→ Her eklemede dizi kaydığı için eşlerin konumu değişir. `chainPos[j]` `chain[j]`'nin
güncel konumunu tutar; ikili aramanın üst sınırı budur. Kaldırırsam karşılaştırma sayısı
%10-15 artıyor ve Knuth sınırının üstüne çıkıyor — ölçtüm.

**S: Neden indeks sıralıyorsun, değer değil?**
→ Tekrarlı sayılarda "bu büyük hangi çiftten geldi" sorusunu değerlerle cevaplayamazdım.
İndeksler benzersiz olduğu için eşleştirme kesin.

**S: Tek sayıda eleman olursa?**
→ Sondaki eleman "stray" olarak ayrılır, eşlemeye girmez, en sonda tüm zincirde ikili
aramayla yerleştirilir.

**S: Neden vector daha hızlı?**
→ Bitişik bellek + tek `memmove` + cache dostu. Deque parçalı bloklar tuttuğu için
ortaya ekleme daha pahalı ve erişim dolaylı.

**S: Neden iki ayrı fonksiyon yazdın, template değil?**
→ Subject generic fonksiyondan kaçınmayı öneriyor; her container için ayrı
implementasyon istiyor.

**S: Module 09'da `<algorithm>` serbest, neden `std::lower_bound` kullanmadın?**
→ Tercih. `result[]` indeks tutuyor, karşılaştırma `values[idx]` üzerinden yapılıyor;
C++98'de lambda olmadığı için comparator functor yazmak gerekirdi. Elle yazınca aramanın
üst sınırının `chainPos[j]` olduğu doğrudan görünüyor.

**S: Taşmayı nasıl yakalıyorsun?**
→ `stream >> value` bir `int`'e okumaya çalışır; değer `INT_MAX`'ı aşarsa stream
failbit kurar ve koşul başarısız olur. `2147483648` reddedilir, `2147483647` kabul edilir.

---

## 13. Test komutları

```bash
cd ex02 && make

# subject örneği
./PmergeMe 3 5 9 7 4
# Before: 3 5 9 7 4
# After: 3 4 5 7 9

# checklist: 5-10 sayı
./PmergeMe 5 2 9 1 7 3 8

# checklist: 3000 sayı (Linux)
./PmergeMe `shuf -i 1-1000 -n 3000 | tr "\n" " "`
# macOS: ./PmergeMe `jot -r 3000 1 1000 | tr '\n' ' '`

# doğruluk kontrolü (sort -n ile karşılaştır)
ARG=$(shuf -i 1-1000 -n 3000 -r | tr '\n' ' ')
diff <(./PmergeMe $ARG | sed -n '2p' | sed 's/^After: //' | tr ' ' '\n') \
     <(echo $ARG | tr ' ' '\n' | sort -n) && echo OK

# hata yolları
./PmergeMe "-1" "2"      # Error
./PmergeMe abc           # Error
./PmergeMe 2147483648    # Error
./PmergeMe               # Error

# leak kontrolü
valgrind --leak-check=full ./PmergeMe 3 5 9 7 4
```
