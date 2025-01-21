#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


FILE *file;
FILE *temp;
FILE *file1;
FILE *order;


//Structure for Menu.
struct node
{
    int id;
    char a[100];
    float price;
}node;


//Structure for Order.
struct or
{
    int id;
    char name[100];
    int q;
    float tprice;
}or;


//Structure for User Data.
struct user
{
    int id;
    char username[100];
    char pass[100];
}user;


//Structure for Student Data for Discount.
struct student
{
    char uni_name[100];
    char name[100];
    int id;
}st;


//Structure for Table Data.
typedef struct {
    int id;
    int capacity;
    int isAvailable; // 1 for available, 0 for reserved
} Table;


// Structure for Reservation Data.
typedef struct {
    int tableID;
    char customerName[100];
    char date[100]; // Reservation date
    char time[100]; // Reservation time
} Reservation;




// Function prototypes.
void registration();
int login();
void admin();
int initializeAutoId();
void write();
void read();
void search();
void delete();
void update();
void placeorder(int student);
void payment(float total);
void bankTransfer(float total);
void paypalPayment(float total);
void cashOnDelivery();
void customermenu();
void staff();
void display_order();
void reservation();
void initializeTables();
void viewTables();
void reserveTable();
void viewReservations();
void cancelReservation();
int isTableAvailable(int tableID);
void updateTableAvailability(int tableID, int isAvailable);
int isReservationExist(int tableID);
void student_details();



//Home Page / Welcome Page.
void welcomedisplay()
 {
    printf("\n");
    printf("*****************************************************\n");
    printf("                    _______________            \n");
    printf("                   /               \\           \n");
    printf("                  /                 \\          \n");
    printf("      ___________/                   \\__________ \n");
    printf("     |            |      DEMO        |           |\n");
    printf("     |     $$     |      LOGO        |     $$    |\n");
    printf("     |____________|__________________|           |\n");
    printf("     |  __________  ____________  ___  _______ _ |\n");
    printf("     | |          ||            ||   ||         ||\n");
    printf("     | |   _____  ||   ______   ||   ||  _____  ||\n");
    printf("     | |  |     | ||  |      |  ||   || |     | ||\n");
    printf("     | |  |     | ||  |______|  ||   || |     | ||\n");
    printf("     | |  |_____| ||____________||___|| |_____| ||\n");
    printf("     | |          | |            | |             |\n");
    printf("     |____________|_|____________|_|_____________|\n");
    printf("******************************************************\n");
    printf("*                                                    *\n");
    printf("*       WELCOME TO >YOUR_RESTAURANT_NAME<            *\n");
    printf("*                                                    *\n");
    printf("******************************************************\n");
    printf("******************************************************\n");
    printf("*                                                    *\n");
    printf("*         We Serve The Best Food in Town             *\n");
    printf("*                                                    *\n");
    printf("******************************************************\n");
    printf("\n");
}


//Main Menu.
int main(){
    int c=1 , choice,l ;
    welcomedisplay();
    while(c){
        printf("\n");
        printf("                 Please choose an option:            \n");
        printf("-----------------------------------------------------\n");
        printf("      1. Register / Create New Account               \n");
        printf("      2. Login                                       \n");
        printf("      3. Exit                                        \n");
        printf("-----------------------------------------------------\n");
        printf("\n");
        choice = _getch();
        switch(choice){
            case '1':
            registration();
            break;

            case '2':
            l = login();
            if(l==1)
            {
                admin();
            }
            else if(l==2){
                staff();
            }
            else if(l==-1){
                c=0;
            }
            else
            {
             customermenu();
            }
                break;

            case '3':{
                printf("----------------------------------------\n");
                printf("------------- Exiting -_-  -------------\n");
                printf("----------------------------------------\n");
                c=0;
                break;
            }
            default:
            printf("\n      Invalid option! Please Try again.         \n");
        }
    }
    return 0;
}



