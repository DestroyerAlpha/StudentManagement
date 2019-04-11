#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void course_add();
struct Course course_init();
void course_display();
int course_modify();
void course_display_all();
void course_display_specific();
int main_menu();
int courses_options();
void course_delete();
void student_add();
struct Student student_init();
void student_display();
int student_modify();
void student_display_all();
void student_display_specific();
int main_menu();
int student_options();
void student_delete();
void fac_add();
struct Instructor fac_init(struct Instructor);
void fac_display();
int fac_modify();
void fac_display_all();
void fac_display_specific();
int main_menu();
int fac_options();
void fac_delete();

int main()
{
	FILE *fp1,*fp2,*fp3;
	fp1 = fopen("students","ab+");
	fp2 = fopen("courses","ab+");
	fp3 = fopen("fac","ab+");
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	
	while(1)
	{
		main_menu();
		
	}
	return 0;
}
		
struct Student
	{	
		int roll;
		char name[50];
		char branch[4];
		int sem;
		int ncourses;
		char course_code[10][6];
		
	};
struct Instructor
	{
		char facid[4];
		char name[50];
		int ncourses;
		char course_code[10][6];
	};
struct Course
	{
		int credits;
		char course_code[6];
		char name[50];
		int nstudents;
		int ninstructors;
		char instructor_ids[10][4];
		int student_rollnos[100];
	};
	

int student_options()

	{
		printf("Enter your Option\n");
		printf("1) Add\n");
		printf("2) Display All\n");
		printf("3) Search by Roll No.\n");
		printf("4) Modify Details\n");
		printf("5) Delete Details\n");
		printf("6) Back\n");
		int option;
		scanf("%d",&option);
		
		switch(option)
		{
		case 1:
			student_add();
			student_options();
			break;
		case 2:
			student_display_all();
			student_options();
			break;
		case 3:
			student_display_specific();
			student_options();
			break;
		case 4:
			student_modify();
			student_options();
			break;
		case 5:
			student_delete();
			student_options();
			break;
		case 6:
			return 0;
		default:
			printf("----------------------\nYou have entered a wrong response\n----------------------\n");
			student_options();
			break;
		}
		
		return 0;
	}


void student_add()
	{
		FILE *fpw;
		fpw = fopen("students","ab+");
		struct Student new,in;
		int flag = 0;
		new = student_init(new);
		while(fread(&in,sizeof(in),1,fpw))
		{
			if(in.roll==new.roll)
			{
				flag = 1;
				break;
			}
		}
		if(flag==1)
			printf("----------------------\nRoll No already exists!\n----------------------\n");
		else
			fwrite(&new,sizeof(new),1,fpw);
		
		fclose(fpw);
	}
void student_display_all()
	{
		FILE *fpr;
		fpr = fopen("students","rb");
		struct Student in;
		while(fread(&in,sizeof(struct Student),1,fpr))
		{
			student_display(in);
		}
		fclose(fpr);
	}

