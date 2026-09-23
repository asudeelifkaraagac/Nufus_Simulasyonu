/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  Sehirin kaynak dosyası, kurucu yıkıcı ve başlık dosyasında bulunan metot imzalarının gövdeleri bulunmakta
* </p> 
*/ 

#include "Sehir.h"
#include "VeriHavuzu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int SehirToplamNufusHesapla(Sehir sehir);
static Sehir sehirleriBol(struct SEHIR* sehir);

Sehir new_Sehir(const char* ad){
    Sehir this;

    this = (Sehir)malloc(sizeof(struct SEHIR));

    this->base = YerlesimOlustur(ad); // yeni bir sehir olusturulurken sehir önce yerlesim yerinden kalıtım alacak onun üzerinden kendisini oluşturacak

    //şehre özgü değişkenleri tanımlıyorum ve ilk değer atamalrı
    this->kapasite = 5; //başlangıç kapasitesi verdik
    this->ilceler = (Ilce*)malloc(this->kapasite * sizeof(Ilce));
    this->ilceSayisi = 0;
    this->mevcutSayi = 0;

    this->ilceEkle = &SehirIlceEkle;
    this->delete_Sehir =(void (*)(struct SEHIR*)) &delete_Sehir;

    //private benzetimi başlarında da static olarak tanımladık
    this->getToplamNufus = &SehirToplamNufusHesapla;
    this->sehirBol = &sehirleriBol;

    // Polimorfizm: Yerlesim yıkıcısını şehre bağlıyoruz
    this->base->yokEt = (void (*)(Yerlesim))&delete_Sehir;

    return this;
}

void SehirIlceEkle(const Sehir sehir, Ilce ilce){
    Sehir this = sehir;
    // dizide kapasite dolması durumundan diziyi genişletme işlemi
    if(this->ilceSayisi >= this->kapasite){
        this->kapasite *= 2; //öyle bir durumda direkt kapasitesyi 2 katına çıkartıyoruz    
        
        Ilce* gecici = (Ilce*)realloc(this->ilceler, this->kapasite * sizeof(Ilce));
       
        if(gecici == NULL){
           fprintf(stderr, "Bellek genişletilemedi\n");
           this->kapasite /= 2; // geri al, kontrollü hale dön
           return;
        }
        this->ilceler = gecici;
    }
    this->ilceler[this->ilceSayisi] = ilce; //ilçeyi diziye ekledik
    this->ilceSayisi++; 
}

//zincirleme olarak toplanan nüfus sayısı, bu zincirleme mahalledeki kişşi sayısından ilçeler şehirler şeklinde gelitor
static int SehirToplamNufusHesapla(Sehir sehir) {
    int toplam = 0;
    
    for (int i = 0; i < sehir->ilceSayisi; i++) {
        
        toplam += sehir->ilceler[i]->getINufus(sehir->ilceler[i]); // her ilçenin kendi nüfus getirme fonksiyonunu çağırıyoruz
    }
    return toplam;
}

// Geri dönüş tipini Sehir yapıyoruz ki oluşan yeni şehri Oyun'a iletebilelim
static Sehir sehirleriBol(struct SEHIR* sehir) {
    if (sehir == NULL) return NULL;
    Sehir this = sehir;

    // Eğer nüfus 1000'den küçükse bölünme olmaz, NULL döneriz
    if(this->getToplamNufus(this) < 1000) {
        return NULL; 
    }

    // yeni sehir olusuyır
    char* yeniAd = RastgeleSehirAdiUret();
    Sehir yeniSehir = new_Sehir(yeniAd);
    free(yeniAd);

    //bölünmenin belirlenmesi için orta nokta hesabı
    int ortaNokta = this->ilceSayisi / 2;
    
    // ilçeleri yeni şehre tasiyoruz
    for(int i = ortaNokta; i < this->ilceSayisi; i++) {
        // Yeni şehre eski şehrin ilçesini bağlıyoruz
        SehirIlceEkle(yeniSehir, this->ilceler[i]); 
    }
    
    // eski sehirin ilce yasını güncelledik
    this->ilceSayisi = ortaNokta;
    
    // nüfusları da güncelledik
    SehirMevcutSayiAyarla(this, this->getToplamNufus(this));
    SehirMevcutSayiAyarla(yeniSehir, yeniSehir->getToplamNufus(yeniSehir));
    
    return yeniSehir;
}

void delete_Sehir(Yerlesim yerlesim) {
    Sehir this = (Sehir)yerlesim;
    if (yerlesim == NULL) return;
    
        //önce ilçeleri sileriz
        for (int i = 0; i < this->ilceSayisi; i++) {
            if (this->ilceler[i] != NULL) {
                this->ilceler[i]->delete_Ilce(this->ilceler[i]);
            }
        }
        
        //ilçe dizisinin kendisini temizleriz
        free(this->ilceler);
        
        // kalıtım alınan base (Yerlesim) yapısını temizleriz
        if (this->base != NULL) {
            YerlesimYokEt(this->base); //karmaşa çıkmamasi için direkt base üzerinden yaptık
        }
        
        //Şehrin kendisini temizle
        free(this);
    
}

void SehirAdAyarla(Sehir sehir, const char* yeniAd) {
    // Eski ismi bellekten silip yeni isme yer açıyoruz
    free(sehir->base->ad);
    sehir->base->ad = (char*)malloc((strlen(yeniAd) + 1) * sizeof(char));
    strcpy(sehir->base->ad, yeniAd);
}

void SehirIlceleriAyarla(Sehir sehir, Ilce* yeniIlceler, int sayi) {
    // Bölünme sonrası yeni ilçe listesini atama
    free(sehir->ilceler);
    sehir->ilceler = yeniIlceler;
    sehir->ilceSayisi = sayi;
    sehir->kapasite = sayi;
}

void SehirMevcutSayiAyarla(Sehir sehir, int mevcutSayi) {
    sehir->mevcutSayi = mevcutSayi;
}

int SehirMevcutSayiGetir(const Sehir sehir) {
    return sehir->mevcutSayi;
}