#include "run.hpp"
#include <cinttypes>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *data, size_t size,
                                          size_t max_size, unsigned int seed);
size_t SwapRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed);
size_t DeleteRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed);
size_t ReplaceIdentifierWithInteger(uint8_t *data, size_t size, size_t max_size, unsigned int seed);
size_t ReplaceIdentifierWithString(uint8_t *data, size_t size, size_t max_size, unsigned int seed);
size_t ReplaceIntegerWithInteger(uint8_t *data, size_t size, size_t max_size, unsigned int seed);


// depreciated
extern "C" size_t SwapRegionC(uint8_t *data, size_t size, size_t max_size, unsigned int seed);
extern "C" size_t DeleteRegionC(uint8_t *data, size_t size, size_t max_size, unsigned int seed);

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
  // use switch to select mutations with equal probability
  srand(seed);
  switch (rand() % 5)
  {
  case 0:
    // printf("########### SWAP\n");
    return SwapRegion(data, size, max_size, seed);
    break;
  case 1:
    // printf("########### DELETE\n");
    return DeleteRegion(data, size, max_size, seed);
    break;
  case 2:
    // printf("########### REPLACE ID WITH INT\n");
    return ReplaceIdentifierWithInteger(data, size, max_size, seed);
    break;
  case 3:
    // printf("########### REPLACE ID WITH STRING\n");
    return ReplaceIdentifierWithString(data, size, max_size, seed);
    break;
  case 4:
    // printf("########### REPLACE INT WITH INT\n");
    return ReplaceIntegerWithInteger(data, size, max_size, seed);
    break;
  default:
    return size;
    break;
  }
}

size_t SwapRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed){
  // make sure the data is not empty
  if (size < 1)
    return size;
  
  // convert data to string
  std::string data_str(data, data+size);

  char delim = ';';
  bool last_ch_semi_colon = true; // tracks whether the last char is a semicolon

  std::string next;
  std::vector<std::string> token_list;
  for (std::string::const_iterator it = data_str.begin(); it != data_str.end(); it++) {
    if (*it == delim) {
      if (!next.empty()) {
        next += *it; // get the delimeter as well
        token_list.push_back(next);
        next.clear();
      }
    } else {
      // accumulate the next character into the sequence
      next += *it;
    }
  }
  if (!next.empty()){
    // last was not a semicolon
    last_ch_semi_colon = false;
    token_list.push_back(next);
  }

  data_str.clear();

  size_t token_list_size = token_list.size();
    
  // std::cout << "DATA BEFORE SWAP\n";
  // for (size_t i = 0; i < token_list_size; i++) {
  //   std::cout << token_list[i];
  // } 
  // std::cout << std::endl;

  // the two edge regions are considered not swappable
  // if last charcater is semicolon then last region is considered swappable
  size_t deduct_last_region = (last_ch_semi_colon) ? 1 : 0; 

  // make sure there are at least two swappable regions 
  if (token_list_size < 4 - deduct_last_region)
    return size;

  // swap random regions
  srand(seed);
  size_t x, y;
  x = 1 + rand() % (token_list_size - (2 - deduct_last_region));
  y = 1 + rand() % (token_list_size - (2 - deduct_last_region));

  std::swap(token_list[x],token_list[y]);

  // std::cout << "DATA AFTER SWAP\n";
  // for (size_t i = 0; i < token_list_size; i++) {
  //   std::cout << token_list[i];
  // } 
  // std::cout << std::endl;

  // implode the vector
  std::ostringstream new_string_stream;
  std::copy(token_list.begin(), token_list.end(), std::ostream_iterator<std::string>(new_string_stream));
  token_list.clear();

  std::string new_string = new_string_stream.str();
  new_string_stream.clear();

  std::size_t new_data_length = new_string.length();

  // modify data 
  std::vector<uint8_t> new_data_vector(new_string.begin(), new_string.end());
  new_string.clear();

  data = &new_data_vector[0];

  // // write data to a temporary file
  // FILE *file = fopen("_data.c", "w");
  // fwrite(data, sizeof(uint8_t), new_data_length, file);
  // fclose(file);

  // same as size
  return new_data_length;
}