int student_modify()
	{
		FILE *fpr,*fpw;
		fpr = fopen("students","rb+");
		struct Student mod,trans;
		int roll,counter=0;
		fpw = fopen("temp","wb");
		while(fread(&trans,sizeof(trans),1,fpr))
		{
			fwrite(&trans,sizeof(trans),1,fpw);
		}
		fclose(fpw);
		rewind(fpr);
		printf("Whose entry do you wish to modify?\n");
		printf("Enter Roll No to modify\n");
		scanf("%d",&roll);
		while(fread(&mod,sizeof(mod),1,fpr))
		{
			if(roll == mod.roll)
			{
				student_display(mod);
				counter = 1;
				break;
				
			}
			

		}
		if(counter==0)
		{
				printf("----------------------\nThis roll no has no details available\n----------------------\n");
				return 0;
		}
		fseek(fpr,-sizeof(mod),SEEK_CUR);
		printf("What do you wish to modify?\n");
		printf("1)Roll \n");
		printf("2)Name \n");
		printf("3)Branch \n");
		printf("4)Sem \n");
		printf("5)No. Of Courses\n");
		printf("6)Back \n");
		int inp;
		scanf("%d",&inp);
		getchar();
		switch(inp)
		{
			case 1:
				printf("Enter New Roll no:\n");
				int roll1;
				scanf("%d",&roll1);
				int flag = 0;
				struct Student in;
				FILE *fpw;
				fpw = fopen("temp","rb");
				while(fread(&in,sizeof(in),1,fpw))
				{
					if(in.roll==roll1)
					{
						flag = 1;
						break;
					}
				}
				if(flag==1)
				{
					printf("----------------------\nRoll No already exists!\n----------------------\n");
				}
				else
					mod.roll = roll1;
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 2:
				printf("Enter New name:\n");
				scanf("%[^\n]s",mod.name);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 3:
				printf("Enter New Branch:\n");
				scanf("%s",mod.branch);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 4:
				printf("Enter New Semester:\n");
				scanf("%d",&mod.sem);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 5:
				printf("Enter New No of Courses:\n");
				scanf("%d",&mod.ncourses);
				int course_no = 0;
				while(course_no<mod.ncourses)
				{
					printf("Enter new courses\n");
					scanf("%s",mod.course_code[course_no]);
					fflush(stdin);
					course_no++;
				}
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 6:
				break;
		
		}
		
		fclose(fpr);
	}
		
void student_delete()
	{	
		FILE *fpr,*fpw;
		fpr = fopen("students","rb");
		fpw = fopen("temp","wb");
		int roll;
		printf("Enter the roll no to delete: \n");
		scanf("%d",&roll);
		struct Student trans;
		while(fread(&trans,sizeof(trans),1,fpr))
		{
			if(roll == trans.roll)
			{
				student_display(trans);
				char inp;
				getchar();
				printf("Are you sure you want to delete this? (Y,N)\n");
				scanf("%c",&inp);
				if(inp=='N')
				{
					fwrite(&trans,sizeof(trans),1,fpw);
				}
				
				
			}
			else
			{
				fwrite(&trans,sizeof(trans),1,fpw);
			}

		}
		remove("students");
		rename("temp","students");
		fclose(fpw);
}
		
			
		
		
void student_display(struct Student s)
		{
			printf("\n-----------------------------------\n");
			printf("Roll No : %d\n",s.roll);
			printf("Name : %s\n",s.name);
			printf("Branch : %s\n",s.branch);
			printf("Semester : %d\n",s.sem);
			printf("No of Courses : %d\n",s.ncourses);
			printf("Course code:\n");
			int course_no = 0;
			while(course_no<s.ncourses)
			{
				printf("%.5s\n",s.course_code[course_no]);
				course_no++;
			}
			printf("-----------------------------------\n");
		}
void student_display_specific()
	{
		FILE *fpr;
		fpr = fopen("students","rb");
		struct Student out;
		int roll;
		int flag = 0;
		printf("Enter Roll No to display\n");
		scanf("%d",&roll);
		while(fread(&out,sizeof(out),1,fpr))
		{
			if(roll == out.roll)
			{
				student_display(out);
				flag = 1;
				break;
				
			}

		}
		if(flag == 0)
		{
			printf("----------------------\nOops.... The Roll No does not exists\n----------------------\n");
		}
		
	}
		
		
