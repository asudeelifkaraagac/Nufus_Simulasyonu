/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  Kisi başlık dosyası, ilk elemanı yerlesimden oluşturulacak ondan kalıtım almış gibi olacak sonrasında kendisine ait özellikleri,fonksiyonları işleyecek
* </p> 
*/ 

#ifndef KISI_H
#define KISI_H

typedef struct KISI* Kisi;

struct KISI {
    int id;          
    char* isim;      // stirng  yerine char* kullanılıyor
    char* soyisim;    
    int yas;         
    
    void (*yasArttir)(struct KISI*);
};


Kisi new_Kisi(const char* isim, const char* soyisim, int yas);
void yasArtir(Kisi kisi); //göstericinin işaret edeceği asıl fonksiyon
void delete_Kisi(Kisi kisi);

//getterlar 
int KisiIdGetir(Kisi kisi);
const char* KisiIsimGetir(Kisi kisi);
const char* KisiSoyisimGetir(Kisi kisi);
int KisiYasGetir(Kisi kisi);
#endif