#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//structure to store details of ticket of passengers
struct ticket{
	int PNR;//variable to store PNR number
	char fname[20];//variable to store first name of passenger
	char lname[20];//variable to store last name of passenger
	int tr_no;//variable to store train number
}ticket;

//structure to store details of trains
struct train{
	char source[30],destination[30];//variables to store source and destination
	int seats_left;//variable to store seats left in train during execution of program
	int train_no;//variable to store train number
	float price;//variable to store price of train tickets
}train;

//prototype of menu function
void menu();


//time delay function
void delay()
{
	//delays the output on screen by running 2 for loops for fixed number of iterations
	for(int i=0;i<=25000;i++)
	for(int j=0;j<=i;j++)
	;
}

//returns the user back to the menu function depending on the input of the passenger
void return_homepage()
{
	char ch;//counter variable
	while(1)
	{
		delay();//calling delay function
		printf("\033[1;36m");//Set the text to cyan colour
		printf("\n\nDO YOU WANT TO RETURN TO MAIN MENU:(Y/N):");
		printf("\033[0m");//Resets the text colour

		scanf(" %c",&ch);

		//conditional statement to check the input
		if(ch=='Y' || ch=='y')
		{
			menu();//calling menu function
		}
		else if(ch=='N' || ch=='n')
		{
			//page cleared
			printf("\e[2J\e[H");
			printf("\033[1;36m");//Set the text to cyan colour
			printf("Successfully Exited the Program\n\n\n");
			printf("\033[0m");//Resets the text colour

			exit(0); // exiting the program
		}
		else
		printf("\n\nInvalid Input. Enter Again");
	}
}

