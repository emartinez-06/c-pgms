/*
 * file: easterEggs.c
 * author: erick martinez
 * course: CSI 3336
 * assignment: project 7
 * due date: 11/08/2026
 *
 * date modified: 11/05/2026
 *  - Added binary color counts, child results, output spacing, and comments.
 *
 * date modified: 11/4/2026
 *  - Added directory searches and basic color handling.
 *
 * Five child processes count colors in matching files and report their totals.
 */
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* exit MACROS */
#include <string.h>    /* strcmp() */
#include <sys/types.h> /* ino_t */
#include <sys/wait.h>  /* waitpid */
#include <unistd.h>    /* getcwd(), fork() */

typedef enum color { red, green, blue, yellow, orange } Color;

/**
 * countColors
 *
 * Count one color in a binary file.
 *
 * Parameters:
 *   path: full file path.
 *   color: color to count.
 *
 * Output:
 *   return: count, or -1 on error.
 *   reference parameters: none.
 *   stream: errors to stderr.
 */
int countColors(const char *path, Color color) {
  int occurences;
  occurences = 0;
  FILE *fp;
  int value;

  if ((fp = fopen(path, "rb")) == NULL) {
    perror("fopen");
    return -1;
  }

  while (fread(&value, sizeof value, 1, fp) == 1) {
    if (value == (int)color) {
      occurences++;
    }
  }
  if (ferror(fp)) {
    perror("fread");
    fclose(fp);
    return -1;
  }
  fclose(fp);
  return occurences;
}
/**
 * create_file_path
 *
 * Join a folder path and a file name.
 *
 * Parameters:
 *   charPath: buffer for the full path.
 *   size: buffer size in bytes.
 *   currpath: folder path.
 *   filename: file or folder name.
 *
 * Output:
 *   return: 0 on success, or -1 on error.
 *   reference parameters: charPath holds the full path on success.
 *   stream: errors to stderr.
 */
int create_file_path(char *charPath, size_t size, const char *currpath,
                     const char *filename) {
  int n;
  if ((n = snprintf(charPath, size, "%s/%s", currpath, filename)) < 0 ||
      (size_t)n >= size) {

    fprintf(stderr, "could not build dirpath\n");
    return -1;
  }
  return 0;
}

/**
 * sprawl
 *
 * Search folders and count one color in matching files.
 *
 * Parameters:
 *   path: starting folder.
 *   filename: file name to find.
 *   color: color to count.
 *
 * Output:
 *   return: total count, or -1 on error.
 *   reference parameters: none.
 *   stream: errors to stderr.
 */
int sprawl(const char *path, const char *filename, Color color) {
  DIR *dp;
  struct dirent *entry;
  int occurences;
  occurences = 0;

  if ((dp = opendir(path)) == NULL) {
    fprintf(stderr, "cannot opendir: %s\n", path);
    return -1;
  }

  while ((entry = readdir(dp)) != NULL) {

    if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0) {

      if (entry->d_type == DT_REG && strcmp(entry->d_name, filename) == 0) {
        int subtotal;
        subtotal = 0;
        char filepath[512];
        if ((create_file_path(filepath, 512, path, entry->d_name)) == -1) {
          fprintf(stderr, "create_file_path() error on %s", path);
          return -1;
        }

        if ((subtotal = countColors(filepath, color)) == -1) {
          fprintf(stderr, "counting error on file %s and color %d", filepath,
                  (int)color);
          closedir(dp);
          return -1;
        }
        occurences += subtotal;
      } else if (entry->d_type == DT_DIR) {
        char dirpath[512];
        int subtotal;
        subtotal = 0;
        if ((create_file_path(dirpath, 512, path, entry->d_name)) == -1) {
          fprintf(stderr, "create_file_path() error on %s", path);
          return -1;
        }
        if ((subtotal = sprawl(dirpath, filename, color)) == -1) {
          closedir(dp);
          fprintf(stderr, "recurse error\n");
          return -1;
        }
        occurences += subtotal;
      } else if (entry->d_type == DT_UNKNOWN) {
        fprintf(stderr, "error unknown file type(%u) continuing...\n",
                (unsigned int)entry->d_type);
      }
    }
  }
  closedir(dp);
  return occurences;
}

/**
 * proccessColor
 *
 * Run the file search for the assigned color.
 *
 * Parameters:
 *   color: assigned color.
 *   path: starting folder.
 *   filename: file name to find.
 *
 * Output:
 *   return: total count, or -1 on error.
 *   reference parameters: none.
 *   stream: errors to stderr.
 */
int proccessColor(Color color, const char *path, const char *filename) {
  int occurences;

  switch (color) {
  case red:
    if ((occurences = sprawl(path, filename, red)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case green:
    if ((occurences = sprawl(path, filename, green)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case blue:
    if ((occurences = sprawl(path, filename, blue)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case yellow:
    if ((occurences = sprawl(path, filename, yellow)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case orange:
    if ((occurences = sprawl(path, filename, orange)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  default:
    fprintf(stderr, "error: unknown color %d\n", (int)color);
    return -1;
  }

  return occurences;
}

/**
 * main
 *
 * Start five children, collect their counts, and print results.
 *
 * Parameters:
 *   argc: number of command-line arguments.
 *   argv: program name and target file name.
 *
 * Output:
 *   return: parent exit status or child color count.
 *   reference parameters: none.
 *   stream: results to stdout; errors to stderr.
 */
int main(int argc, char *argv[]) {
  char cwd[256];
  char *filename;
  char *colors[5] = {"red:", "green:", "blue:", "yellow:", "orange:"};
  int counts[5];

  int i, num_children, j;
  num_children = 5;
  pid_t w;
  pid_t c_pids[num_children];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  filename = argv[1];

  if (getcwd(cwd, 256) == NULL) {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < num_children; i++) {
    Color color;
    color = i;
    c_pids[i] = fork();
    int ret;

    switch (c_pids[i]) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    case 0:
      /* child */
      if ((ret = proccessColor(color, cwd, filename)) == -1) {
        fprintf(stderr, "error processing color %d\n", (int)color);
        exit(-1);
      }
      return ret;
      break;
    default:
      /* parent */
      break;
    }
  }

  for (j = 0; j < num_children; j++) {
    int status, count;
    w = waitpid(c_pids[j], &status, 0);
    if (w == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
      counts[j] = WEXITSTATUS(status);
    }
  }

  for (j = 0; j < num_children; j++) {
    printf("%-7s %5d\n", colors[j], (int)counts[j]);
  }

  exit(EXIT_SUCCESS);
}
