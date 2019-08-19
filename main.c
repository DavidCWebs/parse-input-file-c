#include <stdio.h>
#include "course.h"
#include "file-utilities.h"

int courseExists(const char *courseTitle, Course **courses, size_t n);
void printStringArray(char **strings, size_t n);
void writeFiles(Course **courses, size_t n, const char* basename);

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
	// First line of input file: number of students.
	getline(&lineBuf, &n, fp);
	int nStudents = atoi(lineBuf);
	
	Course **courses = NULL;
	size_t nCoursePtrs = 0;

	for (int i = 0; i < nStudents; i++) {
		// Within student block, first line is name.
		length = getline(&lineBuf, &n, fp);
		char *student = calloc(sizeof(student) * length, sizeof(char));
		strncpy(student, lineBuf, length - 1); // Remove final '\n'
		// Within student block, second line is number of courses for this student.
		getline(&lineBuf, &n, fp);
		int nCourses = atoi(lineBuf);
		// The following nCourses lines are the course titles for this student.
		for (int j = 0; j < nCourses; j++) {
			// Initialise space for courseTitle, all values zero.
			length = getline(&lineBuf, &n, fp);
			char *courseTitle = calloc(sizeof(courseTitle) * length, sizeof(*courseTitle));
			strncpy(courseTitle, lineBuf, length - 1);

			// Determine if course exists in the array of stuct pointers
			int courseIndex = courseExists(courseTitle, courses, nCoursePtrs);
			if (nCoursePtrs == 0 || courseIndex == -1) {
				// Course does not exist: create and add student name to it's student member.
				Course **tmp = realloc(courses, ++nCoursePtrs * sizeof(*courses));
				if (!tmp) {
					fprintf(stderr, "realloc failed for courses.\n");
					exit(1);
				}
				courses = tmp;
				Course *c = createCourse(courseTitle);
				addStudentToCourse(student, c);
				courses[nCoursePtrs - 1] = c;
			} else {
				// Course exists - add student to correct course
				addStudentToCourse(student, courses[courseIndex]);		
			}
			free(courseTitle);
		}
		free(student);
	}
	free(lineBuf);
	fclose(fp);
	writeFiles(courses, nCoursePtrs, "output/course");

	// Delete courses array
	for (size_t i = 0; i < nCoursePtrs; i++) {
		deleteCourse(courses[i]);
	}
	free(courses);

	return 0;
}

/**
 * Function to determine if the `courses` array contains a pointer to a Course
 * having the same title as `courseTitle`.
 *
 * Returns 0 if there are no courses - this index can be used to create a new array element in position 0.
 * Returns the array index if the course is found - used to access the correct pointer to amend the course.
 * Returns -1 if course not found - a new course should be created at the end of the courses array.
 * */
int courseExists(const char *courseTitle, Course **courses, size_t n)
{
	if (n == 0) {
		// There are no courses yet, so courseTitle should be first.
		return 0;
	}
	for (int i = 0; i < (int)n; i++) {
		if (!strcmp(courses[i]->title, courseTitle)) {
			// course exists in the array at index i.
			return i;
		}
	}
	// Course does not exist - add to end of courses array.
	return -1;
}

/**
 * Utility print function
 * */
void printStringArray(char **strings, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		printf(i == 0 ? "%s" : ", %s", strings[i]);
	}
	puts("\n");
}

void writeFiles(Course **courses, size_t n, const char* basename)
{
	for (size_t i = 0; i < n; i++) {
		// Enough space for a hypen separator, `.txt` suffix and terminating '\0'. 
		size_t nameLen = strlen(basename) + strlen(courses[i]->title) + 6;
		char *filename = malloc(nameLen);
		snprintf(filename, nameLen, "%s-%s.txt", basename, courses[i]->title);
		replaceSpaces(filename, '-');
		FILE *fp = fopen(filename, "a+");
		fputs(courses[i]->title, fp);
		fputc('\n', fp);
		fputs("-----\n", fp);
		for (size_t j = 0; j < courses[i]->nStudents; j++) {
			fputs(courses[i]->students[j], fp);
			fputc('\n', fp);
		}
		fclose(fp);
		free(filename);
	}
}