//function for booking tickets
void book_ticket()
{
	FILE *fp1,*fp2,*fp3,*fp_duplicate;//File pointers
	//Opening the files required to book tickets
	fp1=fopen("TRAIN_DETAILS.txt", "r+");
	fp2=fopen("TICKET_RECORD.txt", "a+");
	fp3=fopen("PNR_COUNTER.txt", "r+");


	int flag=0,fl2=0, train_no_store;// flag and fl2 are counter variables. train_no_store is to store train number.

	//Conditional Statement to check if the files open
	if (fp1==NULL||fp2==NULL||fp3==NULL)
	{
		puts("Cannot open file");
		exit(1);
	}

	printf("\e[2J\e[H");//clears screen
	printf("\033[1;36m"); //Set the text to cyan colour
	printf("\n******** WELCOME TO RAILWAY RESERVATION SYSTEM FOR MIGRANT LABOURERS ********\n\n");
	printf("\033[0m");//Resets the text colour

	printf("\033[1;32m");//Set the text colour green
	printf("BOOKING WINDOW\n\n\n");
	printf("\033[0m");//Resets the text colour

	char src[30], dest[30], ch, chh;//src and dest are used to store source and destination. ch and chh are counter variables.
	float pr;//variable for storing price

	//Inputting source and destination
	printf("Enter the Source and Destination of the train: ");
	scanf("%s %s", src, dest);
	//checking if the source is "DELHI"
	if(strcasecmp("DELHI",src)!=0)
	{
		//closes the open files
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
		printf("\nNo trains available as trains are only running from DELHI\n\n");
		printf("Would you like to try again (Y/N): ");
		fflush(stdin);//flushes the output buffer of the standard input stream
		//the above statement basically removes the '\n' from the input
		scanf(" %c", &ch);
		if(ch=='Y' || ch=='y')
		book_ticket();//recursive function call
		else if(ch=='N'|| ch=='n')
		return_homepage();//calling return_homepage function
		else
		{
			printf("Invalid Input. Try again.\n\n");
			return_homepage();//calling return_homepage function
		}

	}

	//Structure variable declarations
	struct train tr;
	struct ticket t;

	//Searching for train details in TICKET_DETAILS.txt File
	while(fscanf(fp1, "%s %s %d %d %f", tr.source, tr.destination, &tr.seats_left, &tr.train_no, &tr.price)!=EOF)
	{
		if (strcasecmp(tr.destination,dest)==0 && tr.seats_left>0)
		{

			fscanf(fp3,"%d",&t.PNR);
			rewind(fp3);
			fprintf(fp3,"%d",t.PNR+1);//updating the PNR number
			train_no_store=tr.train_no;//storing the train number obtained from TRAIN_DETAILS.txt
			pr=tr.price;//storing the train ticket price obtained from TRAIN_DETAILS.txt
			flag=1;//set counter flag to 1
			break;
		}
		if(tr.seats_left==0)
		flag=2;//set flag to 2
	}

	if(flag==0)
	{
		//closing the open files due to the flag being 0 implying that no trains are available
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
		printf("No trains available to your destination\n");
		printf("\n\n\nWould you like to try again(Y/N): ");
		scanf(" %c", &chh);
		if(chh=='Y' || chh=='y')
		book_ticket();//recursive function call
		else if(chh=='N' || chh=='n')
		return_homepage();//calling return_homepage function
		else
		{
			printf("Invalid input. Please try again");
			return_homepage();//calling return_homepage function
		}
	}
	if (flag==1)
	{
		//Counter is 1.Hence Booking is Possible.
		fseek(fp2, 0, SEEK_END);//sets the file stream to the end of file

		//Inputting the details
		printf("Enter your First name: ");
		scanf(" %s", t.fname);
		printf("Enter your Last name: ");
		scanf(" %s", t.lname);

		//Printing message of successful booking with all details
		printf("Booking Successful\n\n\nName: %s %s\nPNR: %d\nSource of Train: %s\nDestination of Train: %s\n",t.fname,t.lname, t.PNR+1,src, dest);
		printf("Train no: %d\nPrice: Rs. %.2f\n", train_no_store, pr);
		fprintf(fp2,"%d %s %s %d\n", t.PNR+1,t.fname,t.lname, train_no_store);//updating TICKET_RECORDS.txt file

		fp_duplicate=fopen("DUPLICATE.txt", "w");//creating a duplicate file

		rewind(fp1);//sets the file pointer at the beginning of the stream

		while(fscanf(fp1, "%s %s %d %d %f", tr.source, tr.destination, &tr.seats_left, &tr.train_no, &tr.price)!=EOF)
		{
			//Copying the file contents after updating the seats left of TRAIN_DETAILS.txt to DUPLICATE.txt
			if(tr.train_no==train_no_store)
			(--tr.seats_left);
			fprintf(fp_duplicate, "%s %s %d %d %.2f\n", tr.source, tr.destination, tr.seats_left, tr.train_no, tr.price);
		}
		//closing the files
		fclose(fp_duplicate);
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);

		remove("TRAIN_DETAILS.txt");//deleting the TRAIN_DETAILS.txt file
		rename("DUPLICATE.txt", "TRAIN_DETAILS.txt");//renaming DUPLICATE.txt to TRAIN_DETAILS.txt file

	}
	if(flag==2)
	{
		//closing the files as the flag is 2 implying no seats left for booking
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
		printf("No seats available on the train to your destination\n");
		printf("\n\n\nWould you like to try again with a different destination(Y/N): ");
		scanf(" %c", &chh);
		if(chh=='Y' || chh=='y')
		book_ticket();//calling book_ticket function
		else if(chh=='N' || chh=='n')
		return_homepage();//calling return_homepage function
		else
		{
			printf("Invalid input. Please try again");
			return_homepage();//calling return_homepage function
		}

	}
}



