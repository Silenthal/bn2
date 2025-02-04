#!/usr/bin/python3
import argparse
import io
import shlex
from pathlib import Path
from typing import List, Union
import re

from common import auto_int, is_int


class Section:
    def __init__(self):
        self.buffer: io.BytesIO = io.BytesIO()
        self.len = 0

    def size(self) -> int:
        return 2 if self.len == 0 else self.len

    def emitByte(self, b: int) -> None:
        self.buffer.write(bytes([b & 0xFF]))
        self.len += 1

    def emitShort(self, b: int) -> None:
        self.buffer.write(bytes([b & 0xFF, (b >> 8) & 0xFF]))
        self.len += 2

    def emitInt(self, b: int) -> None:
        self.buffer.write(
            bytes([b & 0xFF, (b >> 8) & 0xFF, (b >> 16) & 0xFF, (b >> 24) & 0xFF])
        )
        self.len += 4

    def getbuffer(self) -> bytes:
        if self.len == 0:
            return bytes([0, 0])
        else:
            return self.buffer.getbuffer()


class Script:
    def __init__(self):
        self.current_section = 0
        self.sections: List[Section] = []

    def setScriptCount(self, size: int):
        if size > 0 and size > len(self.sections):
            for _ in range(size - len(self.sections)):
                self.sections.append(Section())

    def selectSection(self, sectionIndex: int) -> None:
        self.current_section = sectionIndex
        if self.current_section < 0:
            self.current_section = 0
        while len(self.sections) < self.current_section + 1:
            self.sections.append(Section())

    def emitByte(self, b: int) -> None:
        self.sections[self.current_section].emitByte(b)

    def emitShort(self, b: int) -> None:
        self.sections[self.current_section].emitShort(b)

    def emitInt(self, b: int) -> None:
        self.sections[self.current_section].emitInt(b)

    def writeToFile(self, outPath: Path) -> None:
        outBuffer = io.BytesIO()
        offset = len(self.sections) * 2
        ind = 0
        align = offset
        for section in self.sections:
            outBuffer.write(bytes([offset & 0xFF]))
            outBuffer.write(bytes([(offset >> 8) & 0xFF]))
            offset += section.size()
            ind += 1
        for section in self.sections:
            outBuffer.write(section.getbuffer())
            align += section.size()
        align = align % 4
        with open(outPath, "wb") as oFile:
            oFile.write(outBuffer.getbuffer())
            if align != 0:
                while align % 4 != 0:
                    oFile.write(bytes([0]))
                    align += 1


class Reader:
    def __init__(self, string: str):
        self.buffer = string
        self.pos = 0

    def isEmpty(self) -> bool:
        return self.pos >= len(self.buffer)

    def read(self) -> str:
        if self.isEmpty():
            return ""
        else:
            ch = self.buffer[self.pos]
            self.pos = self.pos + 1
            return ch

    def seek(self, count: int) -> None:
        self.pos += count
        if self.pos < 0:
            self.pos = 0
        if self.pos > len(self.buffer):
            self.pos = len(self.buffer)

    def peek(self) -> str:
        if self.isEmpty():
            return ""
        else:
            return self.buffer[self.pos]

    def left(self) -> int:
        if self.isEmpty():
            return 0
        else:
            return len(self.buffer) - self.pos


curScript: Script = Script()

# region
charmap_basic = {
    " ": 0x00,
    "0": 0x01,
    "1": 0x02,
    "2": 0x03,
    "3": 0x04,
    "4": 0x05,
    "5": 0x06,
    "6": 0x07,
    "7": 0x08,
    "8": 0x09,
    "9": 0x0A,
    # "[Lv.]": 0x0B,
    "∥": 0x0C,
    "ウ": 0x0D,
    "エ": 0x0E,
    "オ": 0x0F,
    "カ": 0x10,
    "キ": 0x11,
    "ク": 0x12,
    "ケ": 0x13,
    "コ": 0x14,
    "サ": 0x15,
    "シ": 0x16,
    "ス": 0x17,
    "セ": 0x18,
    "ソ": 0x19,
    "タ": 0x1A,
    "チ": 0x1B,
    "ツ": 0x1C,
    "テ": 0x1D,
    "ト": 0x1E,
    "ナ": 0x1F,
    "ニ": 0x20,
    "ヌ": 0x21,
    "ネ": 0x22,
    "ノ": 0x23,
    "ハ": 0x24,
    "ヒ": 0x25,
    "フ": 0x26,
    "ヘ": 0x27,
    "ホ": 0x28,
    "マ": 0x29,
    "ミ": 0x2A,
    "ム": 0x2B,
    "メ": 0x2C,
    "モ": 0x2D,
    "ヤ": 0x2E,
    "ユ": 0x2F,
    "ヨ": 0x30,
    "ラ": 0x31,
    "リ": 0x32,
    "ル": 0x33,
    "レ": 0x34,
    "ロ": 0x35,
    "ワ": 0x36,
    "ヰ": 0x37,
    "ヱ": 0x38,
    "ヲ": 0x39,
    "ン": 0x3A,
    "ガ": 0x3B,
    "ギ": 0x3C,
    "グ": 0x3D,
    "ゲ": 0x3E,
    "ゴ": 0x3F,
    "ザ": 0x40,
    "ジ": 0x41,
    "ズ": 0x42,
    "ゼ": 0x43,
    "ゾ": 0x44,
    "ダ": 0x45,
    "ヂ": 0x46,
    "ヅ": 0x47,
    "デ": 0x48,
    "ド": 0x49,
    "バ": 0x4A,
    "ビ": 0x4B,
    "ブ": 0x4C,
    "ベ": 0x4D,
    "ボ": 0x4E,
    "パ": 0x4F,
    "ピ": 0x50,
    "プ": 0x51,
    "ペ": 0x52,
    "ポ": 0x53,
    "ァ": 0x54,
    "ィ": 0x55,
    "ゥ": 0x56,
    "ェ": 0x57,
    "ォ": 0x58,
    "ッ": 0x59,
    "ャ": 0x5A,
    "ュ": 0x5B,
    "ョ": 0x5C,
    "ヴ": 0x5D,
    "ー": 0x5E,
    "A": 0x5F,
    "B": 0x60,
    "C": 0x61,
    "D": 0x62,
    "E": 0x63,
    "F": 0x64,
    "G": 0x65,
    "H": 0x66,
    "I": 0x67,
    "J": 0x68,
    "K": 0x69,
    "L": 0x6A,
    "M": 0x6B,
    "N": 0x6C,
    "O": 0x6D,
    "P": 0x6E,
    "Q": 0x6F,
    "R": 0x70,
    "S": 0x71,
    "T": 0x72,
    "U": 0x73,
    "V": 0x74,
    "W": 0x75,
    "X": 0x76,
    "Y": 0x77,
    "Z": 0x78,
    "a": 0x79,
    "b": 0x7A,
    "c": 0x7B,
    "d": 0x7C,
    "e": 0x7D,
    "f": 0x7E,
    "g": 0x7F,
    "h": 0x80,
    "i": 0x81,
    "j": 0x82,
    "k": 0x83,
    "l": 0x84,
    "m": 0x85,
    "n": 0x86,
    "o": 0x87,
    "p": 0x88,
    "q": 0x89,
    "r": 0x8A,
    "s": 0x8B,
    "t": 0x8C,
    "u": 0x8D,
    "v": 0x8E,
    "w": 0x8F,
    "x": 0x90,
    "y": 0x91,
    "z": 0x92,
    "あ": 0x93,
    "い": 0x94,
    "う": 0x95,
    "え": 0x96,
    "お": 0x97,
    "か": 0x98,
    "き": 0x99,
    "く": 0x9A,
    "け": 0x9B,
    "こ": 0x9C,
    "さ": 0x9D,
    "し": 0x9E,
    "す": 0x9F,
    "せ": 0xA0,
    "そ": 0xA1,
    "た": 0xA2,
    "ち": 0xA3,
    "つ": 0xA4,
    "て": 0xA5,
    "と": 0xA6,
    "な": 0xA7,
    "に": 0xA8,
    "ぬ": 0xA9,
    "ね": 0xAA,
    "の": 0xAB,
    "は": 0xAC,
    "ひ": 0xAD,
    "ふ": 0xAE,
    "へ": 0xAF,
    "ほ": 0xB0,
    "ま": 0xB1,
    "み": 0xB2,
    "む": 0xB3,
    "め": 0xB4,
    "も": 0xB5,
    "や": 0xB6,
    "ゆ": 0xB7,
    "よ": 0xB8,
    "ら": 0xB9,
    "り": 0xBA,
    "る": 0xBB,
    "れ": 0xBC,
    "ろ": 0xBD,
    "わ": 0xBE,
    "ゐ": 0xBF,
    "ゑ": 0xC0,
    "を": 0xC1,
    "ん": 0xC2,
    "が": 0xC3,
    "ぎ": 0xC4,
    "ぐ": 0xC5,
    "げ": 0xC6,
    "ご": 0xC7,
    "ざ": 0xC8,
    "じ": 0xC9,
    "ず": 0xCA,
    "ぜ": 0xCB,
    "ぞ": 0xCC,
    "だ": 0xCD,
    "ぢ": 0xCE,
    "づ": 0xCF,
    "で": 0xD0,
    "ど": 0xD1,
    "ば": 0xD2,
    "び": 0xD3,
    "ぶ": 0xD4,
    "べ": 0xD5,
    "ぼ": 0xD6,
    "ぱ": 0xD7,
    "ぴ": 0xD8,
    "ぷ": 0xD9,
    "ぺ": 0xDA,
    "ぽ": 0xDB,
    "ぁ": 0xDC,
    "ぃ": 0xDD,
    "ぅ": 0xDE,
    "ぇ": 0xDF,
    "ぉ": 0xE0,
    "っ": 0xE1,
    "ゃ": 0xE2,
    "ゅ": 0xE3,
    "ょ": 0xE4,
    "\n": 0xE8,
}


