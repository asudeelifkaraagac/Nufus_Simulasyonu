/** 
* 
* @author Asude Elif Karaağaç
* @since 28.04.2026
* <p> 
*  Veri havuzunun kaynak dosyası, rastgele işlemlere ait fonksiyonların gövdeleri burada
* </p> 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERI_SAYISI 10000
#define MAKS_KARAKTER 50

// Global veya statik diziler (RAM'de tutulacak)
char isimHavuzu[VERI_SAYISI][MAKS_KARAKTER];
char soyisimHavuzu[VERI_SAYISI][MAKS_KARAKTER];
char sehirHavuzu[VERI_SAYISI][MAKS_KARAKTER];
char ilceHavuzu[VERI_SAYISI][MAKS_KARAKTER];
char mahalleHavuzu[VERI_SAYISI][MAKS_KARAKTER];

void DosyadanVeriYukle(const char* dosyaAdi,char havuz[][MAKS_KARAKTER]){
    FILE *dosya = fopen(dosyaAdi,"r");
    if(!dosya) return;
    fseek(dosya,0,SEEK_END);
    int uzunluk = ftell(dosya);
    rewind(dosya);
    char* icerik = (char*)malloc(sizeof(char)*uzunluk+1);
    fread(icerik,1,uzunluk,dosya);
    icerik[uzunluk] = 0;
    fclose(dosya);
    int i=0;
    char* satir = strtok(icerik,"\n");
    while(satir != NULL && i < VERI_SAYISI){
        strcpy(havuz[i],satir);
        i++;
        satir = strtok(NULL,"\n");
    }
    free(icerik);
}

// Oyun baslarken cagrilacak ana yukleme fonksiyonu
void VeriHavuzunuDoldur() {
    DosyadanVeriYukle("veri_havuzu/isimler.txt", isimHavuzu);
    DosyadanVeriYukle("veri_havuzu/soyisimler.txt", soyisimHavuzu);
    DosyadanVeriYukle("veri_havuzu/sehirler.txt", sehirHavuzu);
    DosyadanVeriYukle("veri_havuzu/ilceler.txt", ilceHavuzu);
    DosyadanVeriYukle("veri_havuzu/mahalleler.txt", mahalleHavuzu);
}

//c de faker olmadığı için rastgeleleik için yardimci fonksiyonlar tanımlıyoruz

char* RastgeleIsimUret(){
    int r = rand() % VERI_SAYISI;
    char* isim = (char*)malloc(strlen(isimHavuzu[r]) + 1);
    strcpy(isim, isimHavuzu[r]);
    return isim;
}
char* RastgeleSoyisimUret(){
    int r = rand() % VERI_SAYISI;
    char* soyisim = (char*)malloc(strlen(soyisimHavuzu[r]) + 1);
    strcpy(soyisim, soyisimHavuzu[r]);
    return soyisim;
}
char* RastgeleSehirAdiUret(){
    int r = rand() % VERI_SAYISI;
    char* sehir = (char*)malloc(strlen(sehirHavuzu[r]) + 1);
    strcpy(sehir, sehirHavuzu[r]);
    return sehir;
}
char* RastgeleIlceAdiUret(){
    int r = rand() % VERI_SAYISI;
    char* ilce = (char*)malloc(strlen(ilceHavuzu[r]) + 1);
    strcpy(ilce, ilceHavuzu[r]);
    return ilce;
}
char* RastgeleMahalleAdiUret(){
    int r = rand() % VERI_SAYISI;
    char* mahalle = (char*)malloc(strlen(mahalleHavuzu[r]) + 1);
    strcpy(mahalle, mahalleHavuzu[r]);
    return mahalle;
}
int RastgeleYasUret(){ // burda kişilerin yasları 0-50 arası rastgele oluşturulacak
    return (rand() % 51); // 0-50 arasi yas uretir
}