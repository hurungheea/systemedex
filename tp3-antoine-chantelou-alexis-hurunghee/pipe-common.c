#include "pipe-common.h"

void waitingForEnter(char rw)
{
  char *r_or_w = (rw == 'r')?"read":"write";
  char k;
  do
  {
    printf("Press the Enter key to %s... \n",r_or_w);
    k = getchar();
  }while(k != 0x0A);
}

void argument_opt(int argc, char **argv, char* opt_options, int* option_index, int* seconds_receiving, pipe_message_t* message_tmp, int* times_sending, int* seconds_sending, int* times_receiving)
{
    int opt = 0;
    char** end_ptr = '\0';
    static struct option long_options[] =
    {
      {"seconds-for-receiving=SECONDS",  1,  NULL, 'r'},
      {"seconds-for-sending=SECONDS",  1,  NULL, 's'},
      {"times-for-receiving=TIMES",  1,  NULL, 't'},
      {"times-for-sending=TIMES",  1,  NULL, 'u'},
      {"message-text=TEXT",  1,  NULL, 'x'},
      {"version",  0,  NULL, 'v'},
      {"help",  0,  NULL, 'h'},
      {0,  0,  0,  0}
    };

    do
    {
      opterr = 0;
      opt = getopt_long(argc, argv, opt_options, long_options, option_index);
      switch(opt)
      {
        case 'h':
          display_help(argv);
          break;

        case 'r':
          *seconds_receiving = strtol(optarg,end_ptr,10);
          break;

        case 's':
          *seconds_sending = strtol(optarg,end_ptr,10);
          break;

        case 't':
          *times_receiving = strtol(optarg,end_ptr,10);
          break;

        case 'u':
          *times_sending = strtol(optarg,end_ptr,10);
          break;

        case 'v':
          display_version(argv);
          break;

        case 'x':
          if(pipe_message_set_text(message_tmp,optarg) == -1)
          {
            errno = 150;
            display_error(NULL,argv[0],__FILE__,__LINE__,optarg);
            exit(EXIT_FAILURE);
          }
          break;

        case '?':
          errno = 522;
          display_error(NULL, argv[0], __FILE__, __LINE__,argv[1][1]);
          exit(EXIT_FAILURE);
          break;

        case ':':
          errno = 523;
          display_error(NULL, argv[0], __FILE__, __LINE__,argv[1][1]);
          exit(EXIT_FAILURE);
          break;
      }
    } while(opt != -1);
}

void display_help(char **argv)
{
  printf("Usage: %s [OPTION]...\n", argv[0]);
  printf("Send and receive messages through a pipe.\n \n");
  printf("Options:\n");
  printf("\t -h, --help\n\t\t display this help and exit\n");
  printf("\t -r, --seconds-for-receiving=SECONDS\n\t\t set the seconds between each try to receive a message (the default value is \"1\", a value less than or equal to 0 enables the interactive mode where the input stream is read)\n");
  printf("\t -s, --seconds-for-sending=SECONDS\n\t\t set the seconds between each try to send a message (the default value is \"1\", a value less than or equal to 0 enables the interactive mode where the input stream is read)\n");
  printf("\t -t, --times-for-receiving=TIMES\n\t\t set the number of times this program tries to receive a message (the default value is \"-1\", a negative value means repeat for ever)\n");
  printf("\t -u, --times-for-sending=TIMES\n\t\t set the number of times this program tries to send a message (the default value is \"1\", a negative value means repeat for ever)\n");
  printf("\t -v, --version\n\t\t  output version information and exit\n");
  printf("\t -x, --messages-text=TEXT\n\t\t set the message text to TEXT (the default value is \"This is the default message text\")\n");

  printf("\nReport bugs to Antoine Chantelou <achantelou@etud.univ-pau.fr> and Alexis Hurunghee <ahurunchee@etud.univ-pau.fr>.\n");
  exit(EXIT_SUCCESS);
}

void display_version(char **argv)
{
  printf("pipe-main 1.0.0\n\n");
  printf("Copyright (C) 2019 Antoine Chantelou and Alexis Hurunghee.\n\n");
  printf("Written by Antoine Chantelou <achantelou@etud.univ-pau.fr> and Alexis Hurunghee <ahurunchee@etud.univ-pau.fr>.\n");
  exit(EXIT_SUCCESS);
}

void display_error(void* t, ...)
{
  char* toPrint = NULL;
  va_list args;
  switch(errno)
  {
    case 140:
      toPrint = "%s:%s:%d: Unable to copy the message because the target message is not empty.\n";
      break;

    case 150:
      toPrint = "%s:%s:%d: Unable to set \"%s\" message text.\n";
      break;

    case 510:
      toPrint = "%s:%s:%d: Unable to set the \"%s\" message text because its \"%ld\" size is greater than \"%d\".\n";
      break;

    case 520:
      toPrint = "%s:%s:%d: Unable to set the \"%d\" message type because its value is less than or equal to \"0\".\n";
      break;

    case 521:
      toPrint = "%s:%s:%d: Unable to set the \"%d\" message type.\n";
      break;

    case 522:
      toPrint = "%s:%s:%d: Unknown option \"-%c\".\n";
      break;

    case 523:
      toPrint = "%s:%s:%d: Argument is missing in the \"-%c\" option.\n";
      break;

    case 524:
      toPrint = "%s:%s:%d: Can not write into the pipe. Error %d \n";
      break;

    default:
      fprintf(stderr,"Unknown error : %d\n",errno);
      break;
  }
  va_start(args, t);
  vfprintf(stderr, toPrint,args);
  va_end(args);
}
