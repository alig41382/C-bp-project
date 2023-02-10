#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//#include<curl/curl.h>
struct Date
{
    int dd;
    int mm;
    int yy;
};struct Date date;

struct Remainder
{
    int dd;
    int mm;
    char note[50];
};struct Remainder R;


/*
void http_request()
{
    CURL *curl;
    CURLcode response;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl,CURLOPT_URL,"http://parsamabani.pythonanywhere.com/reminder/check/?student_id=401521444");

        response=curl_easy_perform(curl);
        if (response != CURLE_OK)
        {
            fprintf(stderr,"Request failed: %s \n ", curl_easy_strerror(response));
        }
        else
        {
            printf("%s",response);
        }
        
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

}
*/

int get_1st_weekday(int year){

  int d;
  d = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
  return d;
}


void Calendar()
{
   int year,month,day,daysInMonth,weekDay=0,startingDay;
   printf("\nEnter your desired year:");
   scanf("%d",&year);

   char *months[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
   int monthDay[]={31,28,31,30,31,30,31,31,30,31,30,31};

   if((year%4==0&&year%100!=0)||year%400==0)
       monthDay[1]=29;

   startingDay=get_1st_weekday(year);

   for(month=0;month<12;month++){

      daysInMonth=monthDay[month];
      printf("\n\n---------------%s-------------------\n",months[month]);
      printf("\n  Sun  Mon  Tue  Wed  Thurs  Fri  Sat\n");

      for(weekDay=0;weekDay<startingDay;weekDay++)
        printf("     ");

      for(day=1;day<=daysInMonth;day++){
        printf("%5d",day);

        if(++weekDay>6){
            printf("\n");
            weekDay=0;
        }
        startingDay=weekDay;
      }

   }


}

void Addflag()
{
    FILE *fp;
    fp = fopen("note.txt", "a");
    printf("Enter the date(DD/MM) to Flag: ");
    scanf("%d%d", &R.dd, &R.mm);


    if (fwrite(&R, sizeof(R), 1, fp))
    {
        puts("Flag Date is saved sucessfully");
        fclose(fp);
    }
    else
    {
        puts("\aFail to save!!\a");
    }
    printf("Press any key............");
    getch();
    fclose(fp);

}




void AddNote(){
    FILE *fp;
    fp = fopen("note.dat","a");
    
    printf("Enter the date(DD/MM): ");
    scanf("%d%d",&R.dd, &R.mm);
    printf("Enter the Note(50 character max): ");
    fflush(stdin);
    scanf("%s[^\n]",R.note);
    if(fwrite(&R,sizeof(R),1,fp))
    {
        puts("Note is saved sucessfully");
        fclose(fp);
    }
    else
    {
        puts("\aFail to save!!\a");
    }
    printf("Press any key............");
    getch();
    fclose(fp);
}

void showNote(int mm){
    FILE *fp;
    int i = 0, isFound = 0;
    
    fp = fopen("note.txt","a");
    if(fp == NULL){
        printf("Error in opening the file");
    }
    while(fread(&R,sizeof(R),1,fp) == 1)
    {
        if(R.mm == mm){
            printf("Note %d Day = %d: %s", i+1, R.dd,  R.note);
            isFound = 1;
            i++;
        }
    }
    if(isFound == 0)
    {

        printf("This Month contains no note");
    }
    printf("Press any key to back.......");
    getch();

}


void removetxt()
{
    FILE *fileptr1, *fileptr2;
    char filename[40]="note.txt";
    char ch;
    int delete_line, temp = 1;

    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    //rewind
    rewind(fileptr1);
    printf(" \n Enter number of the line to be deleted:");
    scanf("%d", &delete_line);
    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        ch = getc(fileptr1);
        if (ch == '\n')
            temp++;
            //except the line to be deleted
            if (temp != delete_line)
            {
                //copy all lines in file replica.c
                putc(ch, fileptr2);
            }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);
    printf("\n The contents of file after being modified are as follows:\n");
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    fclose(fileptr1);



}

int main(){
    int choice;
    char ch = 'a';
    while(1){
        
        printf("1. Show Calendar\n");
        printf("2. Show Note\n");
        printf("3. Add Note\n");
        printf("4. Add Flag\n");
        printf("5. Remove \n");
        printf("6. EXIT\n");
        printf("ENTER YOUR CHOICE : ");
        scanf("%d",&choice);
        
        switch(choice){
            case 1:
                Calendar();
                printf("\nPress any key to continue......");
                getch();
                break;
            case 2 :
                printf("Enter month and year (MM YYYY) : ");
                scanf("%d",&date.mm);
                        showNote(date.mm); 
                break;
            case 3:
                AddNote();
                break;
            case 4:
                Addflag();
                break;
            case 5:
                removetxt();
            case 6 :
                exit(0);
        }
    }
    return 0;
}