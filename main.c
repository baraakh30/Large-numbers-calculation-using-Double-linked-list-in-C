//Name : Baraa Khanfar
// Id : 1210640
//section No : 5

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* prev;
    struct Node* next;
} Node;
//doubly link list and its not circular since
//the next of the tail is always null
//i added the tail because in some operations wee need to start from the last

typedef struct DDL
{
    Node* head;
    Node* tail;
    int size;
} DDL;
DDL* subtractLists(DDL* list1, DDL* list2);
DDL* addLists(DDL* list1, DDL* list2);

//initializing the list
DDL* createList()
{
    DDL* list = (DDL*) malloc(sizeof(DDL));
    list->head = NULL;
    list->size=0;
    list->tail = NULL;
    return list;
}
//inserting node at the end of the list
void insertNodeAtLast(DDL* list, int data)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        list-> size++;
        return;
    }
    list->size++;
    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
}
//inserting in the head of the list
void insertNodeAtFirst(DDL* list, int data)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->size++;
}
//deleting the head of the list
void deleteFirst(DDL* list)
{
    if (list->head == NULL || list->size==0)
    {
        printf("Err: The List is Empty!\n\n");
        return;
    }

    Node* temp = list->head;
    list->head = list->head->next;

    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    else
    {
        list->head->prev = NULL;
    }
    list->size--;
    free(temp);
}
//deleting last node in the list
void deleteLast(DDL* list)
{
    if (list->tail == NULL || list->size==0)
    {
        printf("Err: The List is Empty!\n\n");
        return;
    }

    Node* temp = list->tail;
    list->tail = list->tail->prev;

    if (list->tail == NULL)
    {
        list->head = NULL;
    }
    else
    {
        list->tail->next = NULL;
    }
    list->size--;

    free(temp);
}