struct Student student_init(struct Student s)
		{
			printf("Enter Roll No :\n");
			scanf("%d",&s.roll);
			getchar();
			printf("Enter name:\n");
			scanf("%[^\n]s",s.name);
			fflush(stdin);
			printf("Enter Branch:\n");
			scanf("%s",s.branch);
			fflush(stdin);
			printf("Enter Semester:\n");
			scanf("%d",&s.sem);
			printf("Enter No of courses:\n");
			scanf("%d",&s.ncourses);
			int course_no = 0;
			printf("Enter Course Code:\n");
			while(course_no<s.ncourses)
			{
				printf("%d) ",course_no+1);
				scanf("%s",s.course_code[course_no]);
				fflush(stdin);
				FILE *fpr;
				int flag = 0;
				fpr = fopen("courses","rb+");
				struct Course in,out;
				while(fread(&in,sizeof(in),1,fpr))
				{
					if(strcmp(in.course_code,s.course_code[course_no])==0)
					{
						flag = 1;
						break;
					}
				}
				if(flag==0)
				{
					printf("----------------------\nCourse Code doesn't exist exists! Add details please.\n----------------------\n");
					out = course_init(out);
					fwrite(&out,sizeof(out),1,fpr);
					
				}
				else
				{
					fseek(fpr,-sizeof(in),SEEK_CUR);
					int flag = 0;
					for(int i = 0;i<in.nstudents;i++)
					{
						if(in.student_rollnos[i]==s.roll)
							flag = 1;
					}
					if(flag == 0)
					{
						in.nstudents++;
						in.student_rollnos[in.nstudents-1] = s.roll;
						fwrite(&in,sizeof(in),1,fpr);
					}
				}
				course_no++;
				fclose(fpr);
			}
			return s;
		}


int courses_options()

	{
		printf("Enter your Option\n");
		printf("1) Add\n");
		printf("2) Display All\n");
		printf("3) Search by Course Code.\n");
		printf("4) Modify Details\n");
		printf("5) Delete Details\n");
		printf("6) Back\n");
		int option;
		scanf("%d",&option);
		
		switch(option)
		{
		case 1:
			course_add();
			courses_options();
			break;
		case 2:
			course_display_all();
			courses_options();
			break;
		case 3:
			course_display_specific();
			courses_options();
			break;
		case 4:
			course_modify();
			courses_options();
			break;
		case 5:
			course_delete();
			courses_options();
			break;
		case 6:
			return 0;
		default:
			printf("You have entered a wrong response\n");
			courses_options();
			break;
		}
		
		return 0;
	}


void course_add()
	{
		FILE *fpw;
		fpw = fopen("courses","ab+");
		struct Course new,in;
		int flag = 0;
		new = course_init(new);
		while(fread(&in,sizeof(in),1,fpw))
		{
			if(strcmp(in.course_code,new.course_code)==0)
			{
				flag = 1;
				break;
			}
		}
		if(flag==1)
			printf("----------------------\nCourse Code already exists!\n----------------------\n");
		else
			fwrite(&new,sizeof(new),1,fpw);
		
		fclose(fpw);
	}
void course_display_all()
	{
		FILE *fpr;
		fpr = fopen("courses","rb+");
		struct Course in;
		while(fread(&in,sizeof(in),1,fpr))
		{
			course_display(in);
		}
		fclose(fpr);
	}

