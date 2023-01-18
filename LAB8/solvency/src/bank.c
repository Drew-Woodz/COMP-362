/*
Axel Mora
COMP 362 L
Lab 08
10/17/2022
*/


#include "bank.h"

int numOfCustomers;        // the number of customers of the bank
int numOfAccounts;         // the number of accounts offered by the bank

double *available;    // the amount available of each customer
double **maximum;     // the maximum demand of each customer
double **allocation;  // the amount currently allocated to each customer
double **need;     // the remaining needs of each customer

/***
 * Read the state of the bank from a file.
 *
 * The file format is as follows:
 *
 * <num of customers> <num of accounts>
 * <initial state of accounts>
 * <max needs for each customer>
 *
 * e.g.,
 *
 * 5 3
 * 15 10 5
 * 7,5,3
 * 3,2,2
 * 9,0,2
 * 2,2,2
 * 4,3,3
 *
 * Any of  ", \n\t" is a valid separator
 *
 */
void loadBankState()
{
    // create the bank
    initBank();

    // read initial values for maximum array
    for (int i = 0; i < numOfCustomers; i++)
        addBankCustomer(i);
}

/***
 * Initialize the bank for a number of accounts and customers.
 */
void initBank()
{
    double in[2];
    readLine(in);
    numOfCustomers = (int) in[0];
    numOfAccounts = (int) in[1];

    available = calloc(numOfAccounts, sizeof(double));
    readLine(available);

    // initialize the accounts
    maximum = calloc(numOfCustomers, sizeof(double *));
    allocation = calloc(numOfCustomers, sizeof(double *));
    need = calloc(numOfCustomers, sizeof(double *));
}

/***
 * This function adds a customer to the bank system.
 * It records its maximum fund demand with the bank.
 */
void addBankCustomer(int customerNum)
{
    maximum[customerNum] = calloc(numOfAccounts, sizeof(double));
    readLine(maximum[customerNum]);

    allocation[customerNum] = calloc(numOfAccounts, sizeof(double));
    // we start with zero allocated

    need[customerNum] = calloc(numOfAccounts, sizeof(double));
    arraycpy(need[customerNum], maximum[customerNum], numOfAccounts);
}

/***
 * Outputs the state of the bank; i.e., funds in each account of each customer
 */
void displayBankState()
{
    printf("%13s", "Available =");
    display(available, numOfAccounts);

    printf("\n%13s", "Allocation =");
    for (int i = 0; i < numOfCustomers; i++)
        display(allocation[i], numOfAccounts);

    printf("\n%13s", "Max =");
    for (int i = 0; i < numOfCustomers; i++)
        display(maximum[i], numOfAccounts);

    printf("\n%13s", "Need =");
    for (int i = 0; i < numOfCustomers; i++)
        display(need[i], numOfAccounts);

    printf("\n");
}


/***
 * Determines whether the currect system state is safe.
 */
bool isSafeState(int customerNum, double *request)
{
    //Safety Algorithm

    //Array to store the safe sequence of customers to handle
    int safeSequence[numOfCustomers];

    //Step 1    
    double work[numOfAccounts];    
    bool finish[numOfCustomers];

    arraycpy(work, available, numOfAccounts );

    set(false, finish, numOfCustomers);

    //Step 2
    int count = 0;
    while (count < numOfCustomers) {
        
        bool foundUnfinishedCustomer = false;

        //Iterating through each customer to find one that's NOT finished
        for (int customer = 0; customer < numOfCustomers; customer++) {
            
            //If we find a customer that's NOT finished
            if (finish[customer] == false) {
                
                //For all 3 resources, checking if need[i] <= work
                lessOrSame(*need, work, numOfAccounts);


                //Step 3
                //We get here if all 3 of the customer's needs are satsified
                if(numOfAccounts) {
                    
                    /*
                    Freeing resources which represent the allocated funds,
                    by adding amount of funds allocated to work,
                    which in itself is the available loan limit.
                    */
                   add(work, *allocation, numOfAccounts);

                   //Appends the customer to the list of sequences which are safe
                   safeSequence[count++] = customer;
                
                   //Setting the customer as finished
                   finish[customer] = true;

                   /*
                   We found a customer that was not finished,
                   and now that its needs are satsified,
                   we can set it to true
                   */
                   foundUnfinishedCustomer = true;
                } 

            }
        }

        //If we couldn't find a next customer that is safe, return false.
        if (foundUnfinishedCustomer == false) {
            return false;
        }


    }

    //Displays the list of safe sequences of customers
    
    printf("\n");
    printf("The customers that could be satisfied (in order): ");
    for (int i = 0; i < numOfCustomers; i++) {
        printf("%d ", safeSequence[i]);
    }

    return true;
}

/***
 * Determines whether a request for loan can be granted.
 */
bool solvencyTest(int customerNum, double *request)
{
    // TODO implement
    
    //Formulas
    // Max = Need + Allocation
    // Need = Max - Allocation

    // 1. Is the customer requesting an amount less than what they need?

    // Need = Max - Allocation
    sub2(*need, *maximum, *allocation, customerNum);
    
    //Checking if the amount requested is greater than the customer's Available loan limit.
    if ( !lessOrSame(request, need[customerNum], numOfAccounts) ) {
        
        // 3. Return the result of the test.
        return false;
    }

    // 2. Does the bank have enough money to grant the request?

    isSafeState(customerNum, request);

    //Checking if the amount requested is greater than the bank's treasury.
    if ( !lessOrSame(request, available, numOfAccounts) ) {
        
        // 3. Return the result of the test.
        return false;
    }

    // 3. Return the result of the test.
    return true; // TODO: modify as appropriate
}

