# 🔐 KriptoChat — Encrypted Terminal Chat in C & Python

> A terminal-based and GUI-based peer-to-peer encrypted chat application written in C and Python, featuring a custom multi-layer encryption algorithm.

---

## 📋 About the Project

KriptoChat is a real-time encrypted messaging application for Windows. It comes in two flavors: a **C terminal application** and a **Python GUI application** — both sharing the same custom multi-layer symmetric cipher at their core.

Messages are encrypted before being sent over the network and decrypted upon arrival. Both parties must use the same two secret keys for the encryption and decryption to work correctly. The application supports a simple **server/client** architecture over TCP.

---

## 🗂️ File Structure

```
.
├── main.c          # Main flow: connection setup, input loop, receive thread
├── encrypter.h     # Encrypt function declaration and round constants
├── encrypter.c     # Encryption logic (multi-round)
├── decrypter.h     # Decrypt function declaration and round constants
├── decrypter.c     # Decryption logic (reverse of encryption)
├── functions.h     # Helper function declarations and ANSI color macros
├── functions.c     # Core cipher operations (XOR, shift, add, subtract)
└── gui.py          # Python GUI application (tkinter) — standalone, same cipher
```

---

## 🔒 Encryption Algorithm

KriptoChat uses a **custom symmetric multi-layer cipher** applied in multiple rounds. The encryption and decryption are performed in exact reverse order.

### Operations Used

| Function | Description |
|----------|-------------|
| `ToplamaCift` / `TersToplamaCift` | Add a derived value to even-indexed bytes |
| `ToplamaTek` / `TersToplamaTek` | Add a derived value to odd-indexed bytes |
| `CikarmaCift` / `TersCikarmaCift` | Subtract a derived value from even-indexed bytes |
| `CikarmaTek` / `TersCikarmaTek` | Subtract a derived value from odd-indexed bytes |
| `XOR` / `TersXOR` | XOR bytes using both keys and message length |
| `SagaKaydirma` / `TersSagaKaydirma` | Bitwise right circular shift per byte |
| `SolaKaydirma` / `TersSolaKaydirma` | Bitwise left circular shift per byte |

### Round Structure

Encryption applies **3 phases**:

```
Phase 1 — TUR1 (25) rounds:
  AddEven → SubOdd → XOR → AddOdd → SubEven → ShiftRight×2 → SubEven → SubOdd → ShiftLeft

Phase 2 — TUR2 (15) rounds:
  Same as Phase 1 + XOR → ShiftRight

Phase 3 — TUR1 (25) rounds:
  XOR → AddEven → SubOdd → XOR → AddOdd → SubEven → ShiftRight×2 → SubEven → SubOdd → ShiftLeft
```

Decryption applies all operations **in exact reverse order** across the 3 phases.

### Key Derivation

The shift/add/subtract values are derived dynamically from the two keys and the message length using XOR combinations, making the cipher **message-length-dependent**.

> ⚠️ Both users must enter the **exact same two keys** for messages to decrypt correctly.

---

## 🖥️ GUI Application (gui.py)

`gui.py` is a standalone Python reimplementation of KriptoChat with a graphical interface built using **tkinter**. It shares the exact same custom cipher logic as the C version, ported line-by-line to Python.

### Key Differences from the Terminal Version

- **Graphical UI** — dark-themed window (600×750) with a Consolas font and green/blue accent colors, featuring a scrollable chat area
- **Dual encryption mode** — selectable before connecting; each session runs entirely on either the **custom algorithm** or **AES-256-GCM** (via the `cryptography` library). The custom algorithm mode is fully wire-compatible with the C terminal version
- **AES key derivation** — when AES-256-GCM is selected, the two user-entered keys are concatenated and hashed with SHA-256 to produce a 32-byte AES key
- **Configurable IP and port** — target IP and port can be set from the UI, so the app works over any network without touching the source code
- **Enter key support** — pressing Enter in the message box sends the message
- **ANSI code stripping** — incoming messages from the C terminal version have ANSI color codes stripped automatically before display

### Requirements

```bash
pip install cryptography
```

