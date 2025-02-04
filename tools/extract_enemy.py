#!/usr/bin/python3
import argparse
from pathlib import Path
from typing import BinaryIO

import common
from common import auto_int, get_byte, get_short


mp_dist = [
    5, 5, 5, 5, 5, 6, 5, 5, 5, 5
]

def bytelist(inFile: BinaryIO, count: int) -> str:
    if count > 0:
        b = inFile.read(count)
        return ".byte " + ", ".join([f"0x{x:X}" for x in b])
    else:
        return ""


def reward(val):
    return (
        f"zenny {val & 0x7FFF}"
        if val & 0x8000 != 0
        else f"battlechip {common.chip_id(val & 0xFF)} {common.chip_code(val >> 8)}"
    )


def element(inFile: BinaryIO) -> str:
    elem = get_byte(inFile)
    if elem == 0:
        return "noelement"
    else:
        return f"element {common.element(elem)}"


def reward(val):
    flag = val >> 0xE
    if flag == 0:
        return f"battlechip {common.chip_id(val & 0x1FF)} {common.chip_code(val >> 9)}"
    elif flag == 1:
        return f"zenny {val & 0x3FFF}"
    else:
        return f"health {val & 0x3FFF}"


def spriteIndex(inFile: BinaryIO):
    groupDict = {
        0x00: "MegaMan",
        0x04: "Virus",
        0x08: "Navi",
        0x0C: "ChipAttack",
        0x10: "VirusAttack",
        0x14: "BattleEffect",
        0x18: "Character",
        0x1C: "Object",
        0x20: "Portrait"
    }
    group = get_byte(inFile)
    index = get_byte(inFile)
    return f"sprite {groupDict[group]}, 0x{index:02X}"


def main():
    parser = argparse.ArgumentParser(
        description="Extract enemy data from Mega Man Battle Network."
    )
    parser.add_argument(
        "-eo",
        "--enemy-offset",
        type=auto_int,
        default=0x15154,
        help="The offset to start reading from.",
    )
    parser.add_argument(
        "-n",
        "--count",
        type=auto_int,
        default=185,
        help="The amount of enemy data to extract.",
    )
    parser.add_argument(
        "-o", "--output", type=str, default="", help="The output file name."
    )
    parser.add_argument("path", type=str, help="The path to the game.")
    args = parser.parse_args()
    inPath = Path(args.path)
    if not inPath.exists():
        exit(f"Couldn't find file {args.path}")
    outPath = "enemy_data.txt" if args.output == "" else args.output
    with open(inPath, mode="rb") as inFile:
        with open(outPath, mode="w", encoding="utf-8") as outFile:
            inFile.seek(args.enemy_offset)
            for i in range(args.count):
                outFile.write(f"    @ _{i} (0x{i:02X}) (0x{inFile.tell():X}): {common.enemy_id(i)}\n")
                temp = get_short(inFile)
                fact = temp & 0xF000
                hp = temp & 0xFFF
                prefix = f"0x{fact:X} | " if fact != 0 else ""
                outFile.write(f"        hp {prefix}{hp}\n")
                outFile.write(f"        {bytelist(inFile, 2)}\n")
                outFile.write(f"        {spriteIndex(inFile)}\n")
                outFile.write(f"        @ {inFile.tell():X}\n")
                outFile.write(f"        hard_mode_hp 0x{get_byte(inFile):02X}\n")
                outFile.write(f"        .byte 0x{get_byte(inFile):02X}\n")
    outPath = "drop_data.txt"
    with open(inPath, mode="rb") as inFile:
        with open(outPath, mode="w", encoding="utf-8") as outFile:
            inFile.seek(0x125E8)
            for i in range(args.count):
                outFile.write(f"    @ _{i} (0x{i:02X}) (0x{inFile.tell():X}): {common.enemy_id(i)}\n")
                for dropType in ["high", "mid", "low"]:
                    outFile.write(f"    @ {dropType}\n")
                    for _ in range(10):
                        outFile.write(f"        {reward(get_short(inFile))}\n")
    outPath = "mp_drop.txt"
    with open(inPath, mode='rb') as inFile:
        with open(outPath, mode='w', encoding='utf-8') as outFile:
            inFile.seek(0xA4D0)
            for i in range(len(mp_dist)):
                outFile.write(f"    @ _{i} (0x{inFile.tell():X}):\n")
                for count in range(mp_dist[i]):
                    outFile.write(f"        {reward(get_short(inFile))}\n")



if __name__ == "__main__":
    main()
