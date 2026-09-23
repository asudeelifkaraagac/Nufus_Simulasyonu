/** 
* 
* @author Asude Elif Karaağaç
* @since 28.04.2026
* <p> 
*  Main kaynak dosyası, oyunun başlatılması ve yönetimi, tüm ekran işlemleri burada
* </p> 
*/ 
#include "Oyun.h"
#include "VeriHavuzu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Yardimci fonksiyonlar
void SehirleriListele(Oyun oyun);
void SecimEkrani(Oyun oyun);
void KonsoluTemizle();

int main() {
    KonsoluTemizle();

    SetConsoleOutputCP(65001);  // UTF-8 çıktı
    SetConsoleCP(65001);        // UTF-8 girdi

    // Rastgelelik başlat
    srand((unsigned int)time(NULL));
    
    // C programı başlar başlamaz txt dosyalarını RAM'e çekiyorz
    VeriHavuzunuDoldur();

    Oyun oyun = new_Oyun();
    if (oyun == NULL) return 1;

    int turSayisi;
    printf("Tur sayisini girin: ");
    scanf("%d", &turSayisi);
    getchar(); // Buffer temizleme ,Java'daki scanner.nextLine() gibi

    char girdi[500];
    int formatDogru = 0;

    while (!formatDogru) {
        printf("Oyun formatina uyacak sekilde bosluklu giris yapiniz (or:18 25 79): \n");
        fgets(girdi, sizeof(girdi), stdin);
        girdi[strcspn(girdi, "\n")] = 0; // Sondaki yeni satir karakterini sil

        // format kontrolü strtok ile parçalayıp kontrol ediyoruz
        char kopya[500];
        strcpy(kopya, girdi);
        char* parca = strtok(kopya, " ");
        int hataVar = 0;

        while (parca != NULL) {
            if (strlen(parca) != 2) {
                hataVar = 1;
                break;
            }
            parca = strtok(NULL, " ");
        }

        if (hataVar) {
            printf("HATA: Lutfen sadece 2 basamakli sayilar giriniz!\n");
        } else {
            formatDogru = 1;
        }
    }

    // Simulasyonu hazirla
    OyunSimulasyonuHazirla(oyun, girdi);

    printf("\nTurlara hazirlik sonu durumu:\n");
    SehirleriListele(oyun);

    // Turlar
    for (int i = 1; i <= turSayisi; i++) {
        OyunTuruGerceklestir(oyun);
        
        printf("------%d. TUR------\n", i);
        SehirleriListele(oyun);
    
        Sleep(1000);
        KonsoluTemizle(); //yönergede istenildiği gibi her tur sonu ekran temizleniyor
    }

    KonsoluTemizle();

    printf("\n------ OYUN SONU DURUM ------\n");
    SehirleriListele(oyun);
    printf("-----------------------------\n");

    // Detayli sorgulama ekranı
    SecimEkrani(oyun);

    printf("\nProgrami kapatmak icin Enter tusuna basin...");
    getchar(); // Buffer'da kalan karakteri temizle
    getchar(); // Bekle

    delete_Oyun(oyun);
    printf("Program kapatiliyor...\n");
    
    return 0;
}

// Şehirleri [Nüfus]-[Nüfus] formatında 5'erli listeler
void SehirleriListele(Oyun oyun) {
    Sehir* sehirler = OyunSehirleriGetir(oyun);
    for (int i = 0; i < oyun->sehirSayisi; i++) {
        printf("[%d]", sehirler[i]->getToplamNufus(sehirler[i]));

        if ((i + 1) % 5 != 0 && i != oyun->sehirSayisi - 1) {
            printf("-");
        }
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Detaylı sorgulama (Satır/Sütun mantığı)
void SecimEkrani(Oyun oyun) {
    int satir, sutun;
    printf("\n         SEHIR DETAYLI SORGULAMA EKRANI         \n");
    printf("================================================\n");

    printf("SATIR numarasini gir(0'dan baslayarak): ");
    scanf("%d", &satir);
    printf("SUTUN numarasini gir(0'dan baslayarak): ");
    scanf("%d", &sutun);

    printf("\n");

    int hedefIndeks = (satir * 5) + sutun;
    Sehir* sehirler = OyunSehirleriGetir(oyun);

    if (hedefIndeks >= 0 && hedefIndeks < oyun->sehirSayisi) {
        Sehir secilen = sehirler[hedefIndeks];
        printf("Sehir: %s - Nufus: %d\n", secilen->base->ad, secilen->getToplamNufus(secilen));

        for (int i = 0; i < secilen->ilceSayisi; i++) {
            Ilce ilce = secilen->ilceler[i];
            printf("  Ilce: %s - Nufus: %d\n", ilce->base->ad, ilce->getINufus(ilce));

            for (int j = 0; j < ilce->mahalleSayisi; j++) {
                Mahalle mahalle = ilce->mahalleler[j];
                printf("    Mahalle: %s - Nufus: %d\n", mahalle->base->ad, mahalle->getM_Nufus(mahalle));
                printf("    Kisiler:\n");
                
                for (int k = 0; k < mahalle->kisiSayisi; k++) {
                    Kisi kisi = mahalle->yasayanKisiler[k];
                    printf("      %d - %s %s - %d\n", 
                           KisiIdGetir(kisi), 
                           KisiIsimGetir(kisi), 
                           KisiSoyisimGetir(kisi), 
                           KisiYasGetir(kisi));
                }
            }
        }
    } else {
        printf("\nHATA: %d nolu indekste bir sehir bulunamadi.\n", hedefIndeks);
    }
}

void KonsoluTemizle() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}