#!/usr/bin/python3
from enum import Enum
from pathlib import Path
from typing import List, BinaryIO
from common import get_int, get_byte
import io
import sys

enemyIdDict: dict[int,str] = {
    0: "MegaMan",
    1: "Mettaur1",
    2: "Mettaur2",
    3: "Mettaur3",
    4: "Canodumb1",
    5: "Canodumb2",
    6: "Canodumb3",
    7: "Beetank1",
    8: "Beetank2",
    9: "Beetank3",
    10: "Fishy1",
    11: "Fishy2",
    12: "Cloudy1",
    13: "Cloudy2",
    14: "Cloudy3",
    15: "Spooky1",
    16: "Spooky2",
    17: "Spooky3",
    18: "Handy1",
    19: "Handy2",
    20: "Handy3",
    21: "Bunny",
    22: "TuffBunny",
    23: "MegaBunny",
    24: "MettFire",
    25: "FullFire",
    26: "DeathFire",
    27: "Puffy",
    28: "Buffy",
    29: "HardHead1",
    30: "HardHead2",
    31: "HardHead3",
    32: "CanDevil1",
    33: "CanDevil2",
    34: "CanDevil3",
    35: "Mushy",
    36: "Mashy",
    37: "Moshy",
    38: "Swordy1",
    39: "Swordy2",
    40: "Swordy3",
    41: "Mole1",
    42: "Mole2",
    43: "Poofy",
    44: "Fishy3",
    45: "Flappy1",
    46: "Flappy2",
    47: "Flappy3",
    48: "Ratty1",
    49: "Ratty2",
    50: "Ratty3",
    51: "Twisty1",
    52: "Twisty2",
    53: "Twisty3",
    54: "Popper1",
    55: "Popper2",
    56: "Popper3",
    57: "Spikey1",
    58: "Spikey2",
    59: "Spikey3",
    60: "Flamey1",
    61: "Flamey2",
    62: "Flamey3",
    63: "Shrimpy1",
    64: "Shrimpy2",
    65: "Shrimpy3",
    66: "PuffBall",
    67: "PoofBall",
    68: "GoofBall",
    69: "Sparky",
    70: "Sparkler",
    71: "Sparknoid",
    72: "Octon",
    73: "Octor",
    74: "Octovian",
    75: "Yort",
    76: "Yurt",
    77: "Yart",
    78: "Shellgeek",
    79: "Shellnerd",
    80: "Shellman",
    81: "KillPlant",
    82: "KillWeed",
    83: "KillFleur",
    84: "Dominerd1",
    85: "Dominerd2",
    86: "Dominerd3",
    87: "Protecto1",
    88: "Protecto2",
    89: "Protecto3",
    90: "Null",
    91: "Void",
    92: "NullVoid",
    93: "Magneaker",
    94: "Magmacker",
    95: "Magnoid",
    96: "Shadow",
    97: "RedDevil",
    98: "BlueDemon",
    99: "WindBox",
    100: "VacuumFan",
    101: "StormBox",
    102: "RedUFO",
    103: "BlueUFO",
    104: "GreenUFO",
    105: "Snapper1",
    106: "Snapper2",
    107: "Snapper3",
    108: "Brushman1",
    109: "Brushman2",
    110: "Brushman3",
    111: "Lavagon",
    112: "Bluegon",
    113: "Yellowgon",
    114: "Scutz",
    115: "Scuttle",
    116: "Scuttler",
    117: "Scuttzer",
    118: "Scuttlest",
    119: "MegalianA",
    120: "MegalianH",
    121: "MegalianW",
    122: "MegalianE",
    128: "AirManV1",
    129: "AirManV2",
    130: "AirManV3",
    131: "QuickManV1",
    132: "QuickManV2",
    133: "QuickManV3",
    134: "CutManV1",
    135: "CutManV2",
    136: "CutManV3",
    137: "ShadowManV1",
    138: "ShadowManV2",
    139: "ShadowManV3",
    140: "KnightManV1",
    141: "KnightManV2",
    142: "KnightManV3",
    143: "MagnetManV1",
    144: "MagnetManV2",
    145: "MagnetManV3",
    146: "FreezeManV1",
    147: "FreezeManV2",
    148: "FreezeManV3",
    149: "Gospel",
    152: "HeatManV1",
    153: "HeatManV2",
    154: "HeatManV3",
    155: "ToadManV1",
    156: "ToadManV2",
    157: "ToadManV3",
    158: "ThunderManV1",
    159: "ThunderManV2",
    160: "ThunderManV3",
    161: "SnakeManV1",
    162: "SnakeManV2",
    163: "SnakeManV3",
    164: "GutsManV1",
    165: "GutsManV2",
    166: "GutsManV3",
    167: "ProtoManV1",
    168: "ProtoManV2",
    169: "ProtoManV3",
    170: "GateManV1",
    171: "GateManV2",
    172: "GateManV3",
    173: "PlanetManV1",
    174: "PlanetManV2",
    175: "PlanetManV3",
    176: "NapalmManV1",
    177: "NapalmManV2",
    178: "NapalmManV3",
    179: "PharaohManV1",
    180: "PharaohManV2",
    181: "PharaohManV3",
    182: "Bass",
    183: "BassV2",
    184: "BassDeluxe",
    255: "Invalid"
}


