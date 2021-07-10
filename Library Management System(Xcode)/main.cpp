#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;

void mainMenu();
void adminPanel();
void studentPanel();

void login(){
    string username = "admin", password = "admin", un, pw;

    cout << "\n\nLogin\n";
    cout << "Enter Username: ";
    cin >> un;
    cout << "Enter Password: ";
    cin >> pw;
    if(username == un && password == pw){
        adminPanel();
    }
    else{
        cout << "\n\nWrong Password! try Again";
        getchar();
        system("clear");
        login();
    }
}

void Exit(){
    system("clear");
    cout << "Thank You!\n\n";
    getchar();
    exit(0);
}

class book{
    char bookId[6];
    char bookName[50];
    char authorName[20];

public:
    void addBook(){
        cout<<"\nAdd New Book\n";
        cout<<"\nEnter Book ID: ";
        cin >> bookId;
        cout<<"\nEnter Name of The Book: ";
        fflush(stdin);
        cin.getline(bookName,50);
        cout<<"\nEnter Author's Name: ";
        fflush(stdin);
        cin.getline(authorName,20);
        cout<<"\n\nBook Added Successfully!";
    }

    void showBook(){
        cout<<"\nBook ID: "<<bookId;
        cout<<"\nBook Name: ";
        puts(bookName);
        cout<<"Author's Name: ";
        puts(authorName);
    }

    void modifyBook(){
        cout<<"\nBook ID: "<<bookId;
        cout<<"\nNew Book Name: ";
        fflush(stdin);
        cin.getline(bookName,50);
        cout<<"\nNew Author's Name: ";
        fflush(stdin);
        cin.getline(authorName,20);
    }

    char* returnBookId(){
        return bookId ;
    }

    void report(){
        cout<<bookId<<setw(30)<<bookName<<setw(30)<<authorName<<endl;
    }
};

class student{
    char studentId[6];
    char name[20];
    char issuedBookNo[6]; //Book Number Issued
    int bookIssued; //Is Book Issued ?
public:
    void addStudent(){
        cout<<"\nAdd New Student\n";
        cout<<"\nEnter Student ID: ";
        cin>>studentId;
        cout<<"\nEnter Student Name: ";
        fflush(stdin);
        cin.getline(name,20);
        bookIssued=0;
        issuedBookNo[0]='\0';
        cout<<"\n\nStudent Added Successfully!";
    }

    void showStudent(){
        cout<<"\nStudent ID: "<<studentId;
        cout<<"\nStudent Name : ";
        puts(name);
        cout<<"\nNo. of Book issued : "<<bookIssued;
        if(bookIssued==1)
            cout<<"\nBook No "<<issuedBookNo;
    }

    void modifyStudent(){
        cout<<"\nStudent ID: "<<studentId;
        cout<<"\nNew Student Name: ";
        fflush(stdin);
        cin.getline(name,20);
    }

    char* returnStudentId(){
        return studentId;
    }

    char* returnIssuedBookNo(){
        return issuedBookNo;
    }

    int returnBookIssued(){
        return bookIssued;
    }

    void addBookIssued(){
        bookIssued=1;
    }

    void resetBookIssued(){
        bookIssued=0;
    }

    void getIssuedBookNo(char t[]){
        strcpy(issuedBookNo,t);
    }

    void report(){
        cout<<"\t"<<studentId<<setw(20)<<name<<setw(10)<<bookIssued<<endl;
    }
};

fstream file,file2;
book BOOK;
student STUDENT;

