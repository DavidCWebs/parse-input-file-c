#include <stdio.h>
#include "course.h"

int courseExists(const char *courseTitle)
{
	printf("Checking %s\n", courseTitle);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Please supply an input file.\n");
		exit(1);
	}


	FILE *fp = fopen(argv[1], "r");
	char *lineBuf = NULL;
	size_t n = 0;
	ssize_t length = 0;
	getline(&lineBuf, &n, fp);
	int nStudents = atoi(lineBuf);
	
	Course **courses = NULL;
	size_t nCoursePtrs = 0;

	for (int i = 0; i < nStudents; i++) {
		length = getline(&lineBuf, &n, fp);
		char *student = calloc(sizeof(student) * length, sizeof(char));
		strncpy(student, lineBuf, length - 1); // Remove final '\n'

		getline(&lineBuf, &n, fp);
		int nCourses = atoi(lineBuf);
		
		for (int j = 0; j < nCourses; j++) {
			length = getline(&lineBuf, &n, fp);
			char *courseTitle = calloc(sizeof(courseTitle) * length, sizeof(*courseTitle));
			strncpy(courseTitle, lineBuf, length - 1);
			if (courseExists(courseTitle)) {
				
			} else {
				printf("DEBUG: nCoursePtrs = %lu\n", nCoursePtrs);
				// Create course
				Course **tmp = realloc(courses, ++nCoursePtrs * sizeof(*courses));
				if (!tmp) {
					fprintf(stderr, "realloc failed for courses.\n");
					exit(1);
				}
				courses = tmp;
				courses[nCoursePtrs - 1] = createCourse(courseTitle);

				// Add student
			}
			free(courseTitle);
		}
		free(student);
	}
	free(lineBuf);
	fclose(fp);
	for (size_t i = 0; i < nCoursePtrs; i++) {
		deleteCourse(courses[i]);
	}
	free(courses);


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