charmap_E5 = {
    "!": 0x00,
    "‼️": 0x01,
    "?": 0x02,
    '"': 0x03,
    "„": 0x04,
    "#": 0x05,
    "♭": 0x06,
    "$": 0x07,
    "%": 0x08,
    "&": 0x09,
    "'": 0x0A,
    "(": 0x0B,
    ")": 0x0C,
    "~": 0x0D,
    "ˆ": 0x0E,
    "˜": 0x0F,
    "⌃": 0x10,
    "⌄": 0x11,
    "˂": 0x12,
    "˃": 0x13,
    ",": 0x14,
    "。": 0x15,
    ".": 0x16,
    "・": 0x17,
    "/": 0x18,
    "\\": 0x19,
    "_": 0x1A,
    "「": 0x1B,
    "」": 0x1C,
    "[": 0x1D,
    "]": 0x1E,
    "【": 0x1F,
    "】": 0x20,
    "⊂": 0x21,
    "⊃": 0x22,
    "⋂": 0x23,
    "💧": 0x24,
    "↑": 0x25,
    "→": 0x26,
    "↓": 0x27,
    "←": 0x28,
    "∀": 0x29,
    "α": 0x2A,
    "β": 0x2B,
    "★": 0x2C,
    "♥": 0x2D,
    "♪": 0x2E,
    "℃": 0x2F,
    "♂︎": 0x30,
    "♀︎": 0x31,
    # "_": 0x32,
    "|": 0x33,
    "‾": 0x34,
    ":": 0x35,
    ";": 0x36,
    "…": 0x37,
    "¥": 0x38,
    # "[+]": 0x39,
    "−": 0x3A,
    "×": 0x3B,
    "÷": 0x3C,
    "=": 0x3D,
    "※": 0x3E,
    "*": 0x3F,
    "○": 0x40,
    "⬤": 0x41,
    "◉": 0x42,
    "□": 0x43,
    "■": 0x44,
    "◇": 0x45,
    "◆": 0x46,
    "△": 0x47,
    "▲": 0x48,
    "▽": 0x49,
    "▼": 0x4A,
    "▶": 0x4B,
    "◀": 0x4C,
    "☛": 0x4D,
    "¼": 0xAB,
    # "[inf1]": 0xAC,
    # "[inf2]": 0xAD
}


charmap_bold = {
    " ": 0x00,
    "0": 0x01,
    "1": 0x02,
    "2": 0x03,
    "3": 0x04,
    "4": 0x05,
    "5": 0x06,
    "6": 0x07,
    "7": 0x08,
    "8": 0x09,
    "9": 0x0A,
    "ー": 0x5E,
    "A": 0x5F,
    "B": 0x60,
    "C": 0x61,
    "D": 0x62,
    "E": 0x63,
    "F": 0x64,
    "G": 0x65,
    "H": 0x66,
    "I": 0x67,
    "J": 0x68,
    "K": 0x69,
    "L": 0x6A,
    "M": 0x6B,
    "N": 0x6C,
    "O": 0x6D,
    "P": 0x6E,
    "Q": 0x6F,
    "R": 0x70,
    "S": 0x71,
    "T": 0x72,
    "U": 0x73,
    "V": 0x74,
    "W": 0x75,
    "X": 0x76,
    "Y": 0x77,
    "Z": 0x78,
    "a": 0x79,
    "b": 0x7A,
    "c": 0x7B,
    "d": 0x7C,
    "e": 0x7D,
    "f": 0x7E,
    "g": 0x7F,
    "h": 0x80,
    "i": 0x81,
    "j": 0x82,
    "k": 0x83,
    "l": 0x84,
    "m": 0x85,
    "n": 0x86,
    "o": 0x87,
    "p": 0x88,
    "q": 0x89,
    "r": 0x8A,
    "s": 0x8B,
    "t": 0x8C,
    "u": 0x8D,
    "v": 0x8E,
    "w": 0x8F,
    "x": 0x90,
    "y": 0x91,
    "z": 0x92,
    ".": 0x93,
    "×": 0x94,
    "=": 0x95,
    ":": 0x96,
}


