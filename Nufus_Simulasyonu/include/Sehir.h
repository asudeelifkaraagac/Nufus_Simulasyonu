/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  Sehirin başlık dosyası, ilk elemanı yerlesimden oluşturulacak ondan kalıtım almış gibi olacak sonrasında kendisine ait özellikleri,fonksiyonların imzaları ve göstericileri var
* </p> 
*/ 

#ifndef SEHIR_H
#define SEHIR_H

#include "Yerlesim.h"
#include "Ilce.h"

typedef struct SEHIR* Sehir;

struct SEHIR{
    Yerlesim base; //kalıtım benzetimi olmuş oluyor

    Ilce* ilceler; // javada ArrayList olarak oluşturduğumu burada dinamik dizi olarak oluşturacağım  
    int ilceSayisi; //c de dizilerin boyutnu da bilmek gerekiyor
    int mevcutSayi; // yaşayan kişilerin toplamı
    int kapasite;

    void (*ilceEkle)(struct SEHIR*, struct ILCE*);
    int (*getToplamNufus)(struct SEHIR*);

    struct SEHIR* (*sehirBol)(struct SEHIR*); //Sehir 
    void (*delete_Sehir)(struct SEHIR*);
};

Sehir new_Sehir(const char* ad); //kurucu
void SehirIlceEkle(const Sehir sehir, Ilce ilce);
void delete_Sehir(Yerlesim yerlesim); //yıkıcı

void SehirAdAyarla(Sehir sehir, const char* yeniAd);       // setAd
void SehirIlceleriAyarla(Sehir sehir, Ilce* ilceler, int sayi); // setIlceler
void SehirMevcutSayiAyarla(Sehir sehir, int mevcutSayi);   // setMevcutSayi
int SehirMevcutSayiGetir(const Sehir sehir);                // getMevcutSayi

#endif