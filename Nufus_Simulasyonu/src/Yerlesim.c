/** 
* 
* @author Asude Elif Karaağaç
* @since 27.04.2026
* <p> 
*  Yerleşim yapısısının kaynak dosyası, başlık dosyasında yazılan metotların gövdesi bulunmakta
* </p> 
*/ 

#include "Yerlesim.h"

static int VarsayilanNufusGetir(Yerlesim yerlesim){ // alt sınıflar kendilerine ait nufusu yazarken bu fonksiyonu eecekler o yüzden, ve program hata vermesin diye 0 değrini atıyoruz, başlıkta olmayıp sadece burda olduğu için başında static var
    return 0;
}

Yerlesim YerlesimOlustur(const char* ad){
    Yerlesim this; 
    
    this = (Yerlesim)malloc(sizeof(struct YERLESIM)); // heap bölgesinden yer ayırıyoruz, yeniYerlesim adında Yerlesimden
    
    if(this == NULL){
        fprintf(stderr, "Bellekten yer alınamadı\n"); //hata mesajı gönderiyoruz
        return NULL;
    }

    this->ad = (char*)malloc((strlen(ad) + 1) * sizeof(char)); // +1 bitiriş karakterinden dolayı
    strcpy(this->ad,ad); // kopyalayarak yenisine yazar

    //fonksiyonları bağladık, sanal olanları ilgili olduklarıyla
    this->nufusGetir = &VarsayilanNufusGetir;
    this->yokEt = &YerlesimYokEt; 

    return this;
}

void YerlesimYokEt(Yerlesim yerlesim){
    Yerlesim this = yerlesim; //yerel this tanımlaması
    if(this != NULL){
        if(this->ad != NULL){
            free(this->ad);
            this->ad = NULL;
        }
        free(this);
    }
}
