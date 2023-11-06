char currUN[20];
char currPW[20];

typedef struct User{
	char firstName[20];
	char lastName[20];
	int age;
	char gender[20];
	char address[40];
	char occupation[20];
	char nationality[20];
	int height;
	int weight;
	char status[20];
	char username[20];
	char password[20];
	int savings;
	int current;
	int loan;
	int loanAmt;	
};//Contains all the details for Customers.

typedef struct Transaction{
	char mainTrans[20];
	char transType[20];
	int amount;
};//Used for Transaction History. Check transHist() function in Employee.



//Helper Functions
void mainMenu();//Start of program. When menu() chooses to go back, goes back to this. Can choose from Customer/Employee.
void menu(int type);//Specific menus for each type of user (Customer/Employee). "int type" parameter is used to determine what type of user.
struct User getCustData(char userName[20]);//A helper function to get the data from the txt files. More details in the function.
int getDataLine();//Identifies which line in the txt file belongs to a specific Customer.
void appendData(struct User customer);//Adds the new data to the users.txt file.
void displayData(char userName[20]);//Simply used for printing the data in the User struct;
void updateData(int dataLine);//Removes a specific line to be replaced by the new data inside appendData();
struct User inputData(struct User customer);//Used for inputting data into the values inside the User struct.
void updateFinances(int savings, int current, int loan, int loanAmt);//Useful in the PAYMENT(), applyLoan(), and transferMoney() functions.



//The following functions are explained in more detail in their respective functions.

//Customer Functions
void custLogin();//Login
void custReg();//Registration. Saves into the users.txt file.
void custDash();//Dashboard
void custDisp();//Display Account Details. All details inside User struct.
void accBalance();//Display Account Balance. Savings, Current, and Loan Balance.
void PAYMENT();//PAYMENT option. Deposit or Pay Loan
void applyLoan();//Short-term or Long-term Loans.


//Employee Functions
void empLogin();//Login
void empReg();//Registration. Saves into the employee.txt file.
void empDash();//Dashboard
void userRegLog();//User Registration and Login.
void accMngmnt();//Looking up a customer using their username. Can choose to update their details.
void transactHist();//Transaction history of customer. Scans through the transactions.txt file. Output can be saved into txt file.
void transferMoney();//Transfer money to bank. Choose from Savings or Current.
void loanMngmnt();//Checks loan details of user. Generate report of overall status of customer account. Can be saved into a txt file.
