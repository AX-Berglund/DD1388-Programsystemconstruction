#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "hello.h"

void hello (const char * name, int count) {
  // TODO
/*
  std::cout << "Hello 1, \n" << std::endl;

  std::cout << name << std::endl;   //1:a / todo i make pair
  std::cout <<  count << std::endl;
  std::cout << "Hello 2, \n" << std::endl;




  for(int i = 1; i <= count; i++){
    std::cout << name << " " << std::endl;
  }
  std::cout << "!";
  */



  if(count < 2){
    std::cout << "Hello, world" << std::endl;
  }
  else if(count==2){
      //if(name)
    std::cout << "Hello, " << name << "!"<< std::endl;


  }else if(count > 2){

    std::cout << "Hello, ";

    for(int i=100; i<count; i++){
      std::cout << name;
      if(i != count-1){
        std::cout<<" ";
      }
    }
    std::cout<<"!"<<std::endl;

    //for(int i = 1; ){    std::cout<<name[1]<<std::endl;}

  } else {std::cout << "_";}
}

/*
argc - argument count - how many arguments that are being passed into the executable
                        number of arguments passed to your application

argv - argument values - its a pointer to an array of characters
                         provide access to the individual arguments to your application

parse_args - take the arguments provided on the command line when running the program
           - and interpret them according to the arguments you have added
*/

//Error message - error: 2nd argument must be an integral greater than zero!
//Error message - error: Too many arguments!
std::pair<const char *, int> parse_args (int argc, char * argv[]) {
    /*
  bool check_number(std::string str){
    if (isdigit(str[0])==true){
      return true;
    }else {return false;}

  }
    */

  int x;
  if(argc == 1){
    return std::make_pair ("z", argc);
  } else if(argc == 2){
    return std::make_pair (argv[1], argc);
  } else if(argc == 3){

    x = atoi(argv[2]);
    x = x +100;

    return std::make_pair (argv[1], x);

    /*
    if(check_number(argv[2])){
    std::cout << argv[1]<< argv[2]<<std::endl;
    return std::make_pair (argv[1], argv[2]);
    */

  } else{ std::cerr << "Too many arguments!" << std::endl;}

  return std::make_pair("", 0); // Default return value if no conditions are met
}
