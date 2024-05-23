# C - lestial 
Documentation Page: https://aryan8923.github.io/C-lestial/docs/index.html#/ 

This is the official git repository for the C-lestial library. C-lestial is a project that I have started so as to learn numerical analysis. It contains notes, codes and demonstrations written in C. I wish to learn numerical analysis as well, so I read textbooks, research articles, etc and upload the notes here.

I will be writing the functions and upload them under [GNU GPLv3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) license so you have the freedom to use, change and share the codes for any purposes. The library may not be as good as pre-existing ones, but the goal is to learn and let others learn. I will also be citing resources along with the notes so that the reader can have a deeper look at the topic under study.

## Requirements for the library
`gcc` is required to compile the necessary code. One can use any other compiler if they wish.

## Usage
Download the `c_lestial_library` folder from the git repo. Put the folder wherever you want. While compiling the code using `gcc`, use:
```gcc -Idirectory/where/library/is -o output yourfile.c path/to/includedfile1.c path/to/includedfile2.c ```

For example, if you are using `linalg.c` from the library and your file name is main.c:
`gcc -Idirectory/where/library/is -o output main.c path/to/linalg.c`