key_item_map = {
    "PET": 0x00,
    "HeroData": 0x01,
    "HopeData": 0x02,
    "Fan": 0x03,
    "ExamCard": 0x04,
    "WalkProg": 0x05,
    "NiceData": 0x06,
    "Paper": 0x07,
    "Lighter": 0x08,
    "Stick": 0x09,
    "Binocs": 0x0A,
    "Knife": 0x0B,
    "Firewood": 0x0C,
    "Fish": 0x0D,
    "Balloon": 0x0E,
    "OddProg": 0x0F,
    "BadDataA": 0x10,
    "BadDataB": 0x11,
    "Battery": 0x12,
    "YumKey": 0x13,
    "NoteData": 0x14,
    "Chng_bat": 0x15,
    "Ticket": 0x16,
    "Passport": 0x17,
    "Wireless": 0x18,
    "MiniPET": 0x19,
    "CyberKey": 0x1A,
    "Broach": 0x1B,
    "RoboX": 0x1C,
    "GoldRing": 0x1D,
    "PilotCap": 0x1E,
    "Chopstck": 0x1F,
    "Whiskey": 0x20,
    "Thread": 0x21,
    "RedFrag": 0x22,
    "RedCure": 0x23,
    "HeatData": 0x24,
    "YeloCure": 0x25,
    "BluFragA": 0x26,
    "BluFragB": 0x27,
    "GospelID": 0x28,
    "KotoPass": 0x29,
    "MagSuit": 0x2A,
    "ElBit042": 0x2B,
    "ElBit082": 0x2C,
    "ElBit093": 0x2D,
    "ElBit201": 0x2E,
    "ElBit232": 0x2F,
    "ElBit243": 0x30,
    "ElBit253": 0x31,
    "ElBit271": 0x32,
    "ElBitEV": 0x33,
    "LoveLetr": 0x34,
    "Beetle": 0x35,
    "YumTear": 0x36,
    "KngStone": 0x37,
    "Twilight": 0x38,
    "ArmyData": 0x39,
    "ZLicense": 0x3A,
    "BLicense": 0x3B,
    "ALicense": 0x3C,
    "SLicense": 0x3D,
    "SS_Lic": 0x3E,
    "SSS_Lic": 0x3F,
    "FreePass": 0x40,
    "GateKeyA": 0x41,
    "GateKeyB": 0x42,
    "GateKeyC": 0x43,
    "GateKeyD": 0x44,
    "BugFrag": 0x45,
    "MaylCode": 0x50,
    "DexCode": 0x51,
    "YaiCode": 0x52,
    "RibiCode": 0x53,
    "RaulCode": 0x54,
    "MiliCode": 0x55,
    "ONBACode": 0x56,
    "GospCode": 0x57,
    "ACDCPass": 0x58,
    "MariPass": 0x59,
    "OkuPass": 0x5A,
    "AirPass": 0x5B,
    "HPMemory": 0x60,
    "PowerUP": 0x61,
    "RegUP1": 0x62,
    "RegUP2": 0x63,
    "RegUP3": 0x64,
    "SubMem": 0x65,
    "MiniEnrg": 0x70,
    "FullEnrg": 0x71,
    "SneakRun": 0x72,
    "Untrap": 0x73,
    "LocEnemy": 0x74,
    "Unlocker": 0x75,
    "ITEM7F": 0x7F,
    "NormStyl": 0x80,
    "ElecGuts": 0x86,
    "HeatGuts": 0x87,
    "AquaGuts": 0x88,
    "WoodGuts": 0x89,
    "ElecCust": 0x8B,
    "HeatCust": 0x8C,
    "AquaCust": 0x8D,
    "WoodCust": 0x8E,
    "ElecTeam": 0x90,
    "HeatTeam": 0x91,
    "AquaTeam": 0x92,
    "WoodTeam": 0x93,
    "ElecShld": 0x95,
    "HeatShld": 0x96,
    "AquaShld": 0x97,
    "WoodShld": 0x98,
    "HubStyl": 0x99
}


