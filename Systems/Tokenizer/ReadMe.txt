

Assignment 0
Systems Programming
Sahaj Kohli

*Separate words are considered tokens by my program

Main Method
The main method is basically just used to pass in arguments taken from the command line to the getWords methods which is explained later. It also has a check to make sure there were arguments that were entered, it does this by checking the argc. The struct is also malloc here to dynamically allocate memory for the different parts of it. Later when both getWords and setWords are done processing there is a for loop that actually will loop through the sorted array and print the items. It will return 0 if all is well

Struct
The struct is used to store things that I will need to run the program well. There is a char** array that will be used to store the words. I decided to use an array because it allowed me to very easily sort it using sortWords Selection Sort algorithm (run time discussed there). There are also two ints that have which are used to keep count of how many bytes the array needs to be dynamically allocated and another to count how many words there are in total. The struct dynamically allocated so that these items are available throughout the program and so that I can keep track of them. 

getWords
This is the longest bit of code here. It used the number of bytes in the argument passed to dynamically allocate that much space for the array in the struct. Then using is alpha the program will check if the char is a alphabetic character or something else. anything that is not a char will be thrown out, even if its is between a string. If a non-char is in between a accurate word or separate words the method will then separate them. So hel%lo will not be “hello” it will be “hel” and “lo.” I thought this was the best way to deal with this. There is a special case which is mentioned in the Mentions section. The method then calls upon the sortWords when all the words have been tokenized into the array.

sortWords
I used selection sort to  sort the tokens in the array. I thought that since I have o(1) access to all of the things it might be easier but turns out that having a linked list would’’ve been the same time of access in this case since we are linearly going through it. But, it does provide a easier method of moving the sorted part up by just increasing the first for loops counter by one each time something is placed in the sorted section. This implementation has a worst run time of o(n^2) which is really bad. But, seeing as how I’m not going to be sorting more 100 words it doesn’t worry me too bad. Although something like merge sort (Worst running time of nlogn) would be a better implementation it is far to complicated and uneseccary for this application. The method ends when everything is sorted and passed control back to the main method

Mentions
I should mention there are 2 special test cases that are a bit odd. The first being:
2233 234234 234
where the program will return no array back or nothing because no valid arguments were passed. I could display an error for this but I choose not to because i actually like that it returns nothing because the user has to be smart enough to not enter something that bad. The array list actually does come back with a length of, I actually have a print statement in the main method warning the user that this has happen but its commented out because its not a valid thing.

The other situation is something thats already been mentioned about how tokens are separated when there is a non char in between them, I mentioned how it will split a string up into two if there is a non char in between them.



TESTING
These are some of my test cases (I did do more but I did not list)


3hello @im %sahaj
hello @im sahaj
hello im sahaj
hello im#sahaj
2321 343 34234 *See Mentions
Hello hello
Hello hello Sahaj
Hello hello Sahaj sahaj
abu%dj Sahaj #here Today1now
Abe Apples Arthur able apple arthur art