> `tkinter` is included with standard Python on Windows. No other dependencies needed.

### Run

```bash
python gui.py
```

### GUI Preview

```
┌──────────────────────────────────────────────────┐
│  KRIPTO CHAT SECURE LAYER                        │
│                                                  │
│  Kullanıcı Adı:  [Omer_Faruk          ]          │
│  Anahtar 1:      [***                 ]          │
│  Anahtar 2:      [***                 ]          │
│  Hedef IP:       [127.0.0.1           ]          │
│  Port:           [50000               ]          │
│                                                  │
│  Şifreleme Algoritması:                          │
│  ○ KriptoChat Özel Algoritma (Legacy C Uyumlu)   │
│  ● AES-256-GCM (Modern Standart - Yüksek Güvenlik)│
│                                                  │
│  Bağlantı Modu:                                  │
│  ● Sunucu (Server) Olarak Başlat                 │
│  ○ İstemci (Client) Olarak Bağlan                │
│                                                  │
│            [ SİSTEMİ BAŞLAT ]                    │
└──────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────┐
│                          Aktif Kripto: AES-256-GCM│
│ ┌──────────────────────────────────────────────┐ │
│ │[SİSTEM]: 50000 portu dinleniyor...           │ │
│ │[SİSTEM]: 127.0.0.1 bağlandı! Şifreleme aktif│ │
│ │[Omer_Faruk]: Merhaba!                        │ │
│ │[Karsı_Taraf]: Selam!                         │ │
│ └──────────────────────────────────────────────┘ │
│  [ mesajınızı yazın...          ] [ GÖNDER ]     │
└──────────────────────────────────────────────────┘
```

---

## 🚀 Getting Started (C Terminal Version)

### Requirements

- Windows OS
- GCC with Winsock2 support (MinGW recommended)

### Compilation

```bash
gcc main.c functions.c encrypter.c decrypter.c -o kriptochat -lws2_32
```

### Run

```bash
./kriptochat
```

---

## 🎮 How to Use

1. Both users launch the application.
2. Each user enters **two secret keys** (no spaces).
3. Each user enters a **username**.
4. One user selects **Server (1)**, the other selects **Client (2)**.
5. The server waits for a connection; the client connects to `127.0.0.1:50000`.
6. Once connected, both users can chat in real time.
7. Incoming messages are shown with their **raw encrypted hex bytes** for debugging, then decrypted and displayed.
8. Type `cikis` to exit the application.

---

## ⚙️ Features

- ✅ TCP peer-to-peer chat over Winsock2
- ✅ Custom multi-layer symmetric encryption (65 total rounds)
- ✅ Two-key cipher with message-length-dependent key derivation
- ✅ Threaded message receiving (non-blocking input/output)
- ✅ Raw hex display of incoming encrypted data *(C version)*
- ✅ Colorful terminal UI using ANSI color codes *(C version)*
- ✅ Server / Client mode selection at runtime
- ✅ Dark-themed graphical UI with tkinter *(Python version)*
- ✅ Selectable encryption algorithm: custom cipher or AES-256-GCM *(Python version)*
- ✅ Configurable IP, port, and username from the GUI *(Python version)*
- ✅ Wire-compatible with C terminal version when using the custom algorithm *(Python version)*

---

## 📸 Terminal Preview

```
======================================

            KRIPTO CHAT
        Omer Faruk Kelkitli

======================================

Enter First Key: ****
Enter Second Key: ****

  1-Server
  2-Client

Which side are you: _
```

---

## 📌 Notes

- The C application currently connects only over **localhost** (`127.0.0.1`). To use over a network, replace the IP address in `main.c`. The GUI version has the IP field configurable directly from the UI.
- The encryption algorithm is a **custom academic cipher** and is not intended for production-grade security.
- Both users must run the program on the same machine (or LAN) without a firewall blocking port `50000`.
- The Python GUI and C terminal versions can chat with each other, but **only when both select the custom algorithm**. AES-256-GCM mode is Python-only.

---

## 👤 Developer

**Ömer Faruk Kelkitli**  
Mechatronics Engineering — 1st Year Student
