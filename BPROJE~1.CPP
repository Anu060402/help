#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<process.h>
int tdays;
struct student
{
	long rno;
	int m1,m2,m3;
	float p;
	char sname[30],fname[30],bgrp[5],g1,g2,g3;
	student()
	{
	m1=m2=m3=rno=0;
	p=0;
	strcpy(sname,"nil");
	strcpy(fname,"nil");
	strcpy(bgrp,"nil");
	g1='-';
	g2='-';
	g3='-';
	}
	void enter()
	{
	cout<<"enter roll no. ";
	cin>>rno;
	cout<<"enter student name ";
	gets(sname);
	cout<<"enter fathers name ";
	gets(fname);
	cout<<"enter blood group ";
	gets(bgrp);
	cout<<"Enter marks in physics,chemistry,mathematics out of 80 ";
	cin>>m1>>m2>>m3;
	if(m1>80)
	{
	cout<<"invalid input. enter physics marks again ";
	cin>>m1;
	}
	if(m2>80)
	{
	cout<<"invalid input. enter chemistry marks again ";
	cin>>m2;
	}
	if(m3>80)
	{
	cout<<"invalid input. enter maths marks again ";
	cin>>m3;
	}

	cout<<"enter total no. of days present ";
	cin>>p;
	if(p>tdays)
	{
	cout<<"invalid input. enter no. of days present again ";
	cin>>p;
	}

	}
	void gcalc(int m,char &g)
	{
	if (m>80)
	{
	  cout<<"Invalid entry";

	}
	if(m>=64)
	g='A';
	if(m>=48&&m<64)
	g='B';
	if(m>=40&&m<48)
	g='C';
	if(m>=32&&m<40)
	g='D';
	if(m<32)
	g='E';
	}
	void display()
	{
	gcalc(m1,g1);
	gcalc(m2,g2);
	gcalc(m3,g3);
	cout<<"STUDENT REPORT"<<endl;
	cout<<"STUDENT'S NAME: "<<sname<<endl;
	cout<<"FATHER'S NAME: "<<fname<<endl;
	cout<<"BLOOD GROUP: "<<bgrp<<endl;
	cout<<"\n Marks in Physics: "<<m1<<endl;
	cout<<"Grade in Physics: "<<g1<<endl;
	cout<<"\n Marks in Chemistry: "<<m2<<endl;
	cout<<"Grade in Chemistry: "<<g2<<endl;
	cout<<"\n Marks in Mathematics: "<<m3<<endl;
	cout<<"Grade in Mathematics: "<<g3<<endl;
	cout<<"\n No. of days present: "<<p<<endl;
	cout<<"No. of days absent: "<<tdays-p<<endl;
	cout<<"Total no. of working days: "<<tdays<<endl;
	if(p>=(0.7*tdays)&&g1!='E'&&g2!='E'&&g3!='E')
	cout<<"\n Eligible to write final exam : Yes "<<endl;
	else
	cout<<"Eligible to write final exam : No "<<endl;
	cout<<endl;
	}
};
void create(char cname[])
{
	student s;
	char ch;
	fstream f;
	f.open(cname,ios::in|ios::out|ios::binary|ios::trunc);
	do
	{
	cout<<"student details: "<<endl;
	s.enter();
	f.write((char*)&s,sizeof(s));
	cout<<"do you want to continue adding details? ";
	cin>>ch;
	}while(ch=='y'||ch=='Y');
	f.close();
}
void append(char cname[])
{
	student s;
	char ch;
	fstream f;
	f.open(cname,ios::in|ios::out|ios::binary|ios::app);
	do
	{
	cout<<"student details: "<<endl;
	s.enter();
	f.write((char*)&s,sizeof(s));
	cout<<"do you want to continue adding details? ";
	cin>>ch;
	}while(ch=='y'||ch=='Y');
	f.close();
}
void edit(char cname[])
{
	int flag=0;
	student s,t;
	fstream f;
	f.open(cname,ios::in|ios::out|ios::binary|ios::ate);
	cout<<"enter details to be modified "<<endl;
	t.enter();
	f.seekg(0);
	while(f)
	{
	f.read((char*)&s,sizeof(s));
	if(strcmpi(t.sname,s.sname)==0)
	{
	flag=1;
	f.seekp(f.tellg()-sizeof(s));
	f.write((char*)&t,sizeof(t));
	break;
	}
	}
	if(flag==0)
	cout<<"file not found ";
	f.close();
}
void deletion(char cname[])
{
	int k=0;
	student t;
	long rno;
	fstream f,g;
	f.open(cname,ios::in|ios::out|ios::binary);
	g.open("temp.dat",ios::in|ios::out|ios::binary);
	cout<<"enter the roll no. of the student whose file has to be deleted ";
	cin>>rno;
	f.read((char*)&t,sizeof(t));
	while(f)
	{
	if(rno!=t.rno)
	g.write((char*)&t,sizeof(t));
	else
	k=1;
	f.read((char*)&t,sizeof(t));
	}
	if(k==0)
	cout<<"record not found"<<endl;
	f.close();
	g.close();
	remove(cname);
	rename("temp.dat",cname);
}
void attdisplay(char cname[])
{
	student t;
	fstream f;
	f.open(cname,ios::in|ios::out|ios::binary);
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	cout<<setiosflags(ios::right)<<setw(5)<<"Roll no."<<'\t';
	cout<<setiosflags(ios::left)<<setw(12)<<"Name"<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<"Days present"<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<"Days absent"<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<"Total days"<<'\t'<<endl;
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	f.seekg(0);
	f.read((char*)&t,sizeof(t));
	while(f)
	{
	cout<<setiosflags(ios::right)<<setw(5)<<t.rno<<'\t';
	cout<<setiosflags(ios::left)<<setw(18)<<t.sname<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<t.p<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<tdays-t.p<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<tdays<<'\t'<<endl;
	f.read((char*)&t,sizeof(t));
	}
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	f.close();
}
void disp(char cname[])
{
	student t;
	char ch;
	fstream f;
	f.open(cname,ios::in|ios::out|ios::binary);
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	cout<<setiosflags(ios::right)<<setw(5)<<"Roll no."<<'\t';
	cout<<setiosflags(ios::left)<<setw(12)<<"Name"<<'\t';
	cout<<setiosflags(ios::left)<<setw(12)<<"Father's name"<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<"BGrp"<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<"Physics"<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<"Grade"<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<"Chemistry"<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<"Grade"<<'\t';
	cout<<setiosflags(ios::right)<<setw(8)<<"Maths"<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<"Grade"<<'\t';
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	f.seekg(0);
	f.read((char*)&t,sizeof(t));
	while(f)
	{
	cout<<setiosflags(ios::right)<<setw(5)<<t.rno<<'\t';
	cout<<setiosflags(ios::left)<<setw(18)<<t.sname<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<t.fname<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<t.bgrp<<'\t';
	cout<<setiosflags(ios::right)<<setw(5)<<t.m1<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<t.g1<<'\t';
	cout<<setiosflags(ios::right)<<setw(5)<<t.m2<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<t.g2<<'\t';
	cout<<setiosflags(ios::right)<<setw(5)<<t.m3<<'\t';
	cout<<setiosflags(ios::left)<<setw(8)<<t.g3<<'\t';
	f.read((char*)&t,sizeof(t));
	}
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	f.close();
	attdisplay(cname);
}

