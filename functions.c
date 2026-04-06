#include "functions.h"
#include <string.h>

int ToplamaRastgeleCift(int mesajUzunlugu, char *anahtar1, char *anahtar2){
	return (((mesajUzunlugu ^ anahtar1[0]) ^ strlen(anahtar2)) + 27);
}

int ToplamaRastgeleTek(int mesajUzunlugu, char *anahtar1, char *anahtar2){
	return (((mesajUzunlugu ^ anahtar2[0]) ^ strlen(anahtar1)) + 16);
}

int CikarmaRastgeleCift(int mesajUzunlugu, char *anahtar1, char *anahtar2){
	return (((strlen(anahtar1) ^ anahtar2[0]) ^ mesajUzunlugu) - 25);
}

int CikarmaRastgeleTek(int mesajUzunlugu, char *anahtar1, char *anahtar2){
	return (((strlen(anahtar2) ^ mesajUzunlugu) ^ anahtar1[0]) - 48);
}

void ToplamaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=0; i<mesajUzunlugu; i+=2){
		mesaj[i] += ToplamaRastgeleCift(mesajUzunlugu, anahtar1, anahtar2);
	}
}

void ToplamaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=1; i<mesajUzunlugu; i+=2){
		mesaj[i] += ToplamaRastgeleTek(mesajUzunlugu, anahtar1, anahtar2);
	}
}

void CikarmaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=0; i<mesajUzunlugu; i+=2){
		mesaj[i] -= CikarmaRastgeleCift(mesajUzunlugu, anahtar1, anahtar2);;
	}
}

void CikarmaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=1; i<mesajUzunlugu; i+=2){
		mesaj[i] -= CikarmaRastgeleTek(mesajUzunlugu, anahtar1, anahtar2);;
	}
}

void XOR(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2) {
    int key1_len = strlen(anahtar1);
    int key2_len = strlen(anahtar2);
    
    if (key1_len == 0 || key2_len == 0) return;

    for (int i = 0; i < mesajUzunlugu; i++) {
        char aktif_k1 = anahtar1[i % key1_len] ^ (char)mesajUzunlugu;
        mesaj[i] ^= aktif_k1;
    }
    
    for (int i = 0; i < mesajUzunlugu; i += 3) {
        char aktif_k2 = anahtar2[i % key2_len] ^ (char)mesajUzunlugu;
        mesaj[i] ^= aktif_k2;
    }
}

void SagaKaydirma(char *mesaj, int mesajUzunlugu){
	for(int i=0; i<mesajUzunlugu; i++){
		unsigned char harf = mesaj[i];
		mesaj[i] = (harf>>1) | (harf<<7);
	}
}

void SolaKaydirma(char *mesaj, int mesajUzunlugu){	
	for(int i=0; i<mesajUzunlugu; i++){
		unsigned char harf = mesaj[i];
		mesaj[i] = (harf<<1) | (harf>>7);
	}
}

void TersToplamaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=0; i<mesajUzunlugu; i+=2){
		mesaj[i] -= ToplamaRastgeleCift(mesajUzunlugu, anahtar1, anahtar2);;
	}
}

void TersToplamaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=1; i<mesajUzunlugu; i+=2){
		mesaj[i] -= ToplamaRastgeleTek(mesajUzunlugu, anahtar1, anahtar2);;
	}
}

void TersCikarmaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=0; i<mesajUzunlugu; i+=2){
		mesaj[i] += CikarmaRastgeleCift(mesajUzunlugu, anahtar1, anahtar2);;
	}
}

void TersCikarmaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	for(int i=1; i<mesajUzunlugu; i+=2){
		mesaj[i] += CikarmaRastgeleTek(mesajUzunlugu, anahtar1, anahtar2);;
	}
}

void TersXOR(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
    int key1_len = strlen(anahtar1);
    int key2_len = strlen(anahtar2);
    
    if (key1_len == 0 || key2_len == 0) return;

    for(int i=0; i<mesajUzunlugu; i+=3){
        char aktif_k2 = anahtar2[i % key2_len] ^ (char)mesajUzunlugu;
        mesaj[i] ^= aktif_k2;
    }
    
    for(int i=0; i<mesajUzunlugu; i++){
        char aktif_k1 = anahtar1[i % key1_len] ^ (char)mesajUzunlugu;
        mesaj[i] ^= aktif_k1;
    }
}

void TersSagaKaydirma(char *mesaj, int mesajUzunlugu){
	for(int i=0; i<mesajUzunlugu; i++){
		unsigned char harf = mesaj[i];
		mesaj[i] = (harf<<1) | (harf>>7);
	}
}

void TersSolaKaydirma(char *mesaj, int mesajUzunlugu){
	for(int i=0; i<mesajUzunlugu; i++){
		unsigned char harf = mesaj[i];
		mesaj[i] = (harf>>1) | (harf<<7);
	}
}

