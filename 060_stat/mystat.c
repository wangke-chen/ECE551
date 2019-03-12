#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

/*Get the file type based on the st_mode field*/
void getType(struct stat sb, char ** type) {
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      (*type) = "block special file";
      break;
    case S_IFCHR:
      (*type) = "character special file";
      break;
    case S_IFDIR:
      (*type) = "directory";
      break;
    case S_IFIFO:
      (*type) = "fifo";
      break;
    case S_IFLNK:
      (*type) = "symbolic link";
      break;
    case S_IFREG:
      (*type) = "regular file";
      break;
    case S_IFSOCK:
      (*type) = "socket";
      break;
    default:
      (*type) = "unknown?";
      break;
  }
}

/*Get the human readable description of the permissions based on the given rules*/
void getAccessDiscrtption(struct stat sb, char * access) {
  /*The first character depends on the file type*/
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      access[0] = 'b';
      break;
    case S_IFCHR:
      access[0] = 'c';
      break;
    case S_IFDIR:
      access[0] = 'd';
      break;
    case S_IFIFO:
      access[0] = 'p';
      break;
    case S_IFLNK:
      access[0] = 'l';
      break;
    case S_IFREG:
      access[0] = '-';
      break;
    case S_IFSOCK:
      access[0] = 's';
      break;
    default:
      access[0] = 'u';
      break;
  }

  /*The rest nine characters come from the given rules*/
  access[1] = (sb.st_mode & S_IRUSR) ? 'r' : '-';
  access[2] = (sb.st_mode & S_IWUSR) ? 'w' : '-';
  access[3] = (sb.st_mode & S_IXUSR) ? 'x' : '-';
  access[4] = (sb.st_mode & S_IRGRP) ? 'r' : '-';
  access[5] = (sb.st_mode & S_IWGRP) ? 'w' : '-';
  access[6] = (sb.st_mode & S_IXGRP) ? 'x' : '-';
  access[7] = (sb.st_mode & S_IROTH) ? 'r' : '-';
  access[8] = (sb.st_mode & S_IWOTH) ? 'w' : '-';
  access[9] = (sb.st_mode & S_IXOTH) ? 'x' : '-';

  /*Add '\0' at the end of the array to make it a string*/
  access[10] = '\0';
}

/*Call the function to print the first three lines*/
void printFirstThree(struct stat sb, char * filename) {
  char * type = NULL;

  /*Call getType to get the file type*/
  getType(sb, &type);

  /*Check if the file is a symbolic link. If so, get the target of the link, and print. If not, directly print the filename*/
  if (S_ISLNK(sb.st_mode)) {
    char linktarget[256];
    ssize_t len = readlink(filename, linktarget, 256);
    if (len < 0) {
      perror("Can not read the link.");
      exit(EXIT_FAILURE);
    }
    linktarget[len] = '\0';
    printf("  File: %s -> %s\n", filename, linktarget);
  }
  else {
    printf("  File: %s\n", filename);
  }

  /*Print the second line*/
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         sb.st_size,
         sb.st_blocks,
         sb.st_blksize,
         type);

  /*Check if the file is a device. If so, get the device type and print. If not, print without device type*/
  if ((S_ISBLK(sb.st_mode)) || (S_ISCHR(sb.st_mode))) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink);
  }
}

/*Print the fourth line*/
void printFourth(struct stat sb) {
  char access[11] = "";

  /*Get the human readable description of the permissions*/
  getAccessDiscrtption(sb, access);

  /*Look up the user's name from their uid*/
  struct passwd * User = getpwuid(sb.st_uid);

  /*Look up the group's from their gid*/
  struct group * Group = getgrgid(sb.st_gid);

  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         sb.st_mode & ~S_IFMT,
         access,
         sb.st_uid,
         User->pw_name,
         sb.st_gid,
         Group->gr_name);
}

/*Print the last four lines*/
void printLastFour(struct stat sb) {
  /*Get the access time using function time2str, print and free. Modify time and change time are the same way.*/
  char * timeAccess = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  printf("Access: %s\n", timeAccess);
  free(timeAccess);

  char * timeModify = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  printf("Modify: %s\n", timeModify);
  free(timeModify);

  char * timeChange = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  printf("Change: %s\n", timeChange);
  free(timeChange);

  printf(" Birth: -\n");
}

int main(int argc, char ** argv) {
  struct stat sb;

  /*Check if there is at least one input file*/
  if (argc == 1) {
    perror("At least one input file.\n");
    exit(EXIT_FAILURE);
  }

  /*Print the stat of each file from the first one to the last one*/
  for (int i = 1; i < argc; i++) {
    if (lstat(argv[i], &sb) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }

    /*Print the eight lines of the stat of the file*/
    printFirstThree(sb, argv[i]);
    printFourth(sb);
    printLastFour(sb);
  }
  return (EXIT_SUCCESS);
}
