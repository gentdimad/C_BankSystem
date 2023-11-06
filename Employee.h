//Employee
void empLogin(){
	FILE* o = fopen("employees.txt","r");
	char line[512];
	int success = 0;
	int decision = 0;
	struct User employee;
	if( o != NULL){
		fscanf(o, "%s %s",&employee.username, &employee.password);
	}
	system("cls");
	printf("Employee Login\n\nUsername: ");
	scanf("%s", &currUN);
	printf("Password: ");
	scanf("%s", &currPW);
	
	while(fgets(line, 512, o) != NULL) {
     	sscanf(line, "%s %s",&employee.username, &employee.password);
    	if (strcmp(currUN,employee.username) == 0 && strcmp(currPW,employee.password) == 0){
    		success = 1;
    		fclose(o);
    		empDash();
		}
	}
	if(success == 0){
		fclose(o);
		do{
			system("cls");
			printf("You inputted the wrong credentials. Would you like to try again, or would you like to register?\n\n[1] Login\n[2] Register\n\nOption: ");
			scanf("%d", &decision);
		}while(decision>2||decision<1);
		if (decision == 1){
			fclose(o);
			empLogin();
		}else{
			fclose(o);
			empReg();
		}
	}
}
//Does the same as customer. Matches the inputted username and password and checks the employee.txt file if the username and password is there.

void empReg(){
	FILE* o = fopen("employees.txt","a+");
	char userName[20];
	char passWord[20];
	char decision;
	int decided = 0;
	do{
		system("cls");
		printf("To register, we will have to ask for the following details:\nUsername\nPassword");
		printf("\n\nWould you like to continue? (y/n): ");
		scanf(" %c", &decision);
		if(decision == 'y'||decision == 'n'){
		decided = 1;
		}
	}while(decided == 0);
	if (decision == 'y'){
		system("cls");
		printf("Please set your username and password.\n\n");
		printf("Username: ");
		scanf("%s",&userName);
		printf("Password: ");
		scanf("%s",&passWord);
		
		
		if (o!=NULL){
			fflush(o);
			fprintf(o, "%s %s\n", userName, passWord);//Writes the line of data into the users.txt file.
			fclose(o);
			mainMenu();
		}else{
			fclose(o);
			printf("File not found!");
		}
	}else{
		fclose(o);
		menu(1);
	}
}
//Writes the inputted username and password into the employee.txt file.

void empDash(){
	int decision = 0;
	do{
		system("cls");
		printf("[1] User Registration and Login\n[2] Account Management\n[3] Transaction History\n[4] Transfer Money\n[5] Loan Management\n[6] Go Back To Main Menu\n[7] Exit Application\n\nOption: ");
		scanf("%d",&decision);
		switch(decision){
			case 1:{
				userRegLog();
				break;
			}
			case 2:{
				accMngmnt();
				break;
			}
			case 3:{
				transactHist();
				break;
			}
			case 4:{
				transferMoney();
				break;
			}
			case 5:{
				loanMngmnt();
				break;
			}
			case 6:{
				mainMenu();
				break;
			}
			case 7:{
				exit(1);
			}
		}
	}while(decision>7||decision<1);
}//Employee dashboard options with their respective functions.

void userRegLog(){
	int decision = 0;
	do{
	printf("Would you like to login as a customer or register a customer?\n\n[1] Login\n[2] Register\n\nOption: ");
	scanf("%d",&decision);
	}while(decision>2||decision<1);
	if (decision ==1){
		custLogin();
	}else{
		custReg();
	}
}//Uses custLogin() and custReg() to allow the employee to login as a customer.

void accMngmnt(){
	int decided = 0;
	char decision;
	struct User customer;
	system("cls");
	printf("You have selected 'Accounting Management'.\n\nPlease input username of customer's data that you would like to see.\n\nUsername: ");
	scanf("%s", &currUN);//This is the username the employee wants to look at.
	
	
	int dataLine = getDataLine(); //Gets the data line of the username.
	//Gets the current data for the specific username.
	customer = getCustData(currUN);
	
	do{
		system("cls");
		displayData(currUN);
		printf("DataLine = %d. Would you like to update this user's information (y/n): ", dataLine);
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
		empDash();
	}else{
		empDash();
	}
}//Looks up the username inputted and searches from the users.txt file for its data line.

void transactHist(){
	int decided = 0;
	char decision;
	FILE* o = fopen("transactions.txt", "r");
	FILE* t = fopen("temp.txt", "w");
	char fileName[20];
	char line[512];
	struct User customer;
	struct Transaction list;
	
	system("cls");
	printf("You have selected 'Transaction History'.\n\nPlease input username of customer's transaction history that you would like to see.\n\nUsername: ");
	scanf("%s", &currUN);
	customer = getCustData(currUN);
	//Gets the current data for the specific username.
	do{
		system("cls");
		printf("%s %s TRANSACTION HISTORY:\n\n", customer.firstName, customer.lastName);
		fprintf(t, "%s %s TRANSACTION HISTORY:\n\n", customer.firstName, customer.lastName);
	while(fgets(line, 512, o) != NULL) {
     	sscanf(line, "%s %s %s %d", &customer.username, &list.mainTrans, &list.transType, &list.amount);
    	if (strcmp(currUN,customer.username) == 0){//If it matches with the username in the transactions file, prints the line.
    		if(strcmp(list.transType,"Deposit:Current") == 0||strcmp(list.transType,"Pay-Loan:")==0||strcmp(list.transType,"Deposit:Savings")==0){
    			printf("%s\t%s\t\t%d\n", list.mainTrans, list.transType, list.amount);
    			fprintf(t, "%s\t%s\t\t%d\n", list.mainTrans, list.transType, list.amount);
			}else{
				printf("%s\t%s\t%d\n", list.mainTrans, list.transType, list.amount);
				fprintf(t, "%s\t%s\t%d\n", list.mainTrans, list.transType, list.amount);
			}
		}
	}
	printf("\nWould you like to save this transaction history (y/n)? ");
	scanf(" %c", &decision);
	if(decision == 'y'||decision=='n'){
		decided = 1;
	}
	}while(decided == 0);
	
	if(decision=='y'){
		printf("\nWhat would you like to name the file? ");
		scanf("%s",&fileName);
		fclose(o);
		fclose(t);
		rename("temp.txt", strcat(fileName, ".txt"));
		empDash();
	}else{
		fclose(o);
		fclose(t);
		remove("temp.txt");
		empDash();
	}
	fclose(o);
}//Uses the transactions.txt file to locate all the transactions by the users. If the username in the transactions file matches the username
//of the customer the employee wishes to look at, displays all transactions by that customer.


