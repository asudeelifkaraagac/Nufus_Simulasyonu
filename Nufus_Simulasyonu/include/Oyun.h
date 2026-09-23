/** 
* 
* @author Asude Elif Karaağaç
* @since 28.04.2026
* <p> 
*  Oyun başlık dosyası, oyuna ait tüm kuralların metot imzalarının bulunduğu yer gövdesiz
* </p> 
*/ 
#ifndef OYUN_H
#define OYUN_H

#include "Sehir.h"
#include "VeriHavuzu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // rastgele yas için

typedef struct OYUN* Oyun;

struct OYUN{
    Sehir* sehirler;
    int sehirSayisi;
    int kapasite;
    int turSayisi;

    // Fonksiyon göstericileri 
    void (*simulasyonuHazirla)(struct OYUN*, const char*);
    void (*turuGerceklestir)(struct OYUN*);
    void (*yokEt)(struct OYUN*);
};


Oyun new_Oyun(); // javadaki new Oyun() yerine, başta oyunOluştur du ama benzetim için bu şekilde değiştridm

void OyunSimulasyonuHazirla(Oyun oyun, const char* girdi); //javadaki simulasyonuHazirla(String girdi);
void OyunSehirOlustur(Oyun oyun, int girilenSayi); //javadaki sehirOlustur(int girilenSayi) fonksiyonunun karşılığı
void OyunTuruGerceklestir(Oyun oyun); //javadaki turuGerceklestir()
void OyunTurla(Oyun oyun); // javadaki turla() fonkunun karşılığı

void OyunSehirleriBol(Oyun oyun); //javadaki sehirleriBol()

Sehir* OyunSehirleriGetir(Oyun oyun); // javadaki getSehirler()

void delete_Oyun(Oyun oyun); //javadan farklı olarak yıkıcı fonksiyon yazdık

//c de faker olmadığı için rastgeleleik için yardimci fonksiyonlar tanımlıyoruz
char* RastgeleIsimUret();
char* RastgeleSoyisimUret();
char* RastgeleSehirAdiUret();
char* RastgeleIlceAdiUret();
char* RastgeleMahalleAdiUret();
int RastgeleYasUret(); // burda kişilerin yasları 0-50 arası rastgele oluşturulacak

#endif