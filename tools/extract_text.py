#!/usr/bin/python3
import argparse
import re
from pathlib import Path

from common import auto_int, get_byte, get_int, get_short


def get_text_offset_list(infile, blockOffset):
    infile.seek(blockOffset)
    offTo1 = get_short(infile)
    offsetList = [blockOffset + offTo1]
    for _ in range((offTo1 >> 1) - 1):
        offsetList.append(blockOffset + get_short(infile))
    return offsetList

charmap_en = {
    0x00: " ",
    0x01: "0",
    0x02: "1",
    0x03: "2",
    0x04: "3",
    0x05: "4",
    0x06: "5",
    0x07: "6",
    0x08: "7",
    0x09: "8",
    0x0A: "9",
    0x0B: "a",
    0x0C: "b",
    0x0D: "c",
    0x0E: "d",
    0x0F: "e",
    0x10: "f",
    0x11: "g",
    0x12: "h",
    0x13: "i",
    0x14: "j",
    0x15: "k",
    0x16: "l",
    0x17: "m",
    0x18: "n",
    0x19: "o",
    0x1A: "p",
    0x1B: "q",
    0x1C: "r",
    0x1D: "s",
    0x1E: "t",
    0x1F: "u",
    0x20: "v",
    0x21: "w",
    0x22: "x",
    0x23: "y",
    0x24: "z",
    0x25: "A",
    0x26: "B",
    0x27: "C",
    0x28: "D",
    0x29: "E",
    0x2A: "F",
    0x2B: "G",
    0x2C: "H",
    0x2D: "I",
    0x2E: "J",
    0x2F: "K",
    0x30: "L",
    0x31: "M",
    0x32: "N",
    0x33: "O",
    0x34: "P",
    0x35: "Q",
    0x36: "R",
    0x37: "S",
    0x38: "T",
    0x39: "U",
    0x3A: "V",
    0x3B: "W",
    0x3C: "X",
    0x3D: "Y",
    0x3E: "Z",
    0x3F: "[V2]",
    0x40: "[V3]",
    0x41: "-",
    0x42: "×",
    0x43: ": ",
    0x44: ":",
    0x45: "?",
    0x46: "+",
    0x47: "÷",
    0x48: "※",
    0x49: "*",
    0x4A: "!",
    0x4C: "%",
    0x4D: "&",
    0x4E: ",",
    0x4F: "。",
    0x50: ".",
    0x51: "・",
    0x52: ";",
    0x53: "'",
    0x54: "\"",
    0x55: "~",
    0x56: "/",
    0x57: "(",
    0x58: ")",
    0x59: "「",
    0x5A: "」",
    0x5B: "↑",
    0x5C: "→",
    0x5D: "↓",
    0x5E: "←",
    0x5F: "@",
    0x60: "★",
    0x61: "♪",
    0x62: "<",
    0x63: ">",
    0x64: "[",
    0x65: "]",
    0x66: "■",
    0x67: "$",
    0x68: "#"
}


