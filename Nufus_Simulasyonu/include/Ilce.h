/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  İlçenin başlık dosyası, ilk elemanı yerlesimden oluşturulacak ondan kalıtım almış gibi olacak sonrasında kendisine ait özellikleri,fonksiyonları işleyecek
* </p> 
*/ 

#ifndef ILCE_H
#define ILCE_H

#include "Yerlesim.h"
#include "Mahalle.h" 

typedef struct ILCE* Ilce;

struct ILCE{
    Yerlesim base;

    Mahalle* mahalleler; //pointer dizisi olarak tutuyoruz javadaki ArrayList yerine
    int mahalleSayisi;
    int kapasite;
    
    //fonksiyon göstericileri
    void (*mahalleEkle)(struct ILCE*, Mahalle); 
    int (*getINufus)(struct ILCE*);
    void (*delete_Ilce)(struct ILCE*);
};

//fonksiyon imzalari
Ilce new_Ilce(const char* ad); //kurucu
void IlceMahalleEkle(Ilce ilce, Mahalle mahalle);
int I_NufusHesapla(const Yerlesim yerlesim); // yerlesimden gelen soyut fonksiyon
void delete_Ilce(Yerlesim yerlesim); //yıkıcı

// getterlar 
const char* IlceAdGetir(Ilce ilce);
Mahalle* IlceMahalleleriGetir(Ilce ilce);

#endif