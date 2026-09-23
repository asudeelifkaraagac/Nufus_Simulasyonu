/** 
* 
* @author Asude Elif Karaağaç
* @since 28.04.2026
* <p> 
*  Oyun kaynak dosyası, oyuna ait tüm kuralların metot gövdeleri
* </p> 
*/ 
#include "Oyun.h"
#include "VeriHavuzu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Oyun new_Oyun(){
    Oyun this;
    this = (Oyun)malloc(sizeof(struct OYUN));
    if(this == NULL){
        fprintf(stderr, "Oyun icin bellekte yer alinamadi\n");
        return NULL;
    }

    this->kapasite = 10;
    this->sehirSayisi = 0;
    this->turSayisi = 0;
    this->sehirler = (Sehir*)malloc(this->kapasite * sizeof(Sehir));

    // Fonksiyon atamaları (OOP Benzetimi)
    this->simulasyonuHazirla = &OyunSimulasyonuHazirla;
    this->turuGerceklestir = &OyunTuruGerceklestir;
    this->yokEt = &delete_Oyun;

    srand((unsigned int)time(NULL)); //rastgelelik icin

    return this;
}

void OyunSimulasyonuHazirla(Oyun oyun, const char* girdi){ // boşlukla ayrılmış sayıları parçalar, her biri için sehirOlustur çağırır
    Oyun this = oyun;
    char* kopya = (char*)malloc((strlen(girdi) + 1) * sizeof(char));
    strcpy(kopya, girdi);

    //Java: girdi.split(" ") + Integer.parseInt()
    char* token = strtok(kopya, " "); // girilenlerde boşluğu göre parçalamalar yapacak
    while(token != NULL){
        int deger = atoi(token); // parçalanmış yerdeki tam sayı değer, şehrin nufusunu temsil eden
        OyunSehirOlustur(this, deger); 
        token = strtok(NULL, " ");
    }
    free(kopya);
}

void OyunSehirOlustur(Oyun oyun, int girilenSayi){
    Oyun this = oyun; // Yerel this tanımlaması

    int ilceSayisi = girilenSayi /10;
    int mahalleSayisi = girilenSayi % 10;
    int sehrinMevcutNufusu = girilenSayi;

    //kurallarımızdan ilk mahalle sayısının ilçe sayısına eşit bölünmesi
    if(ilceSayisi >0){
        if(mahalleSayisi ==0){
            mahalleSayisi = ilceSayisi; // eğer ki mahalle sayısı 0 olarak girilmişse bunu tam bölünebileceği en yakın olan ilçe sayısına eşitliyoruz
        }
        while(mahalleSayisi % ilceSayisi != 0){ // tam bölünemiyorsa arttıma işlemleri yapılcak
            mahalleSayisi++;
            if(mahalleSayisi >9){
                mahalleSayisi = 1; //yönergede de söylendiği gibi mahalle sayısının 9 u geçmesi halinde tkerar birler basamağı 1 den başlayacak onlar basında yani ilçede bir değişiklik olmayacal
            }
        }
    }

    sehrinMevcutNufusu = (ilceSayisi*10)+mahalleSayisi; //onlar ve birler basmaklarının desimal toplamı

    //2. ana kuralımız nüfusun mahalle eşit olara kbölünmesini sağlamak

    if(mahalleSayisi>0){
        while(sehrinMevcutNufusu % mahalleSayisi != 0){ // eşit bölünmüyorsa nüfusu en yakın bölünebilecek olana arttıırız ama bu ilçe ve mahalle sayısında bir değişikliğe sebep olmaz
            sehrinMevcutNufusu++;
        }
    }

    // sehrin özellikleri hazırlandıktan sonra sehrin kendisni oluştruyoruz
    char* sehirAdi = RastgeleSehirAdiUret();
    Sehir yeniSehir = new_Sehir(sehirAdi);
    free(sehirAdi); //kullandıktan sonra serbest bırakıyoruz

    int mahalleBasineNufus = (mahalleSayisi>0) ? sehrinMevcutNufusu/mahalleSayisi : 0; //mahalle sayisi 0 dan büyükse direkt oran eğerki 0 ise o zaman nüfus direkt 0 olur
    int ilceBasinaMahalle = (ilceSayisi>0) ? mahalleSayisi/ilceSayisi : 0;

    //zincirleme olarak ilce mahalle kişiyi iç içe oluşturacağız

    for(int i=0; i < ilceSayisi; i++){
        char* ilceAdi = RastgeleIlceAdiUret();
        Ilce ilce = new_Ilce(ilceAdi);
        free(ilceAdi);

        for(int j=0; j<ilceBasinaMahalle; j++){
            char* mahalleAdi = RastgeleMahalleAdiUret();
            Mahalle mahalle = new_Mahalle(mahalleAdi);
            free(mahalleAdi);

            for(int k=0; k<mahalleBasineNufus; k++){
                char* isim = RastgeleIsimUret();
                char* soyisim = RastgeleSoyisimUret();
                int yas = RastgeleYasUret();

                Kisi kisi = new_Kisi(isim, soyisim, yas);
                MahalleKisiEkle(mahalle,kisi);

                free(isim);
                free(soyisim);
            }
            IlceMahalleEkle(ilce,mahalle);
        }
        SehirIlceEkle(yeniSehir, ilce);
    }
    SehirMevcutSayiAyarla(yeniSehir, sehrinMevcutNufusu);

    // şehirler dizisini gerekirse genişlet
    if (this->sehirSayisi >= this->kapasite) {
        this->kapasite *= 2;
        Sehir* gecici = (Sehir*)realloc(this->sehirler,this->kapasite * sizeof(Sehir));
        if (gecici == NULL) {
            fprintf(stderr, "Sehir dizisi genisletilemedi\n");
            this->kapasite /= 2;
            return;
        }
        this->sehirler = gecici;
    }

    this->sehirler[this->sehirSayisi] = yeniSehir;
    this->sehirSayisi++;
}

