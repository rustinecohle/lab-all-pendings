#include <stdio.h>
#include <string.h>
typedef struct {
    int rid;
    char gname[100];
    int rnum;
    char rtype[20];
    char date[20];
    int rent;
    int status; // 0 for vacant, 1 for occupied

}Reservation;
Reservation reservations[100];
int num_reservations = 0;
void addnew();
void searchbyid();
void displaybydate();
void displayvacant();
void totalrevenue();// forgot to add prototypes


int main(){
    int i=1;
    
    while(i){
        printf("Welcome to the Hotel Reservation System\n");
        printf("1. add new reservation \n");
        printf("2. search by reservation id\n");
        printf("3. display by date\n");
        printf("4. display vacant room\n");
        printf("5. calculate total yearly revenue\n");
        printf("6. exit\n");

        int c;
        printf("enter choice\n");
        scanf( "%d",&c);
        switch(c){
            case 1: addnew();
            break;
            case 2: searchbyid();
            break;
            case 3: displaybydate();
            break; 
            case 4: displayvacant();
            break;
            case 5: totalrevenue();
            break;
            case 6: i=0;
            break;
            default: printf("invalid choice\n");
        }
    return 0;
    
    }
}
void addnew(){

    int i=0;
    while(i==0){
    
    printf("Enter reservation ID: ");
    scanf("%d", &reservations[num_reservations].rid);
    printf("Enter guest name: ");
    scanf("%s", reservations[num_reservations].gname);
    printf("Enter room number: ");
    scanf("%d", &reservations[num_reservations].rnum);
    printf("Enter room type: ");
    scanf("%s", reservations[num_reservations].rtype);
    printf("Enter date: ");
    scanf("%s", reservations[num_reservations].date);
    printf("Enter rent: ");
    scanf("%d", &reservations[num_reservations].rent);
    reservations[num_reservations].status = 1;
    num_reservations++;
    printf("quit 1 and continue press any key\n");
    scanf("%d", &i);
    if(i==1){
        break;

        }
    }
}
void searchbyid(){
    int id;
    printf("Enter reservation ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < num_reservations; i++) {
        if (reservations[i].rid == id) {
            printf("Reservation found:\n");
            printf("Guest Name: %s\n", reservations[i].gname);
            printf("Room Number: %d\n", reservations[i].rnum);
            printf("Room Type: %s\n", reservations[i].rtype);
            printf("Date: %s\n", reservations[i].date);
            printf("Rent: %d\n", reservations[i].rent);
            break ;
        }
    }
    printf("Reservation ID not found.\n");
    
}
void displaybydate(){
    char date[20];
    printf("Enter date to display reservations: ");
    scanf("%s", date);
    int found = 0;
    for (int i = 0; i < num_reservations; i++) {
        if (strcmp(reservations[i].date, date) == 0) {
            printf("Reservation ID: %d\n", reservations[i].rid);
            printf("Guest Name: %s\n", reservations[i].gname);
            printf("Room Number: %d\n", reservations[i].rnum);
            printf("Room Type: %s\n", reservations[i].rtype);
            printf("Rent: %d\n", reservations[i].rent);
            found = 1;
        }
    }
    if (!found) {
        printf("No reservations found for the given date.\n");
    }
    
}
void displayvacant(){
    printf("Vacant rooms:\n");
    for (int i = 0; i < num_reservations; i++) {
        if (reservations[i].status == 0) {
            printf("Room Number: %d\n", reservations[i].rnum);
            printf("Room Type: %s\n", reservations[i].rtype);
        }
    }
    
}
void totalrevenue(){
    int total = 0;
    for (int i = 0; i < num_reservations; i++) {
        if (reservations[i].status == 1) {
            total += reservations[i].rent;
        }
    }
    printf("Total yearly revenue: %d\n", total);
    
}
