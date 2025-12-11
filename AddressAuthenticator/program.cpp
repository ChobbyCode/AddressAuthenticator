
#include <iostream>

using namespace std;

int monthsLengths[12] = { 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

char date[30];

int day = 0;
int month = 0;
int year = 0;


// Here we define all the functions and sub routines we think we will need during the course of the program
int main(); // Entry Point Of The Application

// Date Validation
// To Have A Valid Date It Needs To Check A Few Boxes:
// - Exactly Be 10 Characters Long
// - The / are in the 2nd and 5th space respectively
// - It only contains numbers
// - The months, and days match properly
// It is a good idea to write out the goals of what you need, then write out the methods you think you'll need,
// you can see that I've already predefined the methods, below, before I've written what they actually do.

// All Methods Relevent To Validating The Date Are Below:
bool validateDate(); // This method will be the entry point of the validating for the date variable. It runs when we want to begin the validation of the date
bool lengthCheck(); // This returns true if the date is the correct length, and false if it is bad!
bool typeCheck(); // Also A Format Check | Makes sure the / are in the correct place and everything else is numbers
void parseData(); // This will parse the date, and convert the text into int variables stored in the day, month, year in the Date struct, this is so we can do size checks on it
bool sizeCheck(); // This will check that the month is between 1 and 12, the days are relevant to the month etc
bool februaryCheck(); // I decided to do the code for checking for february in a seperate sub routine to make it easier to read


// Main method can mostly be ignored, just know the date the user inputed is stored in date variable
// go to validateDate function to see code
int main() {
	// While True, So The Program Runs Forever, Until The Close Button Is Pressed
	while (true) {
		cout << "Enter a date in the format DD/MM/YYYY: ";
		cin.getline(date, sizeof(date));
		validateDate(); // START VALIDATION
	}
}

// Validate Date Methods Code:

bool validateDate() {
	// Remember! All The Validation Checks Return True If They Are Successful, And False If They Aren't. 
	// We Can Use True & False Conditions Directly In If Statements So We Don't Need To Check If It == 
	// lengthCheck() returns true if it succeeds:
	// if (lengthCheck()) is the same as if (lengthCheck() == true)
	if (lengthCheck()) {
		// This Code Runs If The Length Check Was Successful

		// Next We Need To Do The Type/Format Check
		if (typeCheck()) {
			// This bit will be different.
			// Now we verified that the numbers are in the correct place, we can safely convert it to numbers
			// If we didn't do the checks that it is a number before, it would potentially throw an error & crash
			// if we tried to convert a letter to a integer.
			// We will use the parseData function to house the code to convert the date;
			parseData();
			// Note we don't put this in an if statement as it has the return type of void, so it returns no usable
			// information, and we aren't doing any of our checks with it.
			// Now we've done this, we should have numbers in the day, month, and year variable.

			// The program can take two paths now. This is because we decided to house the code to check for
			// february dates in a seperate method, so if it is february we must then run the february code.

			// Fortuantly, the parseData method put it in the month variable, so if month == 2 then its february
			if (month == 2) {
				// Run This Code If It's Feb
				if (februaryCheck()) {
					// If the code gets here, it passed all the checks
					return true; // return true for success 
				}
				else {
					cout << "Failed February Check! If It's A Leap Year Max Days Are 29, And If It's Not Then It's 28!";
					return false; // return false as it failed
				}
			}
			else {
				// Run This Code If It's Not Feb
				if (sizeCheck()) {
					// If the code gets here, it passed all the checks
					return true; // return true for success
				}
				else {
					cout << "Failed Size Check! Please Make Sure The Month Is Valid & The Days In That Month Are Valid As Well!";
					return false; // return false as it failed
				}
			}
		}
		else {
			cout << "Type Check Failed! Please Make Sure The Date Is In The Format DD/MM/YYYY, & Has The /'s In The Correct Position, And Only Contains Numbers!";
			return false; // return false as it failed
		}
	}
	else {
		// If The Check Fails We Need To Display An Error Message!
		cout << "Length Check Failed! Please Make Sure The Date Is Exactly 10 Characters Long!";
		return false; // return false as it failed
	}
}
bool lengthCheck() {
	// Remember the date is stored in the date char array. 
	// To access that variable it is: date;

	// Pretty Self Explanatory
	if (strlen(date) == 10) {
		return true; // success
	}
	else {
		return false; // failed
	}
}
bool typeCheck() {
	// There's Two Ways We Could Do This. I'm Going To Do The Way Which I Did Originally In College.
	// My Method Works By: 
	// 1) First Check That The / are in the 2nd and 5th spot of the date as it is DD/MM/YYYY. Remember its 2nd & 5th spot as arrays start at 0
	// Then we could go if date[0] is number then and if date[1] is number then and if date[3] is number then...
	// HOWEVER, this is very slow, inefficient, and would likely get you marked down A LOT on your course work, so we should avoid it!
	// A better way is to use a for loop!
	// We can loop through every character in the date and make sure it's a number with the isdigit command!
	// However, if we just used a for loop it would also check the spots where the forward slashes are supposed to be
	// So, we need to have an if statement to only do the isdigit if it's not the 2nd or 5th character.
	// Are you following so far?
	// I Will Write The Code Out In Full Below:

	// Note: Remember to use '' when comparing chars as "" is for strings
	if (date[2] == '/' && date[5] == '/') {
		// now loop through each character
		// the for loop only goes up to 10 as the size of the date is 10! 
		for (int i = 0; i < 10; i++) {
			// Now Check That We Aren't Looking At Digit 2 or Digit 5
			// Try and remove this extra if statement to see what happens! It will always fail
			if (i != 2 && i != 5) {
				// remember isdigit returns a 0 if it fails, so by checking if it's not a zero, thats practically saying if it doesnt fail
				if (isdigit(date[i]) != 0) {
					// all good we can continue
					continue;
				}
				else {
					// Failed! isdigit returned 0 meaning it wasn't a number so return false
					return false;
				}
			} 
		}
	}
	else {
		// 5th or 2nd character weren't / so immedietly fails
		return false;
	}
}
void parseData() {
	// The next thing to do will be to parse the date from being text in a char array into numbers which we can do math on
	// To do this we will make some temporary variables
	char tmpDay[3];
	char tmpMnth[3];
	char tmpYear[5];

	// Next we will use string copy to copy part of the date array into the new arrays we have here.
	// This bit will be hard to explain in works, so I may use excalidraw to explain it in full.
	// First we need to know how the strncpy command works
	// strncpy(destination, source + offset, size)
	// Its a lil hard to explain, so lets do it for day and month first

	// NOTE: You need the _s on the end as this stands for safe and is used by Windows blah blah blah idk basically it can break if u dont use _s
	strncpy_s(tmpDay, sizeof(tmpDay), date + 0, 2);
	// What does this mean! It's saying we are going to put what we copy into the tmpDay variable.
	// and we are going to copy from the variable date! now what does + 0 mean? well this is the offset.
	// So the date format is DD/MM/YYYY. Because the offset is 0 it means we start from the start, but if we put it as 3,
	// it would mean we'd start at the start of the month (MM). A visual diagram would better explain this
	strncpy_s(tmpMnth, sizeof(tmpMnth), date + 3, 2);
	strncpy_s(tmpYear, sizeof(tmpYear), date + 6, 4);

	// The individual dates are now started in those temporary variables. 
	// Quick fire 1.4 revision. the tmpDay etc are local variables meaning their scope can only be accessed within this sub routine.
	// Their life time: they only exist within this method, and as soon as this method ends the varaibles are discarded. 

	// Next Convert The Temp Variables Into The Int Day Month & Year!
	sscanf_s(tmpDay, "%d", &day);
	sscanf_s(tmpMnth, "%d", &month);
	sscanf_s(tmpYear, "%d", &year);
	// We Can Now Do Math On The Variables 
}
bool sizeCheck() {
	// This is the check to make sure the months are proper & days are within correct range.
	// First check that months are between 1 & 12
	// This is done by saying month is bigger than 0 and less than 13
	if (month > 0 && month < 13) {
		// The next easy to check is to make sure day is bigger than 0 as you can't have day 0
		if (day > 0) {
			// Now it gets complicated, well not really.
			// At the top of the file you will see an array called monthLengths and it will be 12 units long. 
			// 12 because there are 12 months. It will have all the lengths of the months defined it it, except feb which is -1 as we do the
			// checks for february in the next method.

			// We can read the length of the month from the array simply like this
			// monthsLengths[month - 1] 
			// Note that we are using -1 because arrays are 0 based index, not 1 based index, meaning we start counting months from 1 but the array
			// does it from 0. to equate for this we do -1.
			if (day < monthsLengths[month - 1] + 1) {
				// One extra thing to note is that we are adding monthsLength + 1 this is because otherwise we'd be say for January:
				// day < 31. and if we had the date 31/01/25 it would return false as less than is not inclusive.
				// we could solve this by doing <= which is inclusive, or we could just add one to the max size, and instead do:
				// day < 32. which would be valid
				// success
				return true;
			}
			else {
				cout << "Days in month " << month << " only go up to " << monthsLengths[month - 1] << endl;
				return false;
			}
		}
		else {
			cout << "Can't have day as 0!";
			return false;
		}
	}
	else {
		cout << "Month was not valid! please enter a month between 1 and 12!";
		return false;
	}
}
bool februaryCheck() {
	// Now the last method of them all is to check february.
	// February has 29 days during a leap year and 28 in the boring years. 
	// we can use modular to calculate this. 
	// Year Mod 4. This gets the remainder of the math. 
	// lets say we have the year 4, and we divide it by 4, the remainder is 0, so it returns 0.
	// likewise if we have year 3, and we divide by 4, our remainder is 3.
	// so if the remainder is 0 it tells us it is a leap year.
	// NOTE! This is not how proper leap years are calculated, and their is some problems with this,
	// however this is good enough for now, as testing for real leap years is much more complicated

	// to use modular in C++ it is the percent (%) symbol.
	if (year % 4 == 0) {
		// Leap year
		if (day < 30) {
			return true;
			// 30, as 29 + 1, < is not inclusive, read reason in sizeCheck method if unsure
		}
		else {
			return false;
		}
	}
	else {
		// Not Leap Year
		if (day < 29) {
			return true;
			// 29, as 28 + 1, < is not inclusive, read reason in sizeCheck method if unsure
		}
		else {
			return false;
		}
	}
}
