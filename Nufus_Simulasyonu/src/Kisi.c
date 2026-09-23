/** 
* 
* @author Asude Elif Karaağaç
* @since 28.04.2026
* <p> 
*  Kisi kaynak dosyası
* </p> 
*/ 
#include "Kisi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int idSayac = 1;

Kisi new_Kisi(const char* isim, const char* soyisim, int yas){
    Kisi this;

    this = (Kisi)malloc(sizeof(struct KISI));

    if(this == NULL){
        fprintf(stderr, "bellekten yer alinamdi\n");
        return NULL;
    }

    this->id = idSayac++; // Global benzersiz ID

    // isim icin heap belleke yer aciyoruz ve ardından koyalaıyoruz
    this->isim = (char*)malloc((strlen(isim) + 1) * sizeof(char));

    if(this->isim == NULL){
        fprintf(stderr, "Isim icin bellek alinamadi\n");
        free(this);
        return NULL;
    }

    strcpy(this->isim , isim);

    // soyisim için bellek ayır ve kopyala
    this->soyisim = (char*)malloc((strlen(soyisim) + 1) * sizeof(char));
    if (this->soyisim == NULL) {
        fprintf(stderr, "Soyisim icin bellek alinamadi\n");
        free(this->isim);
        free(this);
        return NULL;
    }
    strcpy(this->soyisim, soyisim);
    
    this->yas = yas;

    this->yasArttir = &yasArtir; // Fonksiyon göstericisi ataması

    return this;
}
void yasArtir(Kisi kisi){
    Kisi this = kisi;
    if(this != NULL) {
        this->yas++;
    }
}

//getterlar 
int KisiIdGetir(Kisi kisi){
    Kisi this = kisi;
    return this->id;
}

const char* KisiIsimGetir(Kisi kisi){
    Kisi this = kisi;
    return this->isim;
}
const char* KisiSoyisimGetir(Kisi kisi){
    Kisi this = kisi;
    return this->soyisim;
}
int KisiYasGetir(Kisi kisi){
    Kisi this = kisi;
    return this->yas;
}

void delete_Kisi(Kisi kisi){
    Kisi this = kisi;
    if(this == NULL) return;

    if(this->isim != NULL){
        free(this->isim);
        this->isim = NULL;
    }
    if(this->soyisim != NULL){
        free(this->soyisim);
        this->soyisim = NULL;
    }

    free(this);
}