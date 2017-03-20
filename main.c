#include <stdio.h>
#include "wave.h"
#include <math.h>
#include "screen.h"
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	WAVHDR h;
	FILE *fp;	// file handler of wave file
	int ans, ret;
	short int sa[SAMPLE_RATE];
	/*if(argc<2){
		printf("Usage: %s wave_file\n", argv[0]);
		return -1;
	}
	fp = fopen(argv[1], "r");	//open the wav file in read-only
	if(fp == NULL){
		printf("Cannot open wav file %s\n", argv[1]);
		return -1;
	}*/
	while(1){
		ret = system("arecord -r16000 -c1 -d1 -f S16_LE data.wav");
		if(WIFSIGNALED(ret) && WTERMSIG(ret)==SIGINT) break;
		clearScreen();	// makes a fresh screen
		fp = fopen("data.wav", "r");
		fread(&h, sizeof(h), 1, fp);	// read the wav header
		dispWAVHDR(h);	// display the wav header info
		fread(&sa, sizeof(short int), SAMPLE_RATE, fp);
		dispWAVdata(sa);
		fclose(fp);
	}
	printf("Do you want to generate a testtone?(1:yes, 0:no) ");
	scanf("%d", &ans);
	if(ans == 1) testTone(1000,5);
}
/*
// function definition
void printID(char s[]){
	int i;
	for(i=0; i<4; i++) putchar(s[i]);
	printf("\n");
}

void fillID(char *d, const char s[]){
	int i;
	for(i=0; i<4; i++) *d++=s[i];
}

void testTone(int f, double d){
	WAVHDR h;
	FILE *fp;
	int i;
	short int sample;
	fillID(h.ChunkID, "RIFF");
	fillID(h.Format, "WAVE");
	fillID(h.Subchunk1ID, "fmt ");
	fillID(h.Subchunk2ID, "data");
	// chunk size will be calculated later
	h.Subchunk1Size = 16;
	h.AudioFormat = 1;
	h.NumChannels = 1;
	h.SampleRate = SAMPLE_RATE;
	h.BitsperSample = 16;
	h.ByteRate = SAMPLE_RATE*h.NumChannels*(h.BitsperSample/8);
	h.BlockAlign = h.NumChannels*h.BitsperSample/8;
	h.Subchunk2Size = h.ByteRate * d;
	h.ChunkSize = h.Subchunk2Size + 36;
	fp = fopen("testtone.wav", "w");
	fwrite(&h, sizeof(h), 1, fp);	// write the header to file
	for(i=0; i<SAMPLE_RATE*d; i++){
		sample = 32767*sin(2*PI*f*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
	}
	fclose(fp);
	printf("Test tone created!\n");
}

void dispWAVHDR(WAVHDR h){
	double duration;
	printf("Chunk ID: "); printID(h.ChunkID);
	printf("Chunk size: %d\n", h.ChunkSize);
	printf("Form: "); printID(h.Format);
	printf("Subchunk1 ID: "); printID(h.Subchunk1ID);
	printf("Subchunk1 size: %d\n", h.Subchunk1Size);
	printf("Audio Format: %d\n", h.AudioFormat);
	printf("Num of Channels: %d\n", h.NumChannels);
	printf("Sample rate: %d\n", h.ByteRate);
	printf("Block Align: %d\n", h.BlockAlign);
	printf("Bits / Sample: %d\n", h.BitsperSample);
	printf("Subchunk2 ID: "); printID(h.Subchunk2ID);
	printf("Subchunk2 size: %d\n", h.Subchunk2Size);
	duration = (double)h.Subchunk2Size/h.ByteRate;
	printf("Duration: %.3f sec\n", duration);
}
*/
