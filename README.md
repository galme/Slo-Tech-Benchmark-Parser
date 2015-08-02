# Slo-Tech-Benchmark-Parser
Slo-Tech Benchmark parsing tool for user submissions processing

Author: Gal Meznarič ... galu | galme
Meant for: https://slo-tech.com/

FILE COMPATIBILITY INSTRUCTIONS:
- data needs to be delimited by a '|' character. This can be easily changed though (just make sure it's as unique as possible)
- nickname MUST be in the FIRST place, followed by the delimiter, for example: "galu | ..."
- score MUST either be placed BEFORE a verification link, OR in the LAST place, if the verification link is not present, for example: "... | 9000" or "... | 9000 | https://slo-tech.com/forum/t555272/p4850946#p4850946"
- verification link is not necessary, but it's nice
- the program produces a _sorted output file (includes all submissions, ordered by score) and a _sorted_filtered_numbered output file (includes users best unique submissions ordered by score and numbered)
- the program is input compatible with the _sorted version of the output. This means you do not have to keep the source file, because the program can compensate for the HTML tags

HOW TO RUN THIS THING:
- launch the .exe
- when the Open File Dialog opens, select the text file you wish to process and click open
- it shouldn't take more than a moment...
- the 2 text output files are saved in the same folder as the input file lies, but you can also see the absolute path in the terminal
- and there you have it, open the files and paste their contents on the forum!

RECOMMENDATIONS:
- add verification links because it really makes a great navigation
- have one source file and append new results to the bottom of the document. The program doesn't care where you put it, as long as it's on it's seperate line, but you can get a chronological order that way
- don't edit the _sorted output file, IF you're planning to use it for input in the future. You may mess up the parser!

input file example:
------------------------------------------------------------------------------------
vaščan | intel i7 2700k 4.9ghz zračno macho | sapphire 7950 1050/1500 crossfire | 2x4gb ddr3 1866mhz 9.9.9.27| 12457
Moonman | i7 5820K @ 4,9GHz | 29646 | https://slo-tech.com/forum/t649564/p4855886#p4855886
<strong>eDDi</strong> | Intel Core i7 5960X 4373MHz vodno | R9 290X 3X (stock/stock) vodno | 4x8GB@2666MHz 14-14-14-32 | 24407
Shuli| i7 5820K @ stock | 2x Gigabyte GTX 970 Windforce3x @ stock | Crucial 4x8GB 2400DDR4 @ stock | 12061
theGamer | 3770K@4700Mhz (Hydro H90) | 2xGTX780 3GB stock | 8GB 1600mhz 9.9.9.24 | 15381 | <a href="https://slo-tech.com/forum/t649564/p4855887#p4855887">link</a>
Mind_Game | i7 4790K @ 4,7GHz | 2x Galax GTX980 SOC @ 1358core/1948mem | TeamGroup Extreem 2x4GB 2666DDR3 |21108
Evelynn | Intel Core i7 4770K @ 4200MHz (Custom water) | 4x Asus R9 290 @ 1150MHz/1380MHz (Custom water) | 16GB Corsair Vengeance @ 2400MHz 9-9-9-24 | 20667
poiuz | 4770K@4.6GHz | 2x GTX780 Ti @1000/3900 | 8GB@2666MHz | 17238
------------------------------------------------------------------------------------
You may notice that this file has a few inconsistencies (extra <strong> HTML tag, missing data in the middle (RAM and GPU info) and 3 different line endings). The program should handle this just fine.