charmap = {
    0x00: " ",
    0x01: "0",
    0x02: "1",
    0x03: "2",
    0x04: "3",
    0x05: "4",
    0x06: "5",
    0x07: "6",
    0x08: "7",
    0x09: "8",
    0x0A: "9",
    0x0B: "{lv}",  # katakana ア
    0x0C: "∥",  # katakana イ
    0x0D: "ウ",
    0x0E: "エ",
    0x0F: "オ",
    0x10: "カ",
    0x11: "キ",
    0x12: "ク",
    0x13: "ケ",
    0x14: "コ",
    0x15: "サ",
    0x16: "シ",
    0x17: "ス",
    0x18: "セ",
    0x19: "ソ",
    0x1A: "タ",
    0x1B: "チ",
    0x1C: "ツ",
    0x1D: "テ",
    0x1E: "ト",
    0x1F: "ナ",
    0x20: "ニ",
    0x21: "ヌ",
    0x22: "ネ",
    0x23: "ノ",
    0x24: "ハ",
    0x25: "ヒ",
    0x26: "フ",
    0x27: "ヘ",
    0x28: "ホ",
    0x29: "マ",
    0x2A: "ミ",
    0x2B: "ム",
    0x2C: "メ",
    0x2D: "モ",
    0x2E: "ヤ",
    0x2F: "ユ",
    0x30: "ヨ",
    0x31: "ラ",
    0x32: "リ",
    0x33: "ル",
    0x34: "レ",
    0x35: "ロ",
    0x36: "ワ",
    0x37: "ヰ",
    0x38: "ヱ",
    0x39: "ヲ",
    0x3A: "ン",
    0x3B: "ガ",
    0x3C: "ギ",
    0x3D: "グ",
    0x3E: "ゲ",
    0x3F: "ゴ",
    0x40: "ザ",
    0x41: "ジ",
    0x42: "ズ",
    0x43: "ゼ",
    0x44: "ゾ",
    0x45: "ダ",
    0x46: "ヂ",
    0x47: "ヅ",
    0x48: "デ",
    0x49: "ド",
    0x4A: "バ",
    0x4B: "ビ",
    0x4C: "ブ",
    0x4D: "ベ",
    0x4E: "ボ",
    0x4F: "パ",
    0x50: "ピ",
    0x51: "プ",
    0x52: "ペ",
    0x53: "ポ",
    0x54: "ァ",
    0x55: "ィ",
    0x56: "ゥ",
    0x57: "ェ",
    0x58: "ォ",
    0x59: "ッ",
    0x5A: "ャ",
    0x5B: "ュ",
    0x5C: "ョ",
    0x5D: "ヴ",
    0x5E: "ー",
    0x5F: "A",
    0x60: "B",
    0x61: "C",
    0x62: "D",
    0x63: "E",
    0x64: "F",
    0x65: "G",
    0x66: "H",
    0x67: "I",
    0x68: "J",
    0x69: "K",
    0x6A: "L",
    0x6B: "M",
    0x6C: "N",
    0x6D: "O",
    0x6E: "P",
    0x6F: "Q",
    0x70: "R",
    0x71: "S",
    0x72: "T",
    0x73: "U",
    0x74: "V",
    0x75: "W",
    0x76: "X",
    0x77: "Y",
    0x78: "Z",
    0x79: "a",
    0x7A: "b",
    0x7B: "c",
    0x7C: "d",
    0x7D: "e",
    0x7E: "f",
    0x7F: "g",
    0x80: "h",
    0x81: "i",
    0x82: "j",
    0x83: "k",
    0x84: "l",
    0x85: "m",
    0x86: "n",
    0x87: "o",
    0x88: "p",
    0x89: "q",
    0x8A: "r",
    0x8B: "s",
    0x8C: "t",
    0x8D: "u",
    0x8E: "v",
    0x8F: "w",
    0x90: "x",
    0x91: "y",
    0x92: "z",
    0x93: "あ",
    0x94: "い",
    0x95: "う",
    0x96: "え",
    0x97: "お",
    0x98: "か",
    0x99: "き",
    0x9A: "く",
    0x9B: "け",
    0x9C: "こ",
    0x9D: "さ",
    0x9E: "し",
    0x9F: "す",
    0xA0: "せ",
    0xA1: "そ",
    0xA2: "た",
    0xA3: "ち",
    0xA4: "つ",
    0xA5: "て",
    0xA6: "と",
    0xA7: "な",
    0xA8: "に",
    0xA9: "ぬ",
    0xAA: "ね",
    0xAB: "の",
    0xAC: "は",
    0xAD: "ひ",
    0xAE: "ふ",
    0xAF: "へ",
    0xB0: "ほ",
    0xB1: "ま",
    0xB2: "み",
    0xB3: "む",
    0xB4: "め",
    0xB5: "も",
    0xB6: "や",
    0xB7: "ゆ",
    0xB8: "よ",
    0xB9: "ら",
    0xBA: "り",
    0xBB: "る",
    0xBC: "れ",
    0xBD: "ろ",
    0xBE: "わ",
    0xBF: "ゐ",
    0xC0: "ゑ",
    0xC1: "を",
    0xC2: "ん",
    0xC3: "が",
    0xC4: "ぎ",
    0xC5: "ぐ",
    0xC6: "げ",
    0xC7: "ご",
    0xC8: "ざ",
    0xC9: "じ",
    0xCA: "ず",
    0xCB: "ぜ",
    0xCC: "ぞ",
    0xCD: "だ",
    0xCE: "ぢ",
    0xCF: "づ",
    0xD0: "で",
    0xD1: "ど",
    0xD2: "ば",
    0xD3: "び",
    0xD4: "ぶ",
    0xD5: "べ",
    0xD6: "ぼ",
    0xD7: "ぱ",
    0xD8: "ぴ",
    0xD9: "ぷ",
    0xDA: "ぺ",
    0xDB: "ぽ",
    0xDC: "ぁ",
    0xDD: "ぃ",
    0xDE: "ぅ",
    0xDF: "ぇ",
    0xE0: "ぉ",
    0xE1: "っ",
    0xE2: "ゃ",
    0xE3: "ゅ",
    0xE4: "ょ",
    0xE5: "!",
    0xE6: "‼️",
    0xE7: "?",
    0xE8: '\\"',
    0xE9: "„",
    0xEA: "#",
    0xEB: "♭",
    0xEC: "$",
    0xED: "%",
    0xEE: "&",
    0xEF: "'",
    0xF0: "(",
    0xF1: ")",
    0xF2: "~",
    0xF3: "ˆ",
    0xF4: "˜",
    0xF5: "⌃",
    0xF6: "⌄",
    0xF7: "˂",
    0xF8: "˃",
    0xF9: ",",
    0xFA: "。",
    0xFB: ".",
    0xFC: "・",
    0xFD: "/",
    0xFE: "\\\\",
    0xFF: "_",
    0x100: "「",
    0x101: "」",
    0x102: "[",
    0x103: "]",
    0x104: "【",
    0x105: "】",
    0x106: "⊂",
    0x107: "⊃",
    0x108: "⋂",
    0x109: "💧",
    0x10A: "↑",
    0x10B: "→",
    0x10C: "↓",
    0x10D: "←",
    0x10E: "∀",
    0x10F: "α",
    0x110: "β",
    0x111: "★",
    0x112: "♥",
    0x113: "♪",
    0x114: "℃",
    0x115: "♂︎",
    0x116: "♀︎",
    0x117: "_",
    0x118: "|",
    0x119: "‾",
    0x11A: ":",
    0x11B: ";",
    0x11C: "…",
    0x11D: "¥",
    0x11E: "[+]",
    0x11F: "−",
    0x120: "×",
    0x121: "÷",
    0x122: "=",
    0x123: "※",
    0x124: "*",
    0x125: "○",
    0x126: "⬤",
    0x127: "◉",
    0x128: "□",
    0x129: "■",
    0x12A: "◇",
    0x12B: "◆",
    0x12C: "△",
    0x12D: "▲",
    0x12E: "▽",
    0x12F: "▼",
    0x130: "▶",
    0x131: "◀",
    0x132: "☛",
    0x133: "\\x0133",
    0x134: "\\x0134",
    0x135: "\\x0135",
    0x136: "\\x0136",
    0x137: "\\x0137",
    0x138: "\\x0138",
    0x139: "\\x0139",
    0x13A: "\\x013A",
    0x13B: "\\x013B",
    0x13C: "\\x013C",
    0x13D: "\\x013D",
    0x13E: "\\x013E",
    0x13F: "\\x013F",
    0x140: "\\x0140",
    0x141: "\\x0141",
    0x142: "\\x0142",
    0x143: "\\x0143",
    0x144: "\\x0144",
    0x145: "\\x0145",
    0x146: "\\x0146",
    0x147: "\\x0147",
    0x148: "\\x0148",
    0x149: "\\x0149",
    0x14A: "\\x014A",
    0x14B: "\\x014B",
    0x14C: "\\x014C",
    0x14D: "\\x014D",
    0x14E: "\\x014E",
    0x14F: "\\x014F",
    0x150: "\\x0150",
    0x151: "\\x0151",
    0x152: "\\x0152",
    0x153: "\\x0153",
    0x154: "\\x0154",
    0x155: "\\x0155",
    0x156: "\\x0156",
    0x157: "\\x0157",
    0x158: "\\x0158",
    0x159: "\\x0159",
    0x15A: "\\x015A",
    0x15B: "\\x015B",
    0x15C: "\\x015C",
    0x15D: "\\x015D",
    0x15E: "\\x015E",
    0x15F: "\\x015F",
    0x160: "\\x0160",
    0x161: "\\x0161",
    0x162: "\\x0162",
    0x163: "\\x0163",
    0x164: "\\x0164",
    0x165: "\\x0165",
    0x166: "\\x0166",
    0x167: "\\x0167",
    0x168: "\\x0168",
    0x169: "\\x0169",
    0x16A: "\\x016A",
    0x16B: "\\x016B",
    0x16C: "\\x016C",
    0x16D: "\\x016D",
    0x16E: "\\x016E",
    0x16F: "\\x016F",
    0x170: "\\x0170",
    0x171: "\\x0171",
    0x172: "\\x0172",
    0x173: "\\x0173",
    0x174: "\\x0174",
    0x175: "\\x0175",
    0x176: "\\x0176",
    0x177: "\\x0177",
    0x178: "\\x0178",
    0x179: "\\x0179",
    0x17A: "\\x017A",
    0x17B: "\\x017B",
    0x17C: "\\x017C",
    0x17D: "\\x017D",
    0x17E: "\\x017E",
    0x17F: "\\x017F",
    0x180: "\\x0180",
    0x181: "\\x0181",
    0x182: "\\x0182",
    0x183: "\\x0183",
    0x184: "\\x0184",
    0x185: "\\x0185",
    0x186: "\\x0186",
    0x187: "\\x0187",
    0x188: "\\x0188",
    0x189: "\\x0189",
    0x18A: "\\x018A",
    0x18B: "\\x018B",
    0x18C: "\\x018C",
    0x18D: "\\x018D",
    0x18E: "\\x018E",
    0x18F: "\\x018F",
    0x190: "¼",
    0x191: "[inf1]",
    0x192: "[inf2]",
    0x193: "\\x0193",
    0x194: "\\x0194",
    0x195: "\\x0195",
    0x196: "\\x0196",
    0x197: "\\x0197",
    0x198: "\\x0198",
    0x199: "\\x0199",
    0x19A: "\\x019A",
    0x19B: "\\x019B",
    0x19C: "\\x019C",
    0x19D: "\\x019D",
    0x19E: "\\x019E",
    0x19F: "\\x019F",
    0x1A0: "\\x01A0",
    0x1A1: "\\x01A1",
    0x1A2: "\\x01A2",
    0x1A3: "\\x01A3",
    0x1A4: "\\x01A4",
    0x1A5: "\\x01A5",
    0x1A6: "\\x01A6",
    0x1A7: "\\x01A7",
    0x1A8: "\\x01A8",
    0x1A9: "\\x01A9",
    0x1AA: "\\x01AA",
    0x1AB: "\\x01AB",
    0x1AC: "\\x01AC",
    0x1AD: "\\x01AD",
    0x1AE: "\\x01AE",
    0x1AF: "\\x01AF",
    0x1B0: "\\x01B0",
    0x1B1: "\\x01B1",
    0x1B2: "\\x01B2",
    0x1B3: "\\x01B3",
    0x1B4: "\\x01B4",
    0x1B5: "\\x01B5",
    0x1B6: "\\x01B6",
    0x1B7: "\\x01B7",
    0x1B8: "\\x01B8",
    0x1B9: "\\x01B9",
    0x1BA: "\\x01BA",
    0x1BB: "\\x01BB",
    0x1BC: "\\x01BC",
    0x1BD: "\\x01BD",
    0x1BE: "\\x01BE",
    0x1BF: "\\x01BF",
    0x1C0: "\\x01C0",
    0x1C1: "\\x01C1",
    0x1C2: "\\x01C2",
    0x1C3: "\\x01C3",
    0x1C4: "\\x01C4",
    0x1C5: "\\x01C5",
    0x1C6: "\\x01C6",
    0x1C7: "\\x01C7",
    0x1C8: "\\x01C8",
    0x1C9: "\\x01C9",
    0x1CA: "\\x01CA",
    0x1CB: "\\x01CB",
    0x1CC: "\\x01CC",
    0x1CD: "\\x01CD",
    0x1CE: "\\x01CE",
    0x1CF: "\\x01CF",
    0x1D0: "\\x01D0",
    0x1D1: "\\x01D1",
    0x1D2: "\\x01D2",
    0x1D3: "\\x01D3",
    0x1D4: "\\x01D4",
    0x1D5: "\\x01D5",
    0x1D6: "\\x01D6",
    0x1D7: "\\x01D7",
    0x1D8: "\\x01D8",
    0x1D9: "\\x01D9",
    0x1DA: "\\x01DA",
    0x1DB: "\\x01DB",
    0x1DC: "\\x01DC",
    0x1DD: "\\x01DD",
    0x1DE: "\\x01DE",
    0x1DF: "\\x01DF",
    0x1E0: "\\x01E0",
    0x1E1: "\\x01E1",
    0x1E2: "\\x01E2",
    0x1E3: "\\x01E3",
    0x1E4: "\\x01E4",
    0x1E5: "\\x01E5",
    0x1E6: "\\x01E6",
    0x1E7: "\\x01E7",
    0x1E8: "\\x01E8",
    0x1E9: "\\x01E9",
    0x1EA: "\\x01EA",
    0x1EB: "\\x01EB",
    0x1EC: "\\x01EC",
    0x1ED: "\\x01ED",
    0x1EE: "\\x01EE",
    0x1EF: "\\x01EF",
    0x1F0: "\\x01F0",
    0x1F1: "\\x01F1",
    0x1F2: "\\x01F2",
    0x1F3: "\\x01F3",
    0x1F4: "\\x01F4",
    0x1F5: "\\x01F5",
    0x1F6: "\\x01F6",
    0x1F7: "\\x01F7",
    0x1F8: "\\x01F8",
    0x1F9: "\\x01F9",
    0x1FA: "\\x01FA",
    0x1FB: "\\x01FB",
    0x1FC: "\\x01FC",
    0x1FD: "\\x01FD",
    0x1FE: "\\x01FE",
    0x1FF: "\\x01FF",
}


