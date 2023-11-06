void custLogin(){
	FILE* o = fopen("users.txt", "r");
	char line[512];
	int success = 0;
	int decision = 0;
	struct User customer;
	system("cls");
	printf("Customer Login\n\nUsername: ");
	scanf("%s", &currUN);
	printf("Password: ");
	scanf("%s", &currPW);
	
	while(fgets(line, 512, o) != NULL) {
     	sscanf(line, " %s %s %s %s %d %s %s %s %s",&customer.username, &customer.password, &customer.firstName, &customer.lastName, &customer.age, &customer.gender, &customer.address, &customer.occupation,&customer.nationality);
    	if (strcmp(currUN,customer.username) == 0 && strcmp(currPW,customer.password) == 0){
    		fclose(o);
			success = 1;
    		custDash();
		}//Matches if the inputted username and password is found inside the users.txt file.
	}
	if(success == 0){
		fclose(o);
		do{
			system("cls");
			printf("You inputted the wrong credentials. Would you like to try again, or would you like to register?\n\n[1] Login\n[2] Register\n\nOption: ");
			scanf("%d", &decision);
		}while(decision>2||decision<1);
		if (decision == 1){
			custLogin();
		}else{
			custReg();
		}
	}//Logs in if successful. If wrong credentials, asks if user wants to login again or register.
	
}

void custReg(){
	FILE* f = fopen("users.txt", "a");
	struct User customer;
	char decision;
	int decided = 0;
	do{
		system("cls");
		printf("To register, we will have to ask for the following details:\nFirst Name\nLast Name\nUsername\nPassword");
		printf("\n\nWould you like to continue? (y/n): ");
		scanf(" %c", &decision);
		if(decision == 'y'||decision == 'n'){
		decided = 1;
		}
	}while(decided == 0);
	if (decision == 'y'){
		system("cls");
		printf("Please input your first and last name.\n\n");
		printf("First Name: ");
		scanf("%s", &customer.firstName);
		printf("Last Name: ");
		scanf("%s", &customer.lastName);
		system("cls");
		printf("Please set your username and password.\n\n");
		printf("Username: ");
		scanf("%s", &customer.username);
		printf("Password: ");
		scanf("%s", &customer.password);
		customer.age = 0;
		strcpy(customer.gender,"N/A");
		strcpy(customer.address,"N/A");
		strcpy(customer.occupation,"N/A");
		strcpy(customer.nationality,"N/A");
		customer.height = 0;
		customer.weight = 0;
		strcpy(customer.status,"N/A");
		customer.savings = 0;
		customer.current = 0;
		customer.loan = 0;
		customer.loanAmt = 0;
		//The whole block of code above this comment initializes the values inside the User struct so that sscanf doesn't give an error.
		//These are mostly placeholder values.
		
		
		
		if (f!=NULL){
			fflush(f);
			fprintf(f,"%s %s %s %s %d %s %s %s %s %d %d %s %d %d %d %d\n", customer.username, customer.password, customer.firstName, customer.lastName,
			customer.age, customer.gender, customer.address, customer.occupation, customer.nationality, customer.height, customer.weight, customer.status,
			customer.savings, customer.current, customer.loan, customer.loanAmt);//Writes the line of data into the users.txt file.
			fclose(f);
			mainMenu();//Goes back to mainMenu() when done.
		}else{
			printf("File not found!");
		}
	}else{
		menu(2);//Goes to customer menu.
	}
}

void custDash(){
	int decision = 0;
	do{
		system("cls");
		printf("[1] View Account Details\n[2] Account Balance\n[3] PAYMENT\n[4] Apply For Loan\n[5] Go Back To Main Menu\n[6] Exit Application\n\nOption: ");
		scanf("%d",&decision);
		switch(decision){
			case 1:{
				custDisp();
				break;
			}
			case 2:{
				accBalance();
				break;
			}
			case 3:{
				PAYMENT();
				break;
			}
			case 4:{
				applyLoan();
				break;
			}
			case 5:{
				mainMenu();
				break;
			}
			case 6:{
				exit(1);
			}
		}
	}while(decision>6||decision<1);
}//Displays the customer dashboard with their respective functions in each option.