int course_modify()
	{
		FILE *fpr,*fpw;
		fpr = fopen("courses","rb+");
		struct Course mod,trans;
		char code[6];
		int counter = 0;
		fpw = fopen("temp","wb");
		while(fread(&trans,sizeof(trans),1,fpr))
		{
			fwrite(&trans,sizeof(trans),1,fpw);
		}
		fclose(fpw);
		rewind(fpr);
		printf("Whose entry do you wish to modify?\n");
		printf("Enter Course Code to modify\n");
		scanf("%s",code);
		while(fread(&mod,sizeof(mod),1,fpr))
		{
			if(strcmp(code,mod.course_code)==0)
			{
				course_display(mod);
				counter = 1;
				break;
				
			}
			

		}
		if(counter==0)
		{
				printf("----------------------\nThis course has no details available\n----------------------\n");
				return 0;
		}
		fseek(fpr,-sizeof(mod),SEEK_CUR);
		printf("What do you wish to modify?\n");
		printf("1)Course Code \n");
		printf("2)Name \n");
		printf("3)No of Students \n");
		printf("4)No of Instructors \n");
		printf("5)Credits\n");
		printf("6)Back \n");
		int inp;
		scanf("%d",&inp);
		getchar();
		
		switch(inp)
		{
			case 1:
				printf("Enter New Course Code:\n");
				char course1[6];
				scanf("%s",course1);
				int flag = 0;
				struct Course in;
				FILE *fpw;
				fpw = fopen("temp","rb");
				while(fread(&in,sizeof(in),1,fpw))
				{
					if(strcmp(in.course_code,course1)==0)
					{
						flag = 1;
						break;
					}
				}
				if(flag==1)
				{
					printf("----------------------\nCourse Code already exists!\n----------------------\n");
				}
				else
					strcpy(mod.course_code,course1);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 2:
				printf("Enter New name:\n");
				scanf("%[^\n]s",mod.name);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 3:
				printf("Enter New no of students enrolled:\n");
				scanf("%d",&mod.nstudents);
				int stu_no = 0;
				printf("Enter Roll No of Students Enrolled:");
				while(stu_no<mod.nstudents)
				{
					scanf("%d",&mod.student_rollnos[stu_no]);
					fflush(stdin);
					stu_no++;
				}
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 4:
				printf("Enter New No of Instructors:\n");
				scanf("%d",&mod.ninstructors);
				int fac_no = 0;
				printf("Enter Faculty Code:\n");
				while(fac_no<mod.ninstructors)
				{
					scanf("%s",mod.instructor_ids[fac_no]);
					fflush(stdin);
					fac_no++;
				}
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 5:
				printf("Enter New Credits:\n");
				scanf("%d",&mod.credits);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 6:
				break;
		
		}
		fclose(fpr);
	}
		
void course_delete()
	{	
		FILE *fpr,*fpw;
		fpr = fopen("courses","rb");
		fpw = fopen("temp","wb");
		char code[6];
		printf("Enter the Course Code to delete: \n");
		scanf("%s",code);
		struct Course trans;
		while(fread(&trans,sizeof(trans),1,fpr))
		{
			if(strcmp(code,trans.course_code)==0)
			{
				course_display(trans);
				char inp;
				getchar();
				printf("Are you sure you want to delete this? (Y,N)\n");
				scanf("%c",&inp);
				if(inp=='N')
				{
					fwrite(&trans,sizeof(trans),1,fpw);
				}
			}
			else
			{
				fwrite(&trans,sizeof(trans),1,fpw);
			}

		}
		remove("courses");
		rename("temp","courses");
		fclose(fpw);
}
		
			
		
		
void course_display(struct Course s)
		{
			printf("\n-----------------------------------\n");
			printf("Course Code : %s\n",s.course_code);
			printf("Name : %s\n",s.name);
			printf("Credits : %d\n",s.credits);
			printf("Total No of Instructors : %d\n",s.ninstructors);
			printf("Faculty ID:\n");
			int fac_no = 0;
			while(fac_no<s.ninstructors)
			{
				printf("%s\n",s.instructor_ids[fac_no]);
				fac_no++;
			}
			printf("No of Students : %d\n",s.nstudents);
			printf("Roll no of enrolled students:\n");
			int stu_no = 0;
			while(stu_no<s.nstudents)
			{
				printf("%d\n",s.student_rollnos[stu_no]);
				stu_no++;
			}
			printf("-----------------------------------\n");
		}
void course_display_specific()
	{
		FILE *fpr;
		fpr = fopen("courses","rb");
		struct Course out;
		char code[6];
		int flag = 0;
		printf("Enter Course Code to display\n");
		scanf("%s",code);
		while(fread(&out,sizeof(out),1,fpr))
		{
			if(strcmp(code,out.course_code)==0)
			{
				course_display(out);
				flag = 1;
				break;
				
			}

		}
		if(flag == 0)
		{
			printf("----------------------\nOops.... the Course does not exists....\n----------------------\n");
		}
		
	}
		
		
