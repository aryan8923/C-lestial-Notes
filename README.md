# C - lestial 
Documentation Page is [here](docs/docs.md) 

This is the official git repository for the C-lestial library. C-lestial is a project that I have started so as to learn numerical analysis. It contains notes, codes and demonstrations written in C. I wish to learn numerical analysis as well, so I read textbooks, research articles, etc and upload the notes here.

I will be writing the functions and upload them under [GNU GPLv3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) license so you have the freedom to use, change and share the codes for any purposes. The library may not be as good as pre-existing ones, but the goal is to learn and let others learn. I will also be citing resources along with the notes so that the reader can have a deeper look at the topic under study.

## Requirements for the library
`gcc` is required to compile the necessary code. One can use any other compiler if they wish.

## Usage

Download the `c_lestial_library` folder from the git repo. Put the folder in the same directory as your main file. 

Set the MAIN variable in the Makefile to your file's name (by default set to main.c) 

Keep the Makefile in the same folder as your code. 

Run ```make``` in terminal. 

The code by default compiles to "main". (You can rename the output file by setting the TARGET variable in Makefile)

To remove the compiled executable and object files, run ```make clean```

