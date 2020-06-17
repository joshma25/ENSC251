//The main.cpp file for the program, where the classes will be put to use to read the data from a file of
//different students and their data, temporarily store it in an object (of which class depends on the type 
//of students listed) then outputting all the data using the get functions.
#include <iostream> //cin and cout
#include <fstream> //file processing
#include <sstream> //formatted string processing
#include <cstdlib> //atof and atoi
#include "student.hpp" //header file for the Student, InternationalStudent, DomesticStudent, and ToeflScore classes
#include <string>
#include <iomanip>

int main(){
 
//DOMESTIC STUDENT reading file and outputting



typedef class DomesticStudent* DomStudentPtr;
typedef class InternationalStudent* IntStudentPtr;

//head and tail of domestic list
StudentPtr head = new DomesticStudent;
StudentPtr tail = new DomesticStudent;

//opening and checking to see if the file domestic-stu.txt opened and closing the program if opening failed.
 string line;
 ifstream domesticFile("domestic-stu.txt");
  
  if(!domesticFile.is_open()) {
    cout << "Unable to open file domestic-stu.txt" << endl;
    return -1;
  }

  //Read the first line of domestic-stu.txt, which specifies
  //the file format. And then print it out to the screen
   
   getline(domesticFile, line);
  cout << endl << endl;
 // cout << "DOMESTIC STUDENTS" << endl;
 // cout << "File format: " << line << endl << endl;
  
  //initializing the first student number as 20200000, for the first student. This variable will be used to
  //assign student numbers in the while loop for reading the fi;e
  int studentnum = 20200000;
  
  //for going thru the while loop when reading the file, counting how many entries are made
  int stu_count1 = 0;
   
  while( getline(domesticFile, line) ) {
    //process each line, get each field separated by a comma.
     //use istringstream to handle it.
     
     

    istringstream ss(line);

    //all values read are inputted as strings, declare variables to hold them	
    string firstName, lastName, province, s_cgpa, s_researchScore;
    //variables to use once converted to float,for cgpa, and int, for research score 
    float cgpa;
    int researchScore;

    //since dynamic array automatically uses default constructor to initialize, use set functions to change data andvoid creating new anonymous objects
    //get firstName separated by comma
    getline(ss, firstName, ',');

    //get lastName separated by comma
    getline(ss, lastName, ',');
 
    //get province separated by comma
    getline(ss, province, ',');

   //get cpga separated by comma, and convert string to float
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());

    //get researchScore separated by comma, and convert it to int
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());

   //call insert node function, using data collected from file
   DOMinsertNode(head,tail,stu_count1,firstName, lastName,province,cgpa,researchScore,studentnum);
     
    //incrementing student number counter
    studentnum++;

    //incrementing while loop counter
    stu_count1++;
 }

  //closing the file
  domesticFile.close();


//INTERNATIONAL STUDENT reading file and outputting

//head and tail for international student list
StudentPtr head2 = new InternationalStudent;
StudentPtr tail2 = new InternationalStudent;


//opening and checking to see if the file international-stu.txt opened, if not then closing the program
 ifstream InternationalFile("international-stu.txt");
  
  if(!InternationalFile.is_open()) {
    cout << "Unable to open file international-stu.txt" << endl;
    return -1;
  }