chip_id_map = {
    "Buster": 0,
    "Cannon": 1,
    "HiCannon": 2,
    "M_Cannon": 3,
    "Shotgun": 4,
    "V_Gun": 5,
    "CrossGun": 6,
    "Spreader": 7,
    "Bubbler": 8,
    "Bub_V": 9,
    "BubCross": 10,
    "BubSprd": 11,
    "HeatShot": 12,
    "Heat_V": 13,
    "HeatCros": 14,
    "HeatSprd": 15,
    "MiniBomb": 16,
    "LilBomb": 17,
    "CrosBomb": 18,
    "BigBomb": 19,
    "TreeBom1": 20,
    "TreeBom2": 21,
    "TreeBom3": 22,
    "Sword": 23,
    "WideSwrd": 24,
    "LongSwrd": 25,
    "FireSwrd": 26,
    "AquaSwrd": 27,
    "ElecSwrd": 28,
    "FireBlde": 29,
    "AquaBlde": 30,
    "ElecBlde": 31,
    "StepSwrd": 32,
    "Muramasa": 33,
    "CustSwrd": 34,
    "Kunai1": 35,
    "Kunai2": 36,
    "Kunai3": 37,
    "Slasher": 38,
    "Shockwav": 39,
    "Sonicwav": 40,
    "Dynawave": 41,
    "Quake1": 42,
    "Quake2": 43,
    "Quake3": 44,
    "GutPunch": 45,
    "ColdPnch": 46,
    "Atk20": 47,
    "Atk30": 48,
    "Navi40": 49,
    "DashAtk": 50,
    "Wrecker": 51,
    "CannBall": 52,
    "DoubNdl": 53,
    "TripNdl": 54,
    "QuadNdl": 55,
    "Trident": 56,
    "Ratton1": 57,
    "Ratton2": 58,
    "Ratton3": 59,
    "FireRat": 60,
    "Tornado": 61,
    "Twister": 62,
    "Blower": 63,
    "Burner": 64,
    "ZapRing1": 65,
    "ZapRing2": 66,
    "ZapRing3": 67,
    "Spice1": 68,
    "Spice2": 69,
    "Spice3": 70,
    "Satelit1": 71,
    "Satelit2": 72,
    "Satelit3": 73,
    "Yo_Yo1": 74,
    "Yo_Yo2": 75,
    "Yo_Yo3": 76,
    "MagBomb1": 77,
    "MagBomb2": 78,
    "MagBomb3": 79,
    "Meteor9": 80,
    "Meteor12": 81,
    "Meteor15": 82,
    "Meteor18": 83,
    "Hammer": 84,
    "CrsShld1": 85,
    "CrsShld2": 86,
    "CrsShld3": 87,
    "TimeBom1": 88,
    "TimeBom2": 89,
    "TimeBom3": 90,
    "LilCloud": 91,
    "MedCloud": 92,
    "BigCloud": 93,
    "Mine": 94,
    "FrntSnsr": 95,
    "DblSnsr": 96,
    "Remobit1": 97,
    "Remobit2": 98,
    "Remobit3": 99,
    "AquaBall": 100,
    "ElecBall": 101,
    "HeatBall": 102,
    "Geyser": 103,
    "LavaDrag": 104,
    "GodStone": 105,
    "OldWood": 106,
    "PoisMask": 107,
    "PoisFace": 108,
    "Whirlpl": 109,
    "Blckhole": 110,
    "Guard": 111,
    "Barrier": 112,
    "PanlOut1": 113,
    "PanlOut3": 114,
    "LineOut": 115,
    "Lance": 116,
    "ZeusHamr": 117,
    "BrnzFist": 118,
    "SilvFist": 119,
    "GoldFist": 120,
    "VarSwrd": 121,
    "Recov10": 122,
    "Recov30": 123,
    "Recov50": 124,
    "Recov80": 125,
    "Recov120": 126,
    "Recov150": 127,
    "Recov200": 128,
    "Recov300": 129,
    "PanlGrab": 130,
    "AreaGrab": 131,
    "GrabRvng": 132,
    "Geddon1": 133,
    "Geddon2": 134,
    "Geddon3": 135,
    "Catcher": 136,
    "Mindbndr": 137,
    "Escape": 138,
    "AirShoes": 139,
    "Repair": 140,
    "Candle1": 141,
    "Candle2": 142,
    "Candle3": 143,
    "RockCube": 144,
    "Prism": 145,
    "Guardian": 146,
    "Wind": 147,
    "Fan": 148,
    "Anubis": 149,
    "SloGauge": 150,
    "FstGauge": 151,
    "FullCust": 152,
    "Invis1": 153,
    "Invis2": 154,
    "Invis3": 155,
    "DropDown": 156,
    "PopUp": 157,
    "StoneBod": 158,
    "Shadow1": 159,
    "Shadow2": 160,
    "Shadow3": 161,
    "UnderSht": 162,
    "BblWrap": 163,
    "LeafShld": 164,
    "AquaAura": 165,
    "FireAura": 166,
    "WoodAura": 167,
    "ElecAura": 168,
    "LifeAur1": 169,
    "LifeAur2": 170,
    "LifeAur3": 171,
    "MagLine": 172,
    "LavaLine": 173,
    "IceLine": 174,
    "GrassLne": 175,
    "LavaStge": 176,
    "IceStage": 177,
    "GrassStg": 178,
    "HolyPanl": 179,
    "Jealosy": 180,
    "AntiFire": 181,
    "AntiElec": 182,
    "AntiWatr": 183,
    "AntiDmg": 184,
    "AntiSwrd": 185,
    "AntiNavi": 186,
    "AntiRecv": 187,
    "Atk10": 188,
    "Fire40": 189,
    "Aqua40": 190,
    "Wood40": 191,
    "Elec40": 192,
    "Navi20": 193,
    "RollV1": 194,
    "RollV2": 195,
    "RollV3": 196,
    "GutsManV1": 197,
    "GutsManV2": 198,
    "GutsManV3": 199,
    "ProtomanV1": 200,
    "ProtomanV2": 201,
    "ProtomanV3": 202,
    "AirManV1": 203,
    "AirManV2": 204,
    "AirManV3": 205,
    "QuickManV1": 206,
    "QuickManV2": 207,
    "QuickManV3": 208,
    "CutManV1": 209,
    "CutManV2": 210,
    "CutManV3": 211,
    "ShadowManV1": 212,
    "ShadowManV2": 213,
    "ShadowManV3": 214,
    "KnightManV1": 215,
    "KnightManV2": 216,
    "KnightManV3": 217,
    "MagnetManV1": 218,
    "MagnetManV2": 219,
    "MagnetManV3": 220,
    "FreezeManV1": 221,
    "FreezeManV2": 222,
    "FreezeManV3": 223,
    "HeatManV1": 224,
    "HeatManV2": 225,
    "HeatManV3": 226,
    "ToadManV1": 227,
    "ToadManV2": 228,
    "ToadManV3": 229,
    "ThunderManV1": 230,
    "ThunderManV2": 231,
    "ThunderManV3": 232,
    "SnakeManV1": 233,
    "SnakeManV2": 234,
    "SnakeManV3": 235,
    "GateManV1": 236,
    "GateManV2": 237,
    "GateManV3": 238,
    "PlanetManV1": 239,
    "PlanetManV2": 240,
    "PlanetManV3": 241,
    "NapalmManV1": 242,
    "NapalmManV2": 243,
    "NapalmManV3": 244,
    "PharaohManV1": 245,
    "PharaohManV2": 246,
    "PharaohManV3": 247,
    "BassV1": 248,
    "BassV2": 249,
    "BassV3": 250,
    "BgRedWav": 251,
    "FreezBom": 252,
    "Sparker": 253,
    "GaiaSwrd": 254,
    "BlkBomb": 255,
    "FtrSword": 256,
    "KngtSwrd": 257,
    "HeroSwrd": 258,
    "Meteors": 259,
    "Poltrgst": 260,
    "FireGspl": 261,
    "AquaGspl": 262,
    "ElecGspl": 263,
    "WoodGspl": 264,
    "GateSP": 265,
    "Snctuary": 270,
    "Z_Canon1": 272,
    "Z_Canon2": 273,
    "Z_Canon3": 274,
    "H_Burst": 275,
    "Z_Ball": 276,
    "Z_Raton1": 277,
    "Z_Raton2": 278,
    "Z_Raton3": 279,
    "O_Canon1": 280,
    "O_Canon2": 281,
    "O_Canon3": 282,
    "M_Burst": 283,
    "O_Ball": 284,
    "O_Ratton1": 285,
    "O_Ratton2": 286,
    "O_Ratton3": 287,
    "Arrows": 288,
    "UltraBmd": 289,
    "LifeSrd1": 290,
    "LifeSrd2": 291,
    "LifeSrd3": 292,
    "Punch": 293,
    "Curse": 294,
    "TimeBom": 295,
    "HvyStamp": 296,
    "PoisPhar": 297,
    "Gater": 298,
    "GtsShoot": 299,
    "BigHeart": 300,
    "BodyGrd": 301,
    "2xHero": 302,
    "Darkness": 303,
}


prog_adv_map = {
    "FtrSword": 0x00,
    "KngtSwrd": 0x01,
    "HeroSwrd": 0x02,
    "Meteors": 0x03,
    "Poltrgst": 0x04,
    "FireGspl": 0x05,
    "AquaGspl": 0x06,
    "ElecGspl": 0x07,
    "WoodGspl": 0x08,
    "GateSP": 0x09,
    "Snctuary": 0x0E,
    "Z_Canon1": 0x10,
    "Z_Canon2": 0x11,
    "Z_Canon3": 0x12,
    "H_Burst": 0x13,
    "Z_Ball": 0x14,
    "Z_Raton1": 0x15,
    "Z_Raton2": 0x16,
    "Z_Raton3": 0x17,
    "O_Canon1": 0x18,
    "O_Canon2": 0x19,
    "O_Canon3": 0x1A,
    "M_Burst": 0x1B,
    "O_Ball": 0x1C,
    "O_Raton1": 0x1D,
    "O_Raton2": 0x1E,
    "O_Raton3": 0x1F,
    "Arrows": 0x20,
    "UltraBmb": 0x21,
    "LifeSrd1": 0x22,
    "LifeSrd2": 0x23,
    "LifeSrd3": 0x24,
    "Punch": 0x25,
    "Curse": 0x26,
    "TimeBom_": 0x27,
    "HvyStamp": 0x28,
    "PoisPhar": 0x29,
    "Gater": 0x2A,
    "GtsShoot": 0x2B,
    "BigHeart": 0x2C,
    "BodyGrd": 0x2D,
    "2xHero": 0x2E,
    "Darkness": 0x2F,
    "Punisher": 0x33,
    "PharTrap": 0x34,
    "2xPlanet": 0x35,
    "RemoGate": 0x39
}

def bytes_chip(chip: str):
    global curScript
    chips = chip.split()
    if len(chips) != 2 or chips[0] not in chip_id_map or not chips[1].isalpha():
        exit(f'Unrecognized chip "{chip}"')
    return [chip_id_map[chips[0]], charmap_basic[chips[1].upper()] - charmap_basic["A"]]