void writeBookDetails(){
    char ch;
    file.open("books.txt",ios::out|ios::app);
    do{
        BOOK.addBook();
        file.write((char*)&BOOK,sizeof(book));
        cout<<"\n\nDo you want to add more Books? (Y/N)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    file.close();
    getchar();
    system("clear");
    adminPanel();
}

void displaySpecificBookAdmin(char n[]){
    cout<<"\nBook detail\n";
    int found=0;
    file.open("books.txt",ios::in);
    while(file.read((char*)&BOOK,sizeof(book))){
        if(strcasecmp(BOOK.returnBookId(),n)==0){
            BOOK.showBook();
            found=1;
        }
    }
    file.close();
    if(found==0){
        cout<<"\n\nBook not found";
    }
    getchar();
    adminPanel();
}

void displaySpecificBook(char n[]){
    cout<<"\nBook detail\n";
    int found=0;
    file.open("books.txt",ios::in);
    while(file.read((char*)&BOOK,sizeof(book))){
        if(strcasecmp(BOOK.returnBookId(),n)==0){
            BOOK.showBook();
            found=1;
        }
    }
    file.close();
    if(found==0){
        cout<<"\n\nBook not found";
    }
    getchar();
    studentPanel();
}

void modifybook(){
    char n[6];
    int found=0;
    cout<<"\n\n\tEnter Book ID: ";
    cin>>n;
    file.open("books.txt",ios::in|ios::out);
    while(file.read((char*)&BOOK,sizeof(book)) && found==0){
        if(strcasecmp(BOOK.returnBookId(),n)==0){
            BOOK.showBook();
            cout<<"\nEnter New Details"<<endl;
            BOOK.modifyBook();
            int pos=-1*sizeof(BOOK);
            file.seekp(pos,ios::cur);
            file.write((char*)&BOOK,sizeof(book));
            cout<<"Book Details Updated";
            found=1;
        }
    }
    file.close();
    if(found==0){
        cout<<"\n\nBook Not Found ";
    }
    getchar();
    system("clear");
    adminPanel();
}

void deleteBook(){
    char n[6];
    cout<<"\n\nEnter Book ID: ";
    cin>>n;
    file.open("books.txt",ios::in|ios::out);
    fstream file2;
    file2.open("Temp.txt",ios::out);
    file.seekg(0,ios::beg);
    while(file.read((char*)&BOOK,sizeof(book))){
        if(strcasecmp(BOOK.returnBookId(),n)!=0){
            file2.write((char*)&BOOK,sizeof(book));
        }
    }
    file2.close();
    file.close();
    remove("books.txt");
    rename("Temp.txt","books.txt");
    cout<<"\n\n\tBook Deleted Successfully";
    getchar();
    adminPanel();
}

void displayAllBook(){
    file.open("books.txt",ios::in);
    if(!file){
        cout<<"Error! File Not Found";
        getchar();
        return;
    }
    cout<<"\n\n\t\tAll Books\n\n";
    cout<<"*************************************************************************\n";
    cout<<"Book ID"<<setw(20)<<"Book Name"<<setw(25)<<"Author Name\n";
    cout<<"*************************************************************************\n";
    while(file.read((char*)&BOOK,sizeof(book))){
        BOOK.report();
    }
    file.close();
    getchar();
    studentPanel();
}

void displayAllBookAdmin(){
    file.open("books.txt",ios::in);
    if(!file){
        cout<<"Error! File Not Found";
        getchar();
        return;
    }
    cout<<"\n\n\t\tAll Books\n\n";
    cout<<"*************************************************************************\n";
    cout<<"Book ID"<<setw(20)<<"Book Name"<<setw(25)<<"Author Name\n";
    cout<<"*************************************************************************\n";
    while(file.read((char*)&BOOK,sizeof(book))){
        BOOK.report();
    }
    file.close();
    getchar();
    adminPanel();
}

void writeStudentDetails(){
    char ch;
    file.open("students.txt",ios::out|ios::app);
    do{
        STUDENT.addStudent();
        file.write((char*)&STUDENT,sizeof(student));
        cout<<"\n\ndo you want to add more Students? (Y/N)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    file.close();
    getchar();
    system("clear");
    adminPanel();
}

void displaySpecificStudentAdmin(char n[]){
    cout<<"\nStudent detail\n";
    int found=0;
    file.open("students.txt",ios::in);
    while(file.read((char*)&STUDENT,sizeof(student))){
        if((strcasecmp(STUDENT.returnStudentId(),n)==0)){
            STUDENT.showStudent();
            found=1;
        }
    }
    file.close();
    if(found==0){
        cout<<"\n\nStudent not found";
    }
    getchar();
    adminPanel();
}

void displaySpecificStudent(char n[]){
    cout<<"\nStudent detail\n";
    int found=0;
    file.open("students.txt",ios::in);
    while(file.read((char*)&STUDENT,sizeof(student))){
        if((strcasecmp(STUDENT.returnStudentId(),n)==0)){
            STUDENT.showStudent();
            found=1;
        }
    }
    file.close();
    if(found==0){
        cout<<"\n\nStudent not found";
    }
    getchar();
    system("clear");
    studentPanel();
}

void modifyStudent(){
    char n[6];
    int found=0;
    cout<<"\n\n\tEnter Student ID: ";
    cin>>n;
    file.open("students.txt",ios::in|ios::out);
    while(file.read((char*)&STUDENT,sizeof(student)) && found==0){
        if(strcasecmp(STUDENT.returnStudentId(),n)==0){
            STUDENT.showStudent();
            cout<<"\nEnter The New Details of student"<<endl;
            STUDENT.modifyStudent();
            int pos=-1*sizeof(STUDENT);
            file.seekp(pos,ios::cur);
            file.write((char*)&STUDENT,sizeof(student));
            cout<<"Student Details Updated";
            found=1;
        }
    }
    file.close();
    if(found==0){
        cout<<"\n\nStudent Not Found ";
    }
    getchar();
    system("clear");
    adminPanel();
}

void deleteStudent(){
    char n[6];
    int found=0;
    cout<<"\n\nEnter Student ID: ";
    cin>>n;
    file.open("students.txt",ios::in|ios::out);
    fstream file2;
    file2.open("Temp.txt",ios::out);
    file.seekg(0,ios::beg);
    while(file.read((char*)&STUDENT,sizeof(student))){
        if(strcasecmp(STUDENT.returnStudentId(),n)!=0)
            file2.write((char*)&STUDENT,sizeof(student));
        else
            found=1;
    }
    file2.close();
    file.close();
    remove("students.txt");
    rename("Temp.txt","students.txt");
    if(found==1){
        cout<<"\n\n\tStudent Deleted Successfully";
    }
    else{
        cout<<"\n\nStudent Not Found";
    }
    getchar();
    adminPanel();
}

void displayAllStudent(){
    file.open("students.txt",ios::in);
    if(!file){
        cout<<"Error! File Not Found";
        getchar();
        return;
    }
    cout<<"\n\nAll Students\n\n";
    cout<<"******************************************************************\n";
    cout<<"\tStudent ID"<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"******************************************************************\n";
    while(file.read((char*)&STUDENT,sizeof(student))){
        STUDENT.report();
    }
    file.close();
    getchar();
    studentPanel();
}

void displayAllStudentAdmin(){
    file.open("students.txt",ios::in);
    if(!file){
        cout<<"Error! File Not Found";
        getchar();
        return;
    }
    cout<<"\n\n\t\tAll Students\n\n";
    cout<<"******************************************************************\n";
    cout<<"\tStudent ID"<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"******************************************************************\n";
    while(file.read((char*)&STUDENT,sizeof(student))){
        STUDENT.report();
    }
    file.close();
    getchar();
    adminPanel();
}

void issueBook(){
    char sn[6],bn[6];
    int found=0,flag=0;
    cout<<"\n\n\tEnter Student ID: ";
    cin>>sn;
    file.open("students.txt",ios::in|ios::out);
    file2.open("books.txt",ios::in|ios::out);
    while(file.read((char*)&STUDENT,sizeof(student)) && found==0){
        if(strcasecmp(STUDENT.returnStudentId(),sn)==0){
            found=1;
            if(STUDENT.returnBookIssued()==0){
                cout<<"\n\n\tEnter Book ID: ";
                cin>>bn;
                while(file2.read((char*)&BOOK,sizeof(book))&& flag==0){
                    if(strcasecmp(BOOK.returnBookId(),bn)==0){
                        BOOK.showBook();
                        flag=1;
                        STUDENT.addBookIssued();
                        STUDENT.getIssuedBookNo(BOOK.returnBookId());
                        int pos=-1*sizeof(STUDENT);
                        file.seekp(pos,ios::cur);
                        file.write((char*)&STUDENT,sizeof(student));
                        cout << "Book Issued successfully  Please Note: Return Book within 15 days. After 15 days, Book will be charged as Rs. 1 per day as fine.\n";
                    }
                }
                if(flag==0){
                    cout<<"Book Not Found";
                }

            }
            else{
                cout<<"Return Issued Book First";
            }
        }
    }
    if (found == 0){
        cout << "Student Not Found";
    }
    getchar();
    file.close();
    file2.close();
    studentPanel();
}

void depositBook(){
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    cout<<"\n\n\tEnter Student ID";
    cin>>sn;
    file.open("students.txt",ios::in|ios::out);
    file2.open("books.txt",ios::in|ios::out);
    while(file.read((char*)&STUDENT,sizeof(student)) && found==0){
        if(strcasecmp(STUDENT.returnStudentId(),sn)==0){
            found=1;
            if(STUDENT.returnBookIssued()==1){
                while(file2.read((char*)&BOOK,sizeof(book))&& flag==0){
                    if(strcasecmp(BOOK.returnBookId(),STUDENT.returnIssuedBookNo())==0){
                        BOOK.showBook();
                        flag=1;
                        cout<<"\n\nEnter No. of Days: ";
                        cin>>day;
                        if(day>15){
                            fine=(day-15)*1;
                            cout<<"\n\nFine: Rs"<<fine;
                        }
                        STUDENT.resetBookIssued();
                        int pos=-1*sizeof(STUDENT);
                        file.seekp(pos,ios::cur);
                        file.write((char*)&STUDENT,sizeof(student));
                        cout<<"\n\n\t Book deposited successfully";
                    }
                }
                if(flag==0){
                    cout<<"Book Not Found";
                }
            }
            else{
                cout<<"No book Issued";
            }
        }
    }
    if (found == 0) {
        cout << "Student Not Found";
    }
    getchar();
    file.close();
    file2.close();
    studentPanel();
}

void studentPanel(){
    int option;
    system("clear");
    cout << "\nStudent Panel\n\n";
    cout << "Press 1 to Display All Books" << endl;
    cout << "Press 2 to Display Specific Book" << endl;
    cout << "Press 3 to Display All Students" << endl;
    cout << "Press 4 to Display Specific Student" << endl;
    cout << "Press 5 to Issue Book" << endl;
    cout << "Press 6 to Deposit Book" << endl;
    cout << "Press 7 to go back to Main Menu" << endl;
    cout << "Press 8 to Exit" << endl;
    cin >> option;
    switch (option) {
        case 1:
            displayAllBook();
            break;
        case 2:
            char BOOKID[6];
            system("clear");
            cout<<"Enter Book ID: ";
            cin>>BOOKID;
            displaySpecificBook(BOOKID);
            break;
        case 3:
            displayAllStudent();
            break;
        case 4:
            char STUDENTID[6];
            system("clear");
            cout<<"Enter Student ID: ";
            cin>>STUDENTID;
            displaySpecificStudent(STUDENTID);
            break;
        case 5:
            system("clear");
            issueBook();
            break;
        case 6:
            system("clear");
            depositBook();
            break;
        case 7:
            system("clear");
            mainMenu();
            break;
        case 8:
            Exit();
            break;
        default:
            cout << "Invalid Option\n";
            getchar();
            studentPanel();
    }
}

void adminPanel(){
    int options;
    system("clear");
    cout << "\n\nAdmin Panel\n\n";
    cout << "Press 1 to Add Book" << endl;
    cout << "Press 2 to Display All Books" << endl;
    cout << "Press 3 to Display Specific Book" << endl;
    cout << "Press 4 to Modify Book Record" << endl;
    cout << "Press 5 to Delete Book Record" << endl;
    cout << "Press 6 to Add Student" << endl;
    cout << "Press 7 to Display All Students" << endl;
    cout << "Press 8 to Display Specific Student" << endl;
    cout << "Press 9 to Modify Student" << endl;
    cout << "Press 10 to Delete Student" << endl;
    cout << "Press 11 to go back to Main Menu" << endl;
    cout << "Press 12 to Exit" << endl;
    cin >> options;
    switch (options){
        case 1:
            system("clear");
            writeBookDetails();
            break;
        case 2:
            system("clear");
            displayAllBookAdmin();
            break;
        case 3:
            char BOOKID[6];
            system("clear");
            cout<<"Enter Book ID: ";
            cin>>BOOKID;
            displaySpecificBookAdmin(BOOKID);
            break;
        case 4:
            system("clear");
            modifybook();
            break;
        case 5:
            system("clear");
            deleteBook();
            break;
        case 6:
            system("clear");
            writeStudentDetails();
            break;
        case 7:
            system("clear");
            displayAllStudentAdmin();
            break;
        case 8:
            char STUDENTID[6];
            system("clear");
            cout<<"Enter Student ID: ";
            cin>>STUDENTID;
            displaySpecificStudentAdmin(STUDENTID);
            break;
        case 9:
            system("clear");
            modifyStudent();
            break;
        case 10:
            system("clear");
            deleteStudent();
            break;
        case 11:
            system("clear");
            mainMenu();
            break;
        case 12:
            Exit();
            break;
        default:
            cout << "Invalid Option\n";
            getchar();
            adminPanel();
    }

}

void mainMenu(){
    int user;
    cout << "\nMain Menu\n\n";
    cout << "Press 1 for Admin Panel" << endl;
    cout << "Press 2 for Student Panel" << endl;
    cout << "Press 3 to Exit" << endl;
    cin >> user;
    switch (user) {
        case 1:
            login();
            break;
        case 2:
            studentPanel();
            break;
        case 3:
            Exit();
            break;
        default:
            cout << "Invalid Option";
            getchar();
            mainMenu();
            break;
    }
}

void welcome(){
    cout << "\nWelcome to Library Management System";
    cout << "\nBy Arsh (20BCA1187)";
    cout << "\nPress Enter to Continue";
    getchar();
    system("clear");
}

int main(){
    welcome();
    mainMenu();
}
