#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>	// -lws2_32
#include <windows.h>

#include "encrypter.h"
#include "decrypter.h"
#include "functions.h"

char anahtar1[50];
char anahtar2[50];

char kullaniciAdi[100];
char gidenMesaj[500];
char gidenPaket[700];

int gidenMesajUzunlugu;
int gidenPaketUzunlugu;

WSADATA wsaData;
int sonuc;

SOCKET userSocket;
SOCKET activeSocket;

int taraf;

DWORD WINAPI Thread(LPVOID MesajDinle);

int main() {
	
	printf(KIRMIZI "======================================\n======================================\n\n" RESET);
	printf(YESIL"            KRIPTO CHAT\n        Omer Faruk Kelkitli\n\n" RESET);
	printf(KIRMIZI "======================================\n======================================\n\n\n" RESET);
	
	printf(P_KIRMIZI"Lutfen Anahtarlarin Arasina Bosluk Birakmayiniz!\n\n"RESET);
	
	printf(SARI"Ilk Anahtari Giriniz: "RESET);
	scanf("%49s", anahtar1);
	
	printf(SARI"Ikinci Anahtari Giriniz: "RESET);
	scanf("%49s", anahtar2);
	printf("\n");
	printf(KIRMIZI"======================================\n"RESET);
	
	sonuc = WSAStartup(MAKEWORD(2,2), &wsaData);
	
	if(sonuc){
		printf(P_KIRMIZI"WSAStartup basarisiz oldu! Hata kodu: %d"RESET, sonuc);
		return 1;
	}
	
	printf(P_YESIL"\nWSAStartup basarili oldu!\n"RESET);
	printf(P_TURKUAZ"\nSistem Durumu: %s\n"RESET, wsaData.szSystemStatus);
	
	printf(KIRMIZI"\n======================================"RESET);
	
	do{
		printf(SARI"\n\n  1-Sunucu\n  2-Istemci\n\nHangi Tarafsiniz: "RESET);
		scanf("%d", &taraf);
		printf(KIRMIZI"\n======================================"RESET);
	}while(taraf != 1 && taraf != 2);
	
	getchar();
		
	userSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if(userSocket == INVALID_SOCKET){
		printf(P_KIRMIZI"\n\nSocket olusturulamadi! Hata kodu: %d\n"RESET, WSAGetLastError());
		printf(KIRMIZI"\n======================================\n"RESET);

		WSACleanup();
		return 1;
	}
	
	printf(P_YESIL"\n\nSocket Basariyla Olusturuldu!\n"RESET);
	printf(KIRMIZI"\n======================================\n"RESET);

	
	struct sockaddr_in adr;
	adr.sin_family = AF_INET;
	adr.sin_port = htons(50000);
	
	printf(SARI"\nKullanici Adinizi Giriniz: "RESET);
	fgets(kullaniciAdi, sizeof(kullaniciAdi), stdin);
	kullaniciAdi[strcspn(kullaniciAdi, "\n")] = '\0';
	
	printf(KIRMIZI"\n======================================\n"RESET);
	switch(taraf){
		case 1:
			printf(P_SARI"\n-----SUNUCU MODU-----\n"RESET);
			
			printf(P_TURKUAZ"\nHosgeldin " P_MAVI"%s" P_TURKUAZ". Su Anda KriptoChat Icin Sunucu Olarak Baglandin!\n"RESET,kullaniciAdi);
			
			adr.sin_addr.s_addr = INADDR_ANY;
			if(bind(userSocket, (struct sockaddr*)&adr, sizeof(adr)) == SOCKET_ERROR){
				closesocket(userSocket);
				WSACleanup();
				return 1;
			}
			
			listen(userSocket, 3);
			printf(TURKUAZ"\nBaglanti Bekleniyor!\n"RESET);
			
			SOCKET clientSocket;
			struct sockaddr_in clientAdr;
			int clientAdrSize = sizeof(clientAdr);
			clientSocket = accept(userSocket, (struct sockaddr*)&clientAdr, &clientAdrSize);
			
			activeSocket = clientSocket;

			if(clientSocket != INVALID_SOCKET){
				printf(P_YESIL"\nBir Istemci Baglandi\n"RESET);
			}
			break;
		case 2:
			printf(P_SARI"\n-----ISTEMCI MODU-----\n"RESET);
			
			printf(P_TURKUAZ"\nHosgeldin " P_MAVI"%s" P_TURKUAZ". Su Anda KriptoChat Icin Istemci Olarak Baglandin!\n"RESET,kullaniciAdi);

			adr.sin_addr.s_addr = inet_addr("127.0.0.1");
			
			if(connect(userSocket, (struct sockaddr*)&adr, sizeof(adr)) == SOCKET_ERROR){
				printf(P_KIRMIZI"\nSunucuya Baglanilamadi! Hata Kodu: %d\n"RESET, WSAGetLastError());
				closesocket(userSocket);
				WSACleanup();
				return 1;
			}
			printf(P_YESIL"\nSunucuya Basariyla Baglanildi!\n"RESET);
			activeSocket = userSocket;
			break;
		default:
			printf(P_KIRMIZI"\nHatali Secim Lutfen Tekrar Deneyiniz!"RESET);
	}
		
	printf(P_YESIL"\nBAGLANTI KURULDU!\n"RESET);
	printf(KIRMIZI"\n======================================\n"RESET);

			
	CreateThread(NULL, 0, Thread, gidenMesaj, 0, NULL);

	while (1) {
		memset(gidenMesaj, 0, sizeof(gidenMesaj));
		memset(gidenPaket, 0, sizeof(gidenPaket));
		printf(SARI"[%s]: "RESET, kullaniciAdi);
		fgets(gidenMesaj, sizeof(gidenMesaj), stdin);
		gidenMesaj[strcspn(gidenMesaj, "\n")] = '\0';

		gidenMesajUzunlugu = strlen(gidenMesaj);
		
		snprintf(gidenPaket, sizeof(gidenPaket), "%s[%s]:%s %s", SARI, kullaniciAdi, RESET, gidenMesaj);
		
		gidenPaketUzunlugu = strlen(gidenPaket);
		
		if (strcmp(gidenMesaj, "cikis") == 0) {
			printf(P_KIRMIZI"Sistem Kapatiliyor!"RESET);
			exit(0);
		}
		else {
			encrypt(gidenPaket, gidenPaketUzunlugu, anahtar1, anahtar2);
			send(activeSocket, gidenPaket, gidenPaketUzunlugu, 0);
		}
	}

	WSACleanup();
	return 0;
}


DWORD WINAPI Thread(LPVOID MesajDinle) {
	while (1) {
		char mesaj[600];

		memset(mesaj, 0, sizeof(mesaj));

		int gelenVeri = recv(activeSocket, mesaj, sizeof(mesaj) - 1, 0);
		
		if (gelenVeri == -1) {
			printf(P_KIRMIZI"\n\nBir hata olustu!\n"RESET);
			exit(0);
		}
		else if (gelenVeri == 0) {
			printf(P_KIRMIZI"\n\nKars� taraf baglant�dan c�kt�!\n"RESET);
			exit(0);
		}
		else {
			mesaj[gelenVeri] = '\0';

			
			printf(P_GRI"\nNormalde Gelen Mesaj: "RESET);
			for(int i=0; i<gelenVeri; i++){
				printf(P_GRI"%02X "RESET, (unsigned char)mesaj[i]);
			}
			decrypt(mesaj, gelenVeri, anahtar1, anahtar2);
			printf("\n%s\n", mesaj);
			printf(SARI"[%s]: "RESET, kullaniciAdi);
			fflush(stdout);
		}
	}
}

