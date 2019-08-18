#ifndef CLASSES_H
#define CLASSES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *title;
	char **students;
	size_t nStudents;
} Course; 

Course *createCourse(char *title);
void addStudentToCourse(char *student, Course *course);
void deleteCourse(Course *c);

#endif

