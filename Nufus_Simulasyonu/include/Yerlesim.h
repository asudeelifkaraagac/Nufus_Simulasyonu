/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  Yerleşim yapısısının başlık dosyası, burada şehir,ilçe,mahallenin ortak olan özellikleri bulunacak ve burdan kalıtım alıyorlarmış gibi ayarlnacak 
* </p> 
*/ 

#ifndef YERLESIM_H
#define YERLESIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct YERLESIM* Yerlesim; // pointer gizledik

struct YERLESIM{
    char* ad; // javada string yerine char*
    
    // fonk göstericileri
    int (*nufusGetir)(Yerlesim); // her yapı kendisinin nufus sayısını göndereecl
    void (*yokEt)(Yerlesim); // javadaki çöp toplayıcı c de olmadığı için yıkıcı fonksiyon oluşturmamız gerekiyor
};

Yerlesim YerlesimOlustur(const char* ad); //kurucu
void YerlesimYokEt(Yerlesim yerlesim); //yıkıcı , javada çöp toplayıcı var ama burda olmadığı için kendimiz yazmamız gerekiyor

#endif