struct Course course_init(struct Course s)
		{
			printf("Enter Course Code :\n");
			scanf("%s",s.course_code);
			getchar();
			printf("Enter name:\n");
			scanf("%[^\n]s",s.name);
			printf("Enter Credits:\n");
			scanf("%d",&s.credits);
			printf("Enter No of instructors:\n");
			scanf("%d",&s.ninstructors);
			int fac_no = 0;
			printf("Enter Faculty Code:\n");
			while(fac_no<s.ninstructors)
			{
				scanf("%s",s.instructor_ids[fac_no]);
				fflush(stdin);
				fac_no++;
			}
			printf("Enter No of Students:\n");
			scanf("%d",&s.nstudents);
			int stu_no = 0;
			printf("Enter Roll No of Students Enrolled:\n");
			while(stu_no<s.nstudents)
			{
				scanf("%d",&s.student_rollnos[stu_no]);
				fflush(stdin);
				stu_no++;
			}
			return s;
		}

	
	
int fac_options()

	{
		printf("Enter your Option\n");
		printf("1) Add\n");
		printf("2) Display All\n");
		printf("3) Search by Fac Id.\n");
		printf("4) Modify Details\n");
		printf("5) Delete Details\n");
		printf("6) Back\n");
		int option;
		scanf("%d",&option);
		
		switch(option)
		{
		case 1:
			fac_add();
			fac_options();
			break;
		case 2:
			fac_display_all();
			fac_options();
			break;
		case 3:
			fac_display_specific();
			fac_options();
			break;
		case 4:
			fac_modify();
			fac_options();
			break;
		case 5:
			fac_delete();
			fac_options();
			break;
		case 6:
			return 0;
		default:
			printf("You have entered a wrong response\n");
			fac_options();
			break;
		}
		
		return 0;
	}


void fac_add()
	{
		FILE *fpw;
		fpw = fopen("fac","ab+");
		struct Instructor new,in;
		int flag = 0;
		new = fac_init(new);
		while(fread(&in,sizeof(in),1,fpw))
		{
			if(!strcmp(in.facid,new.facid))
			{
				flag = 1;
				break;
			}
		}
		if(flag==1)
			printf("----------------------\nFaculty ID already exists!\n----------------------\n");
		else
			fwrite(&new,sizeof(new),1,fpw);
		
		fclose(fpw);
	}
void fac_display_all()
	{
		FILE *fpr;
		fpr = fopen("fac","rb");
		struct Instructor in;
		while(fread(&in,sizeof(in),1,fpr))
		{
			fac_display(in);
		}
		fclose(fpr);
	}

int fac_modify()
	{
		FILE *fpr,*fpw;
		fpr = fopen("fac","rb+");
		struct Instructor mod,trans;
		char id[4];
		int counter = 0;
		fpw = fopen("temp","wb");
		while(fread(&trans,sizeof(trans),1,fpr))
		{
			fwrite(&trans,sizeof(trans),1,fpw);
		}
		fclose(fpw);
		rewind(fpr);
		printf("----------------------\nWhose entry do you wish to modify?\n");
		printf("Enter Faculty ID to modify\n----------------------\n");
		scanf("%s",id);
		while(fread(&mod,sizeof(mod),1,fpr))
		{
			if(strcmp(id,mod.facid)==0)
			{
				fac_display(mod);
				counter = 1;
				break;
				
			}
			

		}
		if(counter==0)
		{
				printf("----------------------\nThis faculty ID has no details available\n----------------------\n");
				return 0;
		}
		fseek(fpr,-sizeof(mod),SEEK_CUR);
		printf("What do you wish to modify?\n");
		printf("1)Fac ID \n");
		printf("2)Name \n");
		printf("3)No. Of Courses\n");
		printf("4)Back \n");
		int inp;
		scanf("%d",&inp);
		getchar();
		switch(inp)
		{
			case 1:
				printf("Enter New Faculty ID:\n");
				char id1[4];
				scanf("%s",id1);
				int flag = 0;
				struct Instructor in;
				FILE *fpw;
				fpw = fopen("temp","rb");
				while(fread(&in,sizeof(in),1,fpw))
				{
					if(strcmp(in.facid,id1)==0)
					{
						flag = 1;
						break;
					}
				}
				if(flag==1)
				{
					printf("----------------------\nFaculty ID already exists!\n----------------------\n");
				}
				else
					strcpy(mod.facid,id1);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 2:
				printf("Enter New name:\n");
				scanf("%[^\n]s",mod.name);
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 3:
				printf("Enter New No of Courses:\n");
				scanf("%d",&mod.ncourses);
				int course_no = 0;
				while(course_no<mod.ncourses)
				{
					printf("Enter new courses\n");
					scanf("%s",mod.course_code[course_no]);
					fflush(stdin);
					course_no++;
				}
				fwrite(&mod,sizeof(mod),1,fpr);
				break;
			case 4:
				break;
		
		}
		fclose(fpr);
	}
		