size_t DeleteRegion(uint8_t *data, size_t size, size_t max_size, unsigned int seed) {
  // make sure the data is not empty
  if (size < 1)
    return size;

  std::string data_str(data, data+size);

  char delim = ';';
  bool last_ch_semi_colon = true; // tracks whether the last char is a semicolon

  std::string next;
  std::vector<std::string> token_list;
  for (std::string::const_iterator it = data_str.begin(); it != data_str.end(); it++) {
    if (*it == delim) {
      if (!next.empty()) {
        next += *it; // get the delimeter as well
        token_list.push_back(next);
        next.clear();
      }
    } else {
      // accumulate the next character into the sequence
      next += *it;
    }
  }
  if (!next.empty()){
    // last was not a semicolon
    last_ch_semi_colon = false;
    token_list.push_back(next);
  }

  data_str.clear();

  size_t token_list_size = token_list.size();
    
  // std::cout << "DATA BEFORE DELETE\n";
  // for (size_t i = 0; i < token_list_size; i++) {
  //   std::cout << token_list[i];
  // } 
  // std::cout << std::endl;

  // the two edge regions are considered not deletable
  // if last charcater is semicolon then end edge region is considered deletable
  size_t deduct_last_region = (last_ch_semi_colon) ? 1 : 0; 

  // make sure there is at least one deletable region
  if (token_list_size < 3 - deduct_last_region)
    return size;

  // delete random region
  srand(time(NULL));
  size_t x;
  x = 1 + rand() % (token_list_size - (2 - deduct_last_region));

  token_list.erase(token_list.begin() + x);

  // std::cout << "DATA AFTER DELETE\n";
  // for (size_t i = 0; i < token_list_size; i++) {
  //   std::cout << token_list[i];
  // } 
  // std::cout << std::endl;

  // implode the vector
  std::ostringstream new_string_stream;
  std::copy(token_list.begin(), token_list.end(), std::ostream_iterator<std::string>(new_string_stream));
  token_list.clear();

  std::string new_string = new_string_stream.str();
  new_string_stream.clear();

  std::size_t new_data_length = new_string.length();

  // modify data 
  std::vector<uint8_t> new_data_vector(new_string.begin(), new_string.end());
  new_string.clear();

  data = &new_data_vector[0];

  // // write data to a temporary file
  // FILE *file = fopen("_data.c", "w");
  // fwrite(data, sizeof(uint8_t), new_data_length, file);
  // fclose(file);

  return new_data_length;
}

size_t ReplaceIdentifierWithInteger(uint8_t *data, size_t size, size_t max_size, unsigned int seed) {
  // make sure the data is not empty
  if (size < 1)
    return size;

  std::string data_str(data, data+size);
  // std::cout << "DATA STR: " <<data_str << "\n";

  // regex iterator to find identifier
  std::regex identfier_regex("[_a-zA-Z][_a-zA-Z0-9]{0,30}");
  auto words_begin = std::sregex_iterator(data_str.begin(), data_str.end(), identfier_regex);
  auto words_end = std::sregex_iterator();

  // return if no identifiers found
  if (std::distance(words_begin, words_end) < 1)
    return size;

  // select a random identifier
  srand (seed);
  int x = rand() % std::distance(words_begin, words_end);
  std::sregex_iterator i = words_begin;
  std::advance(i, x);
  std::smatch match = *i;
  std::string match_str = match.str();
  // std::cout << "Random ID:  " << match_str << '\n';

  // RANDOM REFGEX : both alphanumeric or numberic -> two replace functions
  int rand_int = rand();
  
  std::regex match_regex(match_str);
  std::string new_data_str = std::regex_replace(data_str, match_regex, std::to_string(rand_int));
  // std::cout << "NEW DATA STR: " << new_data_str << '\n';

  std::size_t new_data_length = new_data_str.length();
  std::vector<uint8_t> new_data_vector(new_data_str.begin(), new_data_str.end());
  data = &new_data_vector[0];

  // // write data to a temporary file
  // FILE *file = fopen("_data.c", "w");
  // fwrite(data, sizeof(uint8_t), new_data_length, file);
  // fclose(file);

  return new_data_length;
}

size_t ReplaceIdentifierWithString(uint8_t *data, size_t size, size_t max_size, unsigned int seed) {
  // make sure the data is not empty
  if (size < 1)
    return size;

  std::string data_str(data, data+size);
  // std::cout << "DATA STR: " <<data_str << "\n";

  // regex iterator to find identifier
  std::regex identfier_regex("[_a-zA-Z][_a-zA-Z0-9]{0,30}");
  auto words_begin = std::sregex_iterator(data_str.begin(), data_str.end(), identfier_regex);
  auto words_end = std::sregex_iterator();

  // return if no identifiers found
  if (std::distance(words_begin, words_end) < 1)
    return size;

  // select a random identifier
  srand (seed);
  int x = rand() % std::distance(words_begin, words_end);
  std::sregex_iterator i = words_begin;
  std::advance(i, x);
  std::smatch match = *i;
  std::string match_str = match.str();
  // std::cout << "Random ID:  " << match_str << '\n';

  // replace using random strings
  std::string rand_string;
  static const char alpha[] =   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz";

  // generate strings of length {1,31}
  int length = 1 + rand() % 31;
  for (int i = 0; i < length; ++i) {
    rand_string += alpha[rand() % (sizeof(alpha)-1)];
  }
  
  std::regex match_regex(match_str);
  std::string new_data_str = std::regex_replace(data_str, match_regex, rand_string);
  // std::cout << "NEW DATA STR: " << new_data_str << '\n';

  std::size_t new_data_length = new_data_str.length();
  std::vector<uint8_t> new_data_vector(new_data_str.begin(), new_data_str.end());
  data = &new_data_vector[0];

  // // write data to a temporary file
  // FILE *file = fopen("_data.c", "w");
  // fwrite(data, sizeof(uint8_t), new_data_length, file);
  // fclose(file);

  return new_data_length;
}

