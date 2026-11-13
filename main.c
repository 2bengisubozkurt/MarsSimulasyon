#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Degeri 0 ile 100 arasinda tutar.
int sinirla(int deger) {
    if (deger < 0) return 0;
    if (deger > 100) return 100;
    return deger;
}

// Oyuncunun kaynaklarini ve kritik uyarilarini ekrana yazar.
void durumGoster(int saglik, int enerji, int oksijen, int su,
                 int parca, int hasar, int gun, int tur, int kilitMuhurlu) {
    printf("\n--- DURUM RAPORU ---\n");
    printf("Gun: %d | Tur: %d\n", gun, tur);
    printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d | Yedek parca: %d | Modul hasari: %d\n", su, parca, hasar);
    if (kilitMuhurlu == 1) {
        printf("Hava kilidi: Muhurlu\n");
    } else {
        printf("Hava kilidi: Acik\n");
    }

    if (oksijen < 25) printf("UYARI: Oksijen kritik!\n");
    if (saglik < 30) printf("UYARI: Saglik kritik!\n");
    if (hasar > 70) printf("UYARI: Modul hasari yuksek!\n");
    if (enerji < 20) printf("UYARI: Enerji dusuk!\n");
    if (su == 0) printf("UYARI: Su kalmadi!\n");
    if (parca == 0) printf("UYARI: Yedek parca kalmadi!\n");

    if (oksijen >= 25 && saglik >= 30 && enerji >= 20 &&
        hasar <= 70 && su > 0 && parca > 0)
        printf("TUM SISTEMLER NORMAL\n");
}

