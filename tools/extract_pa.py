#!/usr/bin/python3
import argparse
from pathlib import Path

from common import auto_int, get_int, get_short, chip_id, chip_code


def main():
    parser = argparse.ArgumentParser(
        description="Extract chip data from Mega Man Battle Network."
    )
    parser.add_argument(
        "-o", "--output", type=str, default="", help="The output file name."
    )
    parser.add_argument("path", type=str, help="The path to the game.")
    args = parser.parse_args()
    inPath = Path(args.path)
    if not inPath.exists():
        exit(f"Couldn't find file {args.path}")
    outPath = "pa_data.txt" if args.output == "" else args.output
    addrs = {
        0xbd50: "listProgramAdvance3Chip",
        0xc0a4: "listProgramAdvance4Chip",
        0xc0a8: "listProgramAdvance5Chip"
    }
    with open(inPath, mode="rb") as inFile:
        with open(outPath, mode="w", encoding="utf-8") as outFile:
            inFile.seek(0xBD50)
            while inFile.tell() < 0xC16C:
                if inFile.tell() in addrs:
                    outFile.write(f"{addrs[inFile.tell()]}:\n")
                header = get_int(inFile)
                sz = header & 0xFF
                if sz == 0xFF:
                    outFile.write("    pa_end\n\n")
                    continue
                amt = (header >> 8) & 0xFF
                pa_id = chip_id((header >> 16) & 0xFFFF)
                outFile.write(f"    pa_sz 0x{sz:02X}\n")
                outFile.write(f"    pa_amt {amt}\n")
                outFile.write(f"    pa_id {pa_id}\n")
                for _ in range(amt):
                    id = get_short(inFile)
                    cd = get_short(inFile)
                    outFile.write(f"    battlechip {chip_id(id)} {chip_code(cd)}\n")
                outFile.write("\n")



if __name__ == "__main__":
    main()