def arg_list(infile, count=1, func=lambda inf, i: f"0x{get_byte(inf):02X}"):
    argList = []
    for i in range(count):
        arg = str(func(infile, i))
        if arg != "":
            argList.append(arg)
    return ", ".join(argList)


def key_item(bt):
    itemList = {
        0x00: "PET",
        0x01: "HeroData",
        0x02: "HopeData",
        0x03: "Fan",
        0x04: "ExamCard",
        0x05: "WalkProg",
        0x06: "NiceData",
        0x07: "Paper",
        0x08: "Lighter",
        0x09: "Stick",
        0x0A: "Binocs",
        0x0B: "Knife",
        0x0C: "Firewood",
        0x0D: "Fish",
        0x0E: "Balloon",
        0x0F: "OddProg",
        0x10: "BadDataA",
        0x11: "BadDataB",
        0x12: "Battery",
        0x13: "YumKey",
        0x14: "NoteData",
        0x15: "Chng_bat",
        0x16: "Ticket",
        0x17: "Passport",
        0x18: "Wireless",
        0x19: "MiniPET",
        0x1A: "CyberKey",
        0x1B: "Broach",
        0x1C: "RoboX",
        0x1D: "GoldRing",
        0x1E: "PilotCap",
        0x1F: "Chopstck",
        0x20: "Whiskey",
        0x21: "Thread",
        0x22: "RedFrag",
        0x23: "RedCure",
        0x24: "HeatData",
        0x25: "YeloCure",
        0x26: "BluFragA",
        0x27: "BluFragB",
        0x28: "GospelID",
        0x29: "KotoPass",
        0x2A: "MagSuit",
        0x2B: "ElBit042",
        0x2C: "ElBit082",
        0x2D: "ElBit093",
        0x2E: "ElBit201",
        0x2F: "ElBit232",
        0x30: "ElBit243",
        0x31: "ElBit253",
        0x32: "ElBit271",
        0x33: "ElBitEV",
        0x34: "LoveLetr",
        0x35: "Beetle",
        0x36: "YumTear",
        0x37: "KngStone",
        0x38: "Twilight",
        0x39: "ArmyData",
        0x3A: "ZLicense",
        0x3B: "BLicense",
        0x3C: "ALicense",
        0x3D: "SLicense",
        0x3E: "SS_Lic",
        0x3F: "SSS_Lic",
        0x40: "FreePass",
        0x41: "GateKeyA",
        0x42: "GateKeyB",
        0x43: "GateKeyC",
        0x44: "GateKeyD",
        0x45: "BugFrag",
        0x50: "MaylCode",
        0x51: "DexCode",
        0x52: "YaiCode",
        0x53: "RibiCode",
        0x54: "RaulCode",
        0x55: "MiliCode",
        0x56: "ONBACode",
        0x57: "GospCode",
        0x58: "ACDCPass",
        0x59: "MariPass",
        0x5A: "OkuPass",
        0x5B: "AirPass",
        0x60: "HPMemory",
        0x61: "PowerUP",
        0x62: "RegUP1",
        0x63: "RegUP2",
        0x64: "RegUP3",
        0x65: "SubMem",
        0x70: "MiniEnrg",
        0x71: "FullEnrg",
        0x72: "SneakRun",
        0x73: "Untrap",
        0x74: "LocEnemy",
        0x75: "Unlocker",
        0x7F: "ITEM7F",
        0x80: "NormStyl",
        0x86: "ElecGuts",
        0x87: "HeatGuts",
        0x88: "AquaGuts",
        0x89: "WoodGuts",
        0x8B: "ElecCust",
        0x8C: "HeatCust",
        0x8D: "AquaCust",
        0x8E: "WoodCust",
        0x90: "ElecTeam",
        0x91: "HeatTeam",
        0x92: "AquaTeam",
        0x93: "WoodTeam",
        0x95: "ElecShld",
        0x96: "HeatShld",
        0x97: "AquaShld",
        0x98: "WoodShld",
        0x99: "HubStyl"
    }
    return f'"{itemList[bt]}"' if bt in itemList else bt


