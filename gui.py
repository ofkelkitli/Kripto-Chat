import socket
import threading
import tkinter as tk
from tkinter import messagebox, scrolledtext
import re
import ctypes
import os
import hashlib
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

try:
    ctypes.windll.shcore.SetProcessDpiAwareness(1)
except Exception:
    pass

# --- SENİN ÖZEL ALGORİTMİK ARKA PLANIN ---
TUR1 = 25
TUR2 = 15

def ToplamaRastgeleCift(msg_len, k1, k2): return (((msg_len ^ ord(k1[0])) ^ len(k2)) + 27) & 0xFF
def ToplamaRastgeleTek(msg_len, k1, k2): return (((msg_len ^ ord(k2[0])) ^ len(k1)) + 16) & 0xFF
def CikarmaRastgeleCift(msg_len, k1, k2): return (((len(k1) ^ ord(k2[0])) ^ msg_len) - 25) & 0xFF
def CikarmaRastgeleTek(msg_len, k1, k2): return (((len(k2) ^ msg_len) ^ ord(k1[0])) - 48) & 0xFF

def ToplamaCift(b, k1, k2):
    val = ToplamaRastgeleCift(len(b), k1, k2)
    for i in range(0, len(b), 2): b[i] = (b[i] + val) & 0xFF
def ToplamaTek(b, k1, k2):
    val = ToplamaRastgeleTek(len(b), k1, k2)
    for i in range(1, len(b), 2): b[i] = (b[i] + val) & 0xFF
def CikarmaCift(b, k1, k2):
    val = CikarmaRastgeleCift(len(b), k1, k2)
    for i in range(0, len(b), 2): b[i] = (b[i] - val) & 0xFF
def CikarmaTek(b, k1, k2):
    val = CikarmaRastgeleTek(len(b), k1, k2)
    for i in range(1, len(b), 2): b[i] = (b[i] - val) & 0xFF
def XOR(b, k1, k2):
    msg_len = len(b)
    if not k1 or not k2: return
    for i in range(msg_len): b[i] ^= (ord(k1[i % len(k1)]) ^ msg_len) & 0xFF
    for i in range(0, msg_len, 3): b[i] ^= (ord(k2[i % len(k2)]) ^ msg_len) & 0xFF
def SagaKaydirma(b):
    for i in range(len(b)): b[i] = ((b[i] >> 1) | (b[i] << 7)) & 0xFF
def SolaKaydirma(b):
    for i in range(len(b)): b[i] = ((b[i] << 1) | (b[i] >> 7)) & 0xFF

def TersToplamaCift(b, k1, k2):
    val = ToplamaRastgeleCift(len(b), k1, k2)
    for i in range(0, len(b), 2): b[i] = (b[i] - val) & 0xFF
def TersToplamaTek(b, k1, k2):
    val = ToplamaRastgeleTek(len(b), k1, k2)
    for i in range(1, len(b), 2): b[i] = (b[i] - val) & 0xFF
def TersCikarmaCift(b, k1, k2):
    val = CikarmaRastgeleCift(len(b), k1, k2)
    for i in range(0, len(b), 2): b[i] = (b[i] + val) & 0xFF
def TersCikarmaTek(b, k1, k2):
    val = CikarmaRastgeleTek(len(b), k1, k2)
    for i in range(1, len(b), 2): b[i] = (b[i] + val) & 0xFF
def TersXOR(b, k1, k2):
    msg_len = len(b)
    if not k1 or not k2: return
    for i in range(0, msg_len, 3): b[i] ^= (ord(k2[i % len(k2)]) ^ msg_len) & 0xFF
    for i in range(msg_len): b[i] ^= (ord(k1[i % len(k1)]) ^ msg_len) & 0xFF
def TersSagaKaydirma(b):
    for i in range(len(b)): b[i] = ((b[i] << 1) | (b[i] >> 7)) & 0xFF
def TersSolaKaydirma(b):
    for i in range(len(b)): b[i] = ((b[i] >> 1) | (b[i] << 7)) & 0xFF

