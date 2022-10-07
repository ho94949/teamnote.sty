# teamnote.sty

## What is teamnote.sty?

`teamnote.sty` is LaTeX template for making ACM-ICPC team reference document (a. k. a. team-note, team notebook, team cheat sheet, etc,.)

## Usage

Sample Project: https://www.overleaf.com/read/gvbsfchdbdhh

Use Menu > Copy Project for your own team note.

## Feature

Team reference document should meet following constraints:

- Up to 25 pages, single-sided, letter or A4 size.
- Pages numbered in upper right-hand corner, university name printed in upper left-hand corner.
- Text and illustration must be readable by a person with correctable eyesight without magnification from a distance of 1/2 meter.
- It may include hand-written comments and corrections on the fronts of pages only. 
- The document must be in some type of notebook or folder with the name of your institution on the front.

`teamnote.sty` provides following features:

- Document is designed as A4 size single page (recommends landscape two-column).
- Automatically formats page number, university name, team name, title page.
- If document exceeds 25 pages, page number is displayed as red.


`teamnote.sty` have following commands:

- `\teamnote{University Name}{School Name}{Author Name}`
    - It automatically configures document.
- `\maketitlepage`
    - It makes title page with School Name, Author, Compiled Date, and Table of Contents
- `\Algorithm{Name}{Usage}{Complexity}{language}{source code file}{author}`
    - You can give an algorithm that will written in document. If you do not specify name, usage, (time) complexity, source code file or author, it will not be displayed. If you do not specify language, it will be cpp in default.
- `\HideUsage`, `\ShowUsage`, `\HideComplexity`, `\ShowComplexity`, `\HideAuthor`, `\ShowAuthor`
  - Usage, time complexity, and author is showed or hidden after the command.



## Dependency

`teamnote.sty` is LaTeX style file and depends on following packages:

- `geometry`

- `fancyhdr`

- `lastpage`

- `color`

- `minted`

- `indentfirst`

- `amssymb `


If you cannot find package[`minted`](https://ctan.org/pkg/minted?lang=en), you should install it and do not forget to add `-shell-escape` option for `pdflatex`.