//function for enquiry
void find_train()
{
	FILE *fp;//Creating file pointer
	fp=fopen("TRAIN_DETAILS.txt", "r+"); //Opening the files required to find trains for enquiry
	int flag=0;//counter variable

	//Conditional Statement to check if the file opens
	if (fp==NULL)
	{
		puts("Cannot open file");
		exit(1);
	}

	char src[30], dest[30], ch, ch2;//src and dest are to store source and destination of trains.ch and ch2 are counter variables

	printf("\e[2J\e[H");//clears screen
	printf("\033[1;36m"); //Set the text to cyan colour
	printf("\n******** WELCOME TO RAILWAY RESERVATION SYSTEM FOR MIGRANT LABOURERS ********\n\n");
	printf("\033[0m");//Resets the text colour

	printf("\033[1;32m");//Set the text to green colour
	printf("ENQUIRY WINDOW\n\n\n");
	printf("\033[0m");//Resets the text colour

	//Inputting Source and Destination for Enquiry
	printf("Enter the source and destination of the train: ");
	scanf("%s %s", src, dest);

	//checking if the source is "DELHI"
	if(strcasecmp("DELHI",src)!=0)
	{
		fclose(fp);
		printf("\nNo trains available from %s\n",src);
		printf("Trains are only available from DELHI\n\n");
		printf("Do you want to try again(Y/N): ");
		fflush(stdin);//flushes the output buffer of a stream
		scanf(" %c", &ch);
		if(ch=='Y' || ch=='y')
		find_train();//recursive function call
		else
		return_homepage();
	}

	//Structure variable declaration
	struct train tr;
	rewind(fp);//sets the file pointer at the beginning of the stream

	//Searching for train details in TICKET_DETAILS.txt File
	while(fscanf(fp, "%s %s %d %d %f", tr.source, tr.destination, &tr.seats_left, &tr.train_no, &tr.price)!=EOF)
	{
		if (strcasecmp(tr.destination,dest)==0)
		{
			//printing the seats left and prices of tickets
			printf("\nNumber of seats left in the train is: %d\n", tr.seats_left);
			printf("Price of the ticket is: Rs. %.2f\n", tr.price);
			flag=1;//sets the flag as 1
		}
	}
	if (flag==0)
	{
		fclose(fp);//closes the file
		//Flag is 0. Hence Train Details not found
		printf("\nNo trains available to your Destination\n");

		//Asking user if he wants to re-enter train details
		printf("Do you want to try again (Y/N): ");
		fflush(stdin);//flushes the output buffer of a stream
		scanf("%c", &ch2);
		if(ch2=='Y' || ch2=='y')
		find_train();//Calling find_train function
		else
		{
			fflush(stdin);//flushes the output buffer of a stream
			return_homepage();
		}

	}

	fclose(fp);//closes the file
	fflush(stdin);//flushes the output buffer of a stream
}


//fxn for cancellation
void cancel_tickets()
{
	FILE *fp_ticket_rec, *fp_train, *fp_duplicate1, *fp_duplicate2;//File pointers
	//Opening the files required to cancel the booking
	fp_ticket_rec= fopen("TICKET_RECORD.txt", "r+");
	fp_train= fopen("TRAIN_DETAILS.txt", "r+");
	fp_duplicate1=fopen("DUPLICATE1.txt", "w");//creating a duplicate file

	//Conditional Statement to check if the files open
	if (fp_ticket_rec==NULL||fp_train==NULL)
	{
		puts("Cannot open file");
		exit(1);
	}

	int check_pnr, flag=0, train_no_store;//check_pnr to check PNR, flag is a counter variable and train_no_store is to store train number
	char check_fname[20], check_lname[20];//to check first and last name of passenger

	printf("\e[2J\e[H");//clears screen
	printf("\033[1;36m"); //Set the text to cyan colour
	printf("\n******** WELCOME TO RAILWAY RESERVATION SYSTEM FOR MIGRANT LABOURERS ********\n\n");
	printf("\033[0m");//Resets the text colour

	//Cancellation Menu
	printf("\033[1;32m");//Set the text to green colour
	printf("CANCELLATION WINDOW\n\n");
	printf("\033[0m");//Resets the text colour


	printf("\033[1;36m");//Set the text to cyan colour
	printf("NOTE:");
	printf("\033[0m");//Resets the text colour

	printf("\n50 percent of the booking amount will be refunded on cancellation of the ticket.\nOnce the ticket has been cancelled, the action can not be reversed\n\n");
	printf("____________________________________________________\n\n\n");

	//Inputting Details to Cancel the ticket
	printf("Kindly enter the following details to cancel the ticket:\n\nEnter your First Name: ");
	scanf("%s", check_fname);
	printf("\nEnter your Last name: ");
	scanf("%s", check_lname);
	printf("\nEnter your PNR:");
	scanf("%d",&check_pnr);

	//Structure variable declaration
	struct ticket t;

	rewind(fp_ticket_rec);//sets the file pointer at the beginning of the stream

	//Searching for user details in TICKET_RECORD.txt File
	while(fscanf(fp_ticket_rec, "%d %s %s %d", &t.PNR, t.fname, t.lname, &t.tr_no)!=EOF)
	{
		if((strcasecmp(t.fname,check_fname)==0)&&(strcasecmp(t.lname,check_lname)==0)&&(t.PNR==check_pnr))
		{
			//Passenger Found. Storing the train number of Passenger
			printf("\e[2J\e[H");
			train_no_store=t.tr_no;
			flag=1;//sets the counter flag to 1
			continue;
		}
		fprintf(fp_duplicate1, "%d %s %s %d\n", t.PNR, t.fname, t.lname, t.tr_no);//copying the contents of TICKET_RECORD.txt to DUPLICATE1.txt except the passenger demanding cancellation


	}


	if (flag==0)
	{
		//closes the files
		fclose(fp_ticket_rec);
		fclose(fp_duplicate1);
		fclose(fp_train);
		remove("DUPLICATE1.txt");//deletes the DUPLICATE1.txt file
		//Counter is 0. Hence Passenger Details not found
		char ch;
		printf("\nTicket Entry not found\n\n");
		printf("Would you like to try again (Y/N): ");
		fflush(stdin);//flushes the output buffer of a stream
		scanf(" %c", &ch);
		if (ch=='Y' || ch=='y')
		cancel_tickets();//recursive function call

		else if(ch=='N'|| ch=='n')
		return_homepage();//calls return_homepage function

		else
		{
			printf("Invalid Output. Please try again");
			return_homepage();
		}

	}
	else if(flag==1)
	{
		//Counter is 1.Hence Cancellation is Possible.
		fp_duplicate2=fopen("DUPLICATE2.txt", "w");//opens a new file
		struct train tr;
		rewind(fp_train);//sets the file pointer at the beginning of the stream

		//Searching for train details in TRAIN_DETAILS.txt File
		while(fscanf(fp_train, "%s %s %d %d %f", tr.source, tr.destination, &tr.seats_left, &tr.train_no, &tr.price)!=EOF)
		{
			//Searching the train using train number and increasing the number of seats in train by 1 and giving 50% refund.
			if(tr.train_no==train_no_store)
			{
				(++tr.seats_left);
				printf("\nYour Request has been processed.\n\nA refund of Rs. %.2f will be credited to your account\n\n\n", (tr.price/2));
			}
			fprintf(fp_duplicate2, "%s %s %d %d %.2f\n", tr.source, tr.destination, tr.seats_left, tr.train_no, tr.price);//copying contents of TRAIN_DETAILS.txt to DUPLICATE2.txt and updating the seat number.
		}
	}
	else {}

	//closes the files
	fclose(fp_ticket_rec);
	fclose(fp_duplicate1);
	fclose(fp_duplicate2);
	fclose(fp_train);
	//deleting TICKET_RECORD.txt and TRAIN_DETAILS.txt
	remove("TICKET_RECORD.txt");
	remove("TRAIN_DETAILS.txt");

	//Renaming DUPLICATE1.txt to TICKET_RECORD.txt and DUPLICATE2.txt to TRAIN_DETAILS.txt
	rename("DUPLICATE1.txt", "TICKET_RECORD.txt");
	rename("DUPLICATE2.txt", "TRAIN_DETAILS.txt");
	fflush(stdin);//flushes the output buffer of a stream

}

