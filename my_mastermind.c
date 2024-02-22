#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

char* my_read(){
    char* buf = malloc(sizeof(char)*5);
    int index = 0;
    int bytes_read = 0;
    char c;
    int size = sizeof(buf);
    while (index < size && (bytes_read = read(STDIN_FILENO, &c, 1)) > 0)
    {
    if (c == '\n') {
        break;
    }
    buf[index] = c;
    index ++;
    }
    buf[index] = '\0';
    return buf;
    free(buf);
}

int my_strlen(char* param_1){
 int len = 0;
  if(param_1 != 0)
  {
    while(*param_1 != '\0')
    {
      ++len;
      ++param_1;
    }
  }
  return len;
}


bool wrong_input(char* text) {
  if (my_strlen(text) !=4 && my_strlen(text) > 0) {
    printf("Wrong Input !\n");
    return true;
  }
  for(int i = 0; i < my_strlen(text) - 1; i++) {
    if(text[i] < '0' || text[i] > '9'){
      printf("Wrong Input !\n");
      return true;
    }
  }
  return false;
}
bool duplicate(char* text, char symbol) {
    int length = my_strlen(text);
    if (text == 0)
    return true;
    for (int i = 0; i < length; i++) {
        if (text[i] == symbol)
            return false;
    }
    return true;
}


int well_placed(char* text1, char* text2) {
    int good = 0;
    int length = strlen(text1);
    for (int k = 0; k < length; k++) {
        if (text1[k] == text2[k]) {
            good++;
        }
    }
    return good;
}

int misplaced(char* text1, char* text2) {
    int miss = 0;
    for (int j = 0; text1[j] != '\0'; j++) {
        if (!duplicate(text1, text2[j]) && text1[j] != text2[j]) {
            miss ++;
        }
    }
    return miss;
}

char* rando_digit() {
    char *digitnum = malloc(4);
    int dig = 0;
    srand(time(0));
    while (strlen(digitnum) < 4) {
        char m = rand() % 8 + '1';
        if (duplicate(digitnum, m))
            digitnum[dig++] = m;
    }
    return digitnum;
}

int main(int argc, char* argv[]){
    int round = 0;
    int round_max = 10;
    char* secret = malloc(4);
    if (argc == 3) {
        if (strcmp("-t", argv[1]) == 0) {
            round_max = atoi(argv[2]);
            secret = rando_digit();
        }
        if (strcmp("-c", argv[1]) == 0) {
            secret = argv[2];
        }
    }else {
        secret = rando_digit();
    }
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    while (round <= round_max) {
        printf("- - -\n Round %d\n >", round );
        char* user_guess = my_read();
        printf("%s, %d\n", user_guess, my_strlen(user_guess));
        if (user_guess == NULL) {
            return 0;
        }
        if(wrong_input(user_guess) == false) {  
            int g_inp = well_placed(secret, user_guess);
            int w_inp = misplaced(secret, user_guess);
            if (g_inp == 4) {
                printf("Congratz! You did it!\n");
                break;
            }else {
                printf("Well placed pieces: %d\n", g_inp);
                printf("Misplaced pieces: %d\n", w_inp);
            }
        }
        round++;
        if (round == 10) {

            printf("You lost the secret code was: %s\n", secret);
    }
    }
    return 0;
}
