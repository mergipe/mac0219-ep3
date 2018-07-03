#include "dclock.h"
#include "cpu_montecarlo.h"

#include <cstdio>
#include <cstdint>
#include <cstdlib>

#include <argp.h>

// Número de argumentos na linha de comando.
static const int arg_num = 3;

static char doc[] =
    "Esse programa...";

static char args_doc[] = "N k m";

static struct argp_option options[] = 
{
    {0,   0, 0, 0,               "ARGS:"},
    {"N", 0, 0, OPTION_DOC |
                OPTION_NO_USAGE, "número de pontos amostrados aleatoriamente"},
    {"k", 0, 0, OPTION_DOC |
                OPTION_NO_USAGE, "constante inteira"},
    {"M", 0, 0, OPTION_DOC |
                OPTION_NO_USAGE, "constante inteira"},
    {0}
};

struct arguments
{
    char *args[3];
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = (struct arguments *) state->input;

    switch(key)
    {
        case ARGP_KEY_ARG:
        {
            if (state->arg_num >= arg_num)
                argp_state_help(state, stderr, ARGP_HELP_STD_HELP);

            arguments->args[state->arg_num] = arg;

            break;
        }

        case ARGP_KEY_END:
        {
            if (state->arg_num < arg_num)
                argp_state_help(state, stderr, ARGP_HELP_STD_HELP);

            break;
        }

        default:
        {
            return ARGP_ERR_UNKNOWN;
        }
    }

    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

//
static void run_tests(uint64_t N, int k, int M)
{
    double t1, t2, t3, t4,
           e1, e2, e3, e4, e5, e6, e7, e8;

    t1 = dclock();
    t1 = dclock() - t1;
    printf("\nTempo com balanceamento de carga em segundos: %f"
           "\nErro no calculo com a soma: %f"
           "\nErro no calculo com a subtracao: %f\n",
           t1, e1, e2);

    t2 = dclock();
    t2 = dclock() - t2;
    printf("\nTempo na GPU com uma thread na CPU em segundos: %f"
           "\nErro no calculo com a soma: %f"
           "\nErro no calculo com a subtracao: %f\n",
           t2, e3, e4);

    t3 = dclock();
    t3 = dclock() - t3;
    printf("\nTempo na CPU com T threads em segundos: %f"
           "\nErro no calculo com a soma: %f"
           "\nErro no calculo com a subtracao: %f\n",
           t3, e5, e6);

    t4 = dclock();
    sequential_montecarlo(N, k, M, &e7, &e8);
    t4 = dclock() - t4;
    printf("\nTempo sequencial em segundos: %f"
           "\nErro no calculo com a soma: %f"
           "\nErro no calculo com a subtracao: %f\n\n",
           t4, e7, e8);
}

int main(int argc, char **argv)
{
    struct arguments args;
    uint64_t N;
    int k, M;
    char *end_N, *end_k, *end_M;

    argp_parse(&argp, argc, argv, 0, 0, &args);
    N = strtol(args.args[0], &end_N, 10);
    k = strtol(args.args[1], &end_k, 10);
    M = strtol(args.args[2], &end_M, 10);

    if (*end_N != '\0' || *end_k != '\0' || *end_M != '\0')
        argp_help(&argp, stderr, ARGP_HELP_STD_HELP, argv[0]);

    run_tests(N, k, M);

    return EXIT_SUCCESS;
}