void OyunTuruGerceklestir(Oyun oyun){
    Oyun this = oyun;
    OyunTurla(this);
    OyunSehirleriBol(this);
}

void OyunTurla(Oyun oyun){
    Oyun this = oyun; // Yerel this tanımlaması
    for(int s=0; s<this->sehirSayisi; s++){
        Sehir sehir = this->sehirler[s];

        int mevcutSayi = SehirMevcutSayiGetir(sehir);
        int birler = mevcutSayi % 10;
        int onlar = (mevcutSayi / 10) % 10;
        int artisOrani = birler + onlar;

        // Java: boolean sifirKurali = (artisOrani == 0) // eğer toplamlar sıfırsa
        int sifirKurali = (artisOrani == 0);

        //ilce döngüsü
        for(int i=0; i < sehir->ilceSayisi; i++){
            Ilce ilce = sehir->ilceler[i];

            //mahalle
            for(int j=0; j < ilce->mahalleSayisi; j++){
                Mahalle mahalle = ilce->mahalleler[j];

                //kisiler ve yaslari
                for(int k=0; k < mahalle->kisiSayisi; k++){
                    mahalle->yasayanKisiler[k]->yasArttir(mahalle->yasayanKisiler[k]);
                }

                int suAnkiNufus = mahalle->kisiSayisi;
                int eklenecek;

                if(sifirKurali){
                    eklenecek=1;
                }else{
                    eklenecek = (suAnkiNufus * artisOrani) - suAnkiNufus;
                }

                //yeni kisileri ekle
                for(int k=0; k < eklenecek; k++){
                    char* isim = RastgeleIsimUret();
                    char* soyisim = RastgeleSoyisimUret();
                    int yas = RastgeleYasUret();

                    Kisi yeniKisi = new_Kisi(isim, soyisim, yas);
                    MahalleKisiEkle(mahalle, yeniKisi);

                    free(isim);
                    free(soyisim);
                }
            }
        }
        //tur sonu güncel nufusu kaydet
        SehirMevcutSayiAyarla(sehir, sehir->getToplamNufus(sehir));
    }
    this->turSayisi++;
}

