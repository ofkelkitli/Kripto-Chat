#include "encrypter.h"
#include "functions.h"

void encrypt(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2){
	
	for(int i=1; i<=TUR1; i++){
		ToplamaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		XOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		ToplamaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		SagaKaydirma(mesaj, mesajUzunlugu);
		SagaKaydirma(mesaj, mesajUzunlugu);
		CikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		SolaKaydirma(mesaj, mesajUzunlugu);
	}

	for(int j=1;j<=TUR2;j++){
		ToplamaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		XOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		ToplamaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		SagaKaydirma(mesaj, mesajUzunlugu);
		SagaKaydirma(mesaj, mesajUzunlugu);
		CikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		SolaKaydirma(mesaj, mesajUzunlugu);
		XOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		SagaKaydirma(mesaj, mesajUzunlugu);
	}

	for(int i=1; i<=TUR1; i++){
		XOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		ToplamaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		XOR(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		ToplamaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		SagaKaydirma(mesaj, mesajUzunlugu);
		SagaKaydirma(mesaj, mesajUzunlugu);
		CikarmaCift(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		CikarmaTek(mesaj, mesajUzunlugu, anahtar1, anahtar2);
		SolaKaydirma(mesaj, mesajUzunlugu);
	}
}


