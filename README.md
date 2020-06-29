Note: Original README submitted for evaluation.

        RAILWAY MANAGEMENT SYSTEM

Specifics:

1. Code has been made with C programming language.
2. C language standard used is C99.
3. GCC (GNU COMPILER COLLECTION) has been used to compile the project.
4. The code has been run and complied with the following gcc version:
   gcc (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609

NOTE [Very important]: Please make sure that the necessary files mentioned below are in the same directory as the main executable/C program file.


Description of how to run the code and observe the output: 


1. The necessary input files are PNR_COUNTER.txt, TRAIN_DETAILS.txt, TICKET_RECORD.txt

PNR_COUNTER.txt: This text file contains the latest value of the PNR number. When a new booking is made, the value in PNR_COUNTER.txt file is incremented by 1. This file only holds one integer value to be read during run-time in case of a booking. 

TRAIN_DETAILS.txt: This text file contains the list of available trains which are plying from DELHI. For each train, the text file contains the source of the train, the destination of the train, the number of seats left in the train, the train number and the price. The information mentioned above has been printed on the text file due to fields available in the structure used in the main program. In case of a booking, the function in the program edits the TRAIN_DETAILS.txt file by creating a temporary file and decrementing the number of seats in the required train by one. The new values and the other old entries are written to the temporary file, and the temporary file is renamed to TRAIN_DETAILS.txt while the original file itself is deleted. In case of a cancellation, the method mentioned above is adopted, except the fact that the value of the number of seats left for the particular train entry is incremented to reflect the cancellation.

TICKET_RECORD.txt: This text file contains the record of tickets booked. For each ticket, this text file stores the name of the passenger, the PNR number and the train number. When a new booking is made, the PNR_COUNTER.txt file is parsed, and a new entry is made in TICKET_RECORD.txt. When a cancellation is made, a temporary file is created in which all the entries are made except the one that is being cancelled. The duplicate text file itself is renamed to TICKET_RECORD.txt while the original file is deleted. The PNR_COUNTER.txt file does not decrement its value for obvious reasons.   

NOTE: Since the above files are being edited in text mode, the administrator can add a new train entry without any hassle. The administrator can also add new ticket entries in TICKET_RECORD.txt if they are cautious and increment the value in PNR_COUNTER.txt without fail.

2. When the user runs the executable file with gcc, they are greeted with a menu homepage screen which lists out 4 available options in relation to train bookings and enquiry. The user also has an option to exit the program itself. The 4 available options are booking, enquiry, cancellation and booking status. There is a prompt in the page which asks the user to enter numbers between 0-4 corresponding to his desire.

3. If the user chooses the booking option by pressing 1, they are led to the booking window. This booking window immediately prompts the user to enter the source and destination of the train. The logic adopted by the program is that, from this point, the booking function only proceeds to the next step, if the source and destination are present in TRAIN_DETAILS.txt(this is obtained by parsing the txt file for the required entry). Once the program finds a matching train entry to the user's needs, the program proceeds to prompt the user to enter their name. After entering their name, the user is greeted with a confirmation message which provides details of the booking, i.e. name, source of the train, the destination of the train, train number and price of the ticket. Below the confirmation, the user is prompted to a yes or no question(Y/N) if they want to go back to the homepage menu. If the user answers 'N', they will exit the program. On entering 'Y', the user is then led to the homepage menu.

4. If the user chooses the enquiry menu by pressing 2, they are led to the enquiry window. This part of the program serves the purpose of providing the user about the availability of seats in his desired train and the price of the journey. Once the enquiry window is on the screen, the user is prompted to enter the source and destination of his journey. If the source and destination match an entry on the TRAIN_DETAILS.txt file(by parsing), the user is then informed about the number of seats left in the train and the price of the ticket. If the user's source and destination do not match with any entry on the txt file, the user is informed about the limitations of the trains available. If the user finds the necessary information about the required train successfully, they are prompted with a yes or no question(Y/N) if they want to go back to the homepage menu. If the user answers 'N', they will exit the program. On entering 'Y', the user is then led to the homepage menu.

5. If the user chooses the cancellation menu by pressing 3, they are led to the cancellation window. The user is then prompted to enter his name and PNR number. These values are then parsed against the entries in TICKET_RECORD.txt. If a match is found, the user's ticket is cancelled, and they are informed about the refund amount, i.e. 50% cancellation charges. The program also increments the number of seats in TRAIN_DETAILS.txt for the user's train by using the duplicate file method(new and old values are written to a duplicate file while the original file itself is deleted). On successful cancellation of the ticket, the user is prompted with a yes or no question(Y/N) if they want to go back to the homepage menu. If the user answers 'N', they will exit the program. On entering 'Y', the user is then led to the homepage menu.

6. If the user chooses the booking status menu by pressing 4, they are led to the required window. In this part, the user can enter their name and PNR and get complete details of their ticket. This is achieved by parsing TICKET_RECORD.txt for the required entry as well as TRAIN_DETAILS.txt for details about the train. On a successful enquiry, the user is prompted with a yes or no question(Y/N) if they want to go back to the homepage menu. If the user answers 'N', they will exit the program. On entering 'Y', the user is then led to the homepage menu.

7. On pressing 0 from the homepage menu, the user exits the program.



Limitations:

1. During the booking process, the user must make sure that they enter both the first name and the last name. Leaving a field blank is detrimental to the running of the program.

2. Also, during the cancellation process, the user must ensure that they enter both the first name and the last name. Leaving a field blank is detrimental to the running of the program.


 
Contributions from team members:

1. Debaayus Swain: Built the cancellation menu and the enquiry menu.
2. Prakarsh Mehrotra: Built the user interface (home page menu) and the booking status menu.
3. Pranjal Panwar: Built the booking menu and added code for "wrong answer" cases.

















