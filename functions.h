#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int Rastegele(int mesajUzunlugu, char *anahtar1, char *anahtar2);

void ToplamaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void ToplamaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void CikarmaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void CikarmaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void XOR(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void SagaKaydirma(char *mesaj, int mesajUzunlugu);
void SolaKaydirma(char *mesaj, int mesajUzunlugu);

void TersToplamaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void TersToplamaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void TersCikarmaCift(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void TersCikarmaTek(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void TersXOR(char *mesaj, int mesajUzunlugu, char *anahtar1, char *anahtar2);
void TersSagaKaydirma(char *mesaj, int mesajUzunlugu);
void TersSolaKaydirma(char *mesaj, int mesajUzunlugu);

#define SIYAH           "\x1b[30m"
#define KIRMIZI         "\x1b[31m"
#define YESIL           "\x1b[32m"
#define SARI            "\x1b[33m"
#define MAVI            "\x1b[34m"
#define MOR             "\x1b[35m"
#define TURKUAZ         "\x1b[36m"
#define BEYAZ           "\x1b[37m"

#define P_GRI           "\x1b[90m"
#define P_KIRMIZI       "\x1b[91m"
#define P_YESIL         "\x1b[92m"
#define P_SARI          "\x1b[93m"
#define P_MAVI          "\x1b[94m"
#define P_MOR           "\x1b[95m"
#define P_TURKUAZ       "\x1b[96m"
#define P_BEYAZ         "\x1b[97m"

#define BG_BEYAZ		"\x1b[47m"
#define BG_SIYAH        "\x1b[40m"
#define BG_KIRMIZI      "\x1b[41m"
#define BG_YESIL        "\x1b[42m"
#define BG_SARI         "\x1b[43m"
#define BG_MAVI         "\x1b[44m"

#define RESET         "\x1b[0m"
#define KALIN           "\x1b[1m"
#define ALTI_CIZILI     "\x1b[4m"

#endif