void fac_delete()
	{	
		FILE *fpr,*fpw;
		fpr = fopen("fac","rb");
		fpw = fopen("temp","wb");
		char id[4];
		printf("Enter the Faculty ID to delete: \n");
		scanf("%s",id);
		struct Instructor trans;
		while(fread(&trans,sizeof(trans),1,fpr))
		{
			if(!strcmp(id,trans.facid))
			{
				fac_display(trans);
				char inp;
				getchar();
				printf("Are you sure you want to delete this? (Y,N)\n");
				scanf("%c",&inp);
				if(inp=='N')
				{
					fwrite(&trans,sizeof(trans),1,fpw);
				}
				
				
			}
			else
			{
				fwrite(&trans,sizeof(trans),1,fpw);
			}

		}
		remove("fac");
		rename("temp","fac");
		fclose(fpw);
}
		
			
		
		
void fac_display(struct Instructor s)
		{
			printf("\n-----------------------------------\n");
			printf("Faculty ID : %s\n",s.facid);
			printf("Name : %s\n",s.name);
			printf("No of Courses : %d\n",s.ncourses);
			printf("Course code:\n");
			int course_no = 0;
			while(course_no<s.ncourses)
			{
				printf("%.5s\n",s.course_code[course_no]);
				course_no++;
			}
			printf("-----------------------------------\n");
		}
void fac_display_specific()
	{
		FILE *fpr;
		fpr = fopen("fac","rb");
		struct Instructor out;
		char id[4];
		int flag = 0;
		printf("Enter Faculty ID to display\n");
		scanf("%s",id);
		while(fread(&out,sizeof(out),1,fpr))
		{
			if(!strcmp(id,out.facid))
			{
				fac_display(out);
				flag = 1;
				break;
				
			}

		}
		if(flag == 0)
		{
			printf("\n----------------------\nOops.... The Fac ID does not exists....\n----------------------\n");
		}
		
	}
		
		
struct Instructor fac_init(struct Instructor s)
		{
			printf("Enter Faculty ID:\n");
			scanf("%s",s.facid);
			getchar();
			printf("Enter name:\n");
			scanf("%[^\n]s",s.name);
			fflush(stdin);
			printf("Enter No of courses:\n");
			scanf("%d",&s.ncourses);
			int course_no = 0;
			printf("Enter Course Code:\n");
			while(course_no<s.ncourses)
			{
				scanf("%s",s.course_code[course_no]);
				fflush(stdin);
				course_no++;
			}
			return s;
		}

int main_menu()
	{
		printf("Enter your Option\n");
		printf("1) Student\n");
		printf("2) Courses\n");
		printf("3) Instructor\n");
		printf("4) Exit\n");
		int option;
		scanf("%d",&option);
		switch(option)
		{
		case 1:
			student_options();
			break;
		case 2:
			courses_options();
			break;
		case 3:
			fac_options();
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("You have entered a wrong response\n");
			main_menu();
			break;
		}
	}	
