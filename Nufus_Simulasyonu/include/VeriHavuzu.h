/** 
* 
* @author Asude Elif Karaağaç
* @since 28.04.2026
* <p> 
*  Veri havuzunun başlık dosyası, rastgele işlemlere ait fonksiyon imzaları burada
* </p> 
*/ 
#ifndef VERIHAVUZU_H
#define VERIHAVUZU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERI_SAYISI   10000
#define MAKS_KARAKTER 50

// Global diziler — extern ile dışarıdan erişime açıyoruz
extern char isimHavuzu   [VERI_SAYISI][MAKS_KARAKTER];
extern char soyisimHavuzu[VERI_SAYISI][MAKS_KARAKTER];
extern char sehirHavuzu  [VERI_SAYISI][MAKS_KARAKTER];
extern char ilceHavuzu   [VERI_SAYISI][MAKS_KARAKTER];
extern char mahalleHavuzu[VERI_SAYISI][MAKS_KARAKTER];

// Fonksiyon imzaları
void DosyadanVeriYukle(const char* dosyaAdi, char havuz[][MAKS_KARAKTER]);
void VeriHavuzunuDoldur();
char* RastgeleIsimUret();
char* RastgeleSoyisimUret();
char* RastgeleSehirAdiUret();
char* RastgeleIlceAdiUret();
char* RastgeleMahalleAdiUret();
int   RastgeleYasUret();

#endif