def chip_id(bt):
    idSet = {
        0: "Buster",
        1: "Cannon",
        2: "HiCannon",
        3: "M_Cannon",
        4: "Shotgun",
        5: "V_Gun",
        6: "CrossGun",
        7: "Spreader",
        8: "Bubbler",
        9: "Bub_V",
        10: "BubCross",
        11: "BubSprd",
        12: "HeatShot",
        13: "Heat_V",
        14: "HeatCros",
        15: "HeatSprd",
        16: "MiniBomb",
        17: "LilBomb",
        18: "CrosBomb",
        19: "BigBomb",
        20: "TreeBom1",
        21: "TreeBom2",
        22: "TreeBom3",
        23: "Sword",
        24: "WideSwrd",
        25: "LongSwrd",
        26: "FireSwrd",
        27: "AquaSwrd",
        28: "ElecSwrd",
        29: "FireBlde",
        30: "AquaBlde",
        31: "ElecBlde",
        32: "StepSwrd",
        33: "Muramasa",
        34: "CustSwrd",
        35: "Kunai1",
        36: "Kunai2",
        37: "Kunai3",
        38: "Slasher",
        39: "Shockwav",
        40: "Sonicwav",
        41: "Dynawave",
        42: "Quake1",
        43: "Quake2",
        44: "Quake3",
        45: "GutPunch",
        46: "ColdPnch",
        47: "Atk20",
        48: "Atk30",
        49: "Navi40",
        50: "DashAtk",
        51: "Wrecker",
        52: "CannBall",
        53: "DoubNdl",
        54: "TripNdl",
        55: "QuadNdl",
        56: "Trident",
        57: "Ratton1",
        58: "Ratton2",
        59: "Ratton3",
        60: "FireRat",
        61: "Tornado",
        62: "Twister",
        63: "Blower",
        64: "Burner",
        65: "ZapRing1",
        66: "ZapRing2",
        67: "ZapRing3",
        68: "Spice1",
        69: "Spice2",
        70: "Spice3",
        71: "Satelit1",
        72: "Satelit2",
        73: "Satelit3",
        74: "Yo_Yo1",
        75: "Yo_Yo2",
        76: "Yo_Yo3",
        77: "MagBomb1",
        78: "MagBomb2",
        79: "MagBomb3",
        80: "Meteor9",
        81: "Meteor12",
        82: "Meteor15",
        83: "Meteor18",
        84: "Hammer",
        85: "CrsShld1",
        86: "CrsShld2",
        87: "CrsShld3",
        88: "TimeBom1",
        89: "TimeBom2",
        90: "TimeBom3",
        91: "LilCloud",
        92: "MedCloud",
        93: "BigCloud",
        94: "Mine",
        95: "FrntSnsr",
        96: "DblSnsr",
        97: "Remobit1",
        98: "Remobit2",
        99: "Remobit3",
        100: "AquaBall",
        101: "ElecBall",
        102: "HeatBall",
        103: "Geyser",
        104: "LavaDrag",
        105: "GodStone",
        106: "OldWood",
        107: "PoisMask",
        108: "PoisFace",
        109: "Whirlpl",
        110: "Blckhole",
        111: "Guard",
        112: "Barrier",
        113: "PanlOut1",
        114: "PanlOut3",
        115: "LineOut",
        116: "Lance",
        117: "ZeusHamr",
        118: "BrnzFist",
        119: "SilvFist",
        120: "GoldFist",
        121: "VarSwrd",
        122: "Recov10",
        123: "Recov30",
        124: "Recov50",
        125: "Recov80",
        126: "Recov120",
        127: "Recov150",
        128: "Recov200",
        129: "Recov300",
        130: "PanlGrab",
        131: "AreaGrab",
        132: "GrabRvng",
        133: "Geddon1",
        134: "Geddon2",
        135: "Geddon3",
        136: "Catcher",
        137: "Mindbndr",
        138: "Escape",
        139: "AirShoes",
        140: "Repair",
        141: "Candle1",
        142: "Candle2",
        143: "Candle3",
        144: "RockCube",
        145: "Prism",
        146: "Guardian",
        147: "Wind",
        148: "Fan",
        149: "Anubis",
        150: "SloGauge",
        151: "FstGauge",
        152: "FullCust",
        153: "Invis1",
        154: "Invis2",
        155: "Invis3",
        156: "DropDown",
        157: "PopUp",
        158: "StoneBod",
        159: "Shadow1",
        160: "Shadow2",
        161: "Shadow3",
        162: "UnderSht",
        163: "BblWrap",
        164: "LeafShld",
        165: "AquaAura",
        166: "FireAura",
        167: "WoodAura",
        168: "ElecAura",
        169: "LifeAur1",
        170: "LifeAur2",
        171: "LifeAur3",
        172: "MagLine",
        173: "LavaLine",
        174: "IceLine",
        175: "GrassLne",
        176: "LavaStge",
        177: "IceStage",
        178: "GrassStg",
        179: "HolyPanl",
        180: "Jealosy",
        181: "AntiFire",
        182: "AntiElec",
        183: "AntiWatr",
        184: "AntiDmg",
        185: "AntiSwrd",
        186: "AntiNavi",
        187: "AntiRecv",
        188: "Atk10",
        189: "Fire40",
        190: "Aqua40",
        191: "Wood40",
        192: "Elec40",
        193: "Navi20",
        194: "RollV1",
        195: "RollV2",
        196: "RollV3",
        197: "GutsManV1",
        198: "GutsManV2",
        199: "GutsManV3",
        200: "ProtomanV1",
        201: "ProtomanV2",
        202: "ProtomanV3",
        203: "AirManV1",
        204: "AirManV2",
        205: "AirManV3",
        206: "QuickManV1",
        207: "QuickManV2",
        208: "QuickManV3",
        209: "CutManV1",
        210: "CutManV2",
        211: "CutManV3",
        212: "ShadowManV1",
        213: "ShadowManV2",
        214: "ShadowManV3",
        215: "KnightManV1",
        216: "KnightManV2",
        217: "KnightManV3",
        218: "MagnetManV1",
        219: "MagnetManV2",
        220: "MagnetManV3",
        221: "FreezeManV1",
        222: "FreezeManV2",
        223: "FreezeManV3",
        224: "HeatManV1",
        225: "HeatManV2",
        226: "HeatManV3",
        227: "ToadManV1",
        228: "ToadManV2",
        229: "ToadManV3",
        230: "ThunderManV1",
        231: "ThunderManV2",
        232: "ThunderManV3",
        233: "SnakeManV1",
        234: "SnakeManV2",
        235: "SnakeManV3",
        236: "GateManV1",
        237: "GateManV2",
        238: "GateManV3",
        239: "PlanetManV1",
        240: "PlanetManV2",
        241: "PlanetManV3",
        242: "NapalmManV1",
        243: "NapalmManV2",
        244: "NapalmManV3",
        245: "PharaohManV1",
        246: "PharaohManV2",
        247: "PharaohManV3",
        248: "BassV1",
        249: "BassV2",
        250: "BassV3",
        251: "BgRedWav",
        252: "FreezBom",
        253: "Sparker",
        254: "GaiaSwrd",
        255: "BlkBomb",
        256: "FtrSword",
        257: "KngtSwrd",
        258: "HeroSwrd",
        259: "Meteors",
        260: "Poltrgst",
        261: "FireGspl",
        262: "AquaGspl",
        263: "ElecGspl",
        264: "WoodGspl",
        265: "GateSP",
        270: "Snctuary",
        272: "Z_Canon1",
        273: "Z_Canon2",
        274: "Z_Canon3",
        275: "H_Burst",
        276: "Z_Ball",
        277: "Z_Raton1",
        278: "Z_Raton2",
        279: "Z_Raton3",
        280: "O_Canon1",
        281: "O_Canon2",
        282: "O_Canon3",
        283: "M_Burst",
        284: "O_Ball",
        285: "O_Ratton1",
        286: "O_Ratton2",
        287: "O_Ratton3",
        288: "Arrows",
        289: "UltraBmd",
        290: "LifeSrd1",
        291: "LifeSrd2",
        292: "LifeSrd3",
        293: "Punch",
        294: "Curse",
        295: "TimeBom",
        296: "HvyStamp",
        297: "PoisPhar",
        298: "Gater",
        299: "GtsShoot",
        300: "BigHeart",
        301: "BodyGrd",
        302: "2xHero",
        303: "Darkness"
    }
    return idSet[bt] if bt in idSet else f"0x{bt:02X}"


