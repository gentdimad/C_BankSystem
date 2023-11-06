void mainMenu(){
	int decision = 0;
	while(decision<1||decision>3){
	system("cls");
	printf("Welcome to the Banking Management System.\n\n[1] Employee\n[2] Customer\n[3] Exit Application\n\nOption: ");
	scanf("%d", &decision);
	}
	if (decision == 1 ||decision == 2){
		menu(decision);
	}else{
		exit(1);
	}
}//decision is for determining which type of menu() to generate.

void menu(int type){
	int decision = 0;
	while(decision>3||decision<1){
		system("cls");
		if (type == 1){
			printf("You have chosen 'Employee'.\n\n[1] Login\n[2] Register\n[3] Back\n\nOption: ");
		}else{
			printf("You have chosen 'Customer'.\n\n[1] Login\n[2] Register\n[3] Back\n\nOption: ");
		}
		
		scanf("%d", &decision);
		if(type == 1){
			if (decision == 1){
				empLogin();
			}else if(decision == 2){
				empReg();
			}else{
				mainMenu();
			}
		}else{
			if (decision == 1){
				custLogin();
			}else if(decision == 2){
				custReg();
			}else{
				mainMenu();
			}
		}
	}
}//Depending on which type of menu() is generated, the respective nested functions are different. For menu(1)- Employee. For menu(2)- Customer.

struct User getCustData(char userName[20]){
	FILE* o = fopen("users.txt", "r");
	char line[512];//Gets lines that are only up to 512 characters in length.
	struct User customer;
	
	//Gets the current data for the current user.
	while(fgets(line, 712, o) != NULL) {
     	sscanf(line, "%s %s %s %s %d %s %s %s %s %d %d %s %d %d %d %d", &customer.username, &customer.password, &customer.firstName, &customer.lastName, 
		 &customer.age, &customer.gender, &customer.address, &customer.occupation, &customer.nationality, &customer.height, &customer.weight, 
		 &customer.status, & customer.savings, &customer.current, &customer.loan, &customer.loanAmt);
    	if (strcmp(userName,customer.username) == 0){
    		fclose(o);
		}
	}
	fclose(o);
	
	return customer;
}//Getting customer data. FILE* o opens the users.txt file and reads the lines inside it using fgets. sscanf looks for
//data inside the line and places them inside the respective User struct values.

int getDataLine(){
	int dataLine = 1;
	FILE* o = fopen("users.txt", "r");
	char line[512];//Gets lines that are only up to 512 characters in length.
	struct User customer;
	
	//Gets the current data for the current user.
	while(fgets(line, 512, o) != NULL) {
     	sscanf(line, "%s %s %s %s %d %s %s %s %s %d %d %s %d %d %d %d", &customer.username, &customer.password, &customer.firstName, &customer.lastName, 
		 &customer.age, &customer.gender, &customer.address, &customer.occupation, &customer.nationality, &customer.height, &customer.weight, 
		 &customer.status, & customer.savings, &customer.current, &customer.loan, &customer.loanAmt);
    	if (strcmp(currUN,customer.username) != 0){
    		dataLine++;
		}
	}
	fclose(o);
	
	return dataLine;
}//Looks for the line in the users.txt file by using fgets and sscanf. If the username on the line matches the current username,
//The function stops and returns the line number of the current line.

void appendData(struct User customer){
	FILE* f = fopen("users.txt", "a");
	    fprintf(f, "%s %s %s %s %d %s %s %s %s %d %d %s %d %d %d %d\n", customer.username, customer.password, customer.firstName, customer.lastName,
			customer.age, customer.gender, customer.address, customer.occupation, customer.nationality, customer.height, customer.weight, customer.status,
			customer.savings, customer.current, customer.loan, customer.loanAmt);
		fclose(f);//Appends or adds the new data to the users.txt file.
}

void displayData(char userName[20]){
	struct User customer = getCustData(userName);
	printf("Name: %s %s\nAge: %d\nGender: %s\nAddress: %s\nOccupation: %s\nNationality: %s\nHeight: %d cm\nWeight: %d kg\nCivil Status: %s\n\n", customer.firstName, customer.lastName, customer.age, customer.gender, customer.address, customer.occupation, customer.nationality, 
	customer.height, customer.weight, customer.status );
}//Just prints the values inside the User struct.

void updateData(int dataLine){
	
	char line[512];
	int num = 0;
	FILE* r = fopen("temp.txt", "w"); //Opens temp.txt for "w"/writing
	FILE* o = fopen("users.txt", "r"); //Opens users.txt for "r"/reading
	
	    while (!feof(o))
	    {
	        strcpy(line, "\0");
            fgets(line, 512, o);
            if (!feof(o)) 
            {
                num++; //Counts the current line it is scanning.
                /* skip the line at given line number */
                if (num != dataLine) 
                {
                    fprintf(r, "%s", line);
                }
            }
	    }
	fclose(o);
	fclose(r);
	remove("users.txt");//Removing the existing file.
	rename("temp.txt", "users.txt");//Changing the name of the new file into the old file (users.txt).
}//Rewriting the users.txt file by deleting the line with the current data.

struct User inputData(struct User cust){
		struct User customer =  cust;	//Transfers values of passed User struct to local User struct.
		
		printf("\nFirst Name: ");
		scanf("%s", &customer.firstName);
		printf("Last Name: ");
		scanf("%s", &customer.lastName);
		printf("Age: ");
		scanf("%d", &customer.age);
		printf("Gender: ");
		scanf("%s", &customer.gender);
		printf("Address: ");
		scanf("%s", &customer.address);
		printf("Occupation: ");
		scanf("%s", &customer.occupation);
		printf("Nationality: ");
		scanf("%s", &customer.nationality);
		printf("Height(cm): ");
		scanf("%d", &customer.height);
		printf("Weight(kg): ");
		scanf("%d", &customer.weight);
		printf("Civil Status: ");
		scanf("%s", &customer.status);
		
	return customer;
}//Just places new values into the User struct, and returns the new values inside a User struct.

void updateFinances(int savings, int current, int loan, int loanAmt){
	int dataLine = getDataLine();
	struct User customer;
	
	//Gets the current data for the current user.
	customer = getCustData(currUN);
	
	customer.savings += savings;
	customer.current += current;
	customer.loan = loan;
	customer.loanAmt+= loanAmt;
	
	if (customer.loanAmt < 0){
		customer.loan = 0;
		customer.savings += (0-customer.loanAmt);
		customer.loanAmt = 0;
	}
		
	updateData(dataLine);//Removes old line of data.
	appendData(customer);//Adds the new line of data with the new values.
	}//Updates the values of the savings, current, loan, and loanAmt in the User struct.