void booking_status()
{


	FILE *fp_ticket_rec, *fp_train;//File pointers
	//Opening the files required to check booking status
	fp_ticket_rec= fopen("TICKET_RECORD.txt", "r+");
	fp_train= fopen("TRAIN_DETAILS.txt", "r+");
	rewind(fp_train);//sets the file pointer at the beginning of the stream

	//Conditional Statement to check if the files open
	if (fp_ticket_rec==NULL||fp_train==NULL)
	{
		puts("Cannot open file");
		exit(1);
	}

	//variables required to check the booking status
	int check_pnr, flag=0, train_no_store;//check_pnr to check PNR, flag is a counter variable and train_no_store is to store train number
	char check_fname[20], check_lname[20];//to check first and last name of passenger

	printf("\e[2J\e[H");//clears screen
	printf("\033[1;36m"); //Set the text to cyan colour
	printf("\n******** WELCOME TO RAILWAY RESERVATION SYSTEM FOR MIGRANT LABOURERS ********\n\n");
	printf("\033[0m");//Resets the text colour

	//Booking Status Menu
	printf("\033[1;32m");//adding green colour
	printf("BOOKING STATUS WINDOW\n\n\n");
	printf("\033[0m");//reset the green to white

	//Inputting First Name, Last Name and PNR
	printf("Kindly enter the following details to check the status of ticket:\n\nEnter your First Name: ");
	scanf("%s", check_fname);
	printf("\nEnter your Last name: ");
	scanf("%s", check_lname);
	printf("\nEnter your PNR:");
	scanf("%d",&check_pnr);

	//Structure variable declarations
	struct train tr;
	struct ticket t;

	rewind(fp_ticket_rec);//sets the file pointer at the beginning of the stream

	//Searching for user details in TICKET_RECORD.txt File
	while(fscanf(fp_ticket_rec, "%d %s %s %d", &t.PNR, t.fname, t.lname, &t.tr_no)!=EOF)
	{
		if((strcasecmp(t.fname,check_fname)==0)&&(strcasecmp(t.lname,check_lname)==0)&&(t.PNR==check_pnr))
		{
			printf("\e[2J\e[H");
			printf("\033[1;36m"); //Set the text to cyan colour
			printf("\n******** WELCOME TO RAILWAY RESERVATION SYSTEM FOR MIGRANT LABOURERS ********\n\n");
			printf("\033[0m");//Resets the text colour

			printf("BOOKING STATUS WINDOW:\n\n");
			train_no_store=t.tr_no;
			//Using the train number find and print source and destination

			//Searching for train details in TICKET_DETAILS.txt File
			while(fscanf(fp_train, "%s %s %d %d %f", tr.source, tr.destination, &tr.seats_left, &tr.train_no, &tr.price)!=EOF)
			{
				if(tr.train_no==train_no_store)
				{
					//printing the Booking Status Details
					printf("\nSTATUS:\n\n");
					printf("Name:%s %s\nPNR:%d\nSource:%s\nDestination:%s\nTrain Number:%d\n", t.fname, t.lname, t.PNR ,tr.source, tr.destination,tr.train_no);
				}
			}

			flag=1;//set the flag 1
			break;

		}
	}


	if (flag==0)
	{
		//closing the open files
		fclose(fp_ticket_rec);
		fclose(fp_train);
		//flag is 0. Hence Ticket Details not found
		char ch;
		printf("\nTicket entry not found\n\n");
		//Option to re-enter details to check the booking status
		printf("Would you like to try again (Y/N): ");
		fflush(stdin);//flushes the output buffer of a stream
		scanf(" %c", &ch);
		if (ch=='Y' || ch=='y')
		booking_status();//recursive function call
		else if(ch=='N'||ch=='n')
		return_homepage();//function call to return back to homepage
		else
		{
			printf("\nInvalid Input. Please try again");
			return_homepage();
		}

	}

	//closing the files opened
	fclose(fp_ticket_rec);
	fclose(fp_train);
	fflush(stdin);//flushes the output buffer of a stream
}