void custDisp(){
	int decided = 0;
	char decision;
	int dataLine = getDataLine(currUN), num = 0;
	struct User customer;
	
	//Gets the current data for the current user.
	customer = getCustData(currUN);
	
	do{
		system("cls");
		displayData(currUN);
		printf("Would you like to update your information? (y/n): ");
		scanf(" %c",&decision);
		if(decision == 'y'|| decision == 'n'){
			decided = 1;
		}//Prints out the data.
	}while(decided == 0);
	if (decision == 'y'){
		system("cls");
		
		//Getting new values for customer data.
		customer = inputData(customer);
		
		updateData(dataLine);
	    appendData(customer);
		custDash();
	}else{
		custDash();
	}
}//Just displays the information for the current username by using getCustData(currUN) and displayData(currUN);
//If chooses to update, uses inputData(), updateData(), and appendData(). These three always work together.

void accBalance(){
	int decision = 0;
	char line[512];//Gets lines that are only up to 512 characters in length.
	struct User customer;
	char loanStatus[10];
	char loanType[15];
	
	//Gets the current data for the current user.
	customer = getCustData(currUN);
	
	if(customer.loan>0){
		strcpy(loanStatus,"True");
		if(customer.loan == 1){
			strcpy(loanType,"Short Term");
		}else{
			strcpy(loanType,"Long Term");
		}
	}else{
		strcpy(loanType,"None");
		strcpy(loanStatus,"False");
	}//Changes the numerical values into strings. 1 is Short Term. 2 is Long Term, for loanType. 
	//If there is a loanType, then there is a loan. So, loanStatus becomes True. Else, False.
	
	
	
	
	do{
	system("cls");
	printf("ACCOUNT BALANCE\nSavings: %d\nCurrent: %d\n\nLoan Status: %s\nType: %s\nAmount: %d\n\nWhat would you like to do?\n[1] PAYMENT\n[2] Apply For Loan\n[3] Back\n\nOption: ", customer.savings, customer.current, loanStatus, loanType, customer.loanAmt);
	scanf("%d", &decision);
	}while(decision<1||decision>3);
	switch(decision){
		case 1:{
			PAYMENT();
			break;
		}
		case 2:{
			applyLoan();
			break;
		}
		case 3:{
			custDash();
			break;
		}
	}
}//Simply displays the values inside savings, current, and loan.

void PAYMENT(){
	FILE* t = fopen("transactions.txt", "a");
	int decision = 0;
	int savCurr = 0;
	int amount = 0;
	struct User customer = getCustData(currUN);
	
	do{
		system("cls");
		printf("What would you like to do?\n\n[1] Deposit\n[2] Pay Loan\n\nOption: ");
		scanf("%d", &decision);
	}while(decision>2||decision<1);
	
	system("cls");
	printf("Enter amount: ");
	scanf("%d", &amount);
	if(decision == 1){
		if(amount>100000){
			do{	
				system("cls");
				printf("Please enter an amount between 0 and 100000: ");
				scanf("%d", &amount);
			}while(amount>100000||amount<0);//To catch deposit of over 100k.
			do{
				system("cls");
				printf("\nWhere would you like to deposit the amount?\n\n[1] Savings\n[2] Current\n\nOption: ");
				scanf("%d", &savCurr);
			}while(savCurr>2||savCurr<1);
			if(savCurr==1){
				fprintf(t, "%s PAYMENT Deposit:Savings %d\n", currUN, amount);
				fclose(t); 
				updateFinances(amount,0, customer.loan, 0);
				custDash();	
			}else{
				fprintf(t, "%s PAYMENT Deposit:Current %d\n", currUN, amount);
				fclose(t); 
				updateFinances(0, amount, customer.loan, 0);
				custDash();	
			}//If chooses to Deposit. The if else inside is for when choosing Savings or Current. This is for when the amount is more than 100000;
		}else{
			do{
				system("cls");
				printf("\nWhere would you like to deposit the amount?\n\n[1] Savings\n[2] Current\n\nOption: ");
				scanf("%d", &savCurr);
			}while(savCurr>2||savCurr<1);
			if(savCurr==1){
				fprintf(t, "%s PAYMENT Deposit:Savings %d\n", currUN, amount);
				fclose(t); 
				updateFinances(amount,0, customer.loan, 0);
				custDash();	
			}else{
				fprintf(t, "%s PAYMENT Deposit:Current %d\n", currUN, amount);
				fclose(t);
				updateFinances(0, amount, customer.loan, 0); 
				custDash();	
			}
		}//Does the same nested if else as above it but without the loop because the amount is already less than 100000.
	}else{
		if(amount>100000){
			do{	
				system("cls");
				printf("Please enter an amount between 0 and 100000: ");
				scanf("%d", &amount);
			}while(amount>100000||amount<0);//Repeats asking for a proper amount when amount is above 100000.
			fprintf(t, "%s PAYMENT Pay-Loan: %d\n", currUN, amount); 
			fclose(t); 
			updateFinances((0-amount),0,customer.loan,(0-amount));
			custDash();
		}else{
			fprintf(t, "%s PAYMENT Pay-Loan: %d\n", currUN, amount); 
			fclose(t); 
			updateFinances((0-amount),0,customer.loan,(0-amount));
			custDash();
		}
	}//If chooses to Pay Loan. The if else above is just for when the amount is above 100000 or not.
}
	