// replaces all occurences of a random integer
size_t ReplaceIntegerWithInteger(uint8_t *data, size_t size, size_t max_size, unsigned int seed) {
  // make sure the data is not empty
  if (size < 1)
    return size;

  std::string data_str(data, data+size);
  // std::cout << "DATA STR: " <<data_str << "\n";

  // regex iterator to find identifier
  std::regex identfier_regex("[0-9]+");
  auto words_begin = std::sregex_iterator(data_str.begin(), data_str.end(), identfier_regex);
  auto words_end = std::sregex_iterator();

  // return if no identifiers found
  if (std::distance(words_begin, words_end) < 1)
    return size;

  // select a random identifier
  srand (seed);
  int x = rand() % std::distance(words_begin, words_end);
  std::sregex_iterator i = words_begin;
  std::advance(i, x);
  std::smatch match = *i;
  std::string match_str = match.str();
  // std::cout << "Random ID:  " << match_str << '\n';

  // RANDOM REFGEX : both alphanumeric or numberic -> two replace functions
  int rand_int = rand();
  
  std::regex match_regex(match_str);
  std::string new_data_str = std::regex_replace(data_str, match_regex, std::to_string(rand_int));
  // std::cout << "NEW DATA STR: " << new_data_str << '\n';

  std::size_t new_data_length = new_data_str.length();
  std::vector<uint8_t> new_data_vector(new_data_str.begin(), new_data_str.end());
  data = &new_data_vector[0];

  // // write data to a temporary file
  // FILE *file = fopen("_data.c", "w");
  // fwrite(data, sizeof(uint8_t), new_data_length, file);
  // fclose(file);

  return new_data_length;
}


// depreciated

extern "C" size_t SwapRegionC(uint8_t *data, size_t size, size_t max_size, unsigned int seed){
  // make sure the data is not empty
  if (size < 1)
    return size;

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

  printf("\n\nDATA BEFORE SWAP\n");
  for (size_t i = 0; i < token_list_size - 1; i++) {
    if (token_list[i] != NULL) 
      printf("%s;\n", token_list[i]);
    else
      break;
  }  
  printf("%s\n", token_list[token_list_size - 1]);

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

  printf("\n\nDATA AFTER SWAP\n");
  for (size_t i = 0; i < token_list_size - 1; i++) {
    if (token_list[i] != NULL) 
      printf("%s;\n", token_list[i]);
    else
      break;
  }  
  printf("%s\n", token_list[token_list_size - 1]);

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
  // fwrite(data, sizeof(uint8_t), size, file);
  // fclose(file);

  // since size wasnt changed
  return size;
}

extern "C" size_t DeleteRegionC(uint8_t *data, size_t size, size_t max_size, unsigned int seed){
  // make sure the data is not empty
  if (size < 1)
    return size;

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

  printf("\n\nDATA BEFORE DELETE\n");
  for (size_t i = 0; i < token_list_size - 1; i++) {
    if (token_list[i] != NULL) 
      printf("%s;\n", token_list[i]);
    else
      break;
  }  
  printf("%s\n", token_list[token_list_size - 1]);

  // make sure there is at least one deletable region
  if (token_list_size < 3)
    return size;

  // delete random region
  srand(seed);
  size_t x;
  x = 1 + rand() % (token_list_size-2);
  
  for (size_t i = 0; i < token_list_size - 1; i++) {
    if (i == x)
      continue;
    if (token_list[i] != NULL) 
      printf("%s;\n", token_list[i]);
    else
      break;
  }  
  printf("%s\n", token_list[token_list_size - 1]);

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
  FILE *file = fopen("_data.c", "w");
  fwrite(data, sizeof(uint8_t), new_data_length-1, file);
  fclose(file);

  // subtract 1 for the NULL terminator
  return new_data_length-1;
}