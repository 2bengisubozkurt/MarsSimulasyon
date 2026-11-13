# Mars Simülasyonu

Mars Simülasyonu, C dilinde yazılmış, terminal üzerinden oynanan bir hayatta kalma oyunudur. Oyuncu; sağlık, enerji ve oksijen seviyelerini yönetirken su ve yedek parça toplar, modülü onarır ve 15. güne kadar hayatta kalmaya çalışır. Rastgele keşif ve fırtına olayları her oyunu farklı kılar.

## Gereksinimler

- C99 uyumlu bir C derleyicisi (GCC, Clang veya benzeri)
- macOS, Linux ya da Windows üzerinde terminal

## Derleme ve çalıştırma

macOS veya Linux'ta proje klasöründe şu komutları çalıştırın:

```sh
cc -std=c99 -Wall -Wextra -o mars main.c
./mars
```

Windows'ta MinGW gibi GCC sağlayan bir araç zinciriyle derleyip `mars.exe` dosyasını çalıştırabilirsiniz:

```sh
gcc -std=c99 -Wall -Wextra -o mars.exe main.c
mars.exe
```

Program açıldığında kolay (`K`), normal (`N`) veya zor (`Z`) zorluk seviyelerinden birini seçin. Ardından komutları girerek kaynaklarınızı yönetin.

## Komutlar

Komutlar büyük veya küçük harfle girilebilir.

| Komut | Eylem | Tur harcar mı? |
| --- | --- | --- |
| `G` | Keşfe çıkar; su veya yedek parça bulabilir, yaralanma riski vardır. | Evet |
| `O` | Belirttiğiniz miktarda suyu oksijene dönüştürür. Çift miktarlar kullanılır; tek miktarda 1 birim su depoda kalır. | Evet |
| `T` | Yedek parça ve enerji kullanarak modülü onarır. | Evet |
| `D` | Sağlık, enerji, oksijen, su, parça ve modül hasarı durumunu gösterir. | Hayır |
| `U` | Dinlenerek enerji ve sağlık kazanmayı dener; oksijen azalır. | Evet |
| `K` | Bir fırtınaya karşı koyar. Fırtına süresi seçilen zorluk seviyesine göre değişir. | Evet |
| `H` | Hava kilidini mühürlemek için gün numarasına bağlı şifreyi tahmin etmeye çalışır. | Evet |
| `Q` | Oyundan çıkar ve sonuç raporunu gösterir. | Evet |

Her üç geçerli turda bir gün geçer ve gün başında oksijen azalır. Sağlık veya oksijen sıfıra inerse oyun kaybedilir. 15. güne ulaşmak kurtarma ekibinin gelmesini ve oyunun kazanılmasını sağlar.

## Zorluk seviyeleri

| Seviye | Başlangıç enerjisi | Başlangıç suyu | Başlangıç oksijeni | Fırtına turu |
| --- | ---: | ---: | ---: | ---: |
| Kolay (`K`) | 100 | 16 | 90 | 3 |
| Normal (`N`) | 80 | 12 | 80 | 5 |
| Zor (`Z`) | 65 | 8 | 70 | 7 |

Zor seviyede modül hasarı 30'dan başlar; diğer seviyelerde başlangıç hasarı 20'dir.

## Puanlama

Oyun sonunda puan şu formülle hesaplanır:

```text
(gün × 100) + sağlık + oksijen − modül hasarı
```

## Proje dosyaları

- `main.c`: Oyunun kaynak kodu
- `README.md`: Kurulum, komutlar ve oyun kuralları

© 2026 Mars Simülasyonu katkıcıları.