//fxn for menu
void menu()
{
	int counter; //counter for switch case
	printf("\e[2J\e[H");//clears the screen
	printf("\033[1;36m"); //Set the text to cyan colour
	printf("\n******** WELCOME TO RAILWAY RESERVATION SYSTEM FOR MIGRANT LABOURERS ********\n\n\n");
	printf("\033[0m");//Resets the text colour

	while(1)
	{
		//Menu Interface
		printf("1.Booking Menu\n2.Enquiry Menu\n3.Cancellation Facility\n4.Booking Status\n\nEnter '0' to Exit");
		printf("\n\n____________________________________________________\n\n\n");

		printf("\033[1;32m");//Sets the text to green colour
		printf("Kindly Enter Your Choice:");
		printf("\033[0m");//Resets the text colour


		scanf("%d",&counter);

		//switch case for counter variable
		switch(counter)
		{
			case 0:
			printf("\e[2J\e[H");//page cleared
			printf("\033[1;36m");//Sets the text to cyan colour
			printf("Successfully Exited the Program\n\n\n");
			printf("\033[0m");//Resets the text colour
			exit(0); // exiting the program
			break;

			case 1:
			book_ticket();//Calling book_tickets functiom
			return_homepage();//Calling return_homepage function
			break;

			case 2:
			find_train(); //Calling find_train function
			return_homepage();//Calling return_homepage function
			break;

			case 3:
			cancel_tickets(); //Calling cancel_tickets function
			return_homepage();//Calling return_homepage function
			break;

			case 4:
			booking_status();//Calling booking_status function
			return_homepage();//Calling return_homepage function
			break;

			default: printf("\nInvalid Input. Enter again.\n");
			delay();//calling delay function
			//page cleared for re-entering input
			printf("\e[2J\e[H");
			printf("\033[1;36m"); //Set the text to cyan colour
			printf("\n******** WELCOME TO RAILWAY RESERVATION SYSTEM FOR MIGRANT LABOURERS ********\n\n");
			printf("\033[0m");//Resets the text colour

			continue;

		}

		break;
	}
}


//main function
int main()
{
	menu();//calling menu function
	return 0;
}