void transferMoney(){
	system("cls");
	printf("You have selected 'Transfer Money'.\n\nEnter username of customer: ");
	scanf("%s", &currUN);
	struct User customer = getCustData(currUN);
	
	int decision = 0;
	int amount = 0;
	do{
	system("cls");
	printf("Where would you like to withdraw funds:\n\n[1] Savings\n[2] Current\n[3] Back\n\nOption: ");
	scanf("%d", &decision);
	}while(decision>3||decision<1);
	printf("\n\nEnter amount: ");
	scanf("%d", &amount);
	switch(decision){
		case 1:{
			if(amount>customer.savings||amount<0){
				do{
					printf("Insufficient funds.\n\nPlease enter different amount: ");
					scanf("%d", &amount);
				}while(amount>customer.savings||amount<0);
				updateFinances((0-amount), 0, customer.loan, 0);
				empDash();
			}else{
				updateFinances((0-amount), 0, customer.loan, 0);
				empDash();
			}
			break;
		}//When choosing to transfer money from customer Savings account.
		case 2:{
			if(amount>customer.savings||amount<0){
				do{
					printf("Insufficient funds.\n\nPlease enter different amount: ");
					scanf("%d", &amount);
				}while(amount>customer.current||amount<0);
				updateFinances(0,(0-amount), customer.loan, 0);
				empDash();
			}else{
				updateFinances(0,(0-amount), customer.loan, 0);
				empDash();
			}
			break;
		}//When choosing to transfer money from customer Current account.
		case 3:{
			empDash();
			break;
		}
	}
}

void loanMngmnt(){
	int decision = 0;
	int decided = 0;
	char hold;
	char del;
	char fileName[20];
	char loanStatus[10];
	char loanType[15];
	
	system("cls");
	printf("You have selected 'Loan Management'.\n\nEnter username of customer: ");
	scanf("%s", &currUN);
	int dataLine = getDataLine();//To identify which line to delete when choosing to close account.
	struct User customer = getCustData(currUN);
	
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
	}//Identifies the details of the loan values inside the data line.
	
	do{
		system("cls");
		printf("What would you like to do?\n\n[1] Close account\n[2] Check Loan Details\n[3] Generate Account Report\n[4] Back\n\nOption: ");
		scanf("%d", &decision);
	}while(decision>4||decision<1);
	switch(decision){
		case 1:{
			do{
				system("cls");
				printf("Are you sure you want to close %s %s's account (y/n)? ");
				scanf(" %c", &del);
				if(decision == 'y'||decision=='n'){
					decided = 0;
				}
			}while(decided == 0);
			if(decision == 'y'){
				updateData(dataLine);
			}else{
				empDash();
			}//When choosing to delete an account, deletes the data line for that specific username.
			break;
		}
		case 2:{
			system("cls");
			printf("%s %s's Current Loan Details:\n\nLoan Status: %s\nLoan Type: %s\nPending Loan Balance: %d\n\nEnter any key to continue...", customer.firstName, customer.lastName, loanStatus, loanType, customer.loanAmt);
			scanf(" %c", &hold);
			empDash();
			break;
		}//Does the same as customer accBalance() loan details display.
		case 3:{
			FILE* r = fopen("temp.txt", "w");//Temporary file to write the report into.
			do{
				system("cls");
				printf("ACCOUNT REPORT\n\nName: %s %s\n\n------Account Balance------\nSavings: %d\nCurrent: %d\n\n------Loan Details------\nLoan Status: %s\nLoan Type: %s\nPending Loan Balance: %d\n\nWould you like to save this report (y/n)? ",
				customer.firstName, customer.lastName, customer.savings, customer.current, loanStatus, loanType, customer.loanAmt);
				scanf(" %c", &decision);
				if(decision == 'y'||decision=='n'){
						decided = 1;
				}
			}while(decided==0);
			if(decision == 'y'){
				printf("What will you name this file? ");
				scanf("%s", &fileName);
				fprintf(r,"ACCOUNT REPORT\n\nName: %s %s\n------Account Balance------\nSavings: %d\nCurrent: %d\n------Loan Details------\nLoan Status: %s\nLoan Type: %s\nPending Loan Balance: %d ",
				customer.firstName, customer.lastName, customer.savings, customer.current, loanStatus, loanType, customer.loanAmt);
				fclose(r);
				rename ("temp.txt", strcat(fileName, ".txt"));
				empDash();
			}else{
				fclose(r);
				empDash();	
			}
			break;
		}//Simply shows all the balances on the customer account. Can be saved as txt file.
		case 4:{
			empDash();
			break;
		}
	}
}
	
