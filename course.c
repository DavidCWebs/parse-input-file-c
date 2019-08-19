#include "course.h"

Course *createCourse(char *title)
{
	Course *c = malloc(sizeof(Course));
	c->title = malloc(strlen(title) + 1);
	strcpy(c->title, title);
	c->students = NULL;
	c->nStudents = 0;
	return c;
}

void addStudentToCourse(char *student, Course *c)
{
	char **tmp = realloc(c->students, sizeof(c->students) * (c->nStudents + 1));
	if (!tmp) {
		fprintf(stderr, "realloc failed!");
		exit(1);
	}
	c->students = tmp;
	
	*(c->students + c->nStudents) = malloc(strlen(student) + 1);
	strcpy(*(c->students + c->nStudents), student);
	c->nStudents++;
}

void deleteCourse(Course *c)
{
	free(c->title);
	for (size_t i = 0; i < c->nStudents; i++) {
//		printf("deleting student %s\n", c->students[i]);
		free(*(c->students + i));
	}
	free(c->students);
	free(c);
}