void applyLoan(){
	FILE* t = fopen("transactions.txt", "a");
	int type = 0;
	int duration = 0;
	int amount = 0;
	float total = 0;
	int decision = 0;
	char hold;
	struct User customer;
	customer = getCustData(currUN);
	
	do{
		system("cls");
		printf("Select type of loan:\n\n[1] Short-Term\n[2] Long-Term\n[3] Cancel\n\nOption: ");
		scanf("%d", &decision);
	}while(decision>3||decision<1);
	
	printf("\nEnter loan amount: ");
	scanf("%d", &amount);
	switch(decision){
		case 1:{
			if(customer.loan==0){
				printf("\nEnter loan duration (months): ");
				scanf("%d", &duration);
				system("cls");
				while(duration>6||duration<1){
					printf("Please enter a duration betweeen 1 and 6 months: ");
					scanf("%d", &duration);
				}
				if(amount<30000){
					total = amount+(0.03*duration*amount);//The formula is (number of months) multiplied by (3% interest), multiplied to (loan amount) To get the total interest.
													//Then, added to the principal amount to get the resulting loan balance.
				}else{
					total = amount+(0.06*duration*amount);//When amount is above 30000.
				}
				
				updateFinances(amount,0, 1, total);
				fprintf(t, "%s LOAN Short-Term:%dmonths %d\n", currUN, duration, amount);
				fclose(t);
				printf("Your loan amount will be %.2f.\n\nEnter any key to continue... ", total);
				scanf(" %c", &hold);
				custDash();
			}else{
				system("cls");
				printf("You already have an existing loan. Please pay your current loan to avail another one.\n\nEnter any key to continue... ");
				scanf(" %c", &hold);
				fclose(t);
				custDash();
			}//If there is an existing loan, does not allow the user to apply for another one.
			break;
		}
		case 2:{
			if(customer.loan==0){
				printf("\nEnter loan duration (months): ");
				scanf("%d", &duration);
				system("cls");
				while(duration>24||duration<1){
					printf("Please enter a duration betweeen 1 and 24 months: ");
					scanf("%d", &duration);
				}
				total = amount+(0.03*duration*amount);//Does the same formula above but uses 6%.. Long Term loans always use 6%
				updateFinances(amount,0, 2, total);
				fprintf(t, "%s LOAN Long-Term:%dmonths %d\n", currUN, duration, amount);
				fclose(t);
				printf("Your loan amount will be %.2f.\n\nEnter any key to continue... ", total);
				scanf(" %c", &hold);
				custDash();
			}else{
				system("cls");
				printf("You already have an existing loan. Please pay your current loan to avail another one.\n\nEnter any key to continue... ");
				scanf(" %c", &hold);
				fclose(t);
				custDash();
			}//If there is an existing loan, does not allow the user to apply for another one.
			break;
		}
		case 3:{
			fclose(t);
			custDash();
			break;
		}
	}
}