objTypeDict: dict[int, str] = {
    0: "MegaMan",
    1: "Enemy",
    2: "Rock",
    3: "RockCube",
    4: "MetalCube",
    5: "IceCube",
    6: "Guardian",
    7: "BlackBomb"
}


groupDict = {    
    0x168c0: "EncounterGroup_GasComp",
    0x16a94: "EncounterGroup_BombComp",
    0x16ff4: "EncounterGroup_MotherComp",
    0x1765c: "EncounterGroup_CastleComp",
    0x17c6c: "EncounterGroup_AirComp",
    0x18280: "EncounterGroup_ApartComp",
    0x18910: "EncounterGroup_HomePage",
    0x18dd4: "EncounterGroup_OtherComp1",
    0x19afc: "EncounterGroup_OtherComp2",
    0x19f40: "EncounterGroup_DenArea",
    0x1a264: "EncounterGroup_KotobukiArea",
    0x1a5ac: "EncounterGroup_YumlandArea",
    0x1a8f8: "EncounterGroup_NetopiaArea",
    0x1ad78: "EncounterGroup_Undernet"
}


def toAddr(link:int) -> str:
    if False:
        pass
    else:
        return f"Encounter"


def extractSpawnList(inFile: BinaryIO) -> tuple[bool, str]:
    start = inFile.tell()
    buffer = f"EnemySpawn_{start+0x8000000:08X}:\n"
    counter = 0
    good = True
    while True:
        enemy = get_byte(inFile)
        x = get_byte(inFile)
        y = get_byte(inFile)
        type = get_byte(inFile)
        if enemy == 0xFF and x == 0 and y == 0 and type == 0:
            buffer += "    spawn_end\n\n"
            break
        if enemy not in enemyIdDict:
            good = False
            break
        if x < 1 or x > 6 or y < 1 or y > 6:
            good = False
            break
        if type not in objTypeDict:
            good = False
            break
        if type >= 2:
            buffer += f"    spawn_obj {objTypeDict[type]}, {x}, {y}\n"
        elif enemy == 0:
            if x == 2 and y == 2:
                buffer += f"    spawn {enemyIdDict[enemy]}"
            else:
                buffer += f"    spawn {enemyIdDict[enemy]}, {x}, {y}"
            if type != 0:
                buffer += f", {objTypeDict[type]}"
            buffer += "\n"
        elif type == 1:
            buffer += f"    spawn {enemyIdDict[enemy]}, {x}, {y}\n"
        else:
            buffer += f"    spawn {enemyIdDict[enemy]}, {x}, {y}, {objTypeDict[type]}\n"
        counter += 1
        if counter > 10:
            good = False
            break
    if not good:
        inFile.seek(start)
    return (good, buffer)

        
def extractPointer(inFile: BinaryIO) -> tuple[bool, str]:
    start = inFile.tell()
    if start not in groupDict:
        return (False, "")
    listSize = 16
    if start >= 0x19f40:
        listSize = 32
    if start >= 0x1ad78:
        listSize = 64
    buffer = f"{groupDict[start]}:\n"
    for _ in range(listSize):
        link = get_int(inFile)
        buffer += f"    .word EnemySpawnSet_{link:08X}\n"
    buffer += "\n"
    return (True, buffer)


def extractSpawnSet(inFile: BinaryIO) -> tuple[bool, str]:
    start = inFile.tell()
    good = True
    buffer = f"EnemySpawnSet_{start+0x8000000:08X}:\n"
    sum = 0
    amt = 0
    while True:
        args = get_int(inFile)
        link = get_int(inFile)
        if (args < 0x8000000 or args > 0x8800000) and link >= 0x8000000 and link < 0x8800000:
            amt += 1
            a0 = args & 0xFF
            a1 = (args >> 8) & 0xFF
            a2 = (args >> 16) & 0xFF
            a3 = (args >> 24) & 0xFF
            buffer += f"    .byte 0x{a0:02X}, level={a1}, 0x{a2:02X}, 0x{a3:02X}\n"
            buffer += f"    .word EnemySpawn_{link:08X}\n\n"
            sum += a0
            if sum >= 0x100 or a0 == 0:
                break
        else:
            break
    if amt == 0:
        inFile.seek(start)
        good = False
    return (good, buffer)


def printEncounter(inFile: BinaryIO):
    buffer = ""
    inFile.seek(0x1571C)
    while True:
        good, buf = extractSpawnList(inFile)
        if not good:
            good, buf = extractPointer(inFile)
            if not good:
                good, buf = extractSpawnSet(inFile)
        if not good:
            break
        else:
            buffer += buf
    return buffer


def printEnemy(inFile: BinaryIO):
    pass


def main():
    folder  = Path("./base/base.gba")
    buffer = ""
    with open(folder, 'rb') as inFile:
        buffer = printEncounter(inFile)
    with open("out.txt", "w") as outFile:
        outFile.write(buffer)



if __name__ == "__main__":
    main()