def chip_code(bt):
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[bt] if bt < 27 else f"0x{bt:02X}"


def prog_adv(bt):
    prog_adv_dict = {
        0x00: "FtrSword",
        0x01: "KngtSwrd",
        0x02: "HeroSwrd",
        0x03: "Meteors",
        0x04: "Poltrgst",
        0x05: "FireGspl",
        0x06: "AquaGspl",
        0x07: "ElecGspl",
        0x08: "WoodGspl",
        0x09: "GateSP",
        0x0E: "Snctuary",
        0x10: "Z_Canon1",
        0x11: "Z_Canon2",
        0x12: "Z_Canon3",
        0x13: "H_Burst",
        0x14: "Z_Ball",
        0x15: "Z_Raton1",
        0x16: "Z_Raton2",
        0x17: "Z_Raton3",
        0x18: "O_Canon1",
        0x19: "O_Canon2",
        0x1A: "O_Canon3",
        0x1B: "M_Burst",
        0x1C: "O_Ball",
        0x1D: "O_Raton1",
        0x1E: "O_Raton2",
        0x1F: "O_Raton3",
        0x20: "Arrows",
        0x21: "UltraBmb",
        0x22: "LifeSrd1",
        0x23: "LifeSrd2",
        0x24: "LifeSrd3",
        0x25: "Punch",
        0x26: "Curse",
        0x27: "TimeBom_",
        0x28: "HvyStamp",
        0x29: "PoisPhar",
        0x2A: "Gater",
        0x2B: "GtsShoot",
        0x2C: "BigHeart",
        0x2D: "BodyGrd",
        0x2E: "2xHero",
        0x2F: "Darkness",
        0x33: "Punisher",
        0x34: "PharTrap",
        0x35: "2xPlanet",
        0x39: "RemoGate"
    }
    return prog_adv_dict[bt] if bt in prog_adv_dict else f"0x{bt:02X}"


def get_item(infile):
    return key_item(get_byte(infile))


def get_chip_id(infile):
    return f'"{chip_id(get_byte(infile))}"'


def get_chip_code(infile):
    return f'"{chip_code(get_byte(infile))}"'


def get_chip(infile):
    return f'"{chip_id(get_byte(infile))} {chip_code(get_byte(infile))}"'


# region Commands
def Com_E7(infile):
    textBuf = "end()"
    return True, textBuf


def Com_E8(infile):
    return False, "\\n"


def Com_E9(infile):
    return False, "wait()"


def Com_EA(infile):
    command = get_byte(infile)
    isDone = False
    if command == 0:
        delay = get_short(infile)
        textBuf = f"breaks({delay})"
    elif command == 1:
        delay = get_short(infile)
        if delay == 30:
            textBuf = "delay()"
        else:
            textBuf = f"delay({delay})"
    else:
        textBuf = "stop()"
        isDone = True
    return isDone, textBuf


def Com_EB(infile):
    return False, "page()"


def Com_EC(infile):
    command = get_byte(infile)
    if command == 0:
        delay = get_byte(infile)
        textBuf = f"set_delay({delay})"
    elif command == 1:
        textBuf = "skip_on()"
    else:
        textBuf = "skip_off()"
    return False, textBuf


def Com_ED(infile):
    command = get_byte(infile)
    if command == 1:
        textBuf = "hidepic()"
    elif command == 2:
        pal = get_byte(infile)
        textBuf = f"picpal({pal})"
    elif command == 3:
        pal = get_byte(infile)
        textBuf = f"pic3({pal})"
    else:
        pic = get_byte(infile)
        pal = get_byte(infile)
        if pal == 0:
            textBuf = f"pic({pic})"
        else:
            textBuf = f"pic({pic}, {pal})"
    return False, textBuf


def Com_EE(infile):
    command = get_byte(infile)
    count = get_byte(infile)
    if command == 0:
        textBuf = f"pad({count})"
    elif command == 1:
        textBuf = f"col({count})"
    else:
        left = get_byte(infile)
        top = get_byte(infile)
        textBuf = f"margin({left}, {top})"
    return False, textBuf


def Com_EF(infile):
    optpack = get_short(infile)
    rt = (optpack >> 0x0) & 0xF
    lt = (optpack >> 0x4) & 0xF
    dn = (optpack >> 0x8) & 0xF
    up = (optpack >> 0xC) & 0xF
    return False, f"option({up}, {dn}, {lt}, {rt})"


def Com_F0(infile):
    comlen = get_byte(infile)
    opt = get_byte(infile)
    defpick = opt & 0x3F
    isDisableB = (opt >> 6) & 1 != 0
    clearAfterPick = (opt >> 7) & 1 != 0
    return (
        False,
        f"pick([{arg_list(infile, comlen - 3)}], {defpick}, {isDisableB}, {clearAfterPick})",
    )


