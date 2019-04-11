The file doesn't require much of a setup as everything has been packaged into one file.

Just run the command "gcc -o assign assign.c" and then "./assign" and you are all set.

The menus are very intuitive as to what their functions are, and every menu has a back option.

The files are created in a binary format so "cat students" or "cat courses" is useless as it is unreadable.

The files can only be used with the program.

When you enter the details of a student with a new course, the course initialisation function is called and you are supposed to enter the details of the course.

When a student is added to an existing course, his roll no is automatically added to the "courses" file. But deleting the details or modifying them will have no effect on the other file.

There are certain limitations that the user is expected to abid by:-
	Roll no is of int type so the value should not exceed INT_MAX
	Course Code is a character array of size 6 so the input should not exceed 5 characters. e.g. HS101, CS102, PH105, etc.
	Faculty ID is a character array of size 4 so the input should not exceed 3 characters. e.g. BVL, SRB, NRS, etc.
	Student branch is a character array of size 4 so the input should not exceed 3 characters. e.g. CSE, EE, ME, etc.
	The comparisions are case sensitive so if you have Faculty ID 'SRB' in file and you search for 'srb', it will return false.
	Name should be smaller than 50 characters.
	Max no of courses allowed per student and per instructor is 10.
	Max no of students per course is 100.
	

