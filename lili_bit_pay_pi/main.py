import threading
import time
from typing import Optional

import requests
import tkinter as tk
import qrcode
import urllib3


urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

BASE_URL = "https://ygibg-kiaaa-aaaai-ap7yq-cai.icp0.io/"
DEBUG = True


def fetch_text(path: str) -> Optional[str]:
    url = f"{BASE_URL}{path}"
    try:
        response = requests.get(url, timeout=10, verify=False)
        if response.status_code == 200:
            return response.text.strip()
        if DEBUG:
            print(f"[HTTP] {path} -> {response.status_code}")
    except Exception as exc:  # pragma: no cover - runtime network failure
        if DEBUG:
            print(f"[HTTP] {path} error: {exc}")
    return None


def parse_int(value: Optional[str], default: int = 0) -> int:
    if value is None:
        return default
    try:
        return int(str(value).strip())
    except ValueError:
        return default


def format_coin(value: int, decimals: int) -> str:
    if decimals < 0:
        decimals = 0
    scale = 10 ** decimals
    sign = "-" if value < 0 else ""
    value = abs(value)
    whole = value // scale
    fraction = value % scale
    if decimals == 0:
        return f"{sign}{whole}"
    fraction_str = str(fraction).rjust(decimals, "0")
    fraction_str = fraction_str.rstrip("0")
    if not fraction_str:
        return f"{sign}{whole}"
    return f"{sign}{whole}.{fraction_str}"


class PaymentTerminal:
    def __init__(self):
        self.address = ""
        self.balance = 0
        self.history = 0
        self.take = 0
        self.decimals = 6
        self.coin = "USDT"
        self.error = ""
        self.status = "startup"
        self.lock = threading.Lock()

        self.root = None
        try:
            self.root = tk.Tk()
            self.root.title("Lili Bit Pay")
            self.root.configure(bg="black")
            self.root.attributes("-fullscreen", True)
            self.root.bind("<Escape>", lambda event: self.root.destroy())

            self.canvas = tk.Canvas(self.root, width=1920, height=1080, bg="black", highlightthickness=0)
            self.canvas.pack(fill="both", expand=True)
            self.root.after(1000, self.refresh_cycle)
        except tk.TclError:
            if DEBUG:
                print("[APP] No desktop display detected. Running in headless mode.")
            self.root = None
            self.canvas = None
            self.status = "headless"

    def fetch_address(self) -> None:
        value = fetch_text("addres")
        if value:
            self.address = value

    def fetch_balance(self) -> None:
        value = fetch_text("ckusdt_balance")
        balance = parse_int(value)
        with self.lock:
            self.balance = balance

    def fetch_format(self) -> None:
        value = fetch_text("ckusdt_format")
        decimals = parse_int(value, 6)
        with self.lock:
            self.decimals = max(0, decimals)

    def fetch_coin(self) -> None:
        value = fetch_text("howcoin")
        if value:
            with self.lock:
                self.coin = value

    def refresh_cycle(self):
        threading.Thread(target=self._refresh_worker, daemon=True).start()
        self.root.after(3000, self.refresh_cycle)

    def _refresh_worker(self):
        try:
            if not self.address:
                self.fetch_address()
            self.fetch_coin()
            self.fetch_format()
            self.fetch_balance()

            with self.lock:
                if self.balance != self.history:
                    self.take = self.balance - self.history
                    self.history = self.balance

            if not self.address:
                self.error = "Address waiting"
            else:
                self.error = ""

            self.root.after(0, self.render)
        except Exception as exc:  # pragma: no cover - safety net
            self.error = "Network error"
            if DEBUG:
                print(f"[APP] refresh error: {exc}")
            self.root.after(0, self.render)

    def draw_qr(self, text: str, x: int, y: int, size: int = 8):
        if not text:
            return
        try:
            qr = qrcode.QRCode(version=1, box_size=size, border=2)
            qr.add_data(text)
            qr.make(fit=True)
            matrix = qr.get_matrix()
            for row_index, row in enumerate(matrix):
                for col_index, bit in enumerate(row):
                    if bit:
                        self.canvas.create_rectangle(
                            x + col_index * size,
                            y + row_index * size,
                            x + (col_index + 1) * size,
                            y + (row_index + 1) * size,
                            fill="white",
                            outline="white",
                        )
        except Exception as exc:  # pragma: no cover - graceful fallback
            if DEBUG:
                print(f"[QR] render error: {exc}")
            self.canvas.create_text(x + 80, y + 80, text="QR", fill="white", font=("Arial", 20, "bold"))

    def render(self):
        self.canvas.delete("all")

        # Header
        self.canvas.create_text(60, 30, anchor="w", text="network", fill="white", font=("Arial", 20, "bold"))
        self.canvas.create_text(60, 70, anchor="w", text="ICP", fill="white", font=("Arial", 26, "bold"))

        # Coin info
        self.canvas.create_text(60, 120, anchor="w", text=f"coin: {self.coin}", fill="white", font=("Arial", 20))
        self.canvas.create_text(60, 160, anchor="w", text=f"balance: {format_coin(self.balance, self.decimals)}", fill="white", font=("Arial", 22, "bold"))

        if self.address:
            self.draw_qr(self.address, 900, 150, 7)
            self.canvas.create_text(900, 30, anchor="w", text="address", fill="white", font=("Arial", 18, "bold"))
            self.canvas.create_text(900, 70, anchor="w", text=self.address[:32], fill="white", font=("Arial", 14))
            if len(self.address) > 32:
                self.canvas.create_text(900, 95, anchor="w", text=self.address[32:64], fill="white", font=("Arial", 14))

        if self.take != 0:
            self.canvas.create_text(60, 220, anchor="w", text="take", fill="white", font=("Arial", 18, "bold"))
            self.canvas.create_text(200, 220, anchor="w", text=f"{format_coin(self.take, self.decimals)}", fill="#90EE90", font=("Arial", 20, "bold"))

        if self.error:
            self.canvas.create_rectangle(50, 720, 760, 980, fill="white")
            self.canvas.create_text(120, 770, anchor="w", text="ERROR", fill="black", font=("Arial", 28, "bold"))
            self.canvas.create_text(120, 820, anchor="w", text=self.error, fill="black", font=("Arial", 22))

        self.canvas.create_text(60, 1000, anchor="w", text="press ESC to exit", fill="#bbbbbb", font=("Arial", 12))

    def run(self):
        if self.root is None:
            print("[APP] Headless mode: waiting for network and printing status to terminal only.")
            while True:
                self.refresh_cycle()
                time.sleep(5)
            return
        self.root.mainloop()


if __name__ == "__main__":
    app = PaymentTerminal()
    app.run()