def bytes_chip_id(chipid: str):
    global curScript
    if chipid not in chip_id_map:
        exit(f'Unrecognized chip ID "{chipid}"')
    return [chip_id_map[chipid]]


def bytes_prog_adv(pa: str):
    global curScript
    if pa not in prog_adv_map:
        exit(f'Unrecognized program advance "{pa}"')
    return [prog_adv_map[pa]]


def bytes_chip_code(chipcode: str):
    global curScript
    if not chipcode.isalpha():
        exit(f'Unrecognized chip code "{chipcode}"')
    return [charmap_basic[chipcode.upper()] - charmap_basic["A"]]


def bytes_key(itemid: Union[str, int]):
    global curScript
    if isinstance(itemid, int):
        return [itemid]
    elif isinstance(itemid, str):
        if itemid not in key_item_map:
            exit(f"Unrecognized item name {itemid}")
        return [key_item_map[itemid]]
    else:
        exit(f"Unrecognized item name {itemid}")


# endregion


# region Script control
def section_count(count: int) -> None:
    global curScript
    curScript.setScriptCount(count)


def section_start(section: int) -> None:
    global curScript
    curScript.selectSection(section)


def section_end():
    pass
    # global curScript
    # curScript.emitByte(0)
    # curScript.emitByte(0)


# endregion


# region Commands
def emit(bt: int):
    global curScript
    curScript.emitByte(bt)


def end(delay: int = 0):
    global curScript
    curScript.emitByte(0xE7)
    curScript.emitShort(delay)


def newline():
    global curScript
    curScript.emitByte(0xE8)


def wait(amt: int = 0):
    global curScript
    curScript.emitByte(0xE9)
    curScript.emitShort(amt)


def delay_control(com: int):
    global curScript
    curScript.emitByte(0xEA)
    curScript.emitByte(com)


def breaks(amt: int):
    delay_control(0)
    curScript.emitShort(amt)


def delay(amt: int = 30):
    delay_control(1)
    curScript.emitShort(amt)


def stop():
    delay_control(0xFF)
    curScript.emitShort(0)


def page():
    global curScript
    curScript.emitByte(0xEB)


def skip_control(amt: int):
    global curScript
    curScript.emitByte(0xEC)
    curScript.emitByte(amt)


def set_delay(amt: int):
    global curScript
    skip_control(0)
    curScript.emitByte(amt)


def skip_on():
    skip_control(1)


def skip_off():
    skip_control(2)


def picture_control(com: int):
    global curScript
    curScript.emitByte(0xED)
    curScript.emitByte(com)


def pic(picture: int = 0, palette: int = 0):
    global curScript
    picture_control(0)
    curScript.emitByte(picture)
    curScript.emitByte(palette)


def hidepic():
    picture_control(1)


def picpal(palette: int):
    picture_control(2)
    curScript.emitByte(palette)


def pic3(arg: int):
    picture_control(3)
    curScript.emitByte(arg)


def pad_control(com: int):
    global curScript
    curScript.emitByte(0xEE)
    curScript.emitByte(com)


def pad(count: int = 2):
    global curScript
    pad_control(0)
    curScript.emitByte(count)


def col(count: int):
    global curScript
    pad_control(1)
    curScript.emitByte(count)


def margin(left: int, top: int):
    global curScript
    pad_control(2)
    curScript.emitByte(left)
    curScript.emitByte(top)


def option(up: int, down: int, left: int, right: int):
    global curScript
    curScript.emitByte(0xEF)
    high = ((up & 0xF) << 4) | (down & 0xF)
    low = ((left & 0xF) << 4) | (right & 0xF)
    curScript.emitByte(low)
    curScript.emitByte(high)


def pick(optionList: List[int], default, isDisableB=False, isClearAfterPick=True):
    global curScript
    curScript.emitByte(0xF0)
    curScript.emitByte(len(optionList) + 3)
    flag_7 = (1 if isClearAfterPick else 0) << 7
    flag_6 = (1 if isDisableB else 0) << 6
    flag_other = default & 0x3F
    curScript.emitByte(flag_7 | flag_6 | flag_other)
    for opt in optionList:
        curScript.emitByte(opt)


def dialog_control(com: int):
    global curScript
    curScript.emitByte(0xF1)
    curScript.emitByte(com)


def dialog_up():
    dialog_control(0)


def dialog_down():
    dialog_control(1)


def dialog_show():
    dialog_control(2)


def dialog_hide():
    dialog_control(3)


def dialog_set(val: int):
    global curScript
    dialog_control(0x10)
    curScript.emitByte(val)


def flag_control(com: int, flag: int):
    global curScript
    curScript.emitByte(0xF2)
    curScript.emitByte(com << 2)
    curScript.emitShort(flag)


def set_flag(flag: int):
    flag_control(0, flag)


def clear_flag(flag: int):
    flag_control(1, flag)


def mail(flag: int):
    flag_control(2, flag)


def cond_control(com: int):
    global curScript
    curScript.emitByte(0xF4)
    curScript.emitByte(com << 2)


def if_flag(flag: int, eq: int = 0xFF, neq: int = 0xFF):
    global curScript
    cond_control(0)
    curScript.emitShort(flag)
    curScript.emitByte(eq)
    curScript.emitByte(neq)


def if_story(flag: int, inrange: int = 0xFF, outrange: int = 0xFF):
    if_story_in(flag, flag, inrange, outrange)


def if_story_in(lower: int, upper: int, inrange: int = 0xFF, outrange: int = 0xFF):
    global curScript
    cond_control(1)
    curScript.emitByte(lower)
    curScript.emitByte(upper)
    curScript.emitByte(inrange)
    curScript.emitByte(outrange)


def if_shop(shop: int, instock: int = 0xFF, outstock: int = 0xFF):
    global curScript
    cond_control(2)
    curScript.emitByte(shop)
    curScript.emitByte(instock)
    curScript.emitByte(outstock)


def if_chip(chip: str, eq: int = 0xFF, neq: int = 0xFF):
    global curScript
    cond_control(3)
    bchip = bytes_chip(chip)
    curScript.emitByte(bchip[0])
    curScript.emitByte(bchip[1])
    curScript.emitByte(eq)
    curScript.emitByte(neq)


def if_level(lower: int, upper: int, inrange: int = 0xFF, outrange: int = 0xFF):
    global curScript
    cond_control(4)
    curScript.emitByte(lower)
    curScript.emitByte(upper)
    curScript.emitByte(inrange)
    curScript.emitByte(outrange)


def if_bust(lower: int, upper: int, inrange: int = 0xFF, outrange: int = 0xFF):
    global curScript
    cond_control(5)
    curScript.emitByte(lower)
    curScript.emitByte(upper)
    curScript.emitByte(inrange)
    curScript.emitByte(outrange)


def if_library(lower: int, upper: int, inrange: int = 0xFF, outrange: int = 0xFF):
    global curScript
    cond_control(6)
    curScript.emitByte(lower)
    curScript.emitByte(upper)
    curScript.emitByte(inrange)
    curScript.emitByte(outrange)


