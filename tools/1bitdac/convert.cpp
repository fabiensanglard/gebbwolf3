#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct wav_header {
    // RIFF Header
    uint8_t riff_header[4]; // Contains "RIFF"
    uint32_t wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
    uint8_t wave_header[4]; // Contains "WAVE"
    
    // Format Header
    uint8_t fmt_header[4]; // Contains "fmt " (includes trailing space)
    uint32_t fmt_chunk_size; // Should be 16 for PCM
    uint16_t audio_format; // Should be 1 for PCM. 3 for IEEE Float
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate; // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    uint16_t sample_alignment; // num_channels * Bytes Per Sample
    uint16_t bit_depth; // Number of bits per sample
    
    uint8_t plan_header[8]; // Contains "fact"
    //int somestuff;

    // Data
    uint8_t data_header[4]; // Contains "data"
    uint32_t data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size
    uint8_t bytes[]; // Remainder of wave file is bytes
} __attribute__((packed)) wav_header ;

int main(int argc, char** argv) {

	int myfd = open(argv[1], O_RDWR);
	if (myfd<0) { 
		perror("hello.txt open"); 
	    exit(EXIT_FAILURE); 
	}

	struct stat mystat = {};
	if (fstat(myfd,&mystat)) { 
	  perror("fstat"); 
	  exit(EXIT_FAILURE); 
	}

	printf("%s size is %d\n", argv[1], mystat.st_size);

	off_t myfsz = mystat.st_size;

	void*ad = mmap(NULL, myfsz, PROT_READ|PROT_WRITE, MAP_SHARED, myfd, 0);
	if (ad == NULL) { 
	  perror("mmap"); exit(EXIT_FAILURE); 
	}

    wav_header* header = (wav_header*)ad;

    uint8_t* payload = header->bytes; 
    printf("%s riff header %c%c%c%c\n", argv[1], header->riff_header[0], header->riff_header[1], header->riff_header[2], header->riff_header[3]);
    printf("%s fmt  header %c%c%c%c\n", argv[1], header->fmt_header[0], header->fmt_header[1], header->fmt_header[2], header->fmt_header[3]);
    printf("%s fact header %c%c%c%c\n", argv[1], header->plan_header[0], header->plan_header[1], header->plan_header[2], header->plan_header[3]);
    printf("%s fac2 header %c%c%c%c\n", argv[1], header->plan_header[4], header->plan_header[5], header->plan_header[6], header->plan_header[7]);
    printf("%s data header %c%c%c%c\n", argv[1], header->data_header[0], header->data_header[1], header->data_header[2], header->data_header[3]);
    printf("%s header byte size is %d\n", argv[1], header->data_bytes);
    
    for (size_t i = 0 ; i < 5874/*header->data_bytes*/ ; i++) {
    	if (*payload >= 128)
    		*payload = 0;
    	else
    		*payload = 255;
    	payload++;
    }

    msync(ad, myfsz, MS_SYNC);
    close(myfd);
	//((char*)ad) = 'R'
}