void studentdisplay(char cname[],char name[])
{
	int flag=0;
	student t;
	fstream f;
	f.open(cname,ios::in|ios::out|ios::binary);
	f.read((char*)&t,sizeof(t));
	while(f)
	{
	if(strcmpi(name,t.sname)==0)
	{
	clrscr();
	t.display();
	flag=1;
	break;
	}
	f.read((char*)&t,sizeof(t));
	}
	if(flag==0)
	cout<<"invalid input";
	f.close();
}
void namelist(char cname[])
{
	student s;
	fstream f;
	f.open(cname,ios::in|ios::out|ios::binary);
	cout<<"CLASS NAMELIST \n"<<endl;
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	cout<<setiosflags(ios::right)<<setw(8)<<"Roll no."<<'\t';
	cout<<setiosflags(ios::left)<<setw(12)<<"Name"<<'\t'<<endl;
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	f.read((char*)&s,sizeof(s));
	while(f)
	{
	cout<<setiosflags(ios::right)<<setw(8)<<s.rno<<'\t';
	cout<<setiosflags(ios::left)<<setw(12)<<s.sname<<'\t'<<endl;
	f.read((char*)&s,sizeof(s));
	}
	cout<<setw(80)<<setfill('-')<<" "<<endl;
	cout<<setw(80)<<setfill(' ')<<" "<<endl;
	f.close();
}
void main()
{
	clrscr();
	int op,c;
	char s,name[30];
	gotoxy(34,1);
	cout<<"Student Report Card";
	gotoxy(34,3);
	cout<<"And";
	gotoxy(34,5);
	cout<<"Attendance";
	gotoxy(34,7);
	cout<<"Done By:-";
	gotoxy(43,8);
	cout<<"Anushkaa Awasthi and S.Shreela"<<endl;
	cout<<"INTRODUCTION:-"<<endl;
	cout<<"The following program is the C++ version of a student report card and attendance";
	cout<<"details. There is a main menu using which the user can create,append,edit and"<<endl;
	cout<<"delete the details of a student. The attendance display menu enables the user to";
	cout<<"view the attendance details of a particular class.The student report function"<<endl;
	cout<<"enables the user to view an individual's report card which displays the"<<endl;
	cout<<"student's name,father's name,blood group,marks in three subjects,attendance"<<endl;\
	cout<<"details and the eligibility to write the exam.The class namelist displays the"<<endl;
	cout<<"names of the student along with their roll number according to the class which"<<endl;
	cout<<"the user enters."<<endl;
	cout<<"enter total no. of working days ";
	cin>>tdays;

	do
	{
	cout<<"MAIN MENU"<<endl;
	cout<<"choose your option :"<<endl;
	cout<<"1.create file"<<endl;
	cout<<"2.append file"<<endl;
	cout<<"3.edit file"<<endl;
	cout<<"4.delete file"<<endl;
	cout<<"5.display attendance details"<<endl;
	cout<<"6.dislay student report"<<endl;
	cout<<"7.dislay class namelist"<<endl;
	cout<<"8.exit"<<endl;
	cin>>op;
	switch(op)
	{
	case 1:
	{
	cout<<"choose class to enter details: "<<endl;
	cout<<"1.E1"<<endl;
	cout<<"2.E2"<<endl;
	cout<<"3.F1"<<endl;
	cout<<"4.F2"<<endl;
	cin>>c;
	switch(c)
	{
	case 1:
	create("E1.dat");
	break;
	case 2:
	create("E2.dat");
	break;
	case 3:
	create("F1.dat");
	break;
	case 4:
	create("F2.dat");
	break;
	default:
	cout<<"invalid input";
	}
	break;
	}
	case 2:
	{
	cout<<"choose class to add details in: "<<endl;
	cout<<"1.E1"<<endl;
	cout<<"2.E2"<<endl;
	cout<<"3.F1"<<endl;
	cout<<"4.F2"<<endl;
	cin>>c;
	switch(c)
	{
	case 1:
	append("E1.dat");
	break;
	case 2:
	append("E2.dat");
	break;
	case 3:
	append("F1.dat");
	break;
	case 4:
	append("F2.dat");
	break;
	default:
	cout<<"invalid input";
	}
	break;
	}
	case 3:
	{
	cout<<"choose class to edit details: "<<endl;
	cout<<"1.E1"<<endl;
	cout<<"2.E2"<<endl;
	cout<<"3.F1"<<endl;
	cout<<"4.F2"<<endl;
	cin>>c;
	switch(c)
	{
	case 1:
	edit("E1.dat");
	break;
	case 2:
	edit("E2.dat");
	break;
	case 3:
	edit("F1.dat");
	break;
	case 4:
	edit("F2.dat");
	break;
	default:
	cout<<"invalid input";
	}
	break;
	}
	case 4:
	{
	cout<<"choose class to delete details in: "<<endl;
	cout<<"1.E1"<<endl;
	cout<<"2.E2"<<endl;
	cout<<"3.F1"<<endl;
	cout<<"4.F2"<<endl;
	cin>>c;
	switch(c)
	{
	case 1:
	deletion("E1.dat");
	break;
	case 2:
	deletion("E2.dat");
	break;
	case 3:
	deletion("F1.dat");
	break;
	case 4:
	deletion("F2.dat");
	break;
	default:
	cout<<"invalid input";
	}
	break;
	}
	case 5:
	{
	clrscr();
	cout<<"choose class to display attendance details: "<<endl;
	cout<<"1.E1"<<endl;
	cout<<"2.E2"<<endl;
	cout<<"3.F1"<<endl;
	cout<<"4.F2"<<endl;
	cin>>c;
	switch(c)
	{
	case 1:
	attdisplay("E1.dat");
	break;
	case 2:
	attdisplay("E2.dat");
	break;
	case 3:
	attdisplay("F1.dat");
	break;
	case 4:
	attdisplay("F2.dat");
	break;
	default:
	cout<<"invalid input";
	}
	break;
	}
	case 6:
	{
	cout<<"choose class of the student whose report has to be displayed: "<<endl;
	cout<<"1.E1"<<endl;
	cout<<"2.E2"<<endl;
	cout<<"3.F1"<<endl;
	cout<<"4.F2"<<endl;
	cin>>c;
	cout<<"enter name of the student: ";
	gets(name);
	switch(c)
	{
	case 1:
	studentdisplay("E1.dat",name);
	break;
	case 2:
	studentdisplay("E2.dat",name);
	break;
	case 3:
	studentdisplay("F1.dat",name);
	break;
	case 4:
	studentdisplay("F2.dat",name);
	break;
	default:
	cout<<"invalid input";
	}
	break;
	}
	case 7:
	{
	cout<<"choose class of the student whose namelist has to be displayed: "<<endl;
	cout<<"1.E1"<<endl;
	cout<<"2.E2"<<endl;
	cout<<"3.F1"<<endl;
	cout<<"4.F2"<<endl;
	cin>>c;
	switch(c)
	{
	case 1:
	namelist("E1.dat");
	break;
	case 2:
	namelist("E2.dat");
	break;
	case 3:
	namelist("F1.dat");
	break;
	case 4:
	namelist("F2.dat");
	break;
	default:
	cout<<"invalid input";
	}
	break;
	}
	case 8:
	exit(0);
	break;
	}
	cout<<"do you want to choose another option? ";
	cin>>s;
	}while(s=='y'||s=='Y');
}




















