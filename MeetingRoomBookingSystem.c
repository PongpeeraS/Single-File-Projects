#include<stdio.h>
#include<string.h>

// ----------------------------------all global variable and function----------------------------------
char day[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
char month[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char fmonth[12][10] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
int startday[12] = {5,1,2,5,0,3,5,1,4,6,2,4};
int endday[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

int data[12][31][5][8];

char loggedin[8];

int count_user = 0; //อย่าลืมเปลี่ยน
struct user_info{
    char name[100];
    char lastname[100];
    char id[8];
    char password[50];
    char tel[11];
}user[100];

int count_log = 0;
struct report{
    int room;
    char month[4];
    int day;
    int slot;
    char id[8];
}log[800];

void initial(){
    int a,b,c,d;
    for(a=0;a<12;a++){
        for(b=0;b<31;b++){
            for(c=0;c<5;c++){
                for(d=0;d<8;d++){
                    data[a][b][c][d] = 1;
                }
            }
        }
    }
    /*strcpy(loggedin,"5988215");
    strcpy(user[0].name,"may");
    strcpy(user[0].lastname,"nomay");
    strcpy(user[0].id,"5988215");
    strcpy(user[0].password,"12345678");
    strcpy(user[0].tel,"0800000000");
    for(d=0;d<4;d++){
        data[9][12][3][d] = 0;
    }*/
}

int check_input(int enter_room, int enter_date, char enter_month[4], int enter_start,int enter_stop){
    int monthin,startin,stopin,check_error=0;
    int i,j;

    if(strlen(enter_month) == 3){
        for(i=0;i<12;i++){
            if(strcmp(enter_month,month[i])==0){
                monthin=i;
                check_error=0;
                break;
            }else{
                check_error=33;
            }
        }
        if(monthin==1-1||monthin==3-1||monthin==5-1||monthin==7-1||monthin==8-1||monthin==10-1||monthin==12-1){
            if(enter_date>31||enter_date<1){
                check_error=21;
            }
        }else if(monthin==4-1||monthin==6-1||monthin==9-1||monthin==11-1){
            if(enter_date>30||enter_date<1){
                check_error=22;
            }
        }else if(monthin==2-1){
            if(enter_date>29||enter_date<1){
                check_error=23;
            }
        }
    }else {
            check_error=15;
    }
    //Check for Sunday
    if(startday[i]>=2&&startday[i]<=6&&(enter_date%7)+startday[i]==8){
        check_error=85;
    }else if(startday[i]>=0&&startday[i]<=1&&(enter_date%7)+startday[i]==1){
        check_error=86;
    }
    if(enter_room!=101&&enter_room!=102&&enter_room!=103&&enter_room!=104&&enter_room!=105){
            check_error=1;
    }
    if(enter_start<9||enter_start>17){
        check_error=41;
    }else if(enter_stop<9||enter_stop>17){
        check_error=42;
    }
    /*if(enter_stop==enter_start){
        check_error=43;
    }*/
    if(enter_stop<=enter_start){
        check_error=45;
    }
    return check_error;

}
int monthth(char enter_month[4]){
    int i;
    for(i=0;i<12;i++){
        if(strcmp(enter_month,month[i])==0){
            return i;
            break;
        }
    }
}
// ----------------------------------user registration----------------------------------
void user_regist(){
    char namein[100];
    char lastnamein[100];
    char idin[8];
    char passwordin[50],confirmin[50];
    int telin[11];

    printf("\n----------Registration Page----------\n");
    printf("Please enter your first name: ");
    if(scanf("%s", &namein)==EOF){
        printf("\n------------------------\n\n");
        main_menu();
    }
    printf("Please enter your last name: ");
    if(scanf("%s", &lastnamein)==EOF){
        printf("\n------------------------\n\n");
        main_menu();
    }
    int passchecker = 0; //pass = 1     not pass = 0
    do{
        printf("Please enter your studentID: ");
        if(scanf("%s", &idin)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        if(strspn(idin, "0123456789") == strlen(idin) && strlen(idin) == 7) {
            passchecker = 1;
            //break;
            int i;
            for(i=0;i<count_user;i++){
                if(strcmp(idin,user[i].id)==0){
                    printf("This id is used\n");
                    passchecker=0;
                    break;
                }
            }
        }else{
                printf("You can use only 7 digit numbers for studentID\n");
        }
    }while(passchecker == 0);

    passchecker = 0;
    do{
        printf("Please enter your password: ");
        if(scanf("%s", &passwordin)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Please confirm your password: ");
        if(scanf("%s", &confirmin)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        passchecker = 1; // Can  u check length of password before
        if(strcmp (passwordin,confirmin) != 0){
            printf("These passwords don't match\n");
            passchecker = 0;
        }else if(strlen(passwordin)<8){
            printf("You must use at least 8 characters for password\n");
            passchecker =0;
        }
    }while(passchecker == 0);

    passchecker=0;
    do{
        printf("Please enter your mobile phone: ");
        if(scanf("%s", &telin)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        if(strspn(telin, "1234567890") == strlen(telin) && strlen(telin) == 10) {
                //printf("");
                passchecker = 1;
        }else{
            printf("You must use only 10 digit numbers for mobile phone\n");
        }
    }while(passchecker==0);
    strcpy(user[count_user].name, namein);
    strcpy(user[count_user].lastname, lastnamein);
    strcpy(user[count_user].id, idin);
    strcpy(user[count_user].password, passwordin);
    strcpy(user[count_user].tel, telin);
    count_user++;

    printf("\n----------End of Registration Process----------\n");
    printf("\nCongratulation, %s!!!\n",user[count_user-1].name);
    printf("Now  you  can login to the ICT Meeting room booking system \nand start the other functions\n\n");

    main_menu();
}

// ----------------------------------login----------------------------------
void login(){
    printf("\n----------Login Page----------\n");
    char enter_id[8];
    char enter_pass[50];
    int passchecker = 0,i;
    if(strcmp(loggedin,"")!=0){
        printf("Please Logout!!!\n--------------------\n\n");
        main_menu();
    }
    do{
        printf("Please enter your studentID: ");
        if(scanf("%s", &enter_id)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Please enter your password: ");
        if(scanf("%s", &enter_pass)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        for(i=0;i<count_user;i++){
            if(strcmp(user[i].id,enter_id) == 0){
                if(strcmp(user[i].password,enter_pass) == 0){
                    passchecker = 1;
                    strcpy(loggedin,user[i].id);
                    break;
                }
            }
        }
        if(passchecker!=1){
            printf("\nWrong studentID or password\n");
        }
    }while(passchecker!=1);
    printf("\nNow you can start using the system\n--------------------\n\n");
    main_menu();
}
// ----------------------------------room available----------------------------------
void room_avai(){
    printf("\n----------Room Availability----------\n");
    printf("Please select a style to show the available meeting rooms: monthly view (\"m\" or \"M\") and daily view (\"d\" or \"D\"): ");
    char c;

    do{
        if(scanf("%s", &c)==EOF){                           //Please Check Again
            printf("\n------------------------\n\n");
            main_menu();
        }

        if(c=='m'||c=='M'){
            month_view();
            break;
        }else if(c=='d'||c=='D'){
            daily_view();
            break;
        }else{
            printf("Invalid\n");
        }
    }while(1);
}

// ----------------------------------line month view----------------------------------
void line_day(){
    printf("|------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|---------|\n");
}

// ----------------------------------daily view----------------------------------
void daily_view(){
    char enter_month[4];
    int enter_date;
    int i,sp=1;

    printf("\nPlease input the date and the month to to show the available meeting rooms: ");
    while(sp==1){
        //scanf("%d",&enter_date);
        if(scanf("%d", &enter_date)==EOF){                           //Please Check Again
            printf("\n------------------------\n\n");
            main_menu();
        }
        //scanf("%s",&enter_month);
        if(scanf("%s", &enter_month)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }

        if(strlen(enter_month) == 3){
            for(i=0;i<12;i++){
                if(strcmp(enter_month,month[i])==0){
                    sp=0;
                    break;
                }else{
                    sp=1;
                }
            }
            if(i==1-1||i==3-1||i==5-1||i==7-1||i==8-1||i==10-1||i==12-1){
                if(enter_date>31||enter_date<1){
                    sp=1;
                }
            }else if(i==4-1||i==6-1||i==9-1||i==11-1){
                if(enter_date>30||enter_date<1){
                    sp=1;
                }
            }else if(i==2-1){
                if(enter_date>29||enter_date<1){
                    sp=1;
                }
            }
        }
        if(sp==1){
            printf("Invalid date or month\n");
        }
        if(i>=0&&i<12){
            if(startday[i]>=2&&startday[i]<=6&&(enter_date%7)+startday[i]==8){
                printf("Sunday is not available\n");
                printf("Please input the date and the month to to show the available meeting rooms: ");
                sp=1;
            }else if(startday[i]>=0&&startday[i]<=1&&(enter_date%7)+startday[i]==1){
                printf("Sunday is not available\n");
                printf("Please input the date and the month to to show the available meeting rooms: ");
                sp=1;
            }
        }
    }
    printf("\n%d %s 2016\n",enter_date,fmonth[i]);
    line_day();
    printf("| Room |09.00-10.00|10.00-11.00|11.00-12.00|12.00-13.00|13.00-14.00|14.00-15.00|15.00-16.00|16.00-17.00| Summary |\n");
    line_day();
    int rob,robn;
    for(rob=0;rob<5;rob++){
        printf("|IT10%d |",rob+1);
        int suma=0,summ=0;
        for(robn=0;robn<8;robn++){
            printf("     ");
            if(robn>=0&&robn<=2&&data[i][enter_date-1][rob][robn]==1){
                summ++;
            }else if(robn>=3&&robn<=7&&data[i][enter_date-1][rob][robn]==1){
                suma++;
            }
            if(data[i][enter_date-1][rob][robn]==1){
                printf("      |");
            }else if(data[i][enter_date-1][rob][robn]==0){
                printf("X     |");
            }
        }
        if(summ+suma==0){
            printf(" X       |");
        }else{
            if(summ!=0&&suma==0){
                printf(" %d(M)    |",summ+suma);
            }else if(summ==0&&suma!=0){
                printf(" %d(A)    |",summ+suma);
            }else if(summ!=0&&suma!=0){
                printf(" %d(M,A)  |",summ+suma);
            }
        }
        printf("\n");
        line_day();
    }
    printf("\n\n");
    main_menu();
}
// ----------------------------------line month view----------------------------------
void line_month(){
    printf("|-------|--------------|--------------|--------------|--------------|--------------|--------------|\n");
}
// ----------------------------------month view----------------------------------
void month_view(){
    char enter_month[4];
    printf("\nPlease select a month to show the available meeting rooms: ");
    int i,sp=1;

    while(sp==1){
        //scanf("%s",enter_month);
        if(scanf("%s", enter_month)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        if(strlen(enter_month) == 3){
            for(i=0;i<12;i++){
                if(strcmp(enter_month,month[i])==0){
                    sp=0;
                    break;
                }
            }
        }else{
            printf("Invalid month\n");
        }
    }
    printf("\nThe monthly view of all meeting room on %s 2016\n",fmonth[i]);
    int count_line;
    line_month();
    printf("|  Sun  |      Mon     |      Tue     |      Wed     |      Thu     |      Fri     |      Sat     |\n");
    line_month();
    int space,date=1,j,line;
    int lineweek,week,temp = 7 - startday[i];
    for(week=0;week<=6;week++){
        if(temp+(week*7)>=endday[i]){
            break;
        }
    }
    for(lineweek=1;lineweek<=week+1;lineweek++){
        if(lineweek==1){
            for(line=1;line<=6;line++){
                for(space=0;space<startday[i];space++){
                    if(space==0){
                        printf("|\t|");
                    }else{
                        printf("              |");
                    }
                }
                if(line==1){
                    for(j=startday[i];j<7;j++){
                        if(j==0){
                            printf("|  %2d\t|",date);
                            date++;
                        }else{
                            printf("      %2d      |",date);
                            date++;
                            if(j==6){
                                printf("\n");
                            }
                        }
                    }
                }else{
                    int date2=1;
                    for(j=startday[i];j<7;j++){
                        if(j==0){
                            printf("|\t|");
                            date2++;
                        }else{
                            printf(" IT10%d ",line-1);
                            int x,total=0,m=0,a=0;
                            for(x=0;x<8;x++){
                                if(data[i][date2-1][line-2][x]==1){
                                    total++;
                                    if(x>=0&&x<=2){
                                        m=1;
                                    }else if(x>=3&&x<=7){
                                        a=1;
                                    }
                                }
                                if(x==7&&total!=0){
                                    if(m==1&&a==0){
                                        printf("%d(M)   |",total);
                                    }else if(m==0&&a==1){
                                        printf("%d(A)   |",total);
                                    }else if(m==1&&a==1){
                                        printf("%d(M,A) |",total);
                                    }
                                }else if(x==7&&total==0){
                                    printf("X      |");
                                }
                            }
                            if(j==6){
                                printf("\n");
                            }
                            date2++;
                        }
                    }
                }
            }
            line_month();
        }else if(lineweek==week+1){
                        for(line=1;line<=6;line++){
                if(line==1){
                    for(j=0;j<7;j++){
                        if(j==0){
                            printf("|  %2d\t|",date);
                            date++;
                        }else{
                            if(date<=endday[i]){
                            printf("      %2d      |",date);
                            date++;
                            }else if(date>endday[i]){
                            printf("              |",date);
                            date++;
                            }
                            if(j==6){
                                printf("\n");
                            }
                        }
                    }
                }else{
                    int date2=date-7;
                    for(j=0;j<7;j++){
                        if(date2<=endday[i]){
                        if(j==0){
                            printf("|\t|");
                            date2++;
                        }else{
                            printf(" IT10%d ",line-1);
                            int x,total=0,m=0,a=0;
                            for(x=0;x<8;x++){
                                if(data[i][date2-1][line-2][x]==1){
                                    total++;
                                    if(x>=0&&x<=2){
                                        m=1;
                                    }else if(x>=3&&x<=7){
                                        a=1;
                                    }
                                }
                                if(x==7&&total!=0){
                                    if(m==1&&a==0){
                                        printf("%d(M)   |",total);
                                    }else if(m==0&&a==1){
                                        printf("%d(A)   |",total);
                                    }else if(m==1&&a==1){
                                        printf("%d(M,A) |",total);
                                    }
                                }else if(x==7&&total==0){
                                    printf("X      |");
                                }
                            }
                            if(j==6){
                                printf("\n");
                            }
                            date2++;
                        }
                        }else if(date2>endday[i]){
                            if(j==0){
                            printf("|\t|");
                            date2++;
                            }else{
                                printf("              |",line-1);
                                if(j==6){
                                printf("\n");
                                }
                            }
                            date2++;
                        }
                    }
                }
            }
            line_month();

        }else{
            for(line=1;line<=6;line++){
                if(line==1){
                    for(j=0;j<7;j++){
                        if(j==0){
                            printf("|  %2d\t|",date);
                            date++;
                        }else{
                            printf("      %2d      |",date);
                            date++;
                            if(j==6){
                                printf("\n");
                            }
                        }
                    }
                }else{
                    int date2=date-7;
                    for(j=0;j<7;j++){
                        if(j==0){
                            printf("|\t|");
                            date2++;
                        }else{
                            printf(" IT10%d ",line-1);
                            int x,total=0,m=0,a=0;
                            for(x=0;x<8;x++){
                                if(data[i][date2-1][line-2][x]==1){
                                    total++;
                                    if(x>=0&&x<=2){
                                        m=1;
                                    }else if(x>=3&&x<=7){
                                        a=1;
                                    }
                                }
                                if(x==7&&total!=0){
                                    if(m==1&&a==0){
                                        printf("%d(M)   |",total);
                                    }else if(m==0&&a==1){
                                        printf("%d(A)   |",total);
                                    }else if(m==1&&a==1){
                                        printf("%d(M,A) |",total);
                                    }
                                }else if(x==7&&total==0){
                                    printf("X      |");
                                }
                            }
                            if(j==6){
                                printf("\n");
                            }
                            date2++;
                        }
                    }
                }
            }
            line_month();
        }
    }
    printf("\n\n");
    main_menu();
}
// ----------------------------------logout----------------------------------
void logout(){
    printf("\n----------Logout Page----------\n");
    if(strcmp(loggedin,"")!=0){
        printf("Good bye!!!\n--------------------\n\n");
        strcpy(loggedin,"");
    }else{
        printf("You cannot logout because you are not currently logged-in\n--------------------\n\n");
    }
    main_menu();
}

// ----------------------------------booking----------------------------------
void booking(){
    int enter_room, enter_start,enter_stop, enter_date,check_error=0;
    int monthin,startin,stopin,i;
    char enter_month[4];
    printf("\n----------Booking----------\n");
    if(strcmp(loggedin,"")==0){
        printf("Please Login\n\n");
        printf("\n--------------------\n");
        main_menu();
    }else{
        printf("Enter your room: ");
        //scanf("%d",&enter_room);
        if(scanf("%d", &enter_room)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your date: ");
        //scanf("%d",&enter_date);
        if(scanf("%d", &enter_date)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your month (Only 3 first letter): ");
        //scanf("%s",enter_month);
        if(scanf("%s", enter_month)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your start time: ");
        //scanf("%d",&enter_start);
        if(scanf("%d", &enter_start)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your end time: ");
        //scanf("%d",&enter_stop);
        if(scanf("%d", &enter_stop)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        check_error=check_input(enter_room, enter_date, enter_month, enter_start, enter_stop);

        if(check_error==0){
            monthin=monthth(enter_month);
            for(i=enter_start-9;i<enter_stop-9;i++){
                if(data[monthin][enter_date-1][enter_room-101][i]==0){
                    //printf("%d %d %d %d\n",monthin,enter_date-1,enter_room-101,i);
                    check_error=50;
                    break;
                }
            }

        }
        if(check_error==0){
            int i;
            for(i=enter_start-9;i<enter_stop-9;i++){
                data[monthin][enter_date-1][enter_room-101][i]=0;

                log[count_log].room=enter_room;
                strcpy(log[count_log].month,month[monthin]);
                log[count_log].day=enter_date;
                log[count_log].slot=i;
                strcpy(log[count_log].id,loggedin);
                count_log++;
            }
            printf("Your booking is successful, you have booked room no.%d on %.2d o'clock - %.2d o'clock\n--------------------\n\n",enter_room,enter_start,enter_stop);
        }else{
            printf("Invalid booking\n--------------------\n\n");
        }
        main_menu();
    }
}
// ----------------------------------booking cancellation----------------------------------
void cancel(){
    int enter_room, enter_start,enter_stop, enter_date,check_error=0;
    int monthin,startin,stopin,i;
    char enter_month[4];
    printf("\n----------Cancel Booking Page----------\n");
    if(strcmp(loggedin,"")==0){
        printf("Please Login\n\n");
        printf("\n--------------------\n");
        main_menu();
    }else{
        printf("Enter your room: ");
        //scanf("%d",&enter_room);
        if(scanf("%d", &enter_room)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your date: ");
        //scanf("%d",&enter_date);
        if(scanf("%d", &enter_date)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your month (Only 3 first letter): ");
        //scanf("%s",enter_month);
        if(scanf("%s", enter_month)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your start time: ");
        //scanf("%d",&enter_start);
        if(scanf("%d", &enter_start)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        printf("Enter your end time: ");
        //scanf("%d",&enter_stop);
        if(scanf("%d", &enter_stop)==EOF){
            printf("\n------------------------\n\n");
            main_menu();
        }
        check_error=check_input(enter_room, enter_date, enter_month, enter_start, enter_stop);

        if(check_error==0){
            /*if(enter_start<=5){
                enter_start=enter_start+12;
            }else{
                enter_start=enter_start;
            }
            if(enter_stop<=5){
                enter_stop=enter_stop+12;
            }else{
                enter_stop=enter_stop;
            }
            for(i=0;i<12;i++){
                if(strcmp(enter_month,month[i])==0){
                    monthin=i;
                    check_error=0;
                    break;
                }
            }*/
            monthin=monthth(enter_month);
            int sp;
            for(i=enter_start-9;i<enter_stop-9;i++){
                if(data[monthin][enter_date-1][enter_room-101][i]==1){
                    check_error=50;
                    break;
                }
                check_error=55;
                for(sp=0;sp<count_log;sp++){
                    if(log[sp].room==enter_room&&strcmp(log[sp].month,month[monthin])==0&&log[sp].day==enter_date&&log[sp].slot==i&&strcmp(log[sp].id,loggedin)==0){
                        check_error=0;
                        break;
                    }
                }
                if(check_error==55){
                    break;
                }
            }
        }
        if(check_error==0){
            int i,j;
            for(i=enter_start-9;i<enter_stop-9;i++){
                data[monthin][enter_date-1][enter_room-101][i]=1;
                for(j=0;j<count_log;j++){
                     if(log[j].room==enter_room&&(strcmp(log[j].month,month[monthin])==0)&&log[j].day==enter_date&&log[j].slot==i&&(strcmp(log[j].id,loggedin)==0)){
                        strcpy(log[j].id,"NO");
                        break;
                    }
                }
            }
            printf("You successfully cancel booking for the room no. %.2d at time %.2d o'clock - %.2d o'clock\n--------------------\n\n",enter_room,enter_start,enter_stop);
        }else{
            printf("Please try again\n--------------------\n\n");
        }
        main_menu();
    }
}

// ----------------------------------report----------------------------------
void report(){
    printf("\n----------Report Page----------\n");
    int i=-1,start=9,stop=9,increase=0;
    if(strcmp(loggedin,"")==0){
        printf("Please Login\n\n");
        printf("\n--------------------\n");
        main_menu();
    }else{
        int j;
        for(j=0;j<count_user;j++){
            if(strcmp(user[j].id,loggedin) == 0){
                    printf("Name: %s\n",user[j].name);
                    break;
                }
            }
        }
        for(i=0;i<count_log;i++){
            if(strcmp(log[i].id,loggedin)==0){
                break;
            }
        }
    if(i<count_log&&i>=0){
        int next;
        printf("\n ---------------------------------------\n");
        printf("| Room\t|    Date\t|     Time\t|\n");
        printf("|---------------------------------------|\n");
        for(;i<count_log;i++){
            if(strcmp(log[i].id,loggedin)==0){
                printf("| IT%d\t|    %s %d\t| ",log[i].room,log[i].month,log[i].day);
                if(log[i].slot==0){
                    printf("09.00-10.00\t|\n");
                    printf("|---------------------------------------|\n");
                }else if(log[i].slot==1){
                    printf("10.00-11.00\t|\n");
                    printf("|---------------------------------------|\n");
                }else if(log[i].slot==2){
                    printf("11.00-12.00\t|\n");
                    printf("|---------------------------------------|\n");
                }else if(log[i].slot==3){
                    printf("12.00-13.00\t|\n");
                    printf("|---------------------------------------|\n");
                }else if(log[i].slot==4){
                    printf("13.00-14.00\t|\n");
                    printf("|---------------------------------------|\n");
                }else if(log[i].slot==5){
                    printf("14.00-15.00\t|\n");
                    printf("|---------------------------------------|\n");
                }else if(log[i].slot==6){
                    printf("15.00-16.00\t|\n");
                    printf("|---------------------------------------|\n");
                }else if(log[i].slot==7){
                    printf("16.00-17.00\t|\n");
                    printf("|---------------------------------------|\n");
                }
            }
        }
        printf("\n\n");
        main_menu();
    }else{
        printf("Not found booking\n--------------------\n\n");
        main_menu();
    }
}

// ----------------------------------main menu----------------------------------
void main_menu(){
    printf("ICT Meeting-Room Booking System\n\n");
    printf("Enter r or R for \t user registration\n");
    printf("Enter i or I for \t login\n");
    printf("Enter o or O for \t logout\n");
    printf("Enter a or A for \t room availability\n");
    printf("Enter b or B for \t booking\n");
    printf("Enter c or C for \t booking cancellation\n");
    printf("Enter p or P for \t booking report\n");
    char c;

    do{
        scanf(" %c",&c);

        if(c=='r'||c=='R'){
            user_regist();
            break;
        }else if(c=='i'||c=='I'){
            login();
            break;
        }else if(c=='o'||c=='O'){
            logout();
            break;
        }else if(c=='a'||c=='A'){
            room_avai();
            break;
        }else if(c=='b'||c=='B'){
            booking();
            break;
        }else if(c=='c'||c=='C'){
            cancel();
            break;
        }else if(c=='p'||c=='P'){
            report();
            break;
        }else{
            printf("Invalid\n");
        }
    }//while(c!='r'||c!='R'||c!='i'||c!='I'||c!='o'||c!='O'||c!='a'||c!='A'||c!='b'||c!='B'||c!='c'||c!='C'||c!='p'||c!='P');
    while(1);
}
int main(){
    initial();
    main_menu();
    return 0;
}
