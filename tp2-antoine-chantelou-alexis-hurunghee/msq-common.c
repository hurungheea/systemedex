#include "msq-common.h"

void displayError(void* t, ...)
{
  char* toPrint = NULL;
  va_list args;
  printf("errno --> %d\n",errno);
  switch(errno)
  {
    case 2:
      toPrint = "%s:%s:%d: Unable to create the System V IPC key from the \"%s\" pathname and the \"%d\" project identifier.\n";
      break;

    case 17:
      toPrint = "%s:%s:%d: Unable to get the identifier of the System V shared memory segment from the \"0x%x\" key.\n";
      break;

    case 140:
      toPrint = "%s:%s:%d: Unable to copy the message because the target message is not empty.\n";
      break;

    case 150:
      toPrint = "%s:%s:%d: Unable to copy the message.\n";
      break;

    case 510:
      toPrint = "%s:%s:%d: Unable to set the \"%s\" message text because its \"%d\" is greater than \"%d\".\n";
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

    default:
      fprintf(stderr,"Unknown error : %d\n",errno);
      break;
  }
  va_start(args, t);
  vfprintf(stderr, toPrint,args);
  va_end(args);
  exit(EXIT_FAILURE);
}

void waitingForEnter()
{
  char k;
  do
  {
    printf("Press the Enter key to continue... ");
    k = getchar();
  }while(k != 0x0A);
}

void afficheHelp(char **argv, int client)
{
  printf("Usage: %s [OPTION]...\n", argv[0]);
  if(client)
    printf("Send a message to a server through a message queue.\n \n");
  else
    printf("Receive messages from clients through shared memory.\n \n");
  printf("Options:\n");
  printf("\t -h, --help\n\t\tdisplay this help and exit\n");
  printf("\t -i, --key-proj-id=PROJ_ID\n\t\tset the key project identifier to PROJ_ID (the default value is \"1\")\n");
  printf("\t -p, --key-pathname=PATHNAME\n\t\tset the key pathname to PATHNAME (the default value is \"file.ftok\")\n");
  printf("\t -s, --seconds=SECONDS\n\t\tset the seconds between each try (the default value is \"1\", a value less than or equal to 0 enables the interactive mode where the input stream is read)\n");
  if(client)
    printf("\t -t, --times=TIMES\n\t\tset the number of times this program tries to send a message (the default value is \"1\",a negative value means repeat for ever)\n");
  else
    printf("\t -t, --times=TIMES\n\t\tset the number of times this program tries to receive a message (the default value is \"-1\",a negative value means repeat for ever)\n");
  printf("\t -v, --version\n\t\t output version information and exit\n");
  if(client)
  {
    printf("\t -x, --message-text=TEXT\n\t\tset the message text to TEXT (the default value is \"This is the default message text\")\n");
    printf("\t -y, --message-type=TYPE\n\t\tset the message type to TYPE (the default value is \"1\")\n");
  }
  printf("\nReport bugs to Antoine Chantelou <achantelou@etud.univ-pau.fr> and Alexis Hurunghee <ahurunchee@etud.univ-pau.fr>.\n");
  exit(0);
}

void afficheVersion(char **argv)
{
  printf("msq-server 1.0.0\n\n");
  printf("Copyright (C) 2019 Antoine Chantelou and Alexis Hurunghee.\n\n");
  printf("Written by Antoine Chantelou <achantelou@etud.univ-pau.fr> and Alexis Hurunghee <ahurunchee@etud.univ-pau.fr>.\n");
  exit(0);
}

void argumentFromServer(int argc,char **argv,char* optOptions, int* option_index, int* id, char* pathname,int *sec, int* times)
{
  int opt = 0;
  static struct option long_options[] =
  {
    {"help",  0,  NULL, 'h'},
    {"key-proj-id",  1,  NULL, 'i'},
    {"key-pathname",  1,  NULL, 'p'},
    {"seconds",  1,  NULL, 's'},
    {"times",  1,  NULL, 't'},
    {"version",  1,  NULL, 'v'},
    {0,  0,  0,  0}
  };

  do
  {
    opterr = 0;
    opt = getopt_long(argc, argv, optOptions, long_options, option_index);
    switch(opt)
    {
      case 'h':
        afficheHelp(argv, SERVER);
        break;

      case 'v':
        afficheVersion(argv);
        break;

      case 'i':
        *id  = strtol(optarg, NULL, 10);
        break;

      case 'p':
        pathname = optarg;
        break;

      case 's':
        *sec = strtol(optarg, NULL, 10);
        break;

      case 't':
        *times = strtol(optarg, NULL, 10);
        break;

      case '?':
        errno = 522;
        displayError(NULL, argv[0], __FILE__, __LINE__,argv[1][1]);
        break;

      case ':':
        errno = 523;
        displayError(NULL, argv[0], __FILE__, __LINE__,argv[1][1]);
        break;
    }
  } while(opt != -1);
}
