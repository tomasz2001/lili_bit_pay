# lili_bit_pay
License: AGPLv3

lili_bit_pay is low cost and open-source Solana pay terminal using Helius
this project use xiao-esp32-c6 and popular i2c oled 128x64 screan
![alt text](https://github.com/tomasz2001/lili_bit_pay/blob/main/logo.png?raw=true "Logo")

### 💡 Philosophy: Why DIY?

Most commercial crypto terminals are overpriced "black boxes." They charge you for:
- Expensive hardware that lacks even a simple display.
- Centralized backends that can be shut down at any time.
- High fees for "processing" payments that should be peer-to-peer.

**Lili Bit-Pay** is a statement. It proves that for $10 and a bit of open-source code, you can have a transparent, independent, and secure SOL monitor. No middlemen, no "redstone" centralized garbage, just pure blockchain.

## 🛡️ The Vision: Why Lili Bit-Pay?

The core problem with crypto adoption today is that we traded **practicality for nonsense**. For cryptocurrencies to be attractive, they must be easier to implement than legacy Web2 payments.

### The Reality of Payments:

1.  **Cash:**
    * **Pros:** Universal and simple.
    * **Cons:** High physical risk. You must store cash on-site, manage small change, and deal with the constant threat of counterfeit money.

2.  **Electronic Payments (Cards/Web2):**
    * **Cons:** A nightmare for small businesses. You are forced to prove "you are not a camel" (endless bureaucracy/KYC), pay high fees to middleman operators, and wait days for your funds to be unlocked. Most terminals are expensive, closed-source "black boxes."

3.  **Lili Bit-Pay (The Solution):**
    * **Pros:** Zero nonsense. It is a minimalist terminal that monitors your crypto wallet and alerts you when a payment arrives. 
    * **Privacy:** It doesn't ask for your ID or your political views. 
    * **Zero Fees:** No middleman takes a cut. Data is fetched from Helius or your own Solana RPC node.

### 🗺️ Roadmap & Future Plans:
* **API Expansion:** Adding more sources for blockchain data to ensure 100% uptime and decentralization.
* **Sales Records System:** An optional logging module to bring Lili Bit-Pay into the world of "serious business" accounting.
* **Stablecoin Support:** Implementing support for stablecoins to eliminate price volatility for everyday merchants.

## Solana / Helius Setup

1. Create a Helius API key.
2. Put your Solana wallet public address in `address` inside `lili_bit.ino`.
3. Put your Helius API key in `apiKey`.
4. Set `heliusCluster` to `mainnet` or `devnet`.
5. Generate a new QR bitmap for your Solana address and replace `qr_code` in `lili_bit.ino`.

---
*Built for freedom, simplicity, and true peer-to-peer commerce.*


| Feature | **Lili Bit-Pay (This Project)** | **Commercial Terminals** | **Custodial Apps** |
| :--- | :--- | :--- | :--- |
| **Model** | **100% Open Source** | Proprietary | Centralized |
| **Hardware Cost** | **~$10 - $15** (DIY) | $300 - $700+ | $0 |
| **Transaction Fees** | **0%** (Network only) | 1% - 3% + fees | ~1% |
| **Ownership** | **Self-Custody** (Your keys) | Third-party managed | Middleman control |
| **Privacy (KYC)** | **None.** Anonymous. | Full Verification | ID required |
| **Independence** | **High.** Decentralized. | **Low.** Server dependent. | **Low.** Risk of freezes. |
| **Setup** | DIY / Enthusiast | Plug & Play | App Registration |


 /\
\/ \
/\\/
# depression freeze list

| **CODE** | **wat hapent** | **how fix shis shit** |
| :--- | :----- | :------ |
| **E_A0** | API say [fuck you] for your terminal or you terminal have problem to con this API | check Helius api key, wallet address, wifi data and network connection |


![alt text](https://github.com/tomasz2001/lili_bit_pay/blob/main/lili_photo.jpeg?raw=true "IMAGE1")
hack the planet