//compare lists and returns 1 if the first is bigger,0 if both are the same and -1 if the first is smaller
int compareLists(DDL* list1, DDL* list2)
{
    if (list1->size > list2->size)
    {
        return 1;
    }
    else if (list1->size < list2->size)
    {
        return -1;
    }
    else
    {
        Node* current1 = list1->head;
        Node* current2 = list2->head;
        while (current1 != NULL)
        {
            if (current1->data > current2->data)
            {
                return 1;
            }
            else if (current1->data < current2->data)
            {
                return -1;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return 0;
    }
}
//returning the compare of the absolute value of the lists
//by multiplying the list head by -1 if the list is negative
int absCompareLists (DDL* list1,DDL* list2)
{
    if(list1->head->data<0 && list2->head->data>=0)
    {
        list1->head->data*=-1;
        int abs=compareLists(list1,list2);
        list1->head->data*=-1;
        return abs;

    }
    else if(list2->head->data<0 && list1->head->data>=0)
    {
        list2->head->data*=-1;
        int abs=compareLists(list1,list2);
        list2->head->data*=-1;
        return abs;
    }
    else if(list1->head->data<0 && list2->head->data<0)
    {
        list1->head->data*=-1;
        list2->head->data*=-1;
        int abs=compareLists(list1,list2);
        list1->head->data*=-1;
        list2->head->data*=-1;
        return abs;

    }

    else return compareLists(list1,list2);

}

//copies a list and returns the copy
DDL* copyList(DDL* list2)
{
    DDL* list=createList();
    Node * current=list2->head;
    while(current!=NULL )
    {
        insertNodeAtLast(list,current->data);
        current=current->next;
    }
    return list;
}
//prints the list
void printList(DDL* list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}
//frees the list along with each node in it
void freeList(DDL* list)
{
    Node* current=list->head;
    while(current!=NULL )
    {
        Node * temp=current;
        current=current->next;
        free(temp);

    }
    free(list);
}

//add one list to another
DDL* addLists(DDL* list1, DDL* list2)
{
    //if one of the lists is null
    //it will return null
    if (list1==NULL || list2==NULL  || list1->head == NULL || list2->head == NULL )
    {
        printf("Error : Invalid Input List.\n\n");
        return NULL;
    }

    int sign =0;
    int absCmp=absCompareLists(list1,list2);
    // if the first is negtaive and the other isnt
    //it will return the subtract of the first from the second
    //without the sign
    if(list1->head->data<0 && list2->head->data>=0)
    {
        if(absCmp==0)
        {
            DDL* result = createList();
            insertNodeAtLast(result, 0);
            return result;
        }

        list1->head->data*=-1;
        DDL*  result=subtractLists(list2,list1);
        list1->head->data*=-1;
        return result;
    }
    // if the first is negtaive and the other isnt
    //it will return the subtract of the second from the first
    //without the sign
    if(list1->head->data>=0 && list2->head->data<0 )
    {
        if(absCmp==0)
        {
            DDL* result = createList();
            insertNodeAtLast(result, 0);
            return result;
        }

        list2->head->data*=-1;
        DDL* result=subtractLists(list1,list2);
        list2->head->data*=-1;
        return result;

    }
    // if they are both negatvies , it will cancel the negative and add them
    //and and negative to the result
    if(list1->head->data<0 && list2->head->data<0 )
    {
        list2->head->data*=-1;
        list1->head->data*=-1;
        sign=1;
    }
    Node* current1 = list1->tail;
    Node* current2 = list2->tail;
    int carry = 0;
    DDL* result = createList();
    /*performing the addition
     it will start from the tail
      adding each digit in the first list along with the corresponding digit
      in the second list and calculating the carry
      if it exists
    it will added it to the next loop
    then it inserts the sum at the head of the result list
    */
    while (current1 != NULL || current2 != NULL)
    {
        int sum = carry;
        if (current1 != NULL)
        {
            sum += current1->data;
            current1 = current1->prev;
        }
        if (current2 != NULL)
        {
            sum += current2->data;
            current2 = current2->prev;
        }
        carry = sum / 10;
        insertNodeAtFirst(result, sum % 10);
    }
    if (carry > 0)
    {
        insertNodeAtFirst(result, carry);
    }
    //if both of the lists is negatives
    if(sign)
    {
        result->head->data*=-1;
        list2->head->data*=-1;
        list1->head->data*=-1;

    }
    return result;
}

DDL* subtractLists(DDL* list1, DDL* list2)
{
    //if one of the lists is null
    //it will return null
    if (list1==NULL || list2==NULL  || list1->head == NULL || list2->head == NULL )
    {
        printf("Error : Invalid Input List.\n\n");
        return NULL;
    }

    int sign = 0;
    int absCmp=absCompareLists(list1,list2);
    // Check for negative numbers
    // if the first list is negative and the other isnt
    // it will add them without the sign and then assign neagtive
    //to the result
    if (list1->head->data <0 && list2->head->data >=0)
    {

        list1->head->data*=-1;

        DDL* result = addLists(list1, list2);
        list1->head->data*=-1;
        result->head->data*=-1;
        return result;
    }
    //if the second list is negative
    //it will add them without the sign
    // and the add function will handle
    // the negativity of the first list
    if (list2->head->data <0)
    {
        list2->head->data*=-1;
        DDL* result = addLists(list1, list2);
        list2->head->data*=-1;
        return result;
    }

// if the seoncd list is bigger
//it will swap them and assign negative to the result
    if (absCmp==-1)
    {
        DDL* temp = list1;
        list1 = list2;
        list2 = temp;
        sign = 1;
    }
    Node* current1 = list1->tail;
    Node* current2 = list2->tail;
    int borrow = 0;
    DDL* result = createList();
    // Perform subtraction
    /*it works the same as addition works
    the difference that there is borrow instead of carry
    and it will subtract the second list node digit from the corresponding
    digit from the first list
    */
    while (current1 != NULL || current2 != NULL)
    {
        int diff = borrow;
        if (current1 != NULL)
        {
            diff += current1->data;
            current1 = current1->prev;
        }
        if (current2 != NULL)
        {
            diff -= current2->data;
            current2 = current2->prev;
        }
        borrow = 0;
        if (diff < 0)
        {
            borrow = -1;
            diff += 10;
        }
        insertNodeAtFirst(result, diff);
    }

    //remove the zeros from the subtracion
    while (result->size > 1 && result->head->data == 0)
    {
        deleteFirst(result);
    }
//assigning negative if the second is bigger
    if (sign)
    {
        result->head->data*=-1;

    }

    return result;
}
DDL* multiplyLists(DDL* list1, DDL* list2)
{
    //if one of the lists is null
    //it will return null
    if (list1==NULL || list2==NULL  || list1->head == NULL || list2->head == NULL )
    {
        printf("Error : Invalid Input List.\n\n");
        return NULL;
    }
    //if one of the lists is zero
    //it will return zero
    if((list1->size==1 && list1->head->data==0)||(list2->size==1 && list2->head->data==0))
    {

        DDL* result = createList();
        insertNodeAtLast(result, 0);
        return result;
    }
    int sign=0;
    //to determine the sign of the result
    if(list1->head->data<0 )
    {
        list1->head->data*=-1;
        sign+=1;
    }
    if( list2->head->data<0)
    {

        list2->head->data*=-1;
        sign+=2;
    }


    Node* current1 = list1->tail;
    Node* current2 = list2->tail;
    DDL* result = createList();

    int len = list1->size+list2->size;
    //calloc will allocate them and initialize them with zeros
    int* product = (int*) calloc(len,sizeof(int));

    /*
    the outer loop iterates over each digit in the first list
    and initializes the carry with 0 to keep tract of it
    and the inner loop is used to multiply each digit from the first list
    with all digits in the second list
    it computes the product and extracts the carry from it using /10
    and then extracts the digit without the carry using %
    and then it adds the computed digit to the corresponding position in the product array
    and computes the carry from the addition
    then updates the current position to be a single digit
    using % again

    */
    current1 = list1->tail;
    for (int i = 0; i < list1->size; i++)
    {
        current2 = list2->tail;
        int carry = 0;
        int j = 0;
        while (current2 != NULL)
        {
            int temp = current1->data * current2->data + carry;
            carry = temp / 10;
            temp = temp % 10;
            product[i + j] += temp;
            carry += product[i + j] / 10;
            product[i + j] %= 10;
            current2 = current2->prev;
            j++;
        }
        if (carry > 0)
        {
            product[i + j] += carry;
        }
        current1 = current1->prev;
    }

    int i = len - 1;
    //skipping the zeros at the last indexes
    while (i >= 0 && product[i] == 0)
    {
        i--;
    }
    //if the result is zero
    if (i < 0)
    {
        insertNodeAtLast(result, 0);
        return result;
    }
    //inserting the result of the multiplying
    //this line wont be reached
    while (i >= 0)
    {
        insertNodeAtLast(result, product[i]);
        i--;
    }
    //determining result sign
    if(sign==1)
    {
        list1->head->data*=-1;
        result->head->data*=-1;
    }
    else if(sign==2)
    {
        list2->head->data*=-1;
        result->head->data*=-1;
    }
    else if(sign==3)
    {
        list1->head->data*=-1;
        list2->head->data*=-1;
    }
    free(product);
    return result;
}

/*this will calculate the division along with the reminder
it will return them as an array
it will add '/' at the head of the reminder
so the program can determine if its
a reminder or not
*/
DDL** divideLists(DDL* dividend, DDL* divisor)
{
    if (dividend == NULL || divisor == NULL || dividend->head==NULL || divisor->head==NULL)
    {
        printf("Error: Invalid input lists");
        return NULL;
    }
    //if the divisor is zero it will return null
    if (divisor->size == 1 && divisor->head->data == 0)
    {
        printf("Error: Division by zero");

        return NULL;
    }
    //if the divisor is 1 it will return the dividend
    if((divisor->size==1 && divisor->head->data==1))
    {
        DDL** results=(DDL**) malloc(2*sizeof(DDL));
        results[0]= copyList(dividend);
        results[1]= createList();
        insertNodeAtLast( results[1], 0);
        insertNodeAtFirst(results[1],'/');
        return results;
    }
//if the dividend is zero it will return zero
    if((dividend->size==1 && dividend->head->data==0))
    {
        DDL** results=(DDL**) malloc(2*sizeof(DDL));
        results[0]= createList();
        insertNodeAtLast( results[0], 0);
        results[1]= createList();
        insertNodeAtLast( results[1], 0);
        insertNodeAtFirst(results[1],'/');
    }
    int absCmp=absCompareLists(dividend,divisor);
    //(dividend->size==1 && dividend->head->data==0)
    if ( (absCmp < 0) )
    {
        DDL* result = createList();
        insertNodeAtLast(result, 0);
        DDL** results=(DDL**) malloc(2*sizeof(DDL));
        results[0]=copyList(result);
        DDL* rem =copyList(dividend);
        insertNodeAtFirst(rem,'/');
        results[1]=copyList(rem);
        freeList(rem);
        freeList(result);

        return results;
    }
    int sign=0;
    //to determine the sign of the result
    if(dividend->head->data<0 )
    {
        dividend->head->data*=-1;
        sign+=1;
    }
    if( divisor->head->data<0)
    {

        divisor->head->data*=-1;
        sign+=2;
    }

//if the value of both of the divisor and dividend
//it will return 1 along with a zero reminder and
//the right sign
    if(absCmp==0)
    {

        DDL* result = createList();
        DDL* rem=createList();
        insertNodeAtFirst(rem,0);
        if(sign==1)
        {
            insertNodeAtLast(result, -1);
            dividend->head->data*=-1;
        }
        else if(sign==2)
        {
            insertNodeAtLast(result, -1);
            divisor->head->data*=-1;
        }
        else if(sign==3)
        {
            insertNodeAtLast(result, 1);
            dividend->head->data*=-1;
            divisor->head->data*=-1;
        }
        else  insertNodeAtLast(result, 1);
        DDL** results=(DDL**) malloc(2*sizeof(DDL));
        results[0]=copyList(result);
        results[1]=copyList(rem);
        freeList(result);
        freeList(rem);
        return results;
    }


    DDL* result = createList();
    DDL* rem = createList();
    Node* digit = dividend->head;
    //it will keep adding each digit from the first
    //to the reminder and when it becomes the same or bigger than
    //the divisor it will perform subtracting and incrementing the
    //quotient until it becomes smaller than it
    while (digit != NULL)
    {
        insertNodeAtLast(rem, digit->data);
        if(rem->size==1 && rem->head->data==0) deleteFirst(rem);
        digit = digit->next;
        int quotient = 0;
        while (compareLists(rem, divisor) >= 0)
        {

            DDL* temp=rem;
            rem = subtractLists(rem, divisor);
            freeList(temp);
            quotient++;
        }
        insertNodeAtLast(result, quotient);
    }

    while (result->size > 1 && result->head->data == 0)
    {
        deleteFirst(result);
    }


//determining the result sign
    if(sign==1)
    {
        result->head->data*=-1;
        dividend->head->data*=-1;
    }
    else if(sign==2)
    {
        result->head->data*=-1;
        divisor->head->data*=-1;
    }
    else if(sign==3)
    {
        dividend->head->data*=-1;
        divisor->head->data*=-1;
    }
    DDL** results=(DDL**) malloc(2*sizeof(DDL));
    results[0]=copyList(result);
    insertNodeAtFirst(rem,'/');
    results[1]=copyList(rem);
    freeList(rem);
    freeList(result);
    return results;
}

DDL* readList(FILE* fp)
{
    // this will read  list from the file and return it
    //if the file isnt valid it will return null
    DDL* list =createList();
    int ch = fgetc(fp);
    int sign=0;
    if (ch=='-')
    {
        sign=1;
        ch = fgetc(fp);
    }
    do
    {
        if(ch=='\n') break;
        else if(ch<'0' || ch>'9')
        {
            printf("The file entered isnt valid, the system will return\n");
            return NULL;
        }
        if(sign)
        {
            int d= ch-'0';
            d*=-1;
            insertNodeAtLast(list,d);
            sign=0;
            continue;
        }
        insertNodeAtLast(list, ch - '0');
        //  ch = fgetc(fp);
    }
    while((ch = fgetc(fp)) != EOF);
    while(list->size>=1 && list->head->data==0)
        deleteFirst(list);
    return list;
}
//this will count how many lines in the file
// to use it in the main to create an array of lists
int countLines(FILE* fp)
{
    int count = 0;
    char ch = 0;
    char temp=0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
        temp=ch;
    }
    rewind(fp);
    if(temp=='\n') return count;
    return count + 1;  // add 1 for the last line (which may not end with '\n')
}

void DisplayMeun ()
{

    printf("\033[33m"); // set text color to yellow
    printf("===============================================\n");
    printf("|        Welcome To calculator System         |\n");
    printf("===============================================\n");
    printf("|                                             |\n");
    printf("|           1. Read input file                |\n");
    printf("|           2. Add numbers from Another file  |\n");
    printf("|           3. Print numbers in the file      |\n");
    printf("|           4. Print results                  |\n");
    printf("|           5. Add                            |\n");
    printf("|           6. Subtract                       |\n");
    printf("|           7. Multiply                       |\n");
    printf("|           8. Divide                         |\n");
    printf("|           9. Print results to output file   |\n");
    printf("|           10. Show the menu again           |\n");
    printf("|           11. Exit                          |\n");
    printf("|                                             |\n");
    printf("===============================================\n\n");
}
/*this will get the numbers, operation,number of lines,the size of the results\
and the results
 if the operation is division
it will just ask the user to enter the number of the lists you want to divide
other wise the user will get another options
like evaluating range of numbers */
void evaluate(DDL* nums[],int* size,int lines,char mode,DDL* res[])
{
    int div=0;
    // if lines  is two the user wont get options
    if(lines==2 )
    {
        switch (mode)
        {
        case '+' :
            res[*size]=addLists(nums[0],nums[1]);
            break;
        case '-' :
            res[*size]=subtractLists(nums[0],nums[1]);
            break;
        case '*' :
            res[*size]=multiplyLists(nums[0],nums[1]);
            break;
        case '/' :
            DDL** temp=divideLists(nums[0],nums[1]);
            if(temp!=NULL)
            {
                res[*size]=copyList(temp[0]);
                *size=*size+1;
                res[*size]=copyList(temp[1]);
                div=1;
                freeList(temp[0]);
                freeList(temp[1]);
                free(temp);
            }
            else res[*size]=NULL;
            break;
        }
        if(div && res[*size]!=NULL)
        {
            printf("Result : ");
            printList(res[*size-1]);
            printf("   Result reminder : ");
            deleteFirst(res[*size]);
            printList(res[*size]);
            insertNodeAtFirst(res[*size],'/');
            *size=*size+1;
            printf("Since just 2 numbers has been added in the file\nYou cant get other options.\n");
        }
        else if(!div && res[*size]!=NULL)
        {
            printf("Result : ");
            printList(res[*size]);
            *size=*size+1;
            printf("Since just 2 numbers has been added in the file\nYou cant get other options.\n");
        }


        return;
    }
    if(mode!='/')
    {
        int n1,n2;
        printf("Enter 1 for evaluating specific numbers , or 2 for range of numbers : \n");
        scanf("%d",&n1);
        if(n1==1)
        {
            printf("Enter wich numbers to you want to calculate\nUse the form : n1 n2\n");
            scanf("%d %d",&n1,&n2);
            if(n1>=1 && n2<=lines)
            {
                switch(mode)
                {
                case '+' :
                    res[*size]=addLists(nums[n1-1],nums[n2-1]);
                    break;
                case '-' :
                    res[*size]=subtractLists(nums[n1-1],nums[n2-1]);
                    break;
                case '*' :
                    res[*size]=multiplyLists(nums[n1-1],nums[n2-1]);
                    break;

                }
                if(res[*size]!=NULL)
                {
                    printf("Result : ");
                    printList(res[*size]);
                    *size=*size+1;
                    printf("Since just 2 numbers has been added in the file\nYou cant get other options.\n");
                }
            }
            else
                printf("Out Of Range!\n\n");
        }
        else if(n1==2 )
        {
            res[*size]=createList();
            switch(mode)
            {
            case '+' :
            case '-' :
                insertNodeAtLast(res[*size],0);
                break;
            case '*' :
            case '/' :
                insertNodeAtLast(res[*size],1);
                break;
            }

            char temp;
            printf("Use the form n1:n2 or input 0:0 to calculate them all\n");
            scanf("%d%c%d",&n1,&temp,&n2);
            if(n1==0&& n2==0)
            {
                for(int i=0; i<lines; i++)
                {
                    DDL* temp=res[*size];
                    switch(mode)
                    {
                    case '+' :
                        res[*size]=addLists(res[*size],nums[i]);
                        break;
                    case '-' :
                        res[*size]=subtractLists(nums[i],res[*size]);
                        break;
                    case '*' :
                        res[*size]=multiplyLists(res[*size],nums[i]);
                        break;

                    }
                    free(temp);
                }
                if(res[*size]!=NULL)
                {
                    printf("Result : ");
                    printList(res[*size]);
                    *size=*size+1;
                }

            }
            else if (n1>=1 && n2<=lines)
            {
                for(int i=n1-1; i<n2; i++)
                {
                    DDL* temp=res[*size];
                    switch(mode)
                    {
                    case '+' :
                        res[*size]=addLists(res[*size],nums[i]);
                        break;
                    case '-' :
                        res[*size]=subtractLists(nums[i],res[*size]);
                        break;
                    case '*' :
                        res[*size]=multiplyLists(res[*size],nums[i]);
                        break;
                    }
                    free(temp);
                }
                if(res[*size]!=NULL)
                {
                    printf("Result : ");
                    printList(res[*size]);
                    *size=*size+1;
                }

            }
            else
                printf("Out Of Range!\n\n");
        }
        else
        {
            printf("Select a valid option\n\n");
            evaluate(nums,size,lines,mode,res);
        }
    }
    else
    {
        int n1,n2;
        printf("Enter wich numbers to you want to calculate\nUse the form : n1 n2\n");
        scanf("%d %d",&n1,&n2);
        if(n1>=1 && n2<=lines)
        {
            DDL** temp=divideLists(nums[n1-1],nums[n2-1]);
            if(temp!=NULL)
            {
                res[*size]=copyList(temp[0]);
                *size=*size+1;
                res[*size]=copyList(temp[1]);
                div=1;
                freeList(temp[0]);
                freeList(temp[1]);
                free(temp);
            }
            else res[*size]=NULL;

            if( res[*size]!=NULL)
            {
                printf("Result : ");
                printList(res[*size-1]);
                printf("   Result reminder : ");
                deleteFirst(res[*size]);
                printList(res[*size]);
                insertNodeAtFirst(res[*size],'/');
                *size=*size+1;
            }

        }
        else
            printf("Out Of Range!\n\n");

    }
}
//printing the results to the file if the user asked to
void printToFile(FILE* out,DDL* res[],int size)
{
    for(int i=0; i<size; i++)
    {
        if(res[i]->head->data!='/')
            fprintf(out,"Result %d : ",i+1);
        Node* current = res[i]->head;
        while (current != NULL)
        {
            if(current->data=='/')
            {
                fprintf(out,"  Reminder : ");
                current = current->next;
                fprintf(out,"%d", current->data);
                current = current->next;
                continue;

            }
            fprintf(out,"%d", current->data);
            current = current->next;
        }
        fprintf(out,"\n");
    }
}

//this will the read all the numbers from the file
//file name is to be entered by the user
//the mode is  for what option
//1 is for reading he numbers
//0 is for adding numbers
//if the file has less than 2 numbers it will return null
// and the  mode is one it will return null
DDL** readOption(int* read,int* lines,int mode)
{
    printf("Enter the input file name.\n");
    char* filename=(char*)malloc(50*sizeof(char));
    scanf("%s", filename);
    FILE* fp = fopen(filename,"r");
    //keeps asking the user to enter a valid file
    while (fp == NULL)
    {
        printf("Failed to open the file.\n\n");
        printf("Enter the correct name\n\n");
        scanf("%s", filename);
        fp = fopen(filename, "r");
    }
    free(filename);
    *lines=countLines(fp);

    if(*lines<=1 && mode)
    {
        printf("Make Sure to add at least 2 numbers in the file\n %d numbers is added , the system will now restart.\n",*lines);
        return NULL;
    }
    DDL** nums=(DDL**) malloc(*lines*sizeof(DDL));
    for(int i=0; i<*lines; i++)
    {
        nums[i]=  readList(fp);
        if(nums[i]==NULL)
        {
            if(mode) printf("Already added numbers wont be affected\n\n");
            return NULL;
        }
    }
    fclose(fp);
    printf("%d numbers has been read successfully\n\n",*lines);
    *read=1;
    return nums;
}

int main()
{
//allocating the array of results
    DDL** res=(DDL**) malloc(10*sizeof(DDL));
    DDL** nums;
    int size=0;
    //this will become 1 when the numbers is read
    // i used to so i can prevent the user from perfroming
    //any operation until he reads an input file

    int read=0;
    int lines=0;
    printf("\033[2J\033[H");
    DisplayMeun();
    while(1)
    {
        int i=0;
        //reallocating the size of the results
        //if the user reaches the initial size
        if(size==size*i + 9 )  res=(DDL**)realloc(res,(10+(++i + 9))*sizeof(DDL));
        printf("Select an option : \n");
        int n;
        int buffer= scanf("%d",&n);
        //if the user entered a non integer value
        // the program will enter an infinity loop
        //so we have to clear the scan buffer
        if (buffer == 0)
        {
            printf("Invalid input. Please enter an integer.\n");
            // clear input buffer
            scanf("%*[^\n]%*c");
            continue;
        }
        printf("\n");
        switch (n)
        {
        case 1 :
            if(!read)
            {
                nums= readOption(&read,&lines,1);
                break;
            }
            else
            {
                //this will ask the user if he wants to read the file again
                //not adding numbers
                //this will clear the current numbers
                //and then read the other file
                printf("The file has already been read\n\n");
                printf("If you want to read another file enter 1 ,else enter 0 :");

                int q=2;
                scanf("%d",&q);
                if(q==1)
                {
                    printf("\nAre you sure ?\nThis will clear the current numbers,press enter to continue or anything else to cancel\n");
                    char c;
                    scanf("%c",&c);
                    scanf("%c",&c);
                    if(c=='\n')
                    {
                        for(int i=0; i<lines; i++) freeList(nums[i]);
                        free(nums);
                        nums= readOption(&read,&lines,1);
                        break;
                    }
                    else
                    {
                        scanf("%*[^\n]%*c");
                        printf("\n");
                        break;
                    }
                }
                else if(q==0) break;
                else
                {
                    scanf("%*[^\n]%*c");
                    printf("Wrong input,cancelled\n");
                    break;
                }
            }
        case 2 :
            //this is used to add numbers from another file
            //to the current list
            //you also can add the numbers from the same file again
            if(!read)
            {
                printf("You cant use this option before using the first one.\n");
                break;
            }
            int prevLines;
            DDL**  nums2= readOption(&read,&prevLines,0);
            if(nums2==NULL) break;
            lines+=prevLines;
            nums=(DDL**)realloc(nums,lines*sizeof(DDL));
            for(int i=lines-prevLines,j=0; i<lines; i++)
            {
                nums[i]= copyList(nums2[j++]);
            }
            for(int i=0; i<prevLines; i++) freeList(nums2[i]);
            free(nums2);
            break;
        case 3 :
            //this will print the current numbers added
            if(!read)
            {
                printf("Please read a file first\n\n");
                break;
            }
            for(int i=0; i<lines; i++)
            {
                printf("Num %d : ",(i+1));
                printList(nums[i]);
            }
            break;
        case 4 :
            //this will print the results that
            //the user calculated it
            if(!read)
            {
                printf("Please read a file first\n\n");
                break;
            }
            if(size==0)
            {
                printf("Do at least one operation\n\n");
                break;
            }
            for(int i=0; i<size; i++)
                 //if the list is a reminder it will have '/'
                 //at the head

                if(i+1 <size && res[i+1]->head->data=='/')
                {
                     //removing the /
                    deleteFirst(res[i+1]);
                    printf("Result %d : ",i+1);
                    printList(res[i]);
                    printf("   Result reminder : ");
                    printList(res[++i]);
                    // reinserting it
                    insertNodeAtFirst(res[i],'/');
                }
                else
                {
                    printf("Result %d : ",i+1);
                    printList(res[i]);

                }

            break;

        case 5 :
            //adding option
            if(!read)
            {
                printf("Please read a file first\n\n");
                break;
            }
            evaluate(nums,&size,lines,'+',res);
            break;

        case 6 :
            //subtracting
            if(!read)
            {
                printf("Please read a file first\n\n");
                break;
            }
            evaluate(nums,&size,lines,'-',res);
            break;
        case 7:
            //multiplying
            if(!read)
            {
                printf("Please read a file first\n\n");
                break;
            }
            evaluate(nums,&size,lines,'*',res);
            break;
        case 8:
            //dividing
            if(!read)
            {
                printf("Please read a file first\n\n");
                break;
            }
            evaluate(nums,&size,lines,'/',res);
            break;
        case 9 :

            if(!read)
            {
                printf("Please read a file first\n\n");
                break;
            }
            if(size==0)
            {
                printf("Do at least one operation\n\n");
                break;
            }
            //it will ask the user to enter filename
            //and then prints the results in it
            printf("Enter the file name(with the extension).\n");
            char* outputFile=(char*)malloc(50*sizeof(char));
            scanf("%s",outputFile);
            FILE* out = fopen(outputFile,"w");
            free(outputFile);
            printToFile(out,res,size);
            fclose(out);
            break;
        case 10:
            //reshow the menu
            printf("\033[2J\033[H");
            DisplayMeun();
            break;
        case 11:
            //frees the allocated lists and then exit
            for(int i=0; i<size; i++) freeList(res[i]);
            free(res);
            for(int i=0; i<lines; i++) freeList(nums[i]);
            if(read)
                free(nums);
            exit(0);
        default :
            printf("Choose a valid option.\n\n");
            break;
        }
        printf("\n");
    }

    return 0;
}
