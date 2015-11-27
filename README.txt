Algorithm Explanation

for the path of robot, I simply choose the shortest possible length path, which is move left to right for a line and then right to left for the line below.

for the compressing method, i use a library for huffman coding from Michael Dipperstein (mdipper@cs.ucsb.edu), this alogorithm treats numbers as characters, which it counts the frequency of 0 to 9 appear in the file.

this is rather wasting and could be improved by treat number just as number.

the algorithm encode the new line character as well, which would waste 2 bits for each number, this is used for indicate one height when decoding.

since the huffman tree is built based on the sonar file, it is less efficient than directly on actual file.

a codeword list is built for storeing codewords for each symbol, the index is just the ascii value of the numbers, thus the codeword can be easily extracted.