//Registration Page
void registration() {
    FILE *file = fopen("users.text", "a");
    if (file == NULL){
        printf("================================================\n");
        printf("------------- Error opening file! --------------\n");
        printf("================================================\n");
    }
    else{
        printf("Enter username : ");
        scanf("%s", user.username);
        printf("Enter password : ");
        char ch;
        int i = 0;
        while ((ch = getch()) != '\r') {
            if (ch == '\b') {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else {
                user.pass[i++] = ch;
                printf("*");
            }
        }
        user.pass[i] = '\0';
        printf("\n");


        fprintf(file, "%s %s\n", user.username, user.pass);
        fclose(file);
        printf("================================================\n");
        printf("-------------Registration successful!-----------\n");
        printf("================================================\n");
    }
}



//Login Page
int login() {
    FILE *file = fopen("users.text", "r");
    if (file == NULL) {
        printf("No user exist! Register first.\n");
        return -1;
    }

    char a[100], b[100];
    printf("Enter username : ");
    scanf("%s", a);

    printf("Enter password : ");
    char ch;
    int i = 0;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            b[i++] = ch;
            printf("*");
        }
    }
    b[i] = '\0';
    printf("\n");


    while (fscanf(file, "%s %s", user.username, user.pass) != EOF) {
        if (strcmp(user.username, a) == 0 && strcmp(user.pass, b) == 0) {
            fclose(file);
            return 0;
        } else if (strcmp(a, "admin") == 0 && strcmp(b, "admin") == 0) {
            fclose(file);
            return 1;
        } else if (strcmp(a, "staff") == 0 && strcmp(b, "staff") == 0) {
            fclose(file);
            return 2;
        }
    }

    fclose(file);
    printf("Login failed! Invalid username or password.\n");
    return -1;
}



// Admin control panel
void admin() {
    int c = 1, choice;
    while (c) {
        printf("\n");
        printf("******************************************************\n");
        printf("*                    Welcome Admin                   *\n");
        printf("******************************************************\n");
        printf("\n");
        printf("1. Insert Items\n");
        printf("2. Display Items\n");
        printf("3. Search Items\n");
        printf("4. Delete Items\n");
        printf("5. Update Items\n");
        printf("6. Student / Discounted Customer Informations\n");
        printf("7. Back\n");
        printf("\n");
        choice = _getch();
        switch (choice) {
            case '1':
                write();
                break;
            case '2':
                read();
                break;
            case '3':
                search();
                break;
            case '4':
                delete();
                break;
            case '5':
                update();
                break;
            case '6':
                student_details();
                break;
            case '7':
                c = 0;
                break;
            default:
                printf("\nInvalid option! Please, try again.\n");
        }
    }
}



// Initialize autoId from the file
 int initializeAutoId() {
    int autoId;
    file = fopen("menu.text", "r");
    if (file != NULL) {
        int maxId = 0;
        while (fscanf(file, "%d %s %f", &node.id, &node.a, &node.price) != EOF) {
            if (node.id > maxId) {
                maxId = node.id;
            }
        }
        autoId = maxId + 1; // Set autoId to the next ID
        fclose(file);
        return autoId;
    }
}



// Insert new item in the menu
void write() {
    int autoId = initializeAutoId();
    file = fopen("menu.text", "a+"); // Open in append mode
    if (file == NULL) {
        printf("Menu is empty!\n");
    } else {
        int i, k;
        printf("\nHow many items you want to enter : ");
        scanf("%d", &k);
        for (i = 0; i < k; i++) {
            node.id = autoId++; // Auto-generated ID
            printf("Enter name : ");
            scanf("%s", node.a);
            printf("Enter your price : ");
            scanf("%f", &node.price);
            fprintf(file, "%d %s %.2f\n", node.id, node.a, node.price);
            printf("Item added: ID - %d, Name - %s, Price - %.2f\n\n", node.id, node.a, node.price);
        }
        fclose(file);
    }
}



// Display items availabe in menu
void read() {
    file = fopen("menu.text", "r");
    if (file == NULL) {
        printf("\nMenu is empty\n");
    } else {
        printf("******************************************************\n");
        printf("ID\tName\tPrice\n");
        printf("******************************************************\n");
        while (fscanf(file, "%d %s %f", &node.id, node.a, &node.price) != EOF) {
            printf("%d\t%s\t%.2f$\n", node.id, node.a, node.price);
        }
        printf("******************************************************\n");
        fclose(file);
    }
}



