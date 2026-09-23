/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  Mahallenin başlık dosyası, ilk elemanı yerlesimden oluşturulacak ondan kalıtım almış gibi olacak sonrasında kendisine ait özellikleri,fonksiyonları işleyecek
* </p> 
*/ 
#ifndef MAHALLE_H
#define MAHALLE_H

#include "Yerlesim.h"
#include "Kisi.h"

typedef struct MAHALLE* Mahalle;

struct MAHALLE {
    Yerlesim base; //extends mantığını simülesi, kalıtım benzetimi için bit taban sınıf oluşturuyoruz
    Kisi* yasayanKisiler; //referans listesi olarak tutuluyor ,Kisi zaten struct KISI* olduğu için bu bir dizidir (struct KISI**), kişi neslerinin adresleri 
    int kisiSayisi;
    int kapasite; 
    
    //fonksiyon göstericileri 
    void (*kisiEkle)(struct MAHALLE*, Kisi);
    int (*getM_Nufus)(struct MAHALLE*);
    void (*delete_Mahalle)(struct MAHALLE*); // Yıkıcı göstericisi javadan farklı olarak
};

// Fonksiyon İmzaları
Mahalle new_Mahalle(const char* ad); //kurucu
void MahalleKisiEkle(Mahalle mahalle, Kisi kisi);
int M_NufusHesapla(Yerlesim yerlesim); // Yerlesim'deki nufusGetir'e atanacak
void delete_Mahalle(Yerlesim yerlesim); //nesneye özgü yıkıcı

//getterlar
const char* MahalleAdGetir(Mahalle mahalle);
Kisi* MahalleKisileriGetir(Mahalle mahalle);

#endif