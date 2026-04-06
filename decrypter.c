#include "decrypter.h"
#include "functions.h"

void decrypt(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
    
    for(int i=1; i<=TUR1; i++){
        TersSolaKaydirma(mesaj, mesajUzunlugu);
        TersCikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersCikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersSagaKaydirma(mesaj, mesajUzunlugu);
        TersSagaKaydirma(mesaj, mesajUzunlugu);
        TersCikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersToplamaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersXOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersCikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersToplamaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersXOR(mesaj, mesajUzunlugu, anahtar1, anahtar2); 
    }

    for(int j=1;j<=TUR2;j++){
        TersSagaKaydirma(mesaj, mesajUzunlugu);
        TersXOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersSolaKaydirma(mesaj, mesajUzunlugu);
        TersCikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersCikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersSagaKaydirma(mesaj, mesajUzunlugu);
        TersSagaKaydirma(mesaj, mesajUzunlugu);
        TersCikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersToplamaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersXOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersCikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersToplamaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
    }

    for(int i=1; i<=TUR1; i++){
        TersSolaKaydirma(mesaj, mesajUzunlugu);
        TersCikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersCikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersSagaKaydirma(mesaj, mesajUzunlugu);
        TersSagaKaydirma(mesaj, mesajUzunlugu);
        TersCikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersToplamaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersXOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersCikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
        TersToplamaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2); 
    }
}

