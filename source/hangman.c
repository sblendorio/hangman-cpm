#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "xterm.h"

#define MAXERRS 7
#define MESGY   13
#define MESGX   1
#define PROMPTY 12
#define PROMPTX 1
#define KNOWNY  11
#define KNOWNX  2
#define NUMBERY 5
#define NUMBERX (80 - 26)
#define AVGY    6
#define AVGX    (80 - 26)
#define GUESSY  3
#define GUESSX  (80 - 26)

#define WORDFILE "words.txt"

struct errPos {
	int x;
	int y;
	char c;
};

char *noose[] = {
"     ______",
"     |    |",
"     |",
"     |",
"     |",
"     |",
"   __|_____",
"   |      |___",
"   |_________|",
NULL
};

struct errPos man[]= {
	{11, 3, 'O'},
	{11, 4, '|'},
	{11, 5, '|'},
	{10, 6, '/'},
	{10, 4, '/'},
	{12, 4, '\\'},
	{12, 6, '\\'}
};


void drawNoose(void);
void drawScreen(void);
void drawMan(int errCount);
int countLines(char *filename);
char *getWord(char *filename, int wordCount, char *buffer);
void die(int code);
void drawWord(void);
void drawData(void);
void playGame(void);
void endGame(void);
void getGuess(void);

void drawNoose() {
	int i=0;
	while (noose[i]) {
		CursorXY(1,i+1);
		printf("%s",noose[i++]);
	}
}

void drawScreen() {
	CursorXY(PROMPTX, PROMPTY); printf("Guess:");
	CursorXY(GUESSX, GUESSY); printf("Guessed:");
	CursorXY(NUMBERX, NUMBERY); printf("Word #:");
	CursorXY(AVGX, AVGY); printf("Current Average:");
	CursorXY(AVGX, AVGY+1); printf("Overall Average:");
	CursorXY(KNOWNX, KNOWNY); printf("Word: ");
	drawNoose();
}

void drawMan(int errCount) {
	int i;
	for (i=0; i<errCount; ++i) {
		CursorXY(man[i].x, man[i].y);
		putchar(man[i].c);
	}
	while (i<MAXERRS) {
		CursorXY(man[i].x, man[i].y);
		putchar(' ');
		++i;
	}
}

int countLines(char *filename) {
	FILE *fp;
	char line[100];
	int lineCount=0;
	if ((fp=fopen(filename,"r"))) {
		while (fgets(line,100,fp)) {
			if (strlen(line)>1)
				++lineCount;
		}
	} else {
		printf("Missing file %s\n",filename);
		exit(1);
	}
	fclose(fp);
	return lineCount;
}

char *getWord(char *filename, int wordCount, char *buffer) {
	FILE *fp;
	char line[100];
	int index,count;
	index=rand() % wordCount;
	if ((fp=fopen(filename,"r"))) {
		count=0;
		while (count <= index && fgets(line,100,fp)) {
			if (strlen(line)<=1) continue;
			line[strlen(line)-1]='\0';
			++count;
		}
	} else {
		printf("Missing file %s\n",filename);
		exit(1);
	}
	fclose(fp);
	strcpy(buffer,line);
	return buffer;
}

void die(int code) {
	CursorXY(1,16);
	exit(code);
}

int errors=0;
int wordCountTotal=0;
int wordNum=0;
double average=0.0;
bool guessed[26];
char word[100];
char known[100];

void getGuess() {
	int i;
	char ch;
	bool correct;

	while (true) {
		CursorXY(PROMPTX+strlen("Guess: "),PROMPTY);
		ch = ReadChar();
		if (isalpha(ch)) {
			if (isupper(ch))
				ch = tolower(ch);
			if (guessed[ch-'a']) {
				CursorXY(MESGX,MESGY);
				printf("Already guessed '%c'",ch);
			} else
				break;
		} else
			if (ch=='\004' || ch=='\003' || ch=='\033')
				die(0);
			else {
				CursorXY(MESGX,MESGY);
				printf("Invalid guess      ");
			}
	}
	CursorXY(MESGX,MESGY); ClrEol();

	guessed[ch-'a']=true;
	correct=false;
	for (i=0; word[i]!='\0'; ++i) {
		if (word[i]==ch) {
			known[i]=ch;
			correct=true;
		}
	}
	if (!correct) ++errors;
}

void drawWord() {
	CursorXY(KNOWNX+strlen("Word: "),KNOWNY);
	printf("%s",known); ClrEol();
}

void drawData() {
	int i;

	CursorXY(GUESSX+strlen("Guessed: "),GUESSY);
	for (i=0; i<26; ++i)
	if (guessed[i]) putchar('a'+i);
	ClrEol();
	CursorXY(NUMBERX+strlen("Word #:          "),NUMBERY);
	printf("%d",wordNum);
	CursorXY(AVGX+strlen("Current Average: "),AVGY);
	printf("%.3f", (average*(wordNum-1)+errors)/wordNum);
	CursorXY(AVGX+strlen("Overall Average: "),AVGY+1);
	printf("%.3f", average);
}

void playGame() {
	int i;
	for (i=0; i<26; ++i) guessed[i]=false;
	for (i=0; i<100; ++i) known[i]='-';
	errors = 0;
	getWord(WORDFILE, wordCountTotal, word);
	known[strlen(word)]='\0';

	while (errors < MAXERRS && strchr(known,'-') != NULL) {
		drawWord();
		drawData();
		drawMan(errors);
		getGuess();
	}
	endGame();
}

void endGame() {
	char ch;
	drawMan(errors);
	if (errors >= MAXERRS) errors+=2;
	drawWord();
	drawData();
	CursorXY(MESGX,MESGY);
	if (errors > MAXERRS)
		printf("Sorry, the word was \"%s\"\n",word);
	else
		puts("You got it!");

	while (true) {
		CursorXY(MESGX,MESGY+1); printf("Another word? ");
		if ((ch=ReadChar())=='n')
			die(0);
		else if (ch=='y')
			break;
		CursorXY(MESGX,MESGY+2); printf("Please type 'y' or 'n'");
	}
	CursorXY(MESGX,MESGY);
	DelLine();
	DelLine();
	DelLine();
}

int main(int argc, char *argv[]) {
	AskTermType(argc, argv);
	printf("Wait please. Initializing...");
	ResetTerm();
	wordCountTotal = countLines(WORDFILE);
	RandomizeShuffle();
	ClrScr();
	drawScreen();

	while (true) {
		++wordNum;
		playGame();
		average = (average * (wordNum-1) + errors) / wordNum;
	}
}
