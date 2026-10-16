import importlib.util
import unittest
from pathlib import Path

spec = importlib.util.spec_from_file_location("main", Path(__file__).with_name("main.py"))
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


class FormatCoinTest(unittest.TestCase):
    def test_format_coin_basic(self):
        self.assertEqual(module.format_coin(1234567, 6), "1.234567")
        self.assertEqual(module.format_coin(1000000, 6), "1")
        self.assertEqual(module.format_coin(-1234500, 6), "-1.2345")
        self.assertEqual(module.format_coin(42, 0), "42")


if __name__ == "__main__":
    unittest.main()