def if_sub_area_in(lower: int, upper: int, inrange: int = 0xFF, outrange: int = 0xFF):
    global curScript
    cond_control(7)
    curScript.emitByte(lower)
    curScript.emitByte(upper)
    curScript.emitByte(inrange)
    curScript.emitByte(outrange)

def if_event_in(lower: int, upper: int, inrange: int = 0xFF, outrange: int = 0xFF):
    global curScript
    cond_control(8)
    curScript.emitByte(lower)
    curScript.emitByte(upper)
    curScript.emitByte(inrange)
    curScript.emitByte(outrange)


def if_area_in(lower: int, upper: int, inrange: int = 0xFF, outrange: int = 0xFF):
    global curScript
    cond_control(8)
    curScript.emitByte(lower)
    curScript.emitByte(upper)
    curScript.emitByte(inrange)
    curScript.emitByte(outrange)


def input_control(com: int):
    global curScript
    curScript.emitByte(0xF4)
    curScript.emitByte(com)


def input_off():
    input_control(0)


def input_on():
    input_control(1)


def jump_control(sz: int):
    global curScript
    curScript.emitByte(0xF5)
    curScript.emitByte(sz)


def jump(index: int):
    global curScript
    jump_control(0)
    curScript.emitByte(index)


def jumprandom(indexList: List[int]):
    global curScript
    jump_control(len(indexList) - 1)
    for bt in indexList:
        curScript.emitByte(bt)


def inv_control(com: int):
    global curScript
    curScript.emitByte(0xF6)
    curScript.emitByte(com)


def item_control(com: int):
    inv_control(com & 0xF)


def chip_control(com: int):
    inv_control(0x10 + (com & 0xF))


def key_item_control(com: int):
    inv_control(0x20 + (com & 0xF))


def zenny_control(com: int):
    inv_control(0x30 + (com & 0xF))


def arg_inv_control(item: int, amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    curScript.emitByte(item)
    curScript.emitByte(amt)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)


