#include <stdio.h>
#include "course.h"


int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Please supply an input file.\n");
		exit(1);
	}


	FILE *fp = fopen(argv[1], "r");
	char *lineBuf = NULL;
	size_t n = 0;
//	ssize_t lineLength = 0;
//	lineLength = getline(&lineBuf, &n, fp);
	getline(&lineBuf, &n, fp);

	int nStudents = atoi(lineBuf);
	for (int i = 0; i < nStudents; i++) {
		printf("%d\n", i);
	}
	
	free(lineBuf);
	fclose(fp);


//	Course **courses = NULL;
//	Course *c = createCourse("Duel300");
//
//	courses = malloc(sizeof(Course) * 2);
//	courses[0] = c;
//	courses[1] = createCourse("JibberJabber101");
//	printf("*courses[0]->title = %s\n", courses[0]->title);
//	printf("*courses[1]->title = %s\n", courses[1]->title);
//	printf("c: %s\n", c->title);
//	addStudentToCourse("David", c);
//	addStudentToCourse("Elaine", c);
//
//	printf("Students in %s: %lu\n", c->title, sizeof(c->students));
//	printf("c students[0] = %s\n", c->students[0]);
//	printf("c students[1] = %s\n", c->students[1]);
//	deleteCourse(c);	
	return 0;
}
