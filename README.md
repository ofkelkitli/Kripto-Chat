# 🔐 KriptoChat — Encrypted Terminal Chat in C

> A terminal-based, peer-to-peer encrypted chat application written in C using Windows Sockets (Winsock2), featuring a custom multi-layer encryption algorithm.

---

## 📋 About the Project

KriptoChat is a real-time encrypted messaging application for Windows, built in C. Messages are encrypted using a custom algorithm before being sent over the network and decrypted upon arrival. Both parties must use the same two secret keys for the encryption and decryption to work correctly. The application supports a simple **server/client** architecture over TCP.

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
└── functions.c     # Core cipher operations (XOR, shift, add, subtract)
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

## 🚀 Getting Started

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
- ✅ Raw hex display of incoming encrypted data
- ✅ Colorful terminal UI using ANSI color codes
- ✅ Server / Client mode selection at runtime

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

- The application currently connects only over **localhost** (`127.0.0.1`). To use over a network, replace the IP address in `main.c`.
- The encryption algorithm is a **custom academic cipher** and is not intended for production-grade security.
- Both users must run the program on the same machine (or LAN) without a firewall blocking port `50000`.

---

## 👤 Developer

**Ömer Faruk Kelkitli**  
Mechatronics Engineering — 1st Year Student