// Search item inside menu
void search() {
    file = fopen("menu.text", "r");
    char s[100];
    int found = 0;
    printf("Enter the name of the item you are looking for : ");
    scanf("%s", s);
    if (file == NULL) {
        printf("\nSorry! Menu is empty.\n");
        printf("Wait for some moments.\n");
    } else {
        printf("******************************************************\n");
        printf("ID\tName\tPrice\n");
        printf("******************************************************\n");
        while (fscanf(file, "%d %s %f", &node.id, node.a, &node.price) != EOF) {
            if (strcmp(node.a, s) == 0) {
                printf("%d\t%s\t%.2f$\n", node.id, node.a, node.price);
                printf("******************************************************\n");
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("================================================\n");
            printf("-------------Item is not available!-------------\n");
            printf("================================================\n");
        }
        fclose(file);
    }
}



// Deleting items from menu
void delete() {
    file = fopen("menu.text", "r");
    temp = fopen("temp.text", "w");
    if (file == NULL || temp == NULL) {
        printf("\nSorry! Menu is not avaialble right now.\n");
    } else {
        int p = 0, Id;
        printf("\nEnter the ID number of the food you want to delete : ");
        scanf("%d", &Id);
        while (fscanf(file, "%d %s %f", &node.id, node.a, &node.price) != EOF) {
            if (node.id != Id) {
                fprintf(temp, "%d %s %.2f\n", node.id, node.a, node.price);
            } else {
                p = 1;
            }
        }
        fclose(file);
        fclose(temp);
        if (p) {
            remove("menu.text");
            rename("temp.text", "menu.text");
            printf("\n");
            printf("================================================\n");
            printf("----------Item deleted successfully.------------\n");
            printf("================================================\n");
        } else {
            remove("temp.text");
            printf("\nError! Item with ID %d not found.\n", Id);
        }
    }
}



// Update items in menu
void update() {
    file = fopen("menu.text", "r");
    temp = fopen("temp.text", "w");
    if (file == NULL || temp == NULL) {
        printf("Sorry! Menu is not avaialbe right now.\n");
    } else {
        int p = 0, Id;
        printf("\nEnter the ID number of the food you want to update : ");
        scanf("%d", &Id);
        while (fscanf(file, "%d %s %f", &node.id, node.a, &node.price) != EOF) {
            if (node.id == Id) {
                p = 1;
                printf("Enter new name : ");
                scanf("%s", node.a);
                printf("Enter new price : ");
                scanf("%f", &node.price);
                printf("Item updated: ID - %d, Name - %s, Price - %.2f\n", node.id, node.a, node.price);
            }
            fprintf(temp, "%d %s %.2f\n", node.id, node.a, node.price);
        }
        fclose(file);
        fclose(temp);
        if (p) {
            remove("menu.text");
            rename("temp.text", "menu.text");
            printf("================================================\n");
            printf("-----------Item updated successfully.-----------\n");
            printf("================================================\n");
        } else {
            remove("temp.text");
            printf("Error! Item with ID %d not found.\n", Id);
        }
    }
}



//Student Details for Discount Purpuses
void student_details()
{
    FILE *s;
    s = fopen("student.text","r");
    if (s == NULL)
    {
        printf("================================================\n");
        printf("----------------------Error!--------------------\n");
        printf("================================================\n");
    } else {
        printf("\nStudent Details\n");
        printf("================================================\n");
        printf("\n");
        printf("******************************************************\n");
        printf("University\tName\t ID\n");
        printf("******************************************************\n");
        while (fscanf(s, "%s %s %d ", &st.uni_name, &st.name,&st.id) != EOF)
        {
            printf("%s\t\t%s\t %d\n",st.uni_name,st.name,st.id);
        }
        printf("******************************************************\n");
        fclose(s);
    }
}



//customermenu
void customermenu(){
    int student;
    FILE *s;
    s = fopen("student.text","a");

    printf("\n");
    printf("Are you student ? \n");
    printf("1. YES\n");
    printf("2. NO\n");
    student = _getch();

    if(student == '1')
    {
        printf("Your Institution: ");
        getchar();
        gets(st.uni_name);
        printf("Your Name: ");
        gets(st.name);
        printf("Student ID/Roll: ");
        scanf("%d",&st.id);
        fprintf(s," %s  %s  %d\n",st.uni_name,st.name,st.id);
        fclose(s);
    }

    int choice;
    int c=1;
    while(c){
        printf("\n");
        printf("*******************************************************\n");
        printf("*                  Customer Menu                      *\n");
        printf("*******************************************************\n");
        printf("\n");
        printf("1. View Menu\n");
        printf("2. Place Order\n");
        printf("3. Reserve Seat\n");
        printf("4. Back\n");
        printf("\n");
        choice = _getch();
        switch(choice){
            case '1':
            {
                read();
                break;
            }
            case '2':
            {
                placeorder(student);
                break;
            }
            case '3':
            {
                reservation();
                break;
            }
            case '4':
            {
                c = 0;
            }
        }
    }
}



//Place order
    void placeorder(int student){
    printf("\n Order placing...\n");
    int id, quantity;
    float total = 0, price;
    char name[100];
    printf("\n");
    printf("Enter food Id : ");
    scanf("%d",&id);

    printf("Enter quantity : ");
    scanf("%d", &quantity);

    FILE *order;
    order = fopen("order.text","a");

    file = fopen("menu.text","r");

    while(fscanf(file,"%d %s %f",&node.id,&node.a,&node.price)!=EOF){
        if(id==node.id)
        {
            if(student=='1'){
            strcpy(name,node.a);

            total = total+(node.price*quantity);
            total = total-(total*.1);
            printf("Total = %f\n",total);
            fprintf(order,"%d  %s  %d  %f\n",node.id,node.a,quantity,total);
            printf("\n");
            printf("******************************************************\n");
            printf("*                     Your Order                     *\n");
            printf("******************************************************\n");
            printf("\n");
            printf("******************************************************\n");
            printf("\nID\tName\tQuantity\tTotal price\n");
            printf("******************************************************\n");
            printf("%d\t%s\t  %d\t\t%.2f$\n",node.id,node.a,quantity,total);
            printf("******************************************************\n");
            printf("\n");
            printf("You are student.\n");
            printf("\n$$ You have got 10 percent discount ;) !\n");
            printf("\n");
            break;
            }
            else{
            strcpy(name,node.a);

            total = total+(node.price * quantity);
            printf("Total = %f\n",total);
            fprintf(order,"%d  %s  %d  %f\n",node.id,node.a,quantity,total);
            printf("\n");
            printf("******************************************************\n");
            printf("*                     Your Order                     *\n");
            printf("******************************************************\n");
            printf("\n");
            printf("******************************************************\n");
            printf("ID\tName\tQuantity\tTotal price\n");
            printf("******************************************************\n");
            printf("%d\t%s\t  %d\t\t%.2f$\n",node.id,node.a,quantity,total);
            printf("******************************************************\n");
            printf("\n");
            break;
            }
        }
    }
    fclose(file);
    fclose(order);

    // calling payment process function
    payment( total);
}



//  Bank Transfer
void bankTransfer(float total)
{
    char accountNumber[20];
    double amount;

    printf("\n=== Bank Transfer ===\n");
    printf("Enter your bank account number: ");
    scanf("%s", &accountNumber);
    printf("Enter the amount to transfer: ");
    scanf("%lf", &amount);

    printf("Processing bank transfer of $%.2f from account number %s...\n", amount, accountNumber);
    if(amount==total)
    {
        printf("Payment successful.\n");
        printf("Thank you!\n");
    }else{
        printf("Please, pay the accorate amount.\n");
        printf("\nTry again.\n");
    }
}



//bKash Payment
void paypalPayment(float total)
{
    char phoneNumber[15];
    char pin[10];
    double amount;

    printf("\n=== Paypal Payment ===\n");
    printf("Enter your Paypal number: ");
    scanf("%s", &phoneNumber);
    printf("Enter your Paypal PIN: ");
    scanf("%s", &pin);
    printf("Enter the amount to pay: ");
    scanf("%lf", &amount);

    printf("Processing Paypal payment of $%.2f from %s...\n", amount, phoneNumber);
    if(amount==total)
    {
        printf("Payment successful!\n");
        printf("Thank you.\n");
    }else
    {
        printf("Please, pay the accorate amount.\n");
        printf("\nTry again.\n");
    }
}




//Cash on Delivery.
void cashOnDelivery() {
    char deliveryAddress[100];
    int distance;
    printf("\n=== Cash on Delivery ===\n");
    printf("Enter your delivery address = ");
    getchar();
    gets(deliveryAddress);
    printf("Enter distance : ");
    scanf("%d",&distance);
    printf("Your order will be delivered to : %s\n", deliveryAddress);
    printf("In %d minutes.\n",distance*3);
    printf("Please pay cash upon delivery.\n");
    printf("Thank you !\n");
}



//Payment Process.
void payment(float total){

    int choice;
    printf("\n");
    printf("*****************************************************\n");
    printf("============= Payment Process System ================\n");
    printf("*****************************************************\n");
    printf("Select your payment method:\n");
    printf("1. Bank Transfer\n");
    printf("2. Paypal\n");
    printf("3. Cash on Delivery\n");
    printf("4. Back\n");
    choice = _getch();

    switch (choice) {
        case '1':
        {
            bankTransfer(total);
            break;
        }
        case '2':
        {
            paypalPayment(total);
            break;
        }
        case '3':
        {
            cashOnDelivery(total);
            break;
        }
        default:
        {
            printf("Invalid choice! Please select a valid payment method.\n");
        }
    }
 }



//Staff panel
 void staff(){
    int c = 1, choice;
    while (c) {
        printf("\n");
        printf("*****************************************************\n");
        printf("*                   Welcome Staff                   *\n");
        printf("*****************************************************\n");
        printf("\n");
        printf("1. Display Orders\n");
        printf("2. Search Items\n");
        printf("3. Delete Items\n");
        printf("4. Update Items\n");
        printf("5. Back\n");
        printf("\n");
        choice = _getch();
        switch (choice) {
            case '1':
                display_order();
                break;
            case '2':
                search();
                break;
            case '3':
                delete();
                break;
            case '4':
                update();
                break;
            case '5':
                c = 0;
                break;
            default:
                printf("\nInvalid option! Try again.\n");
        }
    }
 }



//Display Order.
void display_order()
{
    order = fopen("order.text", "r");
    if (order == NULL) {
        printf("Order list is empty.\n");
    } else {
        printf("*****************************************************\n");
        printf("*                    Ordered Items                  *\n");
        printf("*****************************************************\n");
        printf("\n");
        printf("*****************************************************\n");
        printf("\nID\tName\tQuantity\tTotal price\n");
        printf("*****************************************************\n");
        while (fscanf(order, "%d %s %d %f", &or.id, &or.name,&or.q, &or.tprice) != EOF) {
            printf("%d\t%s\t  %d\t\t%.2f$\n",or.id,or.name,or.q,or.tprice);
        }
        printf("*****************************************************\n");
        fclose(order);
    }
}



// Seat Reservation Panel.
void reservation()
{
    int choice,c=1;
    printf("\n");
    while (c)
    {
        printf("\n");
        printf("*****************************************************\n");
        printf("*              Table Reservation System             *\n");
        printf("*****************************************************\n");
        printf(" 1. View Tables                \n");
        printf(" 2. Reserve a Table            \n");
        printf(" 3. View Reservations          \n");
        printf(" 4. Cancel Reservation         \n");
        printf(" 5. Back                       \n");
        printf("\n");
        choice = _getch();

        switch (choice)
        {
            case '1':
            {
                viewTables();
                break;
            }
            case '2':
            {
                reserveTable();
                break;
            }
            case '3':
            {
                viewReservations();
                break;
            }
            case '4':
            {
                cancelReservation();
                break;
            }
            case '5':
            {
                c=0;
                break;
            }
            default:
            {
                printf("Invalid choice! Please, Try again.\n");
            }
        }
    }
}



// Tables
void initializeTables()
{
    FILE *file;
    file = fopen("tables.text", "w");
    Table tables[] = {
        {1, 2, 1}, {2, 4, 1}, {3, 6, 1}, {4, 8, 1}, {5, 10, 1}
    };
    for (int i = 0; i < 5; i++)
    {
        fprintf(file, "%d  %d  %d\n", tables[i].id, tables[i].capacity, tables[i].isAvailable);
    }
    fclose(file);
    printf("\n");
}



// View Available Tables
void viewTables()
{
    initializeTables();
    file = fopen("tables.text", "r");
    if (file == NULL)
    {
        printf("Error opening tables file.\n");
        return;
    }else{

    Table table;
    printf("*****************************************************\n");
    printf("*                Available Tables                   *\n");
    printf("*****************************************************\n");
    printf("\n");
    printf("*****************************************************\n");
    printf("ID\tCapacity\tStatus\n");
    printf("*****************************************************\n");
    while (fscanf(file, "%d %d %d", &table.id, &table.capacity, &table.isAvailable) != EOF) {
        printf("%d\t%d\t\t%s\n", table.id, table.capacity, table.isAvailable ? "Available" : "Reserved");
    }
    printf("*****************************************************\n");
    fclose(file);
 }
}



// Reserve a Table
void reserveTable()
{
    int tableID;
    char customerName[100], date[100], time[100];

    viewTables();
    printf("\nEnter the Table ID to reserve: ");
    scanf("%d", &tableID);

    if (!isTableAvailable(tableID))
    {
        printf("Table %d is not available for reservation.\n", tableID);
        printf("Please, try reserving a different table.\n");
        return;
    }

    printf("Your Name: ");
    scanf("%s", &customerName);
    printf("Date for Reservation (DD/MM/YYYY): ");
    scanf("%s", &date);
    printf("Time to Reserve (24 hr format): ");
    scanf("%s", &time);

    FILE *file = fopen("reservations.text", "a");
    fprintf(file, "%d %s %s %s\n", tableID, customerName, date, time);
    fclose(file);

    updateTableAvailability(tableID, 0); // Mark table as reserved
    printf("Table %d reserved successfully!\n", tableID);
}



// View Reservations
void viewReservations()
{
    FILE *file = fopen("reservations.text", "r");
    if (!file)
    {
        printf("No Reservations Exist.\n");
        return;
    }

    Reservation reservation;
    printf("*****************************************************\n");
    printf("*                 Reservations                      *\n");
    printf("*****************************************************\n");
    printf("\n");
    printf("*****************************************************\n");
    printf("TableID\tCustomer\tDate\t\tTime\n");
    printf("*****************************************************\n");
    while (fscanf(file, "%d %s %s %s", &reservation.tableID, &reservation.customerName, &reservation.date, &reservation.time) != EOF) {
        printf("%d\t%s\t\t%s\t%s\n", reservation.tableID, reservation.customerName, reservation.date, reservation.time);
    }
    printf("*****************************************************\n");
    fclose(file);
}



// Cancel Reservation
void cancelReservation()
{
    int tableID;
    printf("\nEnter the Table ID to cancel reservation: ");
    scanf("%d", &tableID);

    if (!isReservationExist(tableID))
    {
        printf("Table %d is not reserved yet.\n", tableID);
        printf("Please, try again.\n");
        return;
    }

    FILE *file = fopen("reservations.text", "r");
    FILE *temp = fopen("temp.text", "w");
    Reservation reservation;

    while (fscanf(file, "%d %s %s %s", &reservation.tableID, &reservation.customerName, &reservation.date, &reservation.time) != EOF)
    {
        if (reservation.tableID != tableID)
        {
            fprintf(temp, "%d %s %s %s\n", reservation.tableID, reservation.customerName, reservation.date, reservation.time);
        }
    }

    fclose(file);
    fclose(temp);
    remove("reservations.text");
    rename("temp.text", "reservations.text");

    updateTableAvailability(tableID, 1); // Mark table as available
    printf("Reservation for Table %d canceled successfully!\n", tableID);
}


void updateTableAvailability(int tableID, int isAvailable)
{
    FILE *file = fopen("tables.text", "r");
    FILE *temp = fopen("temp.text", "w");
    Table table;

    while (fscanf(file, "%d %d %d", &table.id, &table.capacity, &table.isAvailable) != EOF) {
        if (table.id == tableID) {
            table.isAvailable = isAvailable;
        }
        fprintf(temp, "%d %d %d\n", table.id, table.capacity, table.isAvailable);
    }

    fclose(file);
    fclose(temp);
    remove("tables.text");
    rename("temp.text", "tables.text");
}


// Check Table Availability
int isTableAvailable(int tableID)
{
    FILE *file = fopen("tables.text", "r");
    Table table;
    while (fscanf(file, "%d %d %d", &table.id, &table.capacity, &table.isAvailable) != EOF)
    {
        if (table.id == tableID && table.isAvailable == 1)
        {
            fclose(file);
            return 1; // Available
        }
    }
    fclose(file);
    return 0; // Not available
}


// Check if Reservation Exists
int isReservationExist(int tableID)
{
    FILE *file = fopen("reservations.text", "r");
    Reservation reservation;
    while (fscanf(file, "%d %s %s %s", &reservation.tableID, &reservation.customerName, &reservation.date, &reservation.time) != EOF) {
        if (reservation.tableID == tableID)
        {
            fclose(file);
            return 1; // Exists
        }
    }

    fclose(file);
    return 0; // Not found
}
