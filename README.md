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


An input file example can be found as "input_file_example.txt".
You may notice that this file has a few inconsistencies (extra <strong> HTML tag, missing data in the middle (RAM and GPU info) and 3 different line endings). The program should handle this just fine.
