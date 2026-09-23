/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  İlçenin kaynak dosyası
* </p> 
*/ 

#include "Ilce.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ilce new_Ilce(const char* ad){
    Ilce this;

    this = (Ilce)malloc(sizeof(struct ILCE)); //ilçe yapısı için dinamik bellekte yer ayıryor

    if(this == NULL){
        fprintf(stderr,"bellekten yer alinamadi\n");
        return NULL;
    }

    this->base = YerlesimOlustur(ad); // this değşkenine yerlesim olustur diyorz buradaki adı kullnarak

    if(this->base == NULL){
        free(this);
        return NULL;
    }

    this->kapasite = 5;
    this->mahalleSayisi = 0;
    this->mahalleler = (Mahalle*)malloc(this->kapasite * sizeof(Mahalle)); 

    if(this->mahalleler == NULL){
        fprintf(stderr, "Mahalle dizisi icin bellek alinamadi\n");
        this->base->yokEt(this->base);
        free(this);
        return NULL;
    }

    //fonksiyonları bağladık
    this->mahalleEkle = &IlceMahalleEkle;
    this->getINufus = (int (*)(Ilce))&I_NufusHesapla;
    this->base->nufusGetir = &I_NufusHesapla; //yerlesimden geleni overide ettik

    this->base->yokEt = (void (*)(Yerlesim))&delete_Ilce; 
    this->delete_Ilce = (void (*)(struct ILCE*))&delete_Ilce;

    return this;
}

void IlceMahalleEkle(Ilce ilce, Mahalle mahalle){
    Ilce this = ilce; 
    if(this == NULL || mahalle == NULL) return;

    if(this->mahalleSayisi >= this->kapasite){
        this->kapasite *= 2;

        Mahalle* gecici = (Mahalle*) realloc(this->mahalleler, this->kapasite * sizeof(Mahalle));// mahalle nesneleri saklamak icin bellekte sürekliliği olan alan ayırtma

        if(gecici == NULL){
            fprintf(stderr, "Bellek genisletilemedi\n");
            this->kapasite /= 2; //sistemi eski kararlı haline geri döndürmek için
            return;
        }
        this->mahalleler = gecici;
    }

    this->mahalleler[this->mahalleSayisi] = mahalle;
    this->mahalleSayisi++;
}
int I_NufusHesapla(const Yerlesim yerlesim){
    Ilce this = (Ilce)yerlesim; //polimorfiz benzetmesi
    int toplam = 0;

    for(int i=0; i < this->mahalleSayisi; i++){
        //her mahallenin kendi nüfusunu toplayarak zincirleme şekilde toplamı elde edice
        toplam += this->mahalleler[i]->getM_Nufus(this->mahalleler[i]);
    }
    return toplam;
}
void delete_Ilce(const Yerlesim yerlesim){
    Ilce this;

    this = (Ilce)yerlesim;
    if (this == NULL) return;

    // mahalleleri temizle
    for (int i = 0; i < this->mahalleSayisi; i++) {
        if (this->mahalleler[i] != NULL) {
                // Mahallenin kendi delete fonksiyonu
                delete_Mahalle((Yerlesim)this->mahalleler[i]);
        }
    }

    free(this->mahalleler);
    this->mahalleler = NULL;

    // base Yerlesim'i temizle
    if (this->base != NULL) {
        YerlesimYokEt(this->base);
    }

    free(this);
}

const char* IlceAdGetir(Ilce ilce){
    Ilce this = (Ilce)ilce;
    return this->base->ad;
}
Mahalle* IlceMahalleleriGetir(Ilce ilce){
    Ilce this = (Ilce)ilce;
    return this->mahalleler;
}