def add_item(itemid: Union[str, int], amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    item_control(0)
    arg_inv_control(bytes_key(itemid), amt, ifall, ifnone, ifsome)


def sub_item(itemid: Union[str, int], amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    item_control(1)
    arg_inv_control(bytes_key(itemid), amt, ifall, ifnone, ifsome)


def set_item(itemid: Union[str, int], amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    item_control(2)
    arg_inv_control(bytes_key(itemid), amt, ifall, ifnone, ifsome)


def check_item(itemid: Union[str, int], amt: int = 1, eq: int = 0xFF, gt: int = 0xFF, lt: int = 0xFF):
    item_control(4)
    arg_inv_control(bytes_key(itemid), amt, eq, gt, lt)


def if_have_item(itemid: Union[str, int], jump: int):
    check_item(itemid, 1, jump, jump)


def if_no_item(itemid: Union[str, int], jump: int):
    check_item(itemid, 1, lt=jump)


def add_chip(chip: str, amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    global curScript
    chip_control(0)
    bchip = bytes_chip(chip)
    curScript.emitByte(bchip[0])
    curScript.emitByte(bchip[1])
    curScript.emitByte(amt)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)


def sub_chip(chip: str, amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    global curScript
    chip_control(1)
    bchip = bytes_chip(chip)
    curScript.emitByte(bchip[0])
    curScript.emitByte(bchip[1])
    curScript.emitByte(amt)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)


def set_chip(chip: str, amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    global curScript
    chip_control(2)
    bchip = bytes_chip(chip)
    curScript.emitByte(bchip[0])
    curScript.emitByte(bchip[1])
    curScript.emitByte(amt)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)


def check_chip(chip: str, amt: int, ifeq: int = 0xFF, ifgt: int = 0xFF, iflt: int = 0xFF):
    global curScript
    chip_control(4)
    bchip = bytes_chip(chip)
    curScript.emitByte(bchip[0])
    curScript.emitByte(bchip[1])
    curScript.emitByte(amt)
    curScript.emitByte(ifeq)
    curScript.emitByte(ifgt)
    curScript.emitByte(iflt)


def if_have_chip(chip: str, jump: int):
    check_chip(chip, 1, jump, jump, 0xFF)


def check_chip_pack(chip: str, amt: int = 1, eq: int = 0xFF, gt: int = 0xFF, lt: int = 0xFF):
    global curScript
    chip_control(5)
    bchip = bytes_chip(chip)
    curScript.emitByte(bchip[0])
    curScript.emitByte(bchip[1])
    curScript.emitByte(amt)
    curScript.emitByte(eq)
    curScript.emitByte(gt)
    curScript.emitByte(lt)


def add_key(itemid: Union[str, int], amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    key_item_control(0)
    arg_inv_control(bytes_key(itemid), amt, ifall, ifnone, ifsome)


def sub_key(itemid: Union[str, int], amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    key_item_control(1)
    arg_inv_control(bytes_key(itemid), amt, ifall, ifnone, ifsome)


def set_key(itemid: Union[str, int], amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    key_item_control(2)
    arg_inv_control(bytes_key(itemid), amt, ifall, ifnone, ifsome)


def check_key(itemid: Union[str, int], amt: int = 1, eq: int = 0xFF, gt: int = 0xFF, lt: int = 0xFF):
    key_item_control(4)
    arg_inv_control(bytes_key(itemid), amt, eq, gt, lt)


def add_zenny(amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    zenny_control(0)
    curScript.emitByte(amt)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)


def sub_zenny(amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    zenny_control(1)
    curScript.emitByte(amt)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)


def set_zenny(amt: int = 1, ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF):
    zenny_control(2)
    curScript.emitByte(amt)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)


def check_zenny(amt: int = 1, eq: int = 0xFF, gt: int = 0xFF, lt: int = 0xFF):
    zenny_control(4)
    curScript.emitByte(amt)
    curScript.emitByte(eq)
    curScript.emitByte(gt)
    curScript.emitByte(lt)


def passcode_control(com: int):
    global curScript
    curScript.emitByte(0xF8)
    curScript.emitByte(com << 2)


def passcode(pickrand: int, solution: int):
    global curScript
    passcode_control(0)
    curScript.emitByte(pickrand)
    curScript.emitByte(solution)


def passcode_pick(ifconfirm: int, ifabort: int, unused1: int = 0, unused2: int = 0):
    global curScript
    passcode_control(1)
    curScript.emitByte(ifconfirm)
    curScript.emitByte(ifabort)
    curScript.emitByte(unused1)
    curScript.emitByte(unused2)


def passcode_check(
    bothlow: int,
    bothhigh: int,
    secondlow: int,
    firstlow: int,
    secondhigh: int,
    firsthigh: int,
    ifcorrect: int,
):
    global curScript
    passcode_control(2)
    curScript.emitByte(bothlow)
    curScript.emitByte(bothhigh)
    curScript.emitByte(secondlow)
    curScript.emitByte(firstlow)
    curScript.emitByte(secondhigh)
    curScript.emitByte(firsthigh)
    curScript.emitByte(ifcorrect)


def passcode_hide():
    global curScript
    passcode_control(3)


def passcode_shift(firstup: int, firstdown: int, secondup: int, seconddown: int):
    global curScript
    passcode_control(4)
    curScript.emitByte(firstup)
    curScript.emitByte(firstdown)
    curScript.emitByte(secondup)
    curScript.emitByte(seconddown)


def textpal(pal: int):
    global curScript
    curScript.emitByte(0xF7)
    curScript.emitByte(pal)


def pc_control(com: int):
    global curScript
    curScript.emitByte(0xF8)
    curScript.emitByte(com << 2)


def pc_lock():
    pc_control(0)


def pc_anim(anim: int):
    global curScript
    pc_control(1)
    curScript.emitByte(anim)


def pc_anim_start(anim: int):
    pc_lock()
    pc_anim(anim)


def pc_anim_end():
    pc_wait()
    pc_unlock()


def pc_unlock():
    pc_control(2)


def pc_wait():
    pc_control(3)


def pc_restore():
    pc_control(4)


def item_control(com: int):
    global curScript
    curScript.emitByte(0xF9)
    curScript.emitByte(com << 2)


def key_item_buf(index: int):
    global curScript
    item_control(0)
    curScript.emitByte(0)
    pack = (index << 4) & 0xF0
    curScript.emitByte(pack)


def chip_id_buf(index: int):
    global curScript
    item_control(0)
    curScript.emitByte(0)
    pack = (index << 4) & 0xF0
    curScript.emitByte(pack + 1)


def prog_adv_buf(index: int):
    global curScript
    item_control(0)
    curScript.emitByte(0)
    pack = (index << 4) & 0xF0
    curScript.emitByte(pack + 2)


def chip_code_buf(index: int):
    global curScript
    item_control(0)
    curScript.emitByte(0)
    pack = (index << 4) & 0xF0
    curScript.emitByte(pack + 3)


def key_item(itemid: Union[str, int]):
    global curScript
    item_control(0)
    bkey = bytes_key(itemid)
    curScript.emitByte(bkey[0])
    curScript.emitByte(0)


def chip_id(chipid: str):
    global curScript
    item_control(0)
    bcid = bytes_chip_id(chipid)
    curScript.emitByte(bcid[0])
    curScript.emitByte(1)


def prog_adv(chipid: str):
    global curScript
    item_control(0)
    bcid = bytes_prog_adv(chipid)
    curScript.emitByte(bcid[0])
    curScript.emitByte(2)


def chip_code(chipcode: str):
    global curScript
    item_control(0)
    bcode = bytes_chip_code(chipcode)
    curScript.emitByte(bcode[0])
    curScript.emitByte(3)


def chip(chipId: str, chipCode: str):
    chip_id(chipId)
    text(" ")
    chip_code(chipCode)


def item_amt(
    itemid: Union[str, int],
    minlen: int = 0,
    isPadZero: bool = False,
    isPadLeft: bool = False,
):
    global curScript
    item_control(1)
    flag_7 = (1 if isPadLeft else 0) << 7
    flag_6 = (1 if isPadZero else 0) << 6
    flag_other = minlen & 0xF
    curScript.emitByte(flag_7 | flag_6 | flag_other)
    bkey = bytes_key(itemid)
    curScript.emitByte(bkey[0])


def chip_amt(
    chip: str, minlen: int = 0, isPadZero: bool = False, isPadLeft: bool = False
):
    global curScript
    item_control(2)
    flag_7 = (1 if isPadLeft else 0) << 7
    flag_6 = (1 if isPadZero else 0) << 6
    flag_other = minlen & 0xF
    curScript.emitByte(flag_7 | flag_6 | flag_other)
    bchip = bytes_chip(chip)
    curScript.emitByte(bchip[0])
    curScript.emitByte(bchip[1])


def zenny_amt(minlen: int = 0, isPadZero: bool = False, isPadLeft: bool = False):
    global curScript
    item_control(3)
    flag_7 = (1 if isPadLeft else 0) << 7
    flag_6 = (1 if isPadZero else 0) << 6
    flag_other = minlen & 0xF
    curScript.emitByte(flag_7 | flag_6 | flag_other)
    curScript.emitByte(0)


def buffer(
    buffer: int, minlen: int = 0, isPadZero: bool = False, isPadLeft: bool = False
):
    global curScript
    item_control(3)
    flag_7 = (1 if isPadLeft else 0) << 7
    flag_6 = (1 if isPadZero else 0) << 6
    flag_other = minlen & 0xF
    curScript.emitByte(flag_7 | flag_6 | flag_other)
    curScript.emitByte(buffer)


def sound_control(com: int):
    global curScript
    curScript.emitByte(0xFA)
    curScript.emitByte(com << 2)


def se(songid: int):
    global curScript
    sound_control(0)
    curScript.emitShort(songid)


def song(songid: int):
    global curScript
    sound_control(1)
    curScript.emitShort(songid)


def text_se_on():
    sound_control(2)


def text_se_off():
    sound_control(3)


def all_sound_off():
    sound_control(4)


def song_fade(playerId: int, speed: int):
    global curScript
    sound_control(5)
    curScript.emitByte(playerId)
    curScript.emitByte(speed)


def text_se(songId: int):
    global curScript
    sound_control(6)
    curScript.emitShort(songId)


def text_se_default():
    sound_control(7)


def select_se_on():
    sound_control(8)

def select_se_off():
    sound_control(9)


def misc_control(com: int):
    global curScript
    curScript.emitByte(0xFB)
    curScript.emitByte(com << 2)


def award_zenny(
    amtList: List[int], nextjump: int = 0xFF, unused1: int = 0xFF, unused2: int = 0xFF
):
    global curScript
    misc_control(0)
    curScript.emitByte(len(amtList) - 1)
    curScript.emitByte(nextjump)
    curScript.emitByte(unused1)
    curScript.emitByte(unused2)
    for amt in amtList:
        curScript.emitInt(amt)


def award_chip(
    chipList: List[str], ifall: int = 0xFF, ifnone: int = 0xFF, ifsome: int = 0xFF
):
    global curScript
    misc_control(1)
    curScript.emitByte(len(chipList) - 1)
    curScript.emitByte(ifall)
    curScript.emitByte(ifnone)
    curScript.emitByte(ifsome)
    for chip in chipList:
        bchip = bytes_chip(chip)
        curScript.emitByte(bchip[0])
        curScript.emitByte(bchip[1])


def battle():
    misc_control(2)


def battle2(
    mode: int,
    folder: int,
    shuffle: int,
    flags: int,
    noescape: int,
    battleId: int,
    table1: int,
    table2: int,
    table3: int
):
    global curScript
    misc_control(3)
    curScript.emitByte(mode)
    curScript.emitByte(folder)
    curScript.emitByte(shuffle)
    curScript.emitByte(flags)
    curScript.emitByte(noescape)
    curScript.emitByte(battleId)
    curScript.emitByte(table1)
    curScript.emitByte(table2)
    curScript.emitByte(table3)


def battle3():
    misc_control(4)

def shop(shopIndex: int):
    global curScript
    misc_control(5)
    curScript.emitByte(shopIndex)


def trader(amt: int, ifless: int = 0xFF):
    global curScript
    misc_control(6)
    curScript.emitByte(amt)
    curScript.emitByte(ifless)

def leave_map(index: int):
    global curScript
    misc_control(7)
    curScript.emitByte(index)

def style_apply():
    global curScript
    misc_control(8)


def award_item(
    amtList: List[int], nextjump: int = 0xFF, unused1: int = 0xFF, unused2: int = 0xFF
):
    global curScript
    misc_control(9)
    curScript.emitByte(len(amtList) - 1)
    curScript.emitByte(nextjump)
    curScript.emitByte(unused1)
    curScript.emitByte(unused2)
    for amt in amtList:
        curScript.emitByte(amt)


def bbs():
    global curScript
    misc_control(10)


def misc11():
    global curScript
    misc_control(11)


def misc12():
    global curScript
    misc_control(12)


def award_folder(index: int):
    global curScript
    misc_control(13)
    curScript.emitByte(index)


def save(savegood: int, savebad: int):
    global curScript
    curScript.emitByte(0xFC)
    curScript.emitByte(savegood)
    curScript.emitByte(savebad)


def parse_command(reader: Reader):
    global curScript
    com = ""
    while not reader.isEmpty() and reader.peek() != "}":
        com += reader.read()
    if reader.isEmpty():
        exit("Incomplete command")
    reader.read()
    singleMatch = re.match(r"^([0123])$", com)
    padMatch = re.match(r"^([0123]):(([ 0])?(<|>)?)?(\d+)$", com)
    if singleMatch:
        bf = int(singleMatch.group(1))
        curScript.emitByte(0xE9)
        curScript.emitByte(bf)
        curScript.emitByte(1)
        return
    if padMatch:
        bf = int(padMatch.group(1))
        padChar = padMatch.group(3)
        direction = padMatch.group(4)
        count = int(padMatch.group(5))
        if count >= 0x40:
            exit("Pad amount needs to be less than 0x40")
        if direction == ">":
            count += 0x80
        if padChar == "0":
            count += 0x40
        curScript.emitByte(0xE9)
        curScript.emitByte(bf)
        curScript.emitByte(count)
        return

    coms = shlex.split(com)
    if len(coms) > 0:
        if coms[0] == "delay" or coms[0] == "d":
            if len(coms) > 1:
                arg = auto_int(coms[1])
                delay(arg)
            else:
                delay()
        elif coms[0] == "key":
            if len(coms) > 1:
                key_item(coms[1])
            else:
                exit("Key item name required")
        elif coms[0] == "chip":
            if len(coms) == 2:
                chip_id(coms[1])
            elif len(coms) > 2:
                chip(coms[1], coms[2])
            else:
                exit("Chip ID or chip id with code required")
        elif coms[0] == "chip_buf":
            chip_id_buf(1)
            text(" ")
            chip_code_buf(2)
        elif coms[0] == "key_item_buf":
            arg = auto_int(coms[1])
            key_item_buf(arg)
        elif coms[0] == "anim" or coms[0] == "a":
            if len(coms) > 1:
                arg = auto_int(coms[1])
                anim(arg)
            else:
                exit("Animation index required")
        elif coms[0] == "add_chip":
            if len(coms) == 1:
                exit("Arguments required for add_chip")
            item = coms[1]
            args = [auto_int(i) for i in coms[2:]]
            add_chip(item, *args)
        elif coms[0] == "sub_chip":
            if len(coms) == 1:
                exit("Arguments required for sub_chip")
            item = coms[1]
            args = [auto_int(i) for i in coms[2:]]
            sub_chip(item, *args)
        elif coms[0] == "add_item":
            if len(coms) == 1:
                exit("Arguments required for add_item")
            item = coms[1]
            args = [auto_int(i) for i in coms[2:]]
            add_item(item, *args)
        elif coms[0] == "sub_item":
            if len(coms) == 1:
                exit("Arguments required for sub_item")
            item = coms[1]
            args = [auto_int(i) for i in coms[2:]]
            sub_item(item, *args)
        elif coms[0] == "wait" or coms[0] == "w":
            if len(coms) > 1:
                arg = auto_int(coms[1])
                wait(arg)
            else:
                wait()
        elif coms[0] == "buf":
            buffer(1)
        elif coms[0] == "end":
            if len(coms) > 1:
                arg = auto_int(coms[1])
                end(arg)
            else:
                end()
        elif coms[0] == "lv":
            emit(0xB)
        elif coms[0] == "..":
            for _ in range(2):
                curScript.emitByte(0xE5)
                curScript.emitByte(charmap_E5["."])
                delay()
        elif coms[0] == "...":
            for _ in range(3):
                curScript.emitByte(0xE5)
                curScript.emitByte(charmap_E5["."])
                delay()
        elif coms[0] == "item_amt":
            item_amt(coms[1])
        elif coms[0] == "p":
            pad()
        elif coms[0] == "c":
            args = [auto_int(i) for i in coms[1:]]
            option(*args)
            pad()
        elif len(coms[0]) == 6 and coms[0][1:4] == "pad":
            if len(coms) != 2:
                exit("Argument required for pad")
            if not is_int(str(coms[1])):
                exit("Number argument required for pad")
            dr = coms[0][0]
            pd = coms[0][4]
            bf = coms[0][5]
            sz = auto_int(coms[1])
            if dr != "l" and dr != "r":
                exit("Unrecognized direction for pad")
            if pd != "s" and pd != "z":
                exit("Unrecognized padding char for pad")
            if not is_int(str(bf)):
                exit("Buffer for pad function must be a number")
            bf = int(bf)
            if bf < 0 or bf > 3:
                exit("Buffer for pad function required to be from 0 to 3")
            if sz > 0x40:
                exit("Pad amount needs to be less than 0x40")
            if dr == "l":
                sz += 0x80
            if pd == "z":
                sz += 0x40
            curScript.emitByte(0xE9)
            curScript.emitByte(bf)
            curScript.emitByte(sz)
        elif coms[0] == "col":
            if len(coms) > 1:
                arg = auto_int(coms[1])
                col(arg)
            else:
                exit("Argument required for col")
        elif coms[0] == "se":
            if len(coms) == 1:
                exit("Argument required for se")
            arg = auto_int(coms[1])
            se(arg)
        else:
            exit(f"Unrecognized command {coms[0]}")


def text_base(useBold: bool, *txtList):
    global curScript, charmap_bold, charmap_basic, charmap_E5
    for txt in txtList:
        if txt and len(txt) > 0:
            reader = Reader(txt)
            while not reader.isEmpty():
                char = reader.read()
                if char == "{":
                    parse_command(reader)
                elif char == "\\":
                    char += reader.read()
                    if char == "\\p":
                        page()
                    else:
                        exit(f"Unrecognized command {char}")
                else:
                    if useBold and char in charmap_bold:
                        curScript.emitByte(charmap_bold[char])
                    elif not useBold and char in charmap_basic:
                        curScript.emitByte(charmap_basic[char])
                    elif char in charmap_E5:
                        curScript.emitByte(0xE5)
                        curScript.emitByte(charmap_E5[char])
                    else:
                        curScript.emitByte(ord(char))


def text(*txtList):
    text_base(False, *txtList)


def text_bold(*txtList):
    text_base(True, *txtList)


# endregion


def main():
    global curScript
    parser = argparse.ArgumentParser(
        description="Builds Mega Man Battle Network text scripts."
    )
    parser.add_argument("output", type=str, help="The output file.")
    parser.add_argument("input", type=str, help="The input file.")
    args = parser.parse_args()
    inPath = Path(args.input)
    outPath = Path(args.output)
    if not inPath.exists():
        exit(f"Couldn't find file {inPath}")
    with open(inPath, mode="r") as inFile:
        exec(inFile.read())
    curScript.writeToFile(outPath)


if __name__ == "__main__":
    main()