/***
 * Make a request for a loan.
 */

bool borrow(int customerNum, double funds[])
{
    // 1. Performs the checks needed to determine if the customer’s request can be granted.
    bool ret = solvencyTest(customerNum, funds);

    // TODO: complete
    
    //if bank is not solvent, ret is false
    if ( !ret ) {

        // 3. Returns boolean indicated whether or not the loan was granted
        return false;
    }

    // 2. If it passes the checks then grant and process the loan. 

    //Subtracts loan amount from the bank's treasury.
    sub(available, funds, numOfAccounts);

    //Adds loan amount to the customer's balance.
    add(*allocation, funds, numOfAccounts);

    //Subtracts loan amount from the customer's need.
    sub(*need, funds, numOfAccounts);

    // 3. Returns boolean indicated whether or not the loan was granted
    return ret;
}

/***
 * Repay a loan.
 */
bool repay(int customerNum, double funds[])
{
    bool ret = lessOrSame(funds, allocation[customerNum], numOfAccounts);

    // TODO: complete

    // 1. Checks whether the customer has enough money allocated (borrowed) to repay the specified amount.
    
    //Checking if the customer did not borrow anything yet.
    if ( allocation <= 0 ){

        // 3. Return a boolean indicating whether or not the payment succeeded.
        return false;
    }

    // 2. If the above check passes then proceed with the repayment request.
    
    //Adds repayment amount to the bank's treasury.
    add(available, funds, numOfAccounts);

    //Subtracts repayment amount from the customer's balance.
    sub(*allocation, funds, numOfAccounts);

    //Adds repayment amount to the customer's need.
    add(*need, funds, numOfAccounts);


    // 3. Return a boolean indicating whether or not the payment succeeded.
    return ret;
}


/***
 * In a loop, take input from the standard console until 'Q' or 'q' is entered.
 *
 * Each input should have the following syntax:
 *
 * {Q[UIT] | ST[ATUS] | [BO[RROW] | RE[PAY]] <customer number>  {<account funds> ...}}
 *
 * e.g. (for 3 accounts and with at least 2 customers):
 *
 * ST
 * BO 1 3 2 1
 * RE 1 1 0 1
 * QUIT
 *
 */
void bankTeller()
{
    // now loop reading requests to withdraw or deposit funds
    double request[numOfAccounts];
    char *inp = malloc(MAX_LINE_SIZE * sizeof(char));
    while (true)
    {
        printf("Teller: How may I help you? > ");

        if (fgets(inp, MAX_LINE_SIZE, stdin) == 0)
            break;

        if (strlen(inp) == 0)
            goto exception;

        // need a copy, since "line" will be used for tokenizing, so
        // it will change until it gets NULL; we would nnot be able to re-use it
        char *line = strdup(inp);

        // get transaction type - borrow (BO) or repay (RE) or ST (status)
        line[strlen(line) - 1] = '\0';

        if (line == NULL)
            goto exception;

        char *trans = strsep(&line, " ,\t");
        strToUpper(&trans); // so the case does not matter

        printf("REQUEST: %s\n", trans);
        if (trans[0] == 'Q')
        {
            displayBankState();
            exit(1);
        }
        else if (strncmp(trans, "STATUS", 2) == 0)
            displayBankState();
        else
        {
            if ((strncmp(trans, "BORROW", 2) != 0) && (strncmp(trans, "REPAY", 2) != 0))
                goto exception;

            // get the customer number making the tranaction
            if (line == NULL)
                goto exception;

            int custNum = strtod(strsep(&line, " "), NULL);
            printf("CLIENT %d: ", custNum);

            if (custNum >= numOfCustomers)
                goto exception;

            // get the resources involved in the transaction
            for (int i = 0; i < numOfAccounts; i++)
            {
                if (line == NULL)
                    goto exception;

                request[i] = strtod(strsep(&line, " ,\t"), NULL);
            }

            display(request, numOfAccounts);

            // now check the transaction type
            if (strncmp(trans, "BORROW", 2) == 0)
            {
                if (borrow(custNum, request))
                    printf("\n*APPROVED*\n");
                else
                    printf("\n*DENIED*\n");
            }
            else if (strncmp(trans, "REPAY", 2) == 0)
            {
                if (repay(custNum, request))
                    printf("\n*APPROVED*\n");
                else
                    printf("\n*DENIED*\n");
            }
            continue;
            exception:
            printf("\nExpected input: Q[UIT] | ST[ATUS] | [BO[RROW] | RE[PAY]] <customer number> <resource #1> <#2> <#3> ...\n");
            continue;
        }
    }
}

/***
 * Read a line of values separated by a set of delimeters from a file into an array
 */
void readLine(double array[])
{
    char *line = malloc(MAX_LINE_SIZE * sizeof(char));
    fgets(line, MAX_LINE_SIZE, stdin);
    char *tok;
    int i = 0;
    while ((tok = strsep(&line, ", \n\t")) != NULL)
        if (strlen(tok) > 0)
            array[i++] = strtod(tok, NULL);

    free(line);
}

/***
 * Convert the string to upper case
 */
void strToUpper(char **s)
{
    for (char *c = *s; *c; c++)
        if (isascii(*c) && islower(*c))
            *c = toupper(*c);
}
