## Advanced Viginere Cyper

Program encrypts the text files using Viginere cipher.

### Installation

Clone repository. Goto clonned repo dir and run `make`:

```
git clone git@github.com:GhostStarBiter/VIGINERE_CIPHER.git

cd path/to/VIGINERE_CIPHER && make (for local usage)
OR
cd path/to/VIGINERE_CIPHER && make global (to access to program from any place on computer)
```

### Usage

To encode text file:
```
vgnr code /path/to/original/file /path/to/encrypted/file KEYWORD
```

To decode text file:
```
vgnr decode /path/to/encoded/file /path/to/decoded/file KEYWORD
```

To run usage help hit:
```
vgnr 
```

FUTURE IMPROVEMENT:

     - keyword contains of lower and upper case letters;
     
     - encrypted/decrypted text contains of lower and upper case letters;
