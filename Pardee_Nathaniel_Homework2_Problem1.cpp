`/*\
    Programmer: Nathaniel Pardee
    ID: W89275

    Problem:I n a 3x3 array using a loop print characters (not integers) of 1-9. Now write function to ask
        user to input (‘X’ or ‘O’) in each of the selected position 1-9 in the array. If the user selects X in
        one of the positions then it would be O in the next selection and print the 3x3 array in each of the
        total 9 insertions. No repetition in any position is allowed.

        Plan: create a 2D array where const numColumns = 3 and const numRows = 3.
                -use a for loop to print characters 1-9 to fill the array
                -create a function to prompt the user to type X or O in any position of the array.
                -if the user selects X then the next input option will be O. After the user selects the position, print the array
                -example. If user selects X at position 5, place X at array[1][1] and print arr;
                -functions: function to take in input;
                                function to print the array after each use;
        -----------------------------------------------------------------------------------------------------------------------------
		  UPDATE 01/04/2025
		  
		  I opened this file to look for a certain way we did something involving pointers during school. After looking at the code, I found that it was a little jumbled and wanted to refactor and optimize what I had written. Also, the program didn't work as inteded so I thought it would be fun to challenge myself. I also wanted a refresher/more practice with pointers since we didn't do much with them in school and they are highly beneficial. I also thought it would be good to practice writing wrapper functions. Anywho, I forgot what the original intention (aside from what the problem states) was for this program originally. This is turning out to be the basis for a possible tic tac toe project? who knows. It's fun and this has definitely evolved from what it was. If only I had saved a copy of my previous work to compare after.

		  01/05/25

		  Ending my progress for the night. almost done, I just have to fix the output and add a couple of try/catches in to cover odd cases of improepr input.


*/

#include <iostream>


//declare constant globals
const int COLUMNS = 3;
const int ROWS = 3;

//game setup
char** createArray();
char** populateArray(char** arrPtr);
void arrayCreationAndCleanup();
void printRules();

//input functions
void userSelection(char** arrPtr);;
void insertUserSelection(char** arrPtr, char userPosition, char letterChoice);

//validation functions
bool isSpotTaken(char** arr, char userPosition);
bool isValidLetter(char userInput);
bool isOppositeLetter(char current, char previous);
bool isValidLetterAndOppLetterTrue(char current, char previous);

int main()
{
	printRules();
	arrayCreationAndCleanup();
	 return 0;
}

//allocates memory on heap for array
char** createArray()
{
	 char** arrayPtr = new char*[ROWS];

	 for(int i = 0; i < ROWS;i++)
	 {
		  arrayPtr[i] = new char[COLUMNS];
	 }

	 return arrayPtr;
}

//initializes rows and columns to be character nums 1-9
char** initializeArray(char** arrPtr){
	
	char number = '1';
  
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLUMNS; j++)
		{
			arrPtr[i][j] = number;
			std::cout << arrPtr[i][j] << " ";
			number++;
		}

		std::cout << std::endl;
	}
	return arrPtr;
}

//wrapper function to deallocate heap memory used by pointer
void arrayCreationAndCleanup()
{
	 char** arrayPtr = createArray();
	 initializeArray(arrayPtr);
	 userSelection(arrayPtr);

	 for(int i = 0; i < ROWS; i++){
		  delete[] arrayPtr[i];
	 }
	 delete[] arrayPtr;
}

void printRules(){
    std::cout << "Please enter an X or an O and what position you want to place it." << std::endl;
    std::cout << "Whichever letter you select first, you must do the opposite letter after. " << std::endl;
}

//function to prompt user to enter their choices
void userSelection(char** arr)
{
    char currentLetter = '\0';
    char previousLetter = '\0';
    char position;
	int loopIterator = 0;

	while(loopIterator < 9){

	 //prompt user to enter the letter
		std::cout << "Enter Letter: " << std::endl;
		std::cin >> currentLetter;
		std::cout << "Enter position number from 1 through 9 " << std::endl;
		std::cin >> position;
		
		if(isValidLetterAndOppLetterTrue(currentLetter,previousLetter) && !isSpotTaken(arr,position)){
			
			//set previous letter equal to current to check after first iteration
			previousLetter = currentLetter;		
			insertUserSelection(arr, position, currentLetter);			
			loopIterator++;
		}
		//output statement to keep track of iteration
		std::cout << "loop count " << loopIterator<< ": \n\n";
	}
}

void insertUserSelection(char** arrPtr, char userPosition, char userLetterChoice)
{
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLUMNS; j++){	

			if(arrPtr[i][j]==userPosition){			
				arrPtr[i][j] = userLetterChoice;
				std::cout << userLetterChoice << " ";
		 	 }else{
				std::cout << arrPtr[i][j] << " ";
			 }			
		}									
				std::cout << std::endl;
	}
}

bool isSpotTaken(char** arr, char userPosition)
{
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j<COLUMNS;j++){
			if(arr[i][j] == userPosition)
			{
				return false;
			}
		}
	}
	std::cout << "Spot already taken.\n";
	return true;
}

//validate correct input
bool isValidLetter(char userInput)
{
	if(userInput == 'X' || userInput == 'O')
	{
		return true;
	}
	else
	{
		std::cout << "Please Enter either an X or an O" << std::endl;
		return false;		
	}
}
//compare previous input to current input
bool isOppositeLetter(char current, char previous)
{
	if(current == previous)
	{
		std::cout << "Letter must not be same as previous letter." << std::endl;
		return false;
	}
	else{
		return true;
	}

}

//wrapper fn to return true if both previous check functions are true
bool isValidLetterAndOppLetterTrue(char current, char previous)
{
	 if(isValidLetter(current) && isOppositeLetter(current,previous)){
		return true;
	 }else{
		  return false;
	 }
}