def encrypt_custom(data_bytes, k1, k2):
    b = bytearray(data_bytes)
    for _ in range(TUR1):
        ToplamaCift(b, k1, k2); CikarmaTek(b, k1, k2); XOR(b, k1, k2)
        ToplamaTek(b, k1, k2); CikarmaCift(b, k1, k2); SagaKaydirma(b)
        SagaKaydirma(b); CikarmaCift(b, k1, k2); CikarmaTek(b, k1, k2); SolaKaydirma(b)
    for _ in range(TUR2):
        ToplamaCift(b, k1, k2); CikarmaTek(b, k1, k2); XOR(b, k1, k2)
        ToplamaTek(b, k1, k2); CikarmaCift(b, k1, k2); SagaKaydirma(b)
        SagaKaydirma(b); CikarmaCift(b, k1, k2); CikarmaTek(b, k1, k2)
        SolaKaydirma(b); XOR(b, k1, k2); SagaKaydirma(b)
    for _ in range(TUR1):
        XOR(b, k1, k2); ToplamaCift(b, k1, k2); CikarmaTek(b, k1, k2)
        XOR(b, k1, k2); ToplamaTek(b, k1, k2); CikarmaCift(b, k1, k2)
        SagaKaydirma(b); SagaKaydirma(b); CikarmaCift(b, k1, k2)
        CikarmaTek(b, k1, k2); SolaKaydirma(b)
    return bytes(b)

def decrypt_custom(data_bytes, k1, k2):
    b = bytearray(data_bytes)
    for _ in range(TUR1):
        TersSolaKaydirma(b); TersCikarmaTek(b, k1, k2); TersCikarmaCift(b, k1, k2)
        TersSagaKaydirma(b); TersSagaKaydirma(b); TersCikarmaCift(b, k1, k2)
        TersToplamaTek(b, k1, k2); TersXOR(b, k1, k2); TersCikarmaTek(b, k1, k2)
        TersToplamaCift(b, k1, k2); TersXOR(b, k1, k2)
    for _ in range(TUR2):
        TersSagaKaydirma(b); TersXOR(b, k1, k2); TersSolaKaydirma(b)
        TersCikarmaTek(b, k1, k2); TersCikarmaCift(b, k1, k2); TersSagaKaydirma(b)
        TersSagaKaydirma(b); TersCikarmaCift(b, k1, k2); TersToplamaTek(b, k1, k2)
        TersXOR(b, k1, k2); TersCikarmaTek(b, k1, k2); TersToplamaCift(b, k1, k2)
    for _ in range(TUR1):
        TersSolaKaydirma(b); TersCikarmaTek(b, k1, k2); TersCikarmaCift(b, k1, k2)
        TersSagaKaydirma(b); TersSagaKaydirma(b); TersCikarmaCift(b, k1, k2)
        TersToplamaTek(b, k1, k2); TersXOR(b, k1, k2); TersCikarmaTek(b, k1, k2)
        TersToplamaCift(b, k1, k2)
    return bytes(b)

def strip_ansi_codes(text):
    return re.sub(r'\x1b\[[0-9;]*m', '', text)

