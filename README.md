Parse Input File
================

Take command-line reference to a file and parse input. Process data and write output to files.

Learning exercise in C:

* Parsing input
* Dynamically allocating and freeing storage
* Reading and writing from/to files

Input
-----
Input file format:

```
number of students
student 1 name
student 1 number of courses
coursename 1
coursename 2
...
student 2 name
student 2 number of courses
coursename 2,
coursename 4
...
```
The programme creates a file for every unique course and adds students enrolled on the course.		


Main functionality, basic example:

```c
Course **courses = NULL;
Course *c = createCourse("Programming in C");

courses = malloc(sizeof(Course) * 2);
courses[0] = c;
courses[1] = createCourse("JibberJabber101");

printf("*courses[0]->title = %s\n", courses[0]->title);
printf("*courses[1]->title = %s\n", courses[1]->title);
printf("c: %s\n", c->title);

addStudentToCourse("Alice", c);
addStudentToCourse("Bob", c);

printf("Students in %s: %lu\n", c->title, sizeof(c->students));
printf("c students[0] = %s\n", c->students[0]);
printf("c students[1] = %s\n", c->students[1]);

deleteCourse(c);	
```