def Com_F1(infile):
    command = get_byte(infile)
    isDone = False
    if command == 0:
        textBuf = "dialog_up()"
    elif command == 1:
        textBuf = "dialog_down()"
    elif command == 2:
        textBuf = "dialog_show()"
    elif command == 3:
        textBuf = "dialog_hide()"
        isDone = True
    elif command == 0x10:
        val = get_byte(infile)
        textBuf = f"dialog_set({val})"
    else:
        textBuf = f"dialog_control({command})"
    return isDone, textBuf


def Com_F2(infile):
    command = get_byte(infile) >> 2
    flagpack = get_short(infile)
    flag = flagpack
    if command == 0:
        textBuf = f"set_flag({flag})"
    elif command == 1:
        textBuf = f"clear_flag({flag})"
    elif command == 2:
        textBuf = f"mail({flag})"
    else:
        textBuf = f"flag_control({command}, {flagpack})"
    return False, textBuf


def Com_F3(infile):
    command = get_byte(infile) >> 2
    if command == 0:
        def proc(inf, i):
            if i == 0:
                return get_short(inf)
            else:
                return arg_list(inf)

        textBuf = f"if_flag({arg_list(infile, 3, proc)})"
    elif command == 1:
        textBuf = f"if_story({arg_list(infile, 4)})"
    elif command == 2:
        textBuf = f"if_shop({arg_list(infile, 3)})"
    elif command == 3:

        def if_chip(inf, i):
            if i == 0:
                return get_chip(infile)
            else:
                return arg_list(inf)

        textBuf = f"if_chip({arg_list(infile, 3, if_chip)})"
    elif command == 4:

        def if_level(inf, i):
            if i == 0 or i == 1:
                return get_byte(inf)
            else:
                return arg_list(inf)

        textBuf = f"if_level({arg_list(infile, 4, if_level)})"
    elif command == 5:

        def if_bust(inf, i):
            if i == 0 or i == 1:
                lv = get_byte(inf)
                return f"'{lv}'" if lv < 11 else "'S'"
            else:
                return arg_list(inf)

        textBuf = f"if_bust({arg_list(infile, 4, if_bust)})"
    elif command == 6:

        def if_library(inf, i):
            if i == 0 or i == 1:
                return get_byte(inf)
            else:
                return arg_list(inf)

        textBuf = f"if_library({arg_list(infile, 4, if_library)})"
    elif command == 7:
        textBuf = f"if_sub_area_in({arg_list(infile, 4)})"
    elif command == 8:
        textBuf = f"if_event_in({arg_list(infile, 4)})"
    elif command == 9:
        textBuf = f"if_area_in({arg_list(infile, 4)})"
    else:
        textBuf = f"_F4({command})"
    return False, textBuf


def Com_F4(infile):
    command = get_byte(infile)
    if command == 0:
        textBuf = "input_off()"
    else:
        textBuf = "input_on()"
    return False, textBuf


def Com_F5(infile):
    command = get_byte(infile)
    args = arg_list(infile, command + 1)
    done = False
    if command == 0:
        textBuf = f"jump({args})"
        done = True
    else:
        textBuf = f"jumprandom([{args}])"
        done = False
    return done, textBuf


def Com_F6(infile):
    command = get_byte(infile)
    com_block = command >> 4

    def proc_chip(inf, i):
        if i == 0:
            return get_chip(infile)
        elif i == 1:
            return get_byte(infile)
        else:
            return arg_list(infile)
    
    def proc_item(inf, i):
        if i == 0:
            return get_item(infile)
        elif i == 1:
            return get_byte(infile)
        else:
            return arg_list(infile)


    if com_block == 1:
        if command == 0x10:
            textBuf = f"add_chip({arg_list(infile, 5, proc_chip)})"
        elif command == 0x11:
            textBuf = f"sub_chip({arg_list(infile, 5, proc_chip)})"
        elif command == 0x12:
            textBuf = f"set_chip({arg_list(infile, 5, proc_chip)})"
        elif command == 0x13:
            textBuf = f"check_chip({arg_list(infile, 5, proc_chip)})"
        else:
            textBuf = f"check_chip_pack({arg_list(infile, 5, proc_chip)})"
    elif com_block == 2:
        if command == 0x20:
            textBuf = f"add_key({arg_list(infile, 5, proc_item)})"
        elif command == 0x21:
            textBuf = f"sub_key({arg_list(infile, 5, proc_item)})"
        elif command == 0x22:
            textBuf = f"set_key({arg_list(infile, 5, proc_item)})"
        else:
            textBuf = f"check_key({arg_list(infile, 5, proc_item)})"
    elif com_block == 3:
        if command == 0x30:
            textBuf = f"add_zenny({arg_list(infile, 5, proc_item)})"
        elif command == 0x31:
            textBuf = f"sub_zenny({arg_list(infile, 5, proc_item)})"
        elif command == 0x32:
            textBuf = f"set_zenny({arg_list(infile, 5, proc_item)})"
        else:
            textBuf = f"check_zenny({arg_list(infile, 5, proc_item)})"
    else:
        if command == 0:
            textBuf = f"add_item({arg_list(infile, 5, proc_item)})"
        elif command == 1:
            textBuf = f"sub_item({arg_list(infile, 5, proc_item)})"
        elif command == 2:
            textBuf = f"set_item({arg_list(infile, 5, proc_item)})"
        else:
            textBuf = f"check_item({arg_list(infile, 5, proc_item)})"
    return False, textBuf


def Com_F7(infile):
    return False, f"textpal({get_byte(infile)})"


def Com_F8(infile):
    command = get_byte(infile) >> 2
    if command == 0:
        textBuf = "pc_lock()"
    elif command == 1:
        anim = get_byte(infile)
        textBuf = f"pc_anim({anim})"
    elif command == 2:
        textBuf = "pc_unlock()"
    elif command == 3:
        textBuf = "pc_wait()"
    elif command == 4:
        textBuf = "pc_restore()"
    else:
        textBuf = f"F4_{command}()"
    return False, textBuf


def Com_F9(infile):
    command = get_byte(infile) >> 2
    if command == 0:
        itemid = get_byte(infile)
        itempack = get_byte(infile)
        itemtype = itempack & 0xF
        buf = (itempack >> 4) & 0xF
        arg = ""
        if itemtype > 2:
            textBuf = f"FB_0(0x{itemid:02X}, 0x{itempack:02X})"
        else:
            buf_pfx = ""
            if buf == 0:
                if itemtype == 0:
                    arg = key_item(itemid)
                elif itemtype == 1:
                    arg = '"' + chip_id(itemid) + '"'
                else:
                    arg = '"' + chip_code(itemid) + '"'
            else:
                arg = f"{buf}"
                buf_pfx = "_buf"
            if itemtype == 0:
                textBuf = f"key_item{buf_pfx}({arg})"
            elif itemtype == 1:
                textBuf = f"chip_id{buf_pfx}({arg})"
            elif itemtype == 2:
                textBuf = f"prog_adv{buf_pfx}({arg})"
            else:
                textBuf = f"chip_code{buf_pfx}({arg})"
    elif command == 1:
        flags = get_byte(infile)
        minlen = flags & 0xF
        isPadZero = (flags & 0x40) != 0
        isPadLeft = (flags & 0x80) != 0
        item = get_item(infile)
        textBuf = f"item_amt({item}, {minlen}, {isPadZero}, {isPadLeft})"
    elif command == 3:
        flags = get_byte(infile)
        minlen = flags & 0xF
        isPadZero = (flags & 0x40) != 0
        isPadLeft = (flags & 0x80) != 0
        buf = get_byte(infile)
        if buf == 0:
            textBuf = f"zenny_amt({minlen}, {isPadZero}, {isPadLeft})"
        else:
            textBuf = f"buffer({buf}, {minlen}, {isPadZero}, {isPadLeft})"
    else:
        textBuf = f"F9_{command}()"
    return False, textBuf