int main(void) {
    // Oyuncunun baslangictaki saglik, enerji, oksijen ve malzemeleri
    int saglik = 100, enerji = 80, oksijen = 80;
    int su = 12, parca = 3, hasar = 20;
    // Gun 1'den baslar. Kilit 0 ise acik, 1 ise muhurludur.
    int gun = 1, tur = 0, kilitMuhurlu = 0;
    int firtinaTuru = 3, oyunBitti = 0, kazandi = 0;
    char zorluk, komut;

    // Rastgele olaylarin her program acilisinda degismesini saglar.
    srand((unsigned int)time(NULL));

    // Gecersiz zorluk girilirse secim yeniden istenir.
    do {
        printf("Zorluk secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        zorluk = (char)toupper((unsigned char)zorluk);

        switch (zorluk) {
            case 'K':
                enerji = 100; su = 16; oksijen = 90;
                firtinaTuru = 3;
                break;
            case 'N':
                enerji = 80; su = 12; oksijen = 80;
                firtinaTuru = 5;
                break;
            case 'Z':
                enerji = 65; su = 8; oksijen = 70;
                hasar = 30; firtinaTuru = 7;
                break;
            default:
                printf("Gecersiz zorluk. K, N veya Z girin.\n");
        }
    } while (zorluk != 'K' && zorluk != 'N' && zorluk != 'Z');

    printf("\nKomutlar: G O T D U K H Q\n");

    do {
        printf("\nKomut girin: ");
        scanf(" %c", &komut);

        int gecerliTur = 1;

        switch (komut) {
            case 'g':
            case 'G':
            {
                // Kesif 15 enerji ve 10 oksijen harcar; once yeterliligini kontrol et.
                if (enerji < 15 || oksijen < 10) {
                    printf("Kesif iptal: enerji veya oksijen yetersiz.\n");
                    gecerliTur = 0;
                    break;
                }

                int zar = rand() % 100;
                int esik;

                // Enerji ve oksijen iyiyse su bulma esigi yukselir.
                if (enerji > 40 && oksijen > 30) {
                    esik = 55;
                } else {
                    esik = 25;
                }
                enerji -= 15;
                oksijen -= 10;
                printf("Kesif zari: %d / Esikler: su zar<%d, parca zar<%d, yaralanma zar<10, modul hasari>70\n",
                       zar, esik, esik + 20);

                // Zar esigin altindaysa su, sonraki aralikta yedek parca bulunur.
                if (zar < esik) {
                    su += 2;
                    printf("Kesifte su buldunuz (+2).\n");
                } else if (zar < esik + 20) {
                    parca++;
                    printf("Yedek parca buldunuz (+1).\n");
                } else {
                    printf("Kesiften eli bos dondunuz.\n");
                }

                // Yaralanma, dusuk zar veya cok yuksek modul hasariyla olur.
                if (zar < 10 || hasar > 70) {
                    saglik -= 10;
                    printf("Kesif sirasinda yaralandiniz (-10 saglik).\n");
                }
                break;
            }

            // Oksijen uretme komutu
            case 'o':
            case 'O': {
                int miktar;
                printf("Kullanilacak su miktari: ");
                scanf("%d", &miktar);

                if (miktar < 2 || miktar > su || enerji < 5) {
                    printf("Uretim iptal: su miktari veya enerji uygun degil.\n");
                    gecerliTur = 0;
                    break;
                }

                // Mod (%) ile tek sayida bir su birimini depoda birakiriz.
                int kullanilanSu = miktar - (miktar % 2);
                int uretilenOksijen = (kullanilanSu / 2) * 3;
                int eklenen = sinirla(oksijen + uretilenOksijen) - oksijen;

                su -= kullanilanSu;
                enerji -= 5;
                oksijen = sinirla(oksijen + uretilenOksijen);
                printf("%d birim su kullanildi, %d oksijen eklendi.\n",
                       kullanilanSu, eklenen);
                if (miktar % 2 != 0)
                    printf("Tek miktar girildi: 1 birim su depoda kaldi.\n");
                break;
            }

            // Modul hasarina gore farkli tamir miktarlari uygulanir
            case 't':
            case 'T':
                if (parca < 1 || enerji < 5) {
                    printf("Tamir iptal: yedek parca veya enerji yetersiz.\n");
                    gecerliTur = 0;
                } else if (hasar <= 30) {
                    parca--; enerji -= 5; hasar -= 15;
                    printf("Hafif hasar tamir edildi.\n");
                } else if (hasar <= 70) {
                    parca--; enerji -= 5; hasar -= 25;
                    printf("Orta hasar tamir edildi.\n");
                } else {
                    if (parca >= 2) {
                        parca = parca - 2;
                    } else {
                        parca = parca - 1;
                    }
                    enerji -= 5; hasar -= 30;
                    printf("Agir hasar tamir edildi.\n");
                }
                break;

            // Durum komutu bilgi verir, tur harcamaz
            case 'd':
            case 'D':
                durumGoster(saglik, enerji, oksijen, su, parca,
                            hasar, gun, tur, kilitMuhurlu);
                gecerliTur = 0; // Durum raporu tur harcamaz.
                break;

            // Dinlenme enerji ve sagligi artirir, oksijeni azaltir
            case 'u':
            case 'U':
                // Dinlenmek enerji kazandirir, bu nedenle enerji harcama kontrolu yoktur.
                enerji = sinirla(enerji + 20);
                oksijen = oksijen - 10;

                // Oksijen 20'nin altindaysa saglik artmaz, 10 azalir.
                if (oksijen < 20) {
                    saglik = saglik - 10;
                    printf("Oksijen dusuk: saglik 10 azaldi.\n");
                } else {
                    saglik = sinirla(saglik + 10);
                    printf("Dinlendiniz. Saglik ve enerji artti.\n");
                }
                break;

            // FOR dongusu her firtina turunda bir olay uretir
            case 'k':
            case 'K': {
                int hasarliTur = 0, toplamSaglikKaybi = 0, toplamOksijenKaybi = 0;

                if (enerji < 10) {
                    printf("Firtina komutu iptal: enerji yetersiz.\n");
                    gecerliTur = 0;
                    break;
                }

                for (int i = 1; i <= firtinaTuru; i++) {
                    int zar = rand() % 100;
                    printf("Firtina turu %d, zar: %d / Esikler: <30 saglik, <60 oksijen, <80 modul hasari\n",
                           i, zar);

                    // Zar araligi hangi firtina olayinin olacagini belirler.
                    if (zar < 30) {
                        int kayip;

                        // Mod (%) ile cift tur bulunur; cift turda kayip iki kat olur.
                        if (i % 2 == 0) {
                            kayip = 10;
                        } else {
                            kayip = 5;
                        }
                        saglik -= kayip;
                        toplamSaglikKaybi += kayip;
                        hasarliTur++;
                        printf("Ruzgar hasari: -%d saglik.\n", kayip);
                    } else if (zar < 60) {
                        if (kilitMuhurlu == 1) {
                            printf("Kilit muhurlu: sizinti olayi atlandi.\n");
                            continue;
                        }
                        oksijen -= 8;
                        toplamOksijenKaybi += 8;
                        hasarliTur++;
                        printf("Oksijen sizintisi: -8.\n");
                    } else if (zar < 80) {
                        hasar += (i % 2 == 0) ? 10 : 5;
                        hasarliTur++;
                        printf("Modul hasari artti.\n");
                    } else {
                        printf("Firtinadan hasarsiz korundunuz.\n");
                    }

                    saglik = sinirla(saglik);
                    oksijen = sinirla(oksijen);
                    hasar = sinirla(hasar);

                    if (saglik == 0 || oksijen == 0) {
                        printf("Kritik deger sifirlandi; firtina durduruldu.\n");
                        break;
                    }
                }
                enerji -= 10;
                printf("Firtina ozeti: hasarli tur=%d, saglik kaybi=%d, oksijen kaybi=%d\n",
                       hasarliTur, toplamSaglikKaybi, toplamOksijenKaybi);
                break;
            }

            // Gun numarasindan turetilen sifre icin en fazla uc deneme verilir
            case 'h':
            case 'H': {
                char sifre = (char)('A' + (gun % 26));
                char giris;
                int deneme = 0, basarili = 0;

                if (enerji < 5) {
                    printf("Hava kilidi iptal: en az 5 enerji gerekli.\n");
                    gecerliTur = 0;
                    break;
                }

                printf("Sifre ipucu: Alfabenin A harfinden bugunun gun sayisi kadar ilerleyin.\n");
                do {
                    // Her yanlis cevap 5 enerji harcar; enerjisi yetmeyen yeni deneme yapamaz.
                    if (enerji < 5) {
                        printf("Yeni deneme icin enerji yetersiz.\n");
                        break;
                    }
                    printf("Hava kilidi sifresi (A-Z): ");
                    scanf(" %c", &giris);
                    giris = (char)toupper((unsigned char)giris);
                    deneme++;

                    if (giris == sifre) {
                        basarili = 1;
                    } else {
                        enerji -= 5;
                        printf("Yanlis. ");
                        if (giris < sifre) printf("Ileri git.\n");
                        else printf("Geri git.\n");
                    }
                } while (!basarili && deneme < 3 && enerji >= 5);

                if (basarili) {
                    kilitMuhurlu = 1;
                    printf("Dogru sifre. Hava kilidi muhurlendi.\n");
                } else if (deneme == 3) {
                    hasar += 20;
                    printf("Denemeler bitti; modul hasari +20.\n");
                }
                break;
            }

            // Q oyunu bitirir ve PDF kuralina gore gecerli tur sayilir
            case 'q':
            case 'Q':
                printf("Oyundan cikiliyor.\n");
                oyunBitti = 1;
                break;

            default:
                printf("Taninmayan komut. Komut suresi harcanmadi.\n");
                gecerliTur = 0;
        }

        // D ve tanimsiz komut disinda tur sayaci artar.
        // D ve tanimsiz komutlar zaman harcamaz; Q dahil gecerli komutlar sayilir.
        if (gecerliTur) {
            tur++;

            if (tur % 3 == 0) {
                gun++;
                oksijen -= 8;
                printf("Yeni gun: %d. Gun basinda oksijen -8.\n", gun);
                if (hasar > 70) saglik -= 5;
            }
        }

        // Her komut sonunda bu dort degeri 0-100 araliginda tut.
        saglik = sinirla(saglik);
        enerji = sinirla(enerji);
        oksijen = sinirla(oksijen);
        hasar = sinirla(hasar);

        if (saglik == 0 || oksijen == 0) {
            printf("Saglik veya oksijen sifirlandi. Oyun kaybedildi.\n");
            oyunBitti = 1;
        } else if (gun >= 15) {
            printf("Kurtarma ekibi geldi. Oyunu kazandiniz!\n");
            kazandi = 1;
            oyunBitti = 1;
        }

    } while (!oyunBitti);

    // Puan, odevde verilen formulle hesaplanir.
    int puan = (gun * 100) + saglik + oksijen - hasar;
    printf("\n--- SONUC RAPORU ---\n");
    if (kazandi == 1) {
        printf("Sonuc: Kazandin\n");
    } else if (saglik == 0 || oksijen == 0) {
        printf("Sonuc: Kaybettin\n");
    } else {
        printf("Sonuc: Cikis\n");
    }
    printf("Hayatta kalinan gun: %d | Toplam tur: %d\n", gun, tur);
    printf("Saglik=%d Enerji=%d Oksijen=%d Su=%d Parca=%d Hasar=%d\n",
           saglik, enerji, oksijen, su, parca, hasar);
    printf("Puan: %d\n", puan);

    return 0;
}
