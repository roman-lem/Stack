// This file will help you for make colored output |
//==================================================

// Default mode
#define $d printf("\x1b[0m");

// Bold
#define $bd printf("\x1b[1m");

//Underlined
#define $ul printf("\x1b[4m");

//Blinking
#define $bl printf("\x1b[5m");

//Inverted colors
#define $i  printf("\x1b[7m");

//Invisiblipie
#define $v printf("\x1b[8m");

/*------------------Text colors------------------*/

//Black
#define $k printf("k\x1b[30m");

//Red
#define $r printf("\x1b[31m");

//Green
#define $g printf("\x1b[32m");

//Yellow
#define $y printf("\x1b[33m");

//Blue
#define $b printf("\x1b[34m");

//Purpure
#define $p printf("\x1b[35m");

//Light blue
#define $lb printf("\x1b[36m");

//White
#define $w printf("\x1b[37m");

/*------------------Background colors------------------*/

//Black
#define $bgk printf("\x1b[40m");

//Red
#define $bgr printf("\x1b[41m");

//Green
#define $bgg printf("\x1b[42m");

//Yellow
#define $bgy printf("\x1b[43m");

//Blue
#define $bgb printf("\x1b[44m");

//Purpure
#define $bgp printf("\x1b[45m");

//Light blue
#define $bglb printf("\x1b[46m");

//White
#define $bgw printf("\x1b[47m");

//---------------Combinations--------------------//

//Complited test
#define $OK $bgg $w

//Error
#define $E $bgr $w