def Com_FA(infile):
    command = get_byte(infile) >> 2
    if command == 0:
        soundId = get_short(infile)
        textBuf = f"se(0x{soundId:02X})"
    elif command == 1:
        songId = get_short(infile)
        textBuf = f"song(0x{songId:02X})"
    elif command == 2:
        textBuf = "text_se_on()"
    elif command == 3:
        textBuf = "text_se_off()"
    elif command == 4:
        textBuf = "all_sound_off()"
    elif command == 5:
        playerId = get_byte(infile)
        speed = get_byte(infile)
        textBuf = f"song_fade({playerId}, {speed})"
    elif command == 6:
        sound = get_short(infile)
        textBuf = f"text_se(0x{sound:X})"
    elif command == 7:
        textBuf = f"text_se_default()"
    elif command == 8:
        textBuf = f"select_se_on()"
    elif command == 9:
        textBuf = f"select_se_off()"
    else:
        textBuf = f"sound_control({command})"
    return False, textBuf


def Com_FB(infile):
    command = get_byte(infile) >> 2
    isDone = False
    if command == 0:
        count = get_byte(infile)
        jump = get_byte(infile)
        get_short(infile)
        argList = []
        for _ in range(count + 1):
            argList.append(str(get_int(infile)))
        zen = ", ".join(argList)
        textBuf = f"award_zenny([{zen}], 0x{jump:02X})"
    elif command == 1:
        count = get_byte(infile)
        getall = get_byte(infile)
        getnone = get_byte(infile)
        getsome = get_byte(infile)
        chpL = ", ".join(
            [
                f'"{chip_id(get_byte(infile))} {chip_code(get_byte(infile))}"'
                for _ in range(count + 1)
            ]
        )
        if getall == getnone == getsome == 0xFF:
            textBuf = f"award_chip([{chpL}])"
        else:
            textBuf = f"award_chip([{chpL}], 0x{getall:02X}, 0x{getsome:02X}, 0x{getnone:02X})"
    elif command == 2:
        textBuf = "battle()"
        isDone = True
    elif command == 3:
        mode = get_byte(infile)
        folder = get_byte(infile)
        shuffle = get_byte(infile)
        flags = get_byte(infile)
        noescape = get_byte(infile)
        table1 = get_byte(infile)
        table2 = get_byte(infile)
        table3 = get_byte(infile)
        textBuf = f"battle2({mode}, {folder}, {shuffle}, {flags}, {noescape}, {table1}, {table2}, {table3})"
    elif command == 4:
        textBuf = "battle3()"
        isDone = True
    elif command == 5:
        textBuf = f"shop({get_byte(infile)})"
        isDone = True
    elif command == 6:
        count = get_byte(infile)
        ifless = get_byte(infile)
        textBuf = f"trader({count}, 0x{ifless:02X})"
        isDone = True
    elif command == 7:
        index = get_byte(infile)
        textBuf = f"leave_map({index})"
        isDone = True
    elif command == 8:
        textBuf = "style_apply()"
        isDone = True
    elif command == 9:
        count = get_byte(infile)
        jump = get_byte(infile)
        get_short(infile)
        argList = []
        for _ in range(count + 1):
            argList.append(str(get_byte(infile)))
        zen = ", ".join(argList)
        textBuf = f"award_item([{zen}], 0x{jump:02X})"
    elif command == 10:
        textBuf = "bbs()"
        isDone = True
    elif command == 11:
        index = get_byte(infile)
        textBuf = f"misc11({index})"
        isDone = True
    elif command == 12:
        index = get_byte(infile)
        textBuf = f"misc12({index})"
        isDone = True
    elif command == 13:
        index = get_byte(infile)
        textBuf = f"award_folder({index})"
        isDone = True
    else:
        textBuf = f"misc_control({command})"
    return isDone, textBuf


def Com_FC(infile):
    savegood = get_byte(infile)
    savebad = get_byte(infile)
    return False, f"save(0x{savegood:02X}, 0x{savebad:02X})"


# endregion


def interpret(infile):
    funcList = [
        Com_E7,
        Com_E8,
        Com_E9,
        Com_EA,
        Com_EB,
        Com_EC,
        Com_ED,
        Com_EE,
        Com_EF,
        Com_F0,
        Com_F1,
        Com_F2,
        Com_F3,
        Com_F4,
        Com_F5,
        Com_F6,
        Com_F7,
        Com_F8,
        Com_F9,
        Com_FA,
        Com_FB,
        Com_FC
    ]
    textBuf = ""
    isDone = False
    isText = False
    c = get_byte(infile)
    
    if c <= 0xE4:
        textBuf = charmap_en[c] if c in charmap_en else f"[0x{c:02X}]"
        isText = True
    elif c == 0xE5:
        c2 = get_byte(infile)
        textBuf = charmap[c2 + 0xE5]
        isText = True
    elif c == 0xE6:
        c2 = get_byte(infile)
        textBuf = charmap[c2 + 0x1E5]
        isText = True
    elif c < 0xFF:
        isDone, textBuf = funcList[c - 0xE7](infile)
        isText = c in [0xE8]
    else:
        textBuf = f"Com_{chr:02X}()"
    return isDone, textBuf, isText


def interpretUi(infile):
    textBuf = ""
    isDone = False
    isText = False
    c = get_byte(infile)
    if c <= 0xE4:
        textBuf = charmap_en[c] if c in charmap_en else f"^x{c:02X}"
        isText = True
    elif c == 0xE5:
        c2 = get_byte(infile)
        textBuf = charmap[c2 + 0xE5]
        isText = True
    elif c == 0xE6:
        c2 = get_byte(infile)
        textBuf = charmap[c2 + 0x1E5]
        isText = True
    elif c == 0xE7:
        textBuf = "end()"
        isDone = True
    elif c == 0xE8:
        textBuf = "\\n"
        isText = True
    elif c == 0xE9:
        bcdIndex = get_byte(infile)
        commandNum = get_byte(infile)
        pad = "0" if commandNum & 0x40 != 0 else ""
        dir = ">" if commandNum & 0x80 != 0 else ""
        count = commandNum & 0x3F
        suffix = f":{pad}{dir}{count}"
        if suffix == ":1":
            suffix = ""
        textBuf = f"{{{bcdIndex}{suffix}}}"
        isText = True
    elif c == 0xEA:
        arg = get_int(infile)
        textBuf = f"<EA:{arg:08X}>"
        isText = True
    elif c == 0xEB:
        arg = get_byte(infile)
        textBuf = f"<EB:{arg:02X}>"
        isText = True
    elif c == 0xEC:
        skip = [3, 2, 2]
        arg = get_byte(infile)
        fs = []
        for _ in range(skip[arg]):
            fs.append(f"0x{get_byte(infile):02X}")
        joined = ", ".join(fs)
        textBuf = f"<EB({joined})>"
        isText = True
    else:
        textBuf = f"Com_{c:02X}()"
    return isDone, textBuf, isText


