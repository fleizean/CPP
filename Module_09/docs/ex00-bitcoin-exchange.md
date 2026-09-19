# ex00 — BitcoinExchange (`btc`)

> Bir CSV veritabanındaki tarihsel bitcoin kurlarını kullanarak, girdi dosyasındaki
> `tarih | miktar` satırlarının o günkü karşılığını hesaplayan program.

---

## 1. Subject ne istiyor?

| Kural | Nerede karşılanıyor |
|---|---|
| Program adı `btc` | [`Makefile`](../ex00/Makefile) → `NAME = btc` |
| Argüman olarak bir dosya alır | [`main.cpp:6`](../ex00/main.cpp#L6) |
| Satır formatı `date \| value` | [`processInput`](../ex00/BitcoinExchange.cpp#L154) |
| Geçerli tarih `Yıl-Ay-Gün` | [`isValidDate`](../ex00/BitcoinExchange.cpp#L56) |
| Geçerli değer: 0–1000 arası float/pozitif tamsayı | [`processInput:169-178`](../ex00/BitcoinExchange.cpp#L169-L178) |
| **En az bir container** | `std::map<std::string, double>` |
| Tarih DB'de yoksa **bir alttaki** tarih kullanılır | [`findRate`](../ex00/BitcoinExchange.cpp#L118) |

> ⚠️ **Dikkat:** `data.csv` repoda yok — subject'in ek dosyası olduğu için evaluation
> sırasında intranetten indirilip `ex00/` klasörüne konur. Program onu **çalışma
> dizininden** açar ([`main.cpp:16`](../ex00/main.cpp#L16)), yani `./btc`'yi çalıştırdığın
> dizinde `data.csv` bulunmalı.

---

## 2. Dosya haritası

```
ex00/
├── Makefile              → btc
├── main.cpp              → argüman kontrolü + üst seviye hata yakalama
├── BitcoinExchange.hpp   → sınıf arayüzü (sadece bildirimler)
└── BitcoinExchange.cpp   → tüm implementasyon
```

| Üye | Görev |
|---|---|
| `loadDatabase(path)` | `data.csv`'yi okuyup `_database` map'ini doldurur (public) |
| `processInput(path)` | Girdi dosyasını satır satır işler, sonucu basar (public, `const`) |
| `splitLine(line, sep, left, right)` | Satırı ayırıcıya göre böler + boşlukları kırpar (private) |
| `isHeader(line)` | Satır başlık mı (`date \| value` / `date,exchange_rate`) (private) |
| `isValidDate(date)` | Takvim doğrulaması, artık yıl dahil (private) |
| `findRate(date)` | Tarihe karşılık gelen kuru bulur, yoksa **alt** tarihi kullanır (private) |
| `_database` | `std::map<std::string, double>` — tarih → kur |

---

## 3. Program akışı

```
main(argc, argv)
  │
  ├─ argc != 2 ────────────────────► "Error: could not open file." + return 1
  │
  ├─ btc.loadDatabase("data.csv")
  │     └─ dosya açılamazsa throw ──► catch → "Error: could not open file." + return 1
  │
  └─ btc.processInput(argv[1])
        └─ dosya açılamazsa throw ──► catch → "Error: could not open file." + return 1
              │
              └─ her satır için:
                   boş satır?        → atla
                   ilk satır başlık? → atla
                   '|' ile bölünemiyor VEYA tarih geçersiz? → "Error: bad input => <satır>"
                   değer sayı değil / fazla token var?       → "Error: bad input => <satır>"
                   değer < 0                                 → "Error: not a positive number."
                   değer > 1000                              → "Error: too large a number."
                   aksi halde → "<tarih> => <değer> = <değer * kur>"
```

**Kritik nokta:** Hata mesajları `continue` ile devam eder, program **asla** yarıda kesilmez.
Checklist bunu açıkça istiyor: *"The program must not stop its execution before having
performed the operations on the whole file."*

---

## 4. Neden `std::map`? (savunmada mutlaka sorulur)

Üç sebep:

1. **Otomatik sıralı tutar.** `std::map` kırmızı-siyah ağaçtır, anahtarlar her zaman sıralıdır.
   "En yakın alt tarih" problemi bu sayede tek fonksiyon çağrısına iner.
2. **`lower_bound` hazır gelir.** O(log n) ile "bu tarihten büyük-eşit ilk kayıt" bulunur.
   `std::unordered_map` (zaten C++11, yasak) veya `std::vector` ile bunu elle yazmak gerekirdi.
3. **Anahtar `std::string` ve sözlük sırası = takvim sırası.** `YYYY-MM-DD` formatı sıfır
   dolgulu ve sabit uzunlukta olduğu için `"2011-01-09" < "2011-01-10"` karşılaştırması
   takvim sırasıyla **birebir** örtüşür. Tarihi `struct`'a çevirip karşılaştırıcı yazmaya
   gerek kalmaz.

> **"Neden vector değil?"** → Vector'de de ikili arama yapılabilirdi ama sıralamayı
> elle garanti etmek gerekirdi; ayrıca `std::vector` ve `std::deque` ex02 için,
> `std::list` ex01 için saklandı (modül kuralı: bir container bir kez kullanılır).

---

## 5. Fonksiyonlar tek tek

### `splitLine` — [BitcoinExchange.cpp:26](../ex00/BitcoinExchange.cpp#L26)

```cpp
bool splitLine(const std::string &line, char sep, std::string &left, std::string &right) const
```

- Satırdaki **ilk** ayırıcıyı bulur (`find`). Yoksa `false` döner.
- `left` = ayırıcının solu, `right` = sağı.
- `left`'in **sonundaki**, `right`'ın **başındaki ve sonundaki** boşluk/tab karakterlerini siler.
- `right`'ın sonundan ayrıca `\r` de silinir → **Windows'ta yazılmış CRLF satır sonlu
  dosyalar sorunsuz çalışır.**

Hem `'|'` (girdi dosyası) hem `','` (veritabanı) için aynı fonksiyon kullanılıyor.

> **Bilinçli sınır:** `left`'in *başındaki* boşluk kırpılmaz. Yani `"   2011-01-03 | 4"`
> → `bad input`. Subject formatı `"date | value"` olarak sabitlediği için bu kabul edilebilir.

### `isHeader` — [BitcoinExchange.cpp:45](../ex00/BitcoinExchange.cpp#L45)

Satırı önce `'|'`, olmazsa `','` ile bölüp sol tarafın tam olarak `"date"` olup olmadığına bakar.

**Neden var?** Önceden ilk satır **koşulsuz** atlanıyordu. Başlıksız bir dosya verildiğinde
ilk veri satırı sessizce kayboluyordu — bu da checklist'in "tüm dosya işlenmeli" şartını
ihlal ediyordu. Şimdi satır gerçekten başlıksa atlanır, değilse normal işlenir.

### `isValidDate` — [BitcoinExchange.cpp:56](../ex00/BitcoinExchange.cpp#L56)

Sırayla:
1. Uzunluk tam 10 ve 4. ile 7. karakter `'-'` mi?
2. Kalan 8 karakterin hepsi rakam mı?
3. `year >= 1000`, `1 <= month <= 12`, `day >= 1`
4. Aya göre gün sayısı — **artık yıl kuralı tam** (`%4==0 && (%100!=0 || %400==0)`)

Yani `2001-42-42` → geçersiz, `2011-02-29` → geçersiz, `2012-02-29` → geçerli.

### `loadDatabase` — [BitcoinExchange.cpp:87](../ex00/BitcoinExchange.cpp#L87)

- Dosya açılamazsa `std::runtime_error` fırlatır.
- İlk satır başlıksa atlanır (`date,exchange_rate`).
- Her satır `','` ile bölünür; tarih geçersizse **sessizce** atlanır (veritabanı bizim
  kontrolümüzde değil, hata basmak anlamsız).
- Kur `std::atof` ile `double`'a çevrilip `_database[date]`'e yazılır.

### `findRate` — [BitcoinExchange.cpp:118](../ex00/BitcoinExchange.cpp#L118) ⭐ en kritik

```cpp
std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

if (it != _database.end() && it->first == date)   // (1) tam eşleşme
    return it->second;
if (it == _database.begin())                      // (2) daha eski kayıt yok
    throw std::runtime_error("no earlier date available");
--it;                                             // (3) bir önceki = en yakın ALT tarih
return it->second;
```

`lower_bound(date)` → "`date`'ten **büyük veya eşit** ilk kayıt".

| Durum | `lower_bound` sonucu | Yapılan |
|---|---|---|
| Tarih DB'de var | tam o kayıt | doğrudan döndür |
| Tarih DB'nin en başından önce | `begin()` | daha eski kayıt yok → exception |
| Tarih arada bir yerde | bir **sonraki** tarih | `--it` → bir **önceki** tarih |
| Tarih DB'nin sonundan sonra | `end()` | `--it` → son kayıt |

**Örnek** (`data.csv`'de `2011-01-04 → 0.3`, `2011-01-07 → 0.32` var, arası boş):

```
2011-01-05 → lower_bound = 2011-01-07 → --it → 2011-01-04 → kur 0.3  ✓
2011-01-06 → lower_bound = 2011-01-07 → --it → 2011-01-04 → kur 0.3  ✓
```

### `processInput` — [BitcoinExchange.cpp:131](../ex00/BitcoinExchange.cpp#L131)

Değer ayrıştırma numarası ([satır 160-167](../ex00/BitcoinExchange.cpp#L160-L167)):

```cpp
std::istringstream iss(valueStr);
double value;
char extra;
if (!(iss >> value) || (iss >> extra))   // sayı okunamadı VEYA arkasında fazlalık var
    → bad input
```

İkinci koşul önemli: `"1 2"` girdisinde `value=1` okunur ama `extra='2'` de okunabildiği
için satır reddedilir. Bu olmasaydı `"2011-01-03 | 1 abc"` sessizce kabul edilirdi.

---

## 6. `setprecision(10)` neden var? — [satır 140](../ex00/BitcoinExchange.cpp#L140)

`std::cout`'un varsayılan hassasiyeti **6 anlamlı basamaktır**. Bu iki soruna yol açıyordu:

| Girdi | Önce (float, varsayılan) | Şimdi (double, precision 10) | Gerçek değer |
|---|---|---|---|
| `2022-03-29 \| 3` | `141348` | `141347.79` | 141347.79 |
| `2022-03-29 \| 999.99` | `4.71155e+07` | `47115458.84` | 47115458.8407 |

Checklist *"Please compare some dates manually with the specified value"* diyor —
yuvarlanmış veya bilimsel gösterimli sayı elle karşılaştırmada sorun çıkarır.

**Neden `std::fixed` değil?** `std::fixed` sabit ondalık basamak sayısı dayatır ve
subject örneğindeki `= 0.9` çıktısını `= 0.90` yapardı. Varsayılan (bilimsel olmayan)
biçimde `precision(10)` kullanmak hem `0.9`'u hem `47115458.84`'ü doğru basar:
sonuç en fazla ~4.7×10⁷ olabileceği için 10 anlamlı basamak bilimsel gösterime hiç düşmez.

---

## 7. Hata mesajları tablosu

| Durum | Mesaj | Akış |
|---|---|---|
| Argüman yok / fazla | `Error: could not open file.` | `return 1` |
| Dosya açılamıyor | `Error: could not open file.` | `return 1` |
| `\|` yok veya tarih geçersiz | `Error: bad input => <satır>` | devam |
| Değer sayı değil / fazla token | `Error: bad input => <satır>` | devam |
| DB'den eski tarih | `Error: bad input => <satır>` | devam |
| Değer < 0 | `Error: not a positive number.` | devam |
| Değer > 1000 | `Error: too large a number.` | devam |

Hepsi **stdout**'a yazılır — subject'in örnek çıktısı da hata satırlarını normal
çıktıyla aynı akışta gösteriyor.

---

## 8. Subject kuralları kontrol listesi

- ✅ OCF: varsayılan ctor, copy ctor, `operator=`, dtor — [satır 10-24](../ex00/BitcoinExchange.cpp#L10-L24)
- ✅ Header'da fonksiyon gövdesi yok, include guard var
- ✅ Header kendi bağımlılıklarını include ediyor (`<map>`, `<string>`)
- ✅ `*printf`, `*alloc`, `free`, `using namespace`, `friend` yok
- ✅ C++98 (`-std=c++98` ile uyarısız derleniyor)
- ✅ `new`/`delete` hiç kullanılmıyor → leak imkânsız (valgrind temiz)

---

## 9. Bilinen tasarım kararları

| Durum | Davranış | Gerekçe |
|---|---|---|
| Boş dosya | Hiçbir çıktı yok, crash yok | İşlenecek satır yok |
| DB'den eski tarih | `bad input` mesajı | Subject ayrı mesaj tanımlamıyor |
| Dizin argümanı (`./btc .`) | Sessiz, crash yok | `ifstream` dizini açar ama `getline` başarısız olur |
| Tarih öncesi boşluk | `bad input` | Subject formatı `date \| value` olarak sabit |
| `1e3` gibi değer | Kabul (= 1000) | `istringstream >> double` bilimsel gösterimi anlar |

---

## 10. Savunmada sorulabilecekler

**S: Neden `std::map`?**
→ Otomatik sıralı + `lower_bound` hazır + `YYYY-MM-DD` string sırası takvim sırasına eşit.

**S: "En yakın alt tarih"i nasıl buluyorsun?**
→ `lower_bound` büyük-eşit ilkini verir; tam eşleşme değilse `--it` ile bir öncekine
geçerim — o da tanım gereği `date`'ten küçük **en büyük** tarihtir. `begin()`'deysem
daha eski kayıt yoktur.

**S: Program neden hatada durmuyor?**
→ Her hata `continue` ile satır bazında ele alınıyor; sadece dosya açılamama durumu
exception fırlatıp programı sonlandırıyor.

**S: Tarih doğrulamasında artık yılı nasıl ele alıyorsun?**
→ `year%4==0 && (year%100!=0 || year%400==0)` → Şubat 29 çeker. `2012-02-29` geçerli,
`2011-02-29` değil.

**S: `float` yerine neden `double`?**
→ `float` 7 anlamlı basamak tutar; kur ~47115.93 ve değer 1000'e kadar çıkabildiği için
çarpım 4.7×10⁷ olur ve `float` hassasiyeti yetmez.

---

## 11. Test komutları

```bash
cd ex00 && make
# data.csv'yi bu klasöre koy

# subject örneği
printf 'date | value\n2011-01-03 | 3\n2011-01-03 | 2\n2011-01-03 | 1\n2011-01-03 | 1.2\n2011-01-09 | 1\n2012-01-11 | -1\n2001-42-42\n2012-01-11 | 1\n2012-01-11 | 2147483648\n' > input.txt
./btc input.txt

# hata yolları
./btc                       # Error: could not open file.
./btc yok.txt               # Error: could not open file.
: > bos.txt && ./btc bos.txt   # çıktı yok, crash yok

# en yakın alt tarih
printf 'date | value\n2011-01-05 | 1\n2011-01-06 | 1\n' > near.txt
./btc near.txt              # ikisi de 2011-01-04 kurunu (0.3) kullanmalı

# leak kontrolü
valgrind --leak-check=full ./btc input.txt
```