# --- MODERN UI VE NETWORK SINIFI ---
class KriptoChatApp:
    def __init__(self, root):
        self.root = root
        self.root.title("KriptoChat UI - Multi-Layer Crypto")
        self.root.geometry("600x750")
        self.root.configure(bg="#121214")
        
        self.sock = None
        self.conn = None
        self.is_connected = False
        
        self.bg_dark = "#121214"
        self.panel_dark = "#1a1a1e"
        self.accent_green = "#00FF66"
        self.accent_blue = "#00BFFF"
        self.text_white = "#E2E2E6"
        self.font_mono = ("Consolas", 10)
        self.font_mono_bold = ("Consolas", 11, "bold")

        self.build_setup_ui()

    def build_setup_ui(self):
        self.setup_frame = tk.Frame(self.root, bg=self.bg_dark, padx=20, pady=20)
        self.setup_frame.pack(fill="both", expand=True)

        tk.Label(self.setup_frame, text="KRIPTO CHAT SECURE LAYER", fg=self.accent_green, bg=self.bg_dark, font=("Consolas", 16, "bold")).pack(pady=10)

        # Ağ Ayarları
        self.create_label_entry("Kullanıcı Adı:", "kullanici_adi", "Omer_Faruk")
        self.create_label_entry("Anahtar 1:", "anahtar1", "CryptoKey1", show="*")
        self.create_label_entry("Anahtar 2:", "anahtar2", "SecureKey2", show="*")
        self.create_label_entry("Hedef IP (İstemci için):", "ip_adres", "127.0.0.1")
        self.create_label_entry("Port:", "port", "50000")

        # Algoritma Seçimi
        tk.Label(self.setup_frame, text="Şifreleme Algoritması:", fg=self.accent_blue, bg=self.bg_dark, font=self.font_mono_bold).pack(anchor="w", pady=(15,0))
        self.algo_var = tk.IntVar(value=2) # Varsayılan: AES
        tk.Radiobutton(self.setup_frame, text="KriptoChat Özel Algoritma (Legacy C Uyumlu)", variable=self.algo_var, value=1, bg=self.bg_dark, fg=self.text_white, selectcolor=self.panel_dark, font=self.font_mono, activebackground=self.bg_dark).pack(anchor="w", pady=2)
        tk.Radiobutton(self.setup_frame, text="AES-256-GCM (Modern Standart - Yüksek Güvenlik)", variable=self.algo_var, value=2, bg=self.bg_dark, fg=self.text_white, selectcolor=self.panel_dark, font=self.font_mono, activebackground=self.bg_dark).pack(anchor="w", pady=2)

        # Taraf Seçimi (Server / Client)
        tk.Label(self.setup_frame, text="Bağlantı Modu:", fg=self.text_white, bg=self.bg_dark, font=self.font_mono_bold).pack(anchor="w", pady=(15,0))
        self.taraf_var = tk.IntVar(value=1)
        tk.Radiobutton(self.setup_frame, text="Sunucu (Server) Olarak Başlat", variable=self.taraf_var, value=1, bg=self.bg_dark, fg=self.text_white, selectcolor=self.panel_dark, font=self.font_mono, activebackground=self.bg_dark).pack(anchor="w", pady=2)
        tk.Radiobutton(self.setup_frame, text="İstemci (Client) Olarak Bağlan", variable=self.taraf_var, value=2, bg=self.bg_dark, fg=self.text_white, selectcolor=self.panel_dark, font=self.font_mono, activebackground=self.bg_dark).pack(anchor="w", pady=2)

        btn_baslat = tk.Button(self.setup_frame, text="SİSTEMİ BAŞLAT", bg=self.panel_dark, fg=self.accent_green, font=self.font_mono_bold, bd=1, relief="solid", highlightbackground=self.accent_green, command=self.sistemi_baslat, padx=10, pady=5)
        btn_baslat.pack(fill="x", pady=20)

    def create_label_entry(self, label_text, attr_name, default_val, show=None):
        tk.Label(self.setup_frame, text=label_text, fg=self.text_white, bg=self.bg_dark, font=self.font_mono_bold).pack(anchor="w", pady=(5, 2))
        entry = tk.Entry(self.setup_frame, bg=self.panel_dark, fg=self.text_white, insertbackground=self.accent_green, bd=1, relief="solid", font=self.font_mono, show=show)
        entry.insert(0, default_val)
        entry.pack(fill="x", ipady=4)
        setattr(self, attr_name, entry)

    # --- AES İÇİN ANAHTAR ÜRETİMİ ---
    def get_aes_key(self):
        # AES-256 tam olarak 32 byte anahtar ister. 
        # Kullanıcının girdiği iki anahtarı birleştirip SHA-256 ile özetliyoruz (32 byte elde ediyoruz)
        birlestirilmis = (self.k1 + self.k2).encode('utf-8')
        return hashlib.sha256(birlestirilmis).digest()

    def sistemi_baslat(self):
        self.nick = self.kullanici_adi.get()
        self.k1 = self.anahtar1.get()
        self.k2 = self.anahtar2.get()
        self.secilen_algo = self.algo_var.get()
        ip = self.ip_adres.get()
        try:
            port = int(self.port.get())
        except ValueError:
            messagebox.showerror("Hata", "Geçersiz Port Numarası!")
            return

        if not self.nick or not self.k1 or not self.k2:
            messagebox.showerror("Hata", "Lütfen tüm alanları doldurun!")
            return

        self.setup_frame.pack_forget()
        self.build_chat_ui()

        threading.Thread(target=self.network_setup, args=(ip, port), daemon=True).start()

    def build_chat_ui(self):
        self.chat_frame = tk.Frame(self.root, bg=self.bg_dark, padx=10, pady=10)
        self.chat_frame.pack(fill="both", expand=True)
        
        algo_adi = "Özel Algoritma" if self.secilen_algo == 1 else "AES-256-GCM"
        tk.Label(self.chat_frame, text=f"Aktif Kripto: {algo_adi}", fg=self.accent_blue, bg=self.bg_dark, font=("Consolas", 10, "italic")).pack(anchor="e")

        self.text_area = scrolledtext.ScrolledText(self.chat_frame, bg=self.panel_dark, fg=self.text_white, insertbackground=self.accent_green, font=self.font_mono, state="disabled", bd=0)
        self.text_area.pack(fill="both", expand=True, pady=(5, 10))

        input_frame = tk.Frame(self.chat_frame, bg=self.bg_dark)
        input_frame.pack(fill="x")

        self.msg_entry = tk.Entry(input_frame, bg=self.panel_dark, fg=self.text_white, insertbackground=self.accent_green, font=self.font_mono, bd=1, relief="solid")
        self.msg_entry.pack(side="left", fill="x", expand=True, ipady=8, padx=(0, 5))
        self.msg_entry.bind("<Return>", lambda event: self.mesaj_gonder())

        btn_gonder = tk.Button(input_frame, text="GÖNDER", bg=self.panel_dark, fg=self.accent_green, font=self.font_mono_bold, bd=1, relief="solid", command=self.mesaj_gonder, padx=15)
        btn_gonder.pack(side="right", ipady=5)

    def log_yaz(self, text):
        self.root.after(0, self._gui_guncelle, text)

    def _gui_guncelle(self, text):
        self.text_area.configure(state="normal")
        self.text_area.insert(tk.END, text)
        self.text_area.configure(state="disabled")
        self.text_area.see(tk.END)

    def network_setup(self, ip, port):
        taraf = self.taraf_var.get()
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        if taraf == 1: 
            try:
                self.sock.bind(('0.0.0.0', port))
                self.sock.listen(3)
                self.log_yaz(f"[SİSTEM]: {port} portu dinleniyor. Bağlantı bekleniyor...\n")
                self.conn, addr = self.sock.accept()
                self.is_connected = True
                self.log_yaz(f"[SİSTEM]: {addr[0]} bağlandı! Şifreleme aktif.\n\n")
            except Exception as e:
                self.log_yaz(f"[SİSTEM HATA]: Sunucu başlatılamadı: {str(e)}\n")
                return
        else:
            try:
                self.log_yaz(f"[SİSTEM]: {ip}:{port} adresine bağlanılıyor...\n")
                self.sock.connect((ip, port))
                self.conn = self.sock
                self.is_connected = True
                self.log_yaz("[SİSTEM]: Sunucuya başarıyla bağlanıldı!\n\n")
            except Exception as e:
                self.log_yaz(f"[SİSTEM HATA]: Bağlantı kurulamadı: {str(e)}\n")
                return

        self.mesaj_dinle()

    # --- ŞİFRE ÇÖZME VE DİNLEME ---
    def mesaj_dinle(self):
        while self.is_connected:
            try:
                gelen_veri = self.conn.recv(4096)
                if not gelen_veri:
                    self.log_yaz("\n[SİSTEM]: Karşı taraf bağlantıyı kapattı.\n")
                    self.is_connected = False
                    break
                
                if self.secilen_algo == 1:
                    # 1. ÖZEL ALGORİTMA (Legacy C)
                    cozulen_bytes = decrypt_custom(gelen_veri, self.k1, self.k2)
                    temiz_mesaj = cozulen_bytes.decode('utf-8', errors='ignore')
                    temiz_mesaj = strip_ansi_codes(temiz_mesaj)
                    self.log_yaz(f"{temiz_mesaj}\n")
                
                elif self.secilen_algo == 2:
                    # 2. AES-256-GCM
                    aesgcm = AESGCM(self.get_aes_key())
                    # GCM mimarisinde ilk 12 byte Nonce (IV), kalanı Ciphertext+MAC'tir
                    nonce = gelen_veri[:12]
                    ciphertext = gelen_veri[12:]
                    
                    cozulen_bytes = aesgcm.decrypt(nonce, ciphertext, None) # MAC doğrulaması burada otomatik yapılır
                    temiz_mesaj = cozulen_bytes.decode('utf-8')
                    self.log_yaz(f"{temiz_mesaj}\n")

            except Exception as e:
                self.log_yaz(f"\n[SİSTEM HATA]: Veri bütünlüğü bozuldu veya bağlantı koptu.\n")
                self.is_connected = False
                break

    # --- ŞİFRELEME VE GÖNDERME ---
    def mesaj_gonder(self):
        msg = self.msg_entry.get()
        if not msg or not self.is_connected: return
        
        self.msg_entry.delete(0, tk.END)
        ham_paket = f"[{self.nick}]: {msg}"
        ham_bytes = ham_paket.encode('utf-8')
        
        try:
            if self.secilen_algo == 1:
                # 1. ÖZEL ALGORİTMA
                sifreli_bytes = encrypt_custom(ham_bytes, self.k1, self.k2)
                self.conn.send(sifreli_bytes)
            
            elif self.secilen_algo == 2:
                # 2. AES-256-GCM
                aesgcm = AESGCM(self.get_aes_key())
                # Her mesaj için yepyeni 12 byte'lık rastgele bir Nonce üretilir (Çok Kritik!)
                nonce = os.urandom(12)
                ciphertext = aesgcm.encrypt(nonce, ham_bytes, None)
                
                # Karşı tarafın çözebilmesi için Nonce'ı mesajın en başına ekleyerek yolluyoruz
                giden_paket = nonce + ciphertext
                self.conn.send(giden_paket)
                
            self.log_yaz(f"[{self.nick}]: {msg}\n")
        except Exception as e:
            self.log_yaz(f"[SİSTEM HATA]: Mesaj gönderilemedi.\n")

if __name__ == "__main__":
    root = tk.Tk()
    app = KriptoChatApp(root)
    root.mainloop()