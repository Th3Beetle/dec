#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ASCII_SHIFT 48
#define HEX_BASE 16
#define BIN_BASE 2
#define NBITS8 7
#define NBITS6 5
#define PRINT(text) printf("the text is \"%s\"\n", text);
unsigned char * readLine() {
    unsigned char * text;
    text = malloc(sizeof(char));
    unsigned char c = ' ';
    int j = 0;
    getchar();
    while((c = getchar()) != '\n') {
        text = realloc(text, (j+1)*sizeof(char));
        text[j++] = c;
    }
    text = realloc(text, (j+1)*sizeof(char));
    text[j] = '\0';
    return text;
}

unsigned char * decodeHex(unsigned char * text) {
    unsigned char * decodedText;
    decodedText = malloc(sizeof(char));
    int i = 0;
    int k = 0;
    int j = 0;
    while (text[i] != '\0') {
        j = 0;
        char temp[2];
        while (j<=1) {
            temp[j++] = text[i++];
        }
        decodedText = realloc(decodedText, (k+1)*sizeof(char));
        decodedText[k] = (temp[0] >= '0' && temp[0] <= '9') ? (temp[0] - ASCII_SHIFT) * pow(HEX_BASE, 1) : (temp[0] - (ASCII_SHIFT + 8)) * pow(HEX_BASE, 1);
        decodedText[k++] += (temp[1] >= '0' && temp[1] <='9') ? (temp[1] - ASCII_SHIFT) * pow(HEX_BASE, 0) : (temp[1] - (ASCII_SHIFT + 8)) * pow(HEX_BASE, 0);
    }
    decodedText = realloc(decodedText, (k+1)*sizeof(char));
    decodedText[k] = '\0';
    free(text);
    return decodedText;
}

unsigned char * toBin(unsigned char * text) {
    unsigned char * encodedText = malloc(sizeof(char));
    int i = 0;
    int k = 0;
    int j = 0;
    while (text[j]!='\0') {
        i = NBITS8;
        while ( i>=0 ) {
            encodedText = realloc(encodedText, (k+1)*sizeof(char));
            encodedText[k] = trunc((text[j]/pow(BIN_BASE,i))) + ASCII_SHIFT;
            text[j] -= trunc((encodedText[k++] - ASCII_SHIFT) * pow(BIN_BASE,i--));
        }
    j++;
    }
    encodedText = realloc(encodedText, (k+1)*sizeof(char));
    encodedText[k] = '\0';
    free(text);
    return encodedText;
}

unsigned char * encodeBase64Digital (unsigned char * text) {

    unsigned char * base64Digital = malloc(sizeof(char));
    int k = 0;
    int j = 0;
    int i = 0;
    while (text[k] != '\0') {
        base64Digital = realloc(base64Digital, (j+1)*sizeof(char));
        base64Digital[j] = 0;
        i = NBITS6;
        while (i >= 0) {
            base64Digital[j] += (text[k++] - ASCII_SHIFT)*pow(2,i--);
        }
        j++;
    }
    base64Digital = realloc(base64Digital, (j+1)*sizeof(char));
    base64Digital[j]='\0';
    free(text);
    return  base64Digital;
}
unsigned char * encodeBase64Text(unsigned char * text) {



    const unsigned char base64_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
                                '3', '4', '5', '6', '7', '8', '9', '+', '/'};
    unsigned char * encodedText = malloc(sizeof(char));
    unsigned char * binText;
    unsigned char * base64Digital;
    binText = toBin(text);
    base64Digital = encodeBase64Digital(binText);
    int j = 0;
    int k = 0;
    while (base64Digital[j] != '\0') {
        int i = 0;
        while (i<=63) {
            if (base64Digital[j] == i) {
                encodedText = realloc(encodedText, (k+1)*sizeof(char));
                encodedText[k++] = base64_table[i];
                break;
            }
            i++;
        }
        j++;
    }
    encodedText = realloc(encodedText, (k+1)*sizeof(char));
    encodedText[k]='\0';
    free(base64Digital);
    return encodedText;
}

unsigned char * toASC(unsigned char * text) {
    unsigned char * asciiText = malloc(sizeof(char));
    int i = 0;
    int k = 0;
    while (text[i] != '\0') {
        asciiText = realloc(asciiText, (k+1)*sizeof(char));
        asciiText[k] = 0;
        int j = NBITS8;
        while (j >= 0) {
            asciiText[k] += (text[i++] - ASCII_SHIFT) * pow(BIN_BASE, j--);
        }
        asciiText[k++] += ASCII_SHIFT;
    }
    asciiText = realloc(asciiText, (k+1)*sizeof(char));
    asciiText[k] = '\0';
    free(text);
    return asciiText;
}

unsigned char * copyText(unsigned char * text) {
    unsigned char * copiedText = malloc(sizeof(char));
    int i = 0;
    while (text[i]!='\0') {
        copiedText = realloc(copiedText, (i+1)*sizeof(char));
        copiedText[i] = text[i];
        i++;
    }
    copiedText = realloc(copiedText, (i+1)*sizeof(char));
    copiedText[i] = '\0';
    return copiedText;
    }

unsigned char * xorCrypt(unsigned char * text) {


    unsigned char * encodedText = malloc(sizeof(char));
    unsigned char * key;
    printf("Input encryption key\n");
    key = readLine();
    text = toBin(text);
    key = toBin(key);
    int i = 0;
    int j = 0;
    int k = 0;
    while (text[i]!='\0') {
        if (key[j] == '\0') {
            j = 0;
        }
        encodedText = realloc(encodedText, (k+1)*sizeof(char));
        encodedText[k++] = ((text[i++] - ASCII_SHIFT) ^ (key[j++] - ASCII_SHIFT)) + ASCII_SHIFT;
    }
    encodedText = realloc(encodedText, (k+1)*sizeof(char));
    encodedText[k] = '\0';
    free(text);
    free(key);
return encodedText;
}


int main()
{
    const char * actions = "Actions:\n(I)nput text\nUn(h)ex text\nTranslate text to (b)inary\n(E)ncode text into base64\n(O)utput\n(R)estore text\nXor (c)rypt\nHel(p)\nE(x)it\nWaiting for input...\n";
    unsigned char * original;
    unsigned char * text;
    char c = ' ';
    printf(actions);
    while((c = getchar()) != 'x') {
        switch (c) {
            case 'I':
            case 'i': {
            printf("input a text\n");
            text = readLine();
            original = copyText(text);
            PRINT(text);
            break;
            }
            case 'H':
            case 'h': {
            printf("decoding...\n");
            text = decodeHex(text);
            PRINT(text);
            getchar();
            break;
            }
            case 'B':
            case 'b': {
            printf("translating...\n");
            text = toBin(text);
            PRINT(text);
            getchar();
            break;
            }
            case 'E':
            case 'e': {
            printf("encoding...\n");
            text = encodeBase64Text(text);
            PRINT(text);
            getchar();
            break;
            }
            case 'R':
            case 'r': {
            text = copyText(original);
            PRINT(text);
            getchar();
            break;
            }
            case 'P':
            case 'p': {
            printf(actions);
            getchar();
            break;
            }
            case 'C':
            case 'c': {
            text = xorCrypt(text);
            text = toASC(text);
            PRINT(text);
            getchar();
            break;
            }
            default: {
                printf("No such option\n");
            }
        }
    }

    printf("Exiting...\n");
    return 0;
}
