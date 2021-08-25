#include "run.hpp"
#include <cinttypes>
#include <cstddef>
#include <cstdio>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *data, size_t size,
                                          size_t max_size, unsigned int seed);
extern "C" size_t SwapRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed);
extern "C" size_t DeleteRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed);
extern "C" size_t Replace(uint8_t *data, size_t size, size_t max_size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char* input_file = "_temp.c";
  const char* args[] = { "c-to-mips", input_file, "-o", "_temp.mps", "-c" };

  // TODO: write `size` bytes of `data` to a file named `input_file`,
  FILE *file = fopen(input_file, "w");
  fwrite(data, sizeof(uint8_t), size, file);
  fclose(file);

  //  then invoke the `run` method of the compile with `args`
  run(5, args);

  return 0;
}

extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *data, size_t size,
                                          size_t max_size, unsigned int seed) {
  // use random switch to select which one
  // return SwapRegion(data, size, max_size, seed);
  return DeleteRegion(data, size, max_size, seed);
}

extern "C" size_t SwapRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed){
  char data_char[size+1];
  for(int i =0; i < size; i++){
      sprintf (&data_char[i], "%c", (char)data[i]);
  }
  char* token;
  const char* delim = ";";
  
  // get the number of ; separetd regions(tokens) in data
  size_t token_list_size = 0;
  char *ptr = data_char;
  while((ptr = strstr(ptr, delim)) != NULL) {
    token_list_size++;
    ptr++;
  } 
  token_list_size++; // for the starting region
  free(ptr);

  // make sure there are at least two swappable regions 
  if (token_list_size < 4)
    return size;

  // add the tokens to an array
  char* token_list[token_list_size];
  token = strtok(data_char, delim);
  int counter = 0;
  while(token != NULL) {
    token_list[counter++] = token;
    token = strtok(NULL, delim);
  }

  // printf("\n\nDATA BEFORE SWAP\n");
  // for (size_t i = 0; i < token_list_size - 1; i++) {
  //   if (token_list[i] != NULL) 
  //     printf("%s;\n", token_list[i]);
  //   else
  //     break;
  // }  
  // printf("%s\n", token_list[token_list_size - 1]);

  // swap random regions
  srand(seed);
  size_t x, y;
  x = 1 + rand() % (token_list_size-2);
  y = 1 + rand() % (token_list_size-2);
  while (x==y)
    y = rand() % token_list_size;
      
  char *temp = token_list[x];
  token_list[x] = token_list[y];
  token_list[y] = temp;

  // printf("\n\nDATA AFTER SWAP\n");
  // for (size_t i = 0; i < token_list_size - 1; i++) {
  //   if (token_list[i] != NULL) 
  //     printf("%s;\n", token_list[i]);
  //   else
  //     break;
  // }  
  // printf("%s\n", token_list[token_list_size - 1]);

  // join the regions to a single string
  char* new_data = NULL;
  size_t new_data_size = size + 1; // add 1 for the NULL terminator

  new_data = (char*) malloc(new_data_size);
  new_data[0] = '\0';
  for (size_t i = 0; i < token_list_size - 1; i++) {
      strcat(new_data, token_list[i]);
      strcat(new_data, delim);
  } 
  strcat(new_data, token_list[token_list_size - 1]);

  // replace data with the new string
  data = (uint8_t*)new_data;

  // write data to a temporary file
  // FILE *file = fopen("_data.c", "w");
  // fwrite(data, sizeof(__uint8_t), size, file);
  // fclose(file);

  // since size wasnt changed
  return size;
}

extern "C" size_t DeleteRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed){
  char data_char[size+1];
  for(int i =0; i < size; i++){
      sprintf (&data_char[i], "%c", (char)data[i]);
  }
  char* token;
  const char* delim = ";";
  
  // get the number of ; separetd regions(tokens) in data
  size_t token_list_size = 0;
  char *ptr = data_char;
  while((ptr = strstr(ptr, delim)) != NULL) {
    token_list_size++;
    ptr++;
  } 
  token_list_size++; 
  free(ptr);
  
  // add the tokens to an array
  char* token_list[token_list_size];
  token = strtok(data_char, delim);
  int counter = 0;
  while(token != NULL) {
    token_list[counter++] = token;
    token = strtok(NULL, delim);
  }

  // printf("\n\nDATA BEFORE DELETE\n");
  // for (size_t i = 0; i < token_list_size - 1; i++) {
  //   if (token_list[i] != NULL) 
  //     printf("%s;\n", token_list[i]);
  //   else
  //     break;
  // }  
  // printf("%s\n", token_list[token_list_size - 1]);

  // make sure there is at least one deletable region
  if (token_list_size < 3)
    return size;

  // delete random region
  srand(seed);
  size_t x;
  x = 1 + rand() % (token_list_size-2);
  
  // for (size_t i = 0; i < token_list_size - 1; i++) {
  //   if (i == x)
  //     continue;
  //   if (token_list[i] != NULL) 
  //     printf("%s;\n", token_list[i]);
  //   else
  //     break;
  // }  
  // printf("%s\n", token_list[token_list_size - 1]);

  // join the regions to a single string
  char* new_data = NULL;
  // subtract the token + delimeter size, and add 1 for the NULL terminator
  size_t new_data_length = size - (strlen(token_list[x]) + 1) + 1; 
  
  new_data = (char*) malloc(new_data_length);
  new_data[0] = '\0';
  for (size_t i = 0; i < token_list_size-1; i++) {
    if (i == x)
      continue;
    strcat(new_data, token_list[i]);
    strcat(new_data, delim);
  }
  strcat(new_data, token_list[token_list_size-1]);

  // replace data with the new string
  data = (uint8_t*)new_data;

  // write data to a temporary file
  // FILE *file = fopen("_data.c", "w");
  // fwrite(data, sizeof(__uint8_t), new_data_length-1, file);
  // fclose(file);

  // subtract 1 for the NULL terminator
  return new_data_length-1;
}