void OyunSehirleriBol(Oyun oyun){
    Oyun this = oyun; 

    //bölünme sonrası yeni oluşanları geçici bir listede tutacağız sonradan listein sonuna ekleyecekğiz tur sonu
    int yeniKapasite  = 10;
    int yeniSayisi = 0;
    Sehir* yeniSehirler = (Sehir*)malloc(yeniKapasite * sizeof(Sehir));

    int baslangicBoyutu = this->sehirSayisi;

    for(int i=0; i< baslangicBoyutu; i++){
        Sehir mevcutSehir = this->sehirler[i];

        if(mevcutSehir->getToplamNufus(mevcutSehir) < 1000) continue;

        char* yeniAd = RastgeleSehirAdiUret();
        Sehir yeniSehir = new_Sehir(yeniAd);
        free(yeniAd);

        //bölünmedeki özel durumlar

        //ilce sayisi >= 2, normal
        if(mevcutSehir->ilceSayisi >= 2){
            int tasinacak = mevcutSehir->ilceSayisi/2;

            //sondan tasinacak kadar ilçeyi yeni sehre taşıyotuz
            for(int j=0; j< tasinacak; j++){
                int sonIdx = mevcutSehir->ilceSayisi - 1;
                SehirIlceEkle(yeniSehir, mevcutSehir->ilceler[sonIdx]);
                mevcutSehir->ilceSayisi--; //tasinacak ve asıl olandaki ilce sayısı azaltılacak
            }
        }

        //ilce sayisi = 1 ise nüfus 4 bası geçtiğinde ilçe bölünemeyeceği için yeni şehir de direkt 1 ilçeye sahip olack mahalleler bölüncek ve taşınacak
        else if(mevcutSehir->ilceSayisi == 1){
            Ilce anaIlce = mevcutSehir->ilceler[0];

            char* yeniIlceAdi = RastgeleIlceAdiUret();
            Ilce yeniIlce = new_Ilce(yeniIlceAdi);
            free(yeniIlceAdi);

            // mahalle sayisi >= 2, normal
            if(anaIlce->mahalleSayisi >= 2){
                int tasinacak = anaIlce->mahalleSayisi / 2;
                for(int j=0; j < tasinacak; j++){
                    int sonIdx = anaIlce->mahalleSayisi -1;
                    IlceMahalleEkle(yeniIlce, anaIlce->mahalleler[sonIdx]);
                    anaIlce->mahalleSayisi--;
                }
            }
            //mahalle sayisi <= 1 -> kişileri böler
            else{
                Mahalle anaMahalle = anaIlce->mahalleler[0];

                char* yeniMahalleAdi = RastgeleMahalleAdiUret();
                Mahalle yeniMahalle = new_Mahalle(yeniMahalleAdi);
                free(yeniMahalleAdi);

                int tasinacak = anaMahalle->kisiSayisi / 2;
                for(int j=0; j<tasinacak; j++){
                    int sonIdx = anaMahalle->kisiSayisi - 1;
                    MahalleKisiEkle(yeniMahalle, anaMahalle->yasayanKisiler[sonIdx]);
                    anaMahalle->kisiSayisi--;
                }
                IlceMahalleEkle(yeniIlce, yeniMahalle);
            }
            SehirIlceEkle(yeniSehir, yeniIlce);
        }
        SehirMevcutSayiAyarla(mevcutSehir, mevcutSehir->getToplamNufus(mevcutSehir));
        SehirMevcutSayiAyarla(yeniSehir, yeniSehir->getToplamNufus(yeniSehir));

        //gecici diziye ekleriz
        if(yeniSayisi >= yeniKapasite){
            yeniKapasite *= 2;
            Sehir* gecici = (Sehir*)realloc(yeniSehirler, yeniKapasite * sizeof(Sehir));
            
            if(gecici == NULL){
                fprintf(stderr, "Yeni sehir dizisi genisletilemedi\n");
                break;
            }
            yeniSehirler = gecici;
        }
        yeniSehirler[yeniSayisi++] = yeniSehir;
    }

    // geçici listeyi asıl listeye ekle — Java: sehirler.addAll()
    for(int i=0; i<yeniSayisi; i++){
        if(this->sehirSayisi >= this->kapasite){
            this->kapasite *= 2;
            Sehir* gecici = (Sehir*)realloc(this->sehirler, this->kapasite * sizeof(Sehir));

            if(gecici == NULL){
                fprintf(stderr, "Ana sehir dizisi genisletilemedi\n");
                break;
            }
            this->sehirler = gecici;
        }
        this->sehirler[this->sehirSayisi++] = yeniSehirler[i];
    }
    free(yeniSehirler);
}

Sehir* OyunSehirleriGetir(Oyun oyun){
    Oyun this = oyun; 
    return this->sehirler;
}

void delete_Oyun(Oyun oyun){
    Oyun this = oyun; // Yerel this tanımlaması
    
    if(this == NULL) return;

    for(int i=0; i< this->sehirSayisi; i++){
        delete_Sehir((Yerlesim)this->sehirler[i]); // Şehir yıkıcısı artık Yerlesim beklediği için cast ediyoruz
    }

    free(this->sehirler);
    free(this);
}


