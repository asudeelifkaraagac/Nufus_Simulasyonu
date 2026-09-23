/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  Mahallenin kaynak dosyası, başlık dosyasındak imzası olan fonksiyonların gövdeleri, kurucu yıkıcı fonksiyonları burada
* </p> 
*/ 

#include "Mahalle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Mahalle new_Mahalle(const char* ad){
    Mahalle this;

    this = (Mahalle)malloc(sizeof(struct MAHALLE)); //mahalle yapısı için bellekten yer ayırıyoruz

    if(this == NULL){
        fprintf(stderr, "Bellekten yer alinamadi\n");
        return NULL;
    }

    this->base = YerlesimOlustur(ad); //kalıtım benzetimi için taban sınıftan nesne oluşturuyoruz
    
    if(this->base == NULL){
        free(this);
        return NULL;
    }

    //arrayList lerin başlangıcına varsayılan değerleri veriyoruz, başlangıç kapasiteleri
    this->kapasite = 5;
    this->kisiSayisi = 0;
    this->yasayanKisiler = (Kisi*)malloc(this->kapasite * sizeof(Kisi));

    if(this->yasayanKisiler == NULL){
        fprintf(stderr, "Kisi dizisi icin bellek alinamadi\n");
        this->base->yokEt(this->base);
        free(this);
        return NULL;
    }

    //fonksiyonların bağlanması
    this->kisiEkle = &MahalleKisiEkle;
    this->getM_Nufus = (int (*)(Mahalle))&M_NufusHesapla;
    this->delete_Mahalle = (void (*)(struct MAHALLE*))&delete_Mahalle;
    
    //override, çok biçimilik sağlamak için taban sınıftaki fonksiyon göstericilerini, Mahalle sınıfına özgü fonksiyonlarla eziyoruz
    this->base->nufusGetir = &M_NufusHesapla; // yerleşime ait olan soyut sınfı burada dolsuruyoruz
    this->base->yokEt = (void (*)(Yerlesim))&delete_Mahalle;

    return this;
}
void MahalleKisiEkle(Mahalle mahalle, Kisi kisi){
    Mahalle this = mahalle; // Gövdede this çevrimi

    if(this == NULL || kisi == NULL) return;

    if(this->kisiSayisi >= this->kapasite){
        this->kapasite *= 2;

        Kisi* gecici = (Kisi*)realloc(this->yasayanKisiler, this->kapasite * sizeof(Kisi));
        if(gecici == NULL){
            fprintf(stderr, "Bellek genisletilemedi\n");
            this->kapasite /= 2; //başarısız olursa islemi geri al
            return;
        }

        this->yasayanKisiler = gecici;
    }

    this->yasayanKisiler[this->kisiSayisi] = kisi;
    this->kisiSayisi++;
}
int M_NufusHesapla(Yerlesim yerlesim){
    if(yerlesim == NULL) return 0;
    // Gelen Yerlesim nesnesini Mahalle tipine dönüştürerek alt sınıf özelliklerine erişiyoruz
    Mahalle this = (Mahalle) yerlesim; //polimorfizm
    return this->kisiSayisi;
}
void delete_Mahalle(Yerlesim yerlesim){ // Parametre Yerlesim olmalı ki base çağırabilsin
    Mahalle this = (Mahalle)yerlesim;
    // Mahalle this = mahalle;

    if(this == NULL) return;

    //önce içtekiler, kisileri temizliyoruz
    for(int i=0; i<this->kisiSayisi; i++){
        delete_Kisi(this->yasayanKisiler[i]);
    }

    //dinamik dizi taşıyıcısını serbest bırakıyoruz
    free(this->yasayanKisiler); // kişi dizisinin kendisi de silinmeli

    if(this->base != NULL){
        //base ad değişkenini silebilmesi icen YerlesimYokEt çağırır
        YerlesimYokEt(this->base);
    }
    //mahallenin kendisi silinir
    free(this);
}

//getterlar
const char* MahalleAdGetir(Mahalle mahalle){
    return mahalle->base->ad;
}
Kisi* MahalleKisileriGetir(Mahalle mahalle){
    return mahalle->yasayanKisiler;
}