//while loop for reading the file and putting the data into the International object
//for international student file reading, to keep track of how may entries are made
 int stu_count2 = 0;


  while( getline(InternationalFile, line) ) {
  
    //process each line, get each field separated by a comma.
     //use istringstream to handle it.
    istringstream ss(line);
	
   //all data read as a string, so declare variables to store the strings
    string firstName, lastName, country, s_cgpa, s_researchScore, s_reading, s_writing, s_speaking, s_listening;
   //variables to hold float/int values once converted from strings
    float cgpa;
    int researchScore, reading, writing, speaking, listening;

    //since the objects have already been initialized by the default constructor, to avoid creating another anonymous obejct, use the set functions to input data
    //get firstName separated by comma
    getline(ss, firstName, ',');
    
    //get lastName separated by comma
    getline(ss, lastName, ',');
 
    //get country separated by comma
    getline(ss, country, ',');

    //get cpga separated by comma, and convert string to float
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());

    //get researchScore separated by comma, and convert it to int
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());
   

    //get reading, writng, listening and speaking scores and cast to int
    getline(ss, s_reading, ',');
    reading = atoi(s_reading.c_str());
 
    getline(ss, s_listening, ',');
    listening = atoi(s_listening.c_str());
 
    getline(ss, s_speaking, ',');
    speaking = atoi(s_speaking.c_str());
 
    getline(ss, s_writing, ',');
    writing = atoi(s_writing.c_str());
 
    //creating dummy node for checking toefl requirements
     IntStudentPtr forout = new InternationalStudent(firstName,lastName,cgpa, researchScore,studentnum,country,reading,listening,speaking,writing);

    //if the students toefl scores/total dont meet requirements, continue to next student, assigning them the student number, resetting info.
    //student who dont meet the requirements arent sorted
    if(forout->checkTOEFLreq(reading,listening,speaking,writing) == false)
    { 
    //ouput info regardless, adding flag that they didnt meet toefl requirements.
    // cout << "TOEFL REQ. NOT MET" << endl;
     continue;//dont update student counter or student number counter. Next valid student gets that student number
    }
    //if meet toefl requirements, delete dummynode and insert into list
    else
    {
     delete forout;
     //insert node in international list
     INTinsertNode(head2, tail2, stu_count1, firstName, lastName, reading, writing, speaking,listening,country,cgpa,researchScore,studentnum);
    }

     //incrementing student number counter to ensure no 2 students have same number
    studentnum++;	 
    //incrementing loop counter
    stu_count2++;
   }

  //closing the file
  InternationalFile.close();

  //merged list head and tail
  StudentPtr headm = new Student;
  StudentPtr tailm = new Student;
  



cout << "                                                               WELCOME TO THE SFU GRADUATE ADMISSIONS SYSTEM" << endl << endl;


cout << " MAIN MENU: " << endl << "[S] Search for a student/group of students" << endl << "[I] Insert a new student" << endl 
     << "[D] Delete a student" << endl << "[O] Output List" << endl << "[M] Merge Lists"  << endl << "[E] Exit program" << endl;
char ans;
cin >> ans;

bool merge =false;

//not wanting to exit program
while(ans!='E'&& ans!= 'e')
{
 

int searchingtries = 0;
int studenttries = 0;
char student,category;
string FN, LN;
int Ival;
float Fval;
int categorytries = 0;
char repeat;





//searching option
if(ans == 'S'|| ans == 's')
{
 
 do
{
 cout << "[D] Domestic List Search \n" << "[I] International List Search \n";
 cin >> student;
  
 cout << "What category would you like to search for? \n" << "[A] Application ID \n" 
      << "[C] CGPA \n" << "[R] for researchscore\n" << "[N] Full name \n";
 cin >> category;
 //category choice for type of search. Parameters not given are assinged to default
 if(category == 'N' || category == 'n')
 {
  cout << "Enter the first name to be searched: \n";
  cin >> FN;
  cout << "Enter the last name: \n";
  cin >> LN;
  if(student == 'D' || student == 'd')
  DOMsearch(head, category, 0, 0.0, FN, LN);
  if(student=='I'||student=='i')
  INTsearch(head2,category,0,0.0,FN,LN);
 }

 if(category == 'A' || category == 'a')
 {
  cout << "Enter the application ID  you want to find: \n";
  cin >> Ival;   
  if(student=='D'||student=='d')
  DOMsearch(head, category,Ival,0.0,"ab", "ab");
  if(student=='I'||student=='i')
  INTsearch(head2, category,Ival,0.0,"ab","ab");
 }

 if(category == 'R' || category == 'r')
 {
  cout << "Enter the value of the research score you wish to find" << endl;
  cin >> Ival;
  if(student=='D'||student=='d')
  DOMsearch(head, category, Ival,0.0,"ab","ab");
  if(student=='I'||student=='i')
  INTsearch(head2,category,Ival,0.0,"ab","ab");
 }

 if(category=='C'||category =='c')
 {
  cout << "Enter the value of the cgpa you wish to find" << endl;
  cin >> Fval;
  if(student=='D'||student=='d')
  DOMsearch(head, category,0,Fval,"ab","ab");
  if(student == 'I'||student=='i')
  INTsearch(head2,category,0,Fval,"ab","ab");

 }

cout << "Would you like to search again? (Y/N) " << endl;
cin >> repeat;
}while(repeat == 'Y' || repeat == 'y');

}

//insert a new node to the lsit
if(ans == 'I' || ans == 'i')
{

 char stu;
 FN = "ab"; 
 LN = "ab";
 float cgpa;
 int RS,read,write,speak,listen;
 string province, country;

 

do
{
 cout << "What Student would you like to add to the list?\n" <<  "[D] New Domestic Student \n" << "[I] New Interenational Student\n";
 cin >> stu;
 studentnum++;
 cout << "Enter the info of the student you would like to insert \n";
 cout << "First Name: ";
 cin >> FN; 
 cout << endl << "Last Name: ";
 cin >> LN;
 cout << endl << "CGPA: ";
 cin >> cgpa;
 cout << endl << "Research Score: ";
 cin >> RS;
 //depending on type of list wanting to insert to, call domestic or international insert
 if(stu == 'D' || stu == 'd')
 {
  cout << endl <<  "Province: ";
  cin >> province;
  cout << endl;
 DOMinsertNode(head,tail,stu_count1,FN, LN, province,cgpa,RS,studentnum);
 StudentPtr tmpd;
 tmpd = head;
 cout << "----------------------------------------------------UPDATED LIST--------------------------------------------------------" << endl;
 while(tmpd!=NULL)
 {
  cout << tmpd;
  tmpd=tmpd->getlink();
 }
 
 }

 if(stu == 'I' || stu == 'i')
  {
   cout << endl << "Country: ";
   cin >> country;
   cout << endl << "Reading Score: ";
   cin >> read;
   cout << endl << "Writing Score: ";
   cin >> write;
   cout << endl << "Speaking Score: ";
   cin >> speak;
   cout << endl << "Listening Score: ";
   cin >> listen;  
   INTinsertNode(head2, tail2, stu_count2,FN, LN, read, write, speak, listen,country, cgpa, RS, studentnum); 
   StudentPtr tmpi;
   tmpi = head2;
   cout << "----------------------------------------------------UPDATED LIST--------------------------------------------------------" << endl;
   while(tmpi!=NULL)
   {
    cout << tmpi << endl;
    tmpi=tmpi->getlink();
   }
  }

 cout << "Would you like to add another student (Y/N)?" << endl;
 cin >> repeat;
}while(repeat == 'Y' || repeat == 'y');

}






//deleting a node option
if(ans == 'D'|| ans == 'd')
{
do
{
 char response;
 cout << "[H] Delete the head and tail node" << endl << "[D] Delete A specific student" << endl;
 cin >> response;
 //choosing to delete a specific student or the first and last one
 if(response == 'D' || response == 'd')
{

 student = 'd';
 FN = "ab"; 
 LN = "ab";
 
 //choose from international or domestic student lists
 cout << "[D] Delete a Domestic Student\n" << "[I] Delete an International Student\n";
 cin >> student;

 cout << endl << "Enter the first name of the student: "; 
 cin >> FN;
 
 cout << endl << "Enter the last name of the student: ";
 cin >> LN;

 if(student == 'D' || student == 'd')
  DOMdeletenode(head,tail,FN,LN);

 if(student == 'I' || student == 'i')
 INTdeletenode(head2, tail2,FN,LN);
}

//chhose to delete head and tail node, call that function
if(response == 'H' || response == 'h')
{
 cout << "Enter D for Domestic Student List, I for International Student List: " << endl;
 cin >> student;
 
 if(student == 'D' || student == 'd')
  DOMdeleteheadtail(head,tail);
 if(student == 'I' || student == 'i')
  INTdeleteheadtail(head2,tail2);
}

cout << "Would you like to delete a student(s)  again?(y/n)";
cin>>repeat;

}while(repeat=='Y'||repeat=='y');

}






//output a list type option
if(ans == 'O' || ans == 'o')
{
do
{
 StudentPtr tmpd;
 tmpd = head;
 StudentPtr tmpi;
 tmpi = head2;
 
 cout << "[D] Domestic Student Output\n" << "[I] International Student Output\n" <<"[B] Ouput Both Seperately\n";
 cin >> student;

//choice of deleting only domestic, only international, or both lists at the same time
 if(student == 'D' || student == 'd')
 {
 cout << "-----------------------------------------------DOMESTIC STUDENTS---------------------------------------------" << endl;
  //formatting the output for reading the file, with headers for each category at the top
  cout << setw(20) << left << "Application ID" << setw(20) << left << "First Name" << setw(20) << left << "Last Name"
   << setw(20) << left <<  "Research Score" << setw(20) << left << "CGPA" << setw(20) << left << "Province" << endl;
  while(tmpd!=NULL)
  {
   cout << tmpd;
  tmpd = tmpd->getlink();
  }
 }

 if(student == 'I' || student == 'i')
 {
 cout << "------------------------------------------------INTERNATIONAL STUDENTS--------------------------------------------------" << endl;
 //formatting the output to have header categories for each member
  cout << setw(20) << left << "Application ID" << setw(20) << left << "First Name" << setw(20) << left << "Last Name"
       << setw(20) << left <<  "Research Score" << setw(20) << left << "CGPA" << setw(20) << left << "Country" 
       << setw(10) << left << "TOEFL" << setw(10) << left << "Reading" << setw(10) << left << "Writing" 
       << setw(10) << left << "Listening" << setw(10) << left << "Speaking" << endl;
  while(tmpi!=NULL)
  { 
   cout << tmpi;
   tmpi=tmpi->getlink();
  }
 }
//both lists at same time
 if(student == 'B'||student=='b')
 {

 cout << "-----------------------------------------------DOMESTIC STUDENTS---------------------------------------------" << endl;
  //formatting the output for reading the file, with headers for each category at the top
  cout << setw(20) << left << "Application ID" << setw(20) << left << "First Name" << setw(20) << left << "Last Name"
   << setw(20) << left <<  "Research Score" << setw(20) << left << "CGPA" << setw(20) << left << "Province" << endl;
  while(tmpd!=NULL)
  {
   cout << tmpd;
  tmpd = tmpd->getlink();
  }

 cout << "------------------------------------------------INTERNATIONAL STUDENTS--------------------------------------------------" << endl;
 //formatting the output to have header categories for each member
  cout << setw(20) << left << "Application ID" << setw(20) << left << "First Name" << setw(20) << left << "Last Name"
       << setw(20) << left <<  "Research Score" << setw(20) << left << "CGPA" << setw(20) << left << "Country" 
       << setw(10) << left << "TOEFL" << setw(10) << left << "Reading" << setw(10) << left << "Writing" 
       << setw(10) << left << "Listening" << setw(10) << left << "Speaking" << endl;
  while(tmpi!=NULL)
  { 
   cout << tmpi;
   tmpi=tmpi->getlink();
  }


 }

cout << "Would you like to output another list? (y/n)";
cin >> repeat;
}while(repeat == 'Y'||repeat=='y');

}

//merge the lists
if(ans == 'M' || ans == 'm')
{
//if have not merged yet, merge the lists
 if(merge == false)
 {
  mergelists(headm,tailm,head,head2);
  merge = true;
 }

int option;

 cout << "MERGED LIST MAIN MENU: " << endl << "[1] Output merged list" << endl << "[2] Search students meeting threshold" << endl << "[3] Exit Program" << endl;
 cin >> option;


//choice between outputting merged list, searching threshold students and exiting the program
if(option == 1)
{
 StudentPtr tmpm = new Student;
 tmpm = headm;
 while(tmpm!=NULL)
 {
  cout << tmpm;
  tmpm = tmpm->getlink();
 }
}

 if(option == 2)
 {
  float cgpathresh;
  int RSthresh;
  cout << "Enter the Research Score Threshold and CGPA threshold\n" << "Research Score:  ";
  cin>> RSthresh;
  cout << "CGPA:  ";
  cin >> cgpathresh;
  StudentPtr tmps;
  tmps = headm;
  cout << "Students meeting criteria: \n";
  //only outputting students who meet the threshold
  while(tmps!=NULL)
  { 
  if(tmps->get_cgpa()>=cgpathresh && tmps->get_researchscore()>=RSthresh)
   cout << tmps;
 
   tmps = tmps->getlink();
  }
 }
//exit program
if(option==3)
return 0;
 

}


//repeat menu options, will have difffernet menu for merged list and pre merged lists
if(ans =='M' || ans == 'm')
{
 continue;
}



else
{
cout << " MAIN MENU: " << endl << "[S] Search for a student/group of students" << endl << "[I] Insert a new student" << endl 
     << "[D] Delete a student" << endl << "[O] Output current lists" << endl  << "[M] Merge lists" <<  endl << "[E] Exit program" << endl;
cin >> ans;
}


}




//go thru the lists and delete the elements;
 StudentPtr tmpdelete = head;

 while(tmpdelete!=NULL)
 {
  StudentPtr todelete = tmpdelete;
  tmpdelete = tmpdelete->getlink();
  delete todelete;
 }

 StudentPtr itmpdelete = head2;

 while(tmpdelete!=NULL)
 {
  StudentPtr todelete = itmpdelete;
  itmpdelete = itmpdelete->getlink();
  delete todelete;
 }

 return 0;
}