def runner(patterns, input):
    temp = input
    changed = False
    for x in patterns:
        while re.search(x[0], temp, re.MULTILINE):
            temp = re.sub(x[0], x[1], temp, 1, re.MULTILINE)
            changed = True
    return changed, temp


def processDelay(input: str):
    patterns = [
        [r'^delay\((.*)\)\ntext\("""', r'text("""{delay \1}'],
        [r'^text\("""(.*)"""\)\ndelay\((.*)\)', r'text("""\1{delay \2}""")'],
        [r"\{delay \}", r"{delay}"],
    ]
    return runner(patterns, input)


def processKey(input: str):
    patterns = [
        [r'^text\("""(.*)"""\)\nkey_item\("(.*)"\)', r'text("""\1{key \2}""")'],
        [r'^key_item\("(.*)"\)\ntext\("""', r'text("""{key \1}'],
    ]
    return runner(patterns, input)


def processText(input: str):
    patterns = [
        [r'^text\("""(.*)"""\)\ntext\("""(.*)"""\)', r'text("""\1\2""")'],
    ]
    return runner(patterns, input)


def processAnim(input: str):
    patterns = [
        [r'^anim\((.*)\)\ntext\("""', r'text("""{anim \1}'],
        [r'^text\("""(.*)"""\)\nanim\((.*)\)', r'text("""\1{anim \2}""")'],
        [r"\{anim \}", r"{anim}"],
    ]
    return runner(patterns, input)


def processAnim2(input: str):
    patterns = [[r'^text\("""\{anim 2\}(.*)\{anim 1\}"""\)', r'text_talking("""\1""")']]
    return runner(patterns, input)


def processParaTalk(input: str):
    patterns = [
        [
            r'^text_talking\("""(.*)"""\)\npage\(\)\nwait\((.*)\)',
            r'para_talk("""\1""", \2)',
        ],
        [r'^para_talk\("""(.*)""", \)', r'para_talk("""\1""", 0)'],
        [r'^para_talk\("""(.*)""", 5\)', r'para_talk("""\1""")'],
    ]
    return runner(patterns, input)


def processGenWait(input: str):
    patterns = [
        [r'^text\("""(.*)"""\)\npage\(\)\nwait\((.*)\)', r'para_general("""\1""", \2)'],
        [r'^para_general\("""(.*)""", \)', r'para_general("""\1""", 0)'],
        [r'^para_general\("""(.*)""", 5\)', r'para_general("""\1""")'],
    ]
    return runner(patterns, input)


def processGenEnd(input: str):
    patterns = [
        [
            r'^text\("""(.*)"""\)\npage\(\)\nend\((.*)\)',
            r'para_general_end("""\1""", \2)',
        ],
        [r'^para_general_end\("""(.*)""", \)', r'para_general_end("""\1""", 0)'],
        [r'^para_general_end\("""(.*)""", 5\)', r'para_general_end("""\1""")'],
    ]
    return runner(patterns, input)


def processEnd(input: str):
    patterns = [
        [
            r'^text_talking\("""(.*)"""\)\npage\(\)\nend\((.*)\)',
            r'para_talk_end("""\1""", \2)',
        ],
        [r'^para_talk_end\("""(.*)""", \)', r'para_talk_end("""\1""", 0)'],
        [r'^para_talk_end\("""(.*)""", 5\)', r'para_talk_end("""\1""")'],
    ]
    return runner(patterns, input)


def process(input: str):
    funcListTextTemplating = [
        # processText, processDelay, processKey, processAnim
        ]
    funcListFunctionReplacing = [
        # processAnim2,
        # processParaTalk,
        # processEnd,
        # processGenWait,
        # processGenEnd,
    ]
    temp = input
    while True:
        changed = False
        for func in funcListTextTemplating:
            tempChange, tempRes = func(temp)
            changed |= tempChange
            if tempChange:
                temp = tempRes
        if not changed:
            break
    while True:
        changed = False
        for func in funcListFunctionReplacing:
            tempChange, tempRes = func(temp)
            changed |= tempChange
            if tempChange:
                temp = tempRes
        if not changed:
            break
    temp = re.sub(r"\\n", r"\n", temp, 0, re.MULTILINE)
    return temp


def engine1(infile, blockOffset, isUi):
    offsetlist = get_text_offset_list(infile, blockOffset)
    output = f"section_count(0x{len(offsetlist):X})\n\n"
    for idx in range(len(offsetlist)):
        off = offsetlist[idx]
        isLimit = False
        nextOff = 0
        if idx < len(offsetlist) - 1:
            isLimit = True
            nextOff = offsetlist[idx + 1]
        infile.seek(off)
        sh = get_short(infile)
        infile.seek(off)
        if (isLimit and infile.tell() < nextOff - 2) or sh != 0:
            scriptBuf = ""
            textBuf = ""

            def emptyBuf():
                nonlocal scriptBuf, textBuf
                if len(textBuf) > 0:
                    scriptBuf += f'text("""{textBuf}""")\n'
                    textBuf = ""

            while True:
                interp = interpretUi(infile) if isUi else interpret(infile)
                if interp[2]:
                    textBuf += interp[1]
                else:
                    emptyBuf()
                    scriptBuf += interp[1] + "\n"
                if interp[0]:
                # if interp[0] or (isLimit and infile.tell() >= nextOff):
                    emptyBuf()
                    break
            output += f"# 0x{idx:02X} @ 0x{off:X}\nsection_start(0x{idx:02X})\n{scriptBuf}section_end()\n\n"
        idx += 1
    return process(output[:-1])


def main():
    parser = argparse.ArgumentParser(
        description="Extract scripts from Mega Man Battle Network."
    )
    parser.add_argument(
        "-ui", "--ui-string", action="count", default=0, help="Use UI parsing rules."
    )
    parser.add_argument("path", type=str, help="The path to the binary.")
    parser.add_argument(
        "blockOffset", type=auto_int, help="The offset into the binary."
    )
    args = parser.parse_args()
    isUi = args.ui_string > 0
    blockOffset = args.blockOffset
    inPath = Path(args.path)
    if not inPath.exists():
        exit(f"Couldn't find file {args.path}")
    outPath = f"{blockOffset:07X}.txt"
    of = ""
    with open(inPath, mode="rb") as infile:
        of = engine1(infile, blockOffset, isUi)
    with open(outPath, mode="w", encoding="utf-8") as outFile:
        outFile.write(of)


if __name__ == "__